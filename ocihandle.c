#include <stddef.h>
#include <stdlib.h>
#include "ocidump.h"
#include "ocihandle.h"

/* hash table entry */
typedef struct ht_entry {
    struct ht_entry *next;
    const void *addr;
    struct ht_entry *parent;
    struct ht_entry *children;
    struct ht_entry *prev_sibling;
    struct ht_entry *next_sibling;
    ocihandle_t handle;
} ht_entry_t;

static ht_entry_t **hash_table;
static volatile size_t hash_table_size;
static volatile size_t num_hash_entries;

#define MAX_HTYPE 100
static unsigned int issued_ids[MAX_HTYPE];

#ifdef _WIN32
static union {
    CRITICAL_SECTION cs;
    struct {
        PVOID Ptr;
    } srwlock;
} rwlock;

typedef VOID (WINAPI *lock_func_t)(void *);

static lock_func_t rwlock_wrlock;
static lock_func_t rwlock_wrunlock;
static lock_func_t rwlock_rdlock;
static lock_func_t rwlock_rdunlock;

void ocihandle_init(void)
{
    HMODULE hMod = GetModuleHandle("kernel32.dll");
    lock_func_t init = (lock_func_t)GetProcAddress(hMod, "InitializeSRWLock");
    rwlock_wrlock = (lock_func_t)GetProcAddress(hMod, "AcquireSRWLockExclusive");
    rwlock_wrunlock = (lock_func_t)GetProcAddress(hMod, "ReleaseSRWLockExclusive");
    rwlock_rdlock = (lock_func_t)GetProcAddress(hMod, "AcquireSRWLockShared");
    rwlock_rdunlock = (lock_func_t)GetProcAddress(hMod, "ReleaseSRWLockShared");
    if (init != NULL && rwlock_wrlock != NULL && rwlock_wrunlock != NULL && rwlock_rdlock != NULL && rwlock_rdunlock == NULL) {
        /* Use Slim Reader/Writer Lock (Windows Vista or upper) */
        init(&rwlock);
    } else {
        /* Use CriticalSection (Windows XP) */
        rwlock_wrlock = (lock_func_t)EnterCriticalSection;
        rwlock_wrunlock = (lock_func_t)LeaveCriticalSection;
        rwlock_rdlock = (lock_func_t)EnterCriticalSection;
        rwlock_rdunlock = (lock_func_t)LeaveCriticalSection;
        InitializeCriticalSectionAndSpinCount(&rwlock.cs, 2000);
    }
}
#else
#include <pthread.h>

static pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

#define rwlock_wrlock pthread_rwlock_wrlock
#define rwlock_rdlock pthread_rwlock_rdlock
#define rwlock_wrunlock pthread_rwlock_unlock
#define rwlock_rdunlock pthread_rwlock_unlock
#endif

static int rehash()
{
    int new_hash_table_size = hash_table_size + 199;
    ht_entry_t **new_hash_table;
    size_t idx;

    new_hash_table = calloc(new_hash_table_size, sizeof(ht_entry_t *));
    if (new_hash_table == NULL) {
        return -1;
    }
    for (idx = 0; idx < hash_table_size; idx++) {
        ht_entry_t *entry = hash_table[idx];
        while (entry != NULL) {
            ht_entry_t *next = entry->next;
            size_t new_idx = ((size_t)entry->addr) % new_hash_table_size;

            entry->next = new_hash_table[new_idx];
            new_hash_table[new_idx] = entry;
            entry = next;
        }
    }
    free(hash_table);
    hash_table = new_hash_table;
    hash_table_size = new_hash_table_size;
    return 0;
}

static ht_entry_t *find_entry(const void *addr)
{
    ht_entry_t *entry;

    if (hash_table_size == 0) {
        rehash();
    }
    entry = hash_table[((size_t)addr) % hash_table_size];
    while (entry != NULL && entry->addr != addr) {
        entry = entry->next;
    }
    return entry;
}

static void delete_entry(ht_entry_t *entry)
{
    ht_entry_t **entry_p;

    /* unlink from hash_table */
    entry_p = &hash_table[((size_t)entry->addr) % hash_table_size];
    while (*entry_p != NULL) {
        if (*entry_p == entry) {
            *entry_p = entry->next;
            break;
        }
        entry_p = &(*entry_p)->next;
    }

    /* unlink from parent */
    if (entry->parent != NULL) {
        if (entry->parent->children == entry) {
            if (entry->next_sibling == entry) {
                entry->parent->children = NULL;
            } else {
              entry->parent->children = entry->next_sibling;
            }
        }
    }
    /* unlink from siblings */
    entry->next_sibling->prev_sibling = entry->prev_sibling;
    entry->prev_sibling->next_sibling = entry->next_sibling;

    /* free children */
    while (entry->children) {
        delete_entry(entry->children);
    }
    free(entry);
}

const ocihandle_t *ocihandle_add(const void *addr, ub4 type, const void *parent)
{
    ht_entry_t *entry;
    ht_entry_t *parent_entry;
    size_t idx;

    if (!ocidump_trace_handle) {
        return NULL;
    }
    rwlock_wrlock(&rwlock);
    entry = find_entry(addr);
    if (entry != NULL) {
        if (entry->handle.type == type && entry->parent == parent) {
            rwlock_wrunlock(&rwlock);
            return &entry->handle;
        }
        delete_entry(entry);
    }
    entry = (ht_entry_t *)malloc(sizeof(ht_entry_t));
    if (entry == NULL) {
        return NULL;
    }

    entry->next = NULL;
    entry->addr = addr;
    entry->parent = NULL;
    entry->children = NULL;
    entry->next_sibling = entry;
    entry->prev_sibling = entry;
    entry->handle.type = type;
    entry->handle.id = 0;

    if (type < MAX_HTYPE) {
        entry->handle.id = ++issued_ids[type];
    }
    if (hash_table_size == num_hash_entries) {
        rehash();
    }
    idx = ((size_t)addr) % hash_table_size;
    entry->next = hash_table[idx];
    hash_table[idx] = entry;
    parent_entry = find_entry(parent);
    if (parent_entry != NULL) {
        entry->parent = parent_entry;
        if (parent_entry->children != NULL) {
            entry->next_sibling = parent_entry->children->next_sibling;
            entry->prev_sibling = parent_entry->children;
            parent_entry->children->next_sibling->prev_sibling = entry;
            parent_entry->children->next_sibling = entry;
        }
        parent_entry->children = entry;
    }
    rwlock_wrunlock(&rwlock);
    return &entry->handle;
}

const ocihandle_t *ocihandle_find(const void *addr)
{
    ht_entry_t *entry;

    if (!ocidump_trace_handle) {
        return NULL;
    }
    rwlock_rdlock(&rwlock);
    entry = find_entry(addr);
    rwlock_rdunlock(&rwlock);
    return entry ? &entry->handle : NULL;
}

int ocihandle_del(const ocihandle_t *hndl)
{
    ht_entry_t *entry = (ht_entry_t *)((size_t)hndl - offsetof(struct ht_entry, handle));

    rwlock_wrlock(&rwlock);
    delete_entry(entry);
    rwlock_wrunlock(&rwlock);
    return entry ? 0 : -1;
}

void ocihandle_print(const void *addr, ub4 type, ub4 type2, ub4 type3, const ocihandle_t *hndl)
{
    if (hndl != NULL) {
        ocidump_htype_short(hndl->type);
        putc_unlocked('_', ocidump_logfp);
        ocidump_ub4(hndl->id);
        putc_unlocked('(', ocidump_logfp);
        ocidump_pointer(addr);
        putc_unlocked(')', ocidump_logfp);
        if (type != hndl->type && type2 != hndl->type && type3 != hndl->type) {
            fputs("<<< This should be ", ocidump_logfp);
            ocidump_htype_short(type);
            if (type2 != 0 && type3 == 0) {
                fputs(" or ", ocidump_logfp);
                ocidump_htype_short(type2);
            } else {
                fputs(", ", ocidump_logfp);
                ocidump_htype_short(type2);
                fputs(" or ", ocidump_logfp);
                ocidump_htype_short(type3);
            }
            fputs(". >>>", ocidump_logfp);
        }
    } else {
        ocidump_pointer(addr);
    }
}

static void print_ht_entry(ht_entry_t *entry)
{
    ocihandle_print(entry->addr, entry->handle.type, 0, 0, &entry->handle);
}

void ocidump_dump_hash_table(void)
{
    int i;

    for (i = 0; i < hash_table_size; i++) {
        ht_entry_t *entry;

        for (entry = hash_table[i]; entry != NULL; entry = entry->next) {
            print_ht_entry(entry);
            if (entry->parent) {
                ht_entry_t *parent = entry->parent;

                fputs(" parent = ", ocidump_logfp);
                print_ht_entry(parent);
            }
            if (entry->children) {
                ht_entry_t *child;

                fputs(" children = [", ocidump_logfp);
                print_ht_entry(entry->children);
                for (child = entry->children->next_sibling; child != entry->children; child = child->next_sibling) {
                    fputs(", ", ocidump_logfp);
                    print_ht_entry(child);
                }
                fputc(']', ocidump_logfp);
            }
            fputc('\n', ocidump_logfp);
        }
    }
}
