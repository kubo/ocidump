#ifdef _WIN32
#include <windows.h>
#include <dbghelp.h>
#define snprintf _snprintf
#else
#include <pthread.h>
#include <dlfcn.h>
#ifdef __linux
#include <unistd.h>
#include <sys/syscall.h>
#endif
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "ocidump.h"
#include "oranumber_util.h"

#ifndef _WIN32
static pthread_once_t init_once = {PTHREAD_ONCE_INIT};
#endif

#if defined(__linux) || defined(__sun)

typedef void *(dlsym_func_t)(void *map, const char *name);
static dlsym_func_t *dlsym_func;

#ifdef __GNUC__
void init(void) __attribute__((constructor));
#else
#pragma init(init)
#endif

#ifdef __linux
void init(void)
{
    static const char * const dlsym_versions[] = {
        "GLIBC_2.2.5", /* x86_64 */
        "GLIBC_2.0",   /* i386 */
        NULL,
    };
    int idx;

    for (idx = 0; dlsym_versions[idx] != NULL; idx++) {
        dlsym_func = (dlsym_func_t *)dlvsym(RTLD_DEFAULT, "dlsym", dlsym_versions[idx]);
        if (dlsym_func != NULL) {
            break;
        }
    }
}
#endif

#ifdef __sun
extern void *_dlsym(void *, const char *);
void init(void)
{
    dlsym_func = (dlsym_func_t *)_dlsym(RTLD_NEXT, "dlsym");
}
#endif

static int ocidump_hook_cmp(const void *lhs, const void *rhs)
{
    const ocidump_hook_t *l = (const ocidump_hook_t *)lhs;
    const ocidump_hook_t *r = (const ocidump_hook_t *)rhs;
    return strcmp(l->name, r->name);
}

void *dlsym(void *map, const char *name)
{
    ocidump_hook_t key, *found;

    key.name = name;
    found = bsearch(&key, ocidump_hooks, ocidump_hook_cnt, sizeof(ocidump_hook_t), ocidump_hook_cmp);
    if (found) {
        return found->hook_func;
    }
    return dlsym_func(map, name);
}
#define dlsym dlsym_func
#endif

#define OUT_OF_MEMORY_MSG "... out of memory ..."

int ocidump_hide_string = 0;
int ocidump_is_initialized;
FILE *ocidump_logfp;
pthread_key_t ocidump_tls_key;

static unsigned int log_flags = 0;

static void ocidump_do_init(void)
{
    char *val;

    if (ocidump_is_initialized) {
        return;
    }
#if defined(_WIN32)
    ocidump_tls_key = TlsAlloc();
#else
    pthread_key_create(&ocidump_tls_key, NULL);
#endif
    val = getenv("OCIDUMP_HIDE_STRING");
    if (val != NULL) {
        ocidump_hide_string = atoi(val);
    }
    val = getenv("OCIDUMP_LOGFILE");
    if (val != NULL) {
        ocidump_logfp = fopen(val, "a");
    }
    if (ocidump_logfp == NULL) {
        ocidump_logfp = stderr;
    }
    val = getenv("OCIDUMP_CONFIG");
    if (val != NULL) {
        FILE *fp = fopen(val, "r");
        if (fp != NULL) {
            char buf[256];
            int i;

            /* clear all hooks */
            for (i = 0; i < ocidump_hook_cnt; i++) {
                *ocidump_hooks[i].flags = 0;
            }

            while (fgets(buf, sizeof(buf), fp) != NULL) {
                size_t len = strlen(buf);
                while (len > 0 && (buf[len - 1] == '\n' || buf[len - 1] == '\r')) {
                    buf[len - 1] = '\0';
                }
                for (i = 0; i < ocidump_hook_cnt; i++) {
                    if (strcmp(ocidump_hooks[i].name, buf) == 0) {
                        *ocidump_hooks[i].flags = OCIDUMP_HOOK_EXIT;
                        break;
                    }
                }
            }
            fclose(fp);
        }
    }
#ifdef _WIN32
    ocidump_init_win32();
#else
    {
        int i;
        for (i = 0; i < ocidump_hook_cnt; i++) {
            *ocidump_hooks[i].orig_func = dlsym(RTLD_NEXT, ocidump_hooks[i].name);
            ocidump_log(OCIDUMP_LOG_HOOK, "# dlsym(RTLD_NEXT, \"%s\") => %p\n",
                        ocidump_hooks[i].name,
                        *ocidump_hooks[i].orig_func);
        }
    }
#endif
}

void ocidump_init(void)
{
#ifdef _WIN32
    /* ocidump_init is called by DllMain().
     * It will be assured that only one thread call this.
     */
    ocidump_do_init();
#else
    pthread_once(&init_once, ocidump_do_init);
#endif
    ocidump_is_initialized = 1;
}

void ocidump_log_start(const char *funcname)
{
#ifdef _WIN32
    _lock_file(ocidump_logfp);
    fprintf(ocidump_logfp, "%5u: %s", GetCurrentThreadId(), funcname);
#else /* _WIN32 */
    flockfile(ocidump_logfp);
#if defined(__linux)
    fprintf(ocidump_logfp, "%5ld: %s", syscall(SYS_gettid), funcname);
#elif defined(__sun)
    fprintf(ocidump_logfp, "%5u: %s", pthread_self(), funcname);
#else
    fprintf(ocidump_logfp, "%p: %s", (void*)pthread_self(), funcname);
#endif
#endif /* _WIN32 */
}

void ocidump_log_end(void)
{
#ifdef _WIN32
    _unlock_file(ocidump_logfp);
#else
    funlockfile(ocidump_logfp);
#endif
}

void ocidump_log(unsigned int filter, const char *fmt, ...)
{
    va_list ap;

    if (ocidump_logfp == NULL) {
        return;
    }
    if (filter != 0 && !(log_flags & filter)) {
        return;
    }

    va_start(ap, fmt);
    vfprintf(ocidump_logfp, fmt, ap);
    va_end(ap);
}

void ocidump_puts(const char *str)
{
    char c;
    while ((c = *(str++)) != '\0') {
        putc_unlocked(c, ocidump_logfp);
    }
}

#define NUM2HEX(c)  (((c) < 10) ? ((c) + '0') : ((c) - 10 + 'a'))

void ocidump_pointer(const void *ptr)
{
    if (ptr == NULL) {
        ocidump_puts("(nil)");
    } else {
        size_t n = (size_t)ptr;
        int nshift = sizeof(void*) * 8;

        putc_unlocked('0', ocidump_logfp);
        putc_unlocked('x', ocidump_logfp);
        while (nshift != 0) {
            if ((n >> (nshift - 4)) != 0) {
                break;
            }
            nshift -= 4;
        }
        while (nshift != 0) {
            int c = (n >> (nshift - 4)) & 0xF;
            c += (c < 10) ? '0' : ('a' - 10);
            putc_unlocked(c, ocidump_logfp);
            nshift -= 4;
        }
    }
}

void ocidump_function_pointer(void *addr)
{
    const char *file_name = NULL;
    const char *symbol_name = NULL;
#ifdef __linux
    Dl_info info;
    if (addr != NULL) {
        if (dladdr(addr, &info) != 0 && info.dli_saddr == addr) {
            file_name = info.dli_fname;
            symbol_name = info.dli_sname;
        }
    }
#endif
#ifdef _WIN32
    char fbuf[MAX_PATH];
    struct {
        SYMBOL_INFO info;
        char buf[MAX_SYM_NAME];
    } symbol;

    if (addr != NULL) {
        HMODULE hModule;

        if (ocidump_use_dbghelp) {
            HANDLE hProcess = GetCurrentProcess();
            DWORD64 displacement;

            symbol.info.SizeOfStruct = sizeof(symbol);
            symbol.info.MaxNameLen = MAX_SYM_NAME;
            EnterCriticalSection(&ocidump_dbghelp_lock);
            if (SymFromAddr(hProcess, (DWORD64)addr, &displacement, &symbol.info) && displacement == 0) {
                symbol_name = symbol.info.Name;
            }
            LeaveCriticalSection(&ocidump_dbghelp_lock);
        }
        if (GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, addr, &hModule)) {
            if (GetModuleFileName(hModule, fbuf, sizeof(fbuf)) > 0) {
                file_name = fbuf;
            }
            FreeLibrary(hModule);
        }
    }
#endif
    if (symbol_name != NULL) {
        ocidump_puts(symbol_name);
    } else {
        ocidump_pointer(addr);
    }
    if (file_name != NULL) {
        ocidump_puts(" in ");
        ocidump_puts(file_name);
    }
}

void ocidump_long(const signed long sl)
{
    char buf[OCIDUMP_SHORT_BUF_SIZE];
    sprintf(buf, "%ld", sl);
    ocidump_puts(buf);
}

void ocidump_ulong(const unsigned long ul)
{
    char buf[OCIDUMP_SHORT_BUF_SIZE];
    sprintf(buf, "%lu", ul);
    ocidump_puts(buf);
}

#if SIZEOF_LONG == 4
void ocidump_ub8(const ub8 ul)
{
    char buf[OCIDUMP_SHORT_BUF_SIZE];
    sprintf(buf, "%" OCIDUMP_UB8_FMT, ul);
    ocidump_puts(buf);
}

void ocidump_sb8(const sb8 sl)
{
    char buf[OCIDUMP_SHORT_BUF_SIZE];
    sprintf(buf, "%" OCIDUMP_SB8_FMT, sl);
    ocidump_puts(buf);
}
#endif

void ocidump_hex(const unsigned long ul)
{
    char buf[OCIDUMP_SHORT_BUF_SIZE];
    sprintf(buf, "0x%lx", ul);
    ocidump_puts(buf);
}

void ocidump_OCIDate(const OCIDate *date)
{
    fprintf(ocidump_logfp, "{%04d-%02u-%02u %02u:%02u:%02u}", date->OCIDateYYYY, date->OCIDateMM, date->OCIDateDD, date->OCIDateTime.OCITimeHH, date->OCIDateTime.OCITimeMI, date->OCIDateTime.OCITimeSS);
}

void ocidump_OCINumber(const OCINumber *num)
{
    if (num == NULL) {
        ocidump_puts("(nil)");
    } else {
        char buf[128];

        if (ocidump_oranumber_to_str(num, buf, sizeof(buf)) <= 0) {
            ocidump_oranumber_dump(num, buf);
        }
        ocidump_puts(buf);
    }
}

void ocidump_raw_OCINumber(const void *addr, ub4 size)
{
    if (addr == NULL) {
        ocidump_puts("(nil)");
    } else {
        OCINumber num;

        memset(&num, 0, sizeof(num));
        num.OCINumberPart[0] = size;
        if (size > sizeof(num.OCINumberPart) - 1) {
            size = sizeof(num.OCINumberPart) - 1;
        }
        memcpy(&num.OCINumberPart[1], addr, size);
        ocidump_OCINumber(&num);
    }
}

void ocidump_pointer_to_attr_precision(const void *ptr)
{
    if (ptr == NULL) {
        ocidump_puts("(nil)");
    } else {
        union {
            ub1 explicit;
            ub2 implicit;
        } val;
        memcpy(&val, ptr, 2);
        fprintf(ocidump_logfp, "[%d(explicit) or %d(implicit)]", val.explicit, val.implicit);
    }
}

void ocidump_pointer_to_null_indicator(void *ind, OCITypeCode tc, int is_input)
{
    if (ind == NULL) {
        ocidump_puts("(nil)");
    } else if (tc != 108 /* OCI_TYPECODE_OBJECT */) {
        putc_unlocked('[', ocidump_logfp);
        ocidump_OCIInd(*(OCIInd*)ind);
        putc_unlocked(']', ocidump_logfp);
    } else if (is_input) {
        ocidump_pointer(ind);
    } else {
        putc_unlocked('[', ocidump_logfp);
        ocidump_pointer(*(void**)ind);
        putc_unlocked(']', ocidump_logfp);
    }
}

void ocidump_pointer_or_pointer_to_pointer(void *val, int is_pointer)
{
    if (val == NULL) {
        ocidump_puts("(nil)");
    } else if (is_pointer) {
        ocidump_pointer(val);
    } else {
        putc_unlocked('[', ocidump_logfp);
        ocidump_pointer(*(void**)val);
        putc_unlocked(']', ocidump_logfp);
    }
}

void ocidump_string(const text *str)
{
    if (str == NULL) {
        ocidump_puts("(nil)");
    } else {
        ocidump_string_with_length(str, (ub4)strlen((const char*)str));
    }
}

void ocidump_string_with_length(const text *str, ub4 len)
{
    if (str == NULL) {
        ocidump_puts("(nil)");
    } else if (ocidump_hide_string) {
        ocidump_puts("(hidden)");
    } else {
        ub4 idx;
        putc_unlocked('"', ocidump_logfp);
        for (idx = 0; idx < len; idx++) {
            text chr = str[idx];
            switch (chr) {
            case '\0':
                putc_unlocked('\\', ocidump_logfp);
                putc_unlocked('0', ocidump_logfp);
                break;
            case '\r':
                putc_unlocked('\\', ocidump_logfp);
                putc_unlocked('r', ocidump_logfp);
                break;
            case '\n':
                putc_unlocked('\\', ocidump_logfp);
                putc_unlocked('n', ocidump_logfp);
                break;
            case '\\':
            case '"':
                putc_unlocked('\\', ocidump_logfp);
                /* pass through */
            default:
                putc_unlocked(chr, ocidump_logfp);
            }
        }
        putc_unlocked('"', ocidump_logfp);
    }
}

void ocidump_string_with_maxlen(const text *str, ub4 len)
{
    if (str == NULL) {
        ocidump_puts("(nil)");
    } else {
        ub4 i;
        for (i = 0; i < len && str[i] != '\0'; i++);
        ocidump_string_with_length(str, i);
    }
}

void ocidump_pointer_to_int_with_length(const void *val, uword length, uword flag)
{
    switch (flag) {
    case 0: /* OCI_NUMBER_UNSIGNED */
        switch (length) {
        case 1: ocidump_pointer_to_ub1((ub1*)val); break;
        case 2: ocidump_pointer_to_ub2((ub2*)val); break;
        case 4: ocidump_pointer_to_ub4((ub4*)val); break;
        case 8: ocidump_pointer_to_ub8((ub8*)val); break;
        default: ocidump_puts("(invalid length)");
        }
    case 2: /* OCI_NUMBER_SIGNED */
        switch (length) {
        case 1: ocidump_pointer_to_sb1((sb1*)val); break;
        case 2: ocidump_pointer_to_sb2((sb2*)val); break;
        case 4: ocidump_pointer_to_sb4((sb4*)val); break;
        case 8: ocidump_pointer_to_sb8((sb8*)val); break;
        default: ocidump_puts("(invalid length)");
        }
    default:
        ocidump_puts("(invalid flag)");
    }
}

void ocidump_pointer_to_real_with_length(const void *val, uword length, ub4 cnt, sword status)
{
    if (val == NULL) {
        ocidump_puts("(nil)");
    } else {
        ub4 idx;
        char buf[128];

        putc_unlocked('[', ocidump_logfp);
        for (idx = 0; idx < cnt; idx++) {
            switch (length) {
            case 4:
                snprintf(buf, sizeof(buf), "%f", ((float*)val)[idx]);
                ocidump_puts(buf);
                break;
            case 8:
                snprintf(buf, sizeof(buf), "%f", ((double*)val)[idx]);
                ocidump_puts(buf);
                break;
            default:
                ocidump_puts("(invalid length)");
            }
        }
        putc_unlocked(']', ocidump_logfp);
    }
}

void ocidump_pointer_to_string_with_length(text **str, ub4 *len, sword status)
{
    if (str == NULL || len == NULL) {
        ocidump_puts("(nil)");
    } else if (status != 0) {
        ocidump_puts("[skip]");
    } else {
        putc_unlocked('[', ocidump_logfp);
        ocidump_string_with_length(*str, *len);
        putc_unlocked(']', ocidump_logfp);
    }
}

void ocidump_pointer_to_raw_OCINumber(const void **addr, ub4 size, sword status)
{
    if (addr == NULL) {
        ocidump_puts("(nil)");
    } else if (status != 0) {
        ocidump_puts("[skip]");
    } else {
        putc_unlocked('[', ocidump_logfp);
        ocidump_raw_OCINumber(*addr, size);
        putc_unlocked(']', ocidump_logfp);
    }
}

void ocidump_pointer_to_desc_obj(const void *objptr, ub4 objnm_len, ub1 objptr_typ)
{
    if (objptr == NULL) {
        ocidump_puts("(nil)");
    } else if (objptr_typ == 1 /* OCI_OTYPE_NAME */) {
        ocidump_string_with_length(objptr, objnm_len);
    } else {
        ocidump_pointer(objptr);
    }
}

void ocidump_pointer_to_version_number(const ub4 *val)
{
    if (val == NULL) {
        ocidump_puts("(nil)");
    } else {
        char buf[64];
        sprintf(buf,
                "[0x%x(%d.%d.%d.%d.%d)]", *val,
                (*val & 0xFF000000) >> 24,
                (*val & 0x00F00000) >> 20,
                (*val & 0x000FF000) >> 12,
                (*val & 0x00000F00) >> 8,
                (*val & 0x000000FF) >> 0);
        ocidump_puts(buf);
    }
}

#define DECLARE_POINTER_TO_TYPE_FUNC(x, y) \
void ocidump_pointer_to_##x(const y *val) \
{ \
    if (val == NULL) { \
        ocidump_puts("(nil)"); \
    } else { \
        putc_unlocked('[', ocidump_logfp); \
        ocidump_##x(*val); \
        putc_unlocked(']', ocidump_logfp); \
    } \
}

DECLARE_POINTER_TO_TYPE_FUNC(ub1, ub1)
DECLARE_POINTER_TO_TYPE_FUNC(sb1, sb1)
DECLARE_POINTER_TO_TYPE_FUNC(ub2, ub2)
DECLARE_POINTER_TO_TYPE_FUNC(sb2, sb2)
DECLARE_POINTER_TO_TYPE_FUNC(ub4, ub4)
DECLARE_POINTER_TO_TYPE_FUNC(sb4, sb4)
DECLARE_POINTER_TO_TYPE_FUNC(ub8, ub8)
DECLARE_POINTER_TO_TYPE_FUNC(sb8, sb8)
DECLARE_POINTER_TO_TYPE_FUNC(uword, uword)
DECLARE_POINTER_TO_TYPE_FUNC(sword, sword)
DECLARE_POINTER_TO_TYPE_FUNC(size_t, size_t)
DECLARE_POINTER_TO_TYPE_FUNC(boolean, boolean)
DECLARE_POINTER_TO_TYPE_FUNC(OCIDuration, OCIDuration)
DECLARE_POINTER_TO_TYPE_FUNC(OCIInd, OCIInd)
DECLARE_POINTER_TO_TYPE_FUNC(OCITypeCode, OCITypeCode)
DECLARE_POINTER_TO_TYPE_FUNC(OCITypeEncap, OCITypeEncap)
DECLARE_POINTER_TO_TYPE_FUNC(OCITypeParamMode, enum OCITypeParamMode)
DECLARE_POINTER_TO_TYPE_FUNC(OCI_PIECE, ub1)
DECLARE_POINTER_TO_TYPE_FUNC(OCI_PTYPE, ub1)
DECLARE_POINTER_TO_TYPE_FUNC(SQLT, OCITypeCode)
DECLARE_POINTER_TO_TYPE_FUNC(htype, ub4)
DECLARE_POINTER_TO_TYPE_FUNC(SQLCS, ub1)
DECLARE_POINTER_TO_TYPE_FUNC(SQLFNCODE, ub2)
DECLARE_POINTER_TO_TYPE_FUNC(pointer, void *)

#define DECLARE_ARRAY_OF_TYPE_FUNC(x, y) \
void ocidump_array_of_##x(const y *val, const ub4 array_size, sword status) \
{ \
    if (val == NULL) { \
        ocidump_puts("(nil)"); \
    } else if (status != 0) { \
        ocidump_puts("[skip]"); \
    } else { \
        ub4 idx; \
        putc_unlocked('[', ocidump_logfp); \
        for (idx = 0; idx < array_size; idx++) { \
            if (idx != 0) { \
                putc_unlocked(',', ocidump_logfp); \
            } \
            ocidump_##x(val[idx]); \
        } \
        putc_unlocked(']', ocidump_logfp); \
    } \
}

DECLARE_ARRAY_OF_TYPE_FUNC(pointer, void *)
DECLARE_ARRAY_OF_TYPE_FUNC(ub1, ub1)
DECLARE_ARRAY_OF_TYPE_FUNC(ub4, ub4)
DECLARE_ARRAY_OF_TYPE_FUNC(OCINumber, OCINumber *)

void ocidump_array_of_string_with_length(text **str, ub4 *len, const ub4 array_size, sword status)
{
    ocidump_array_of_const_string_with_length((const text **)str, (const ub4 *)len, array_size, status);
}

void ocidump_array_of_const_string_with_length(const text **str, const ub4 *len, const ub4 array_size, sword status)
{
    if (str == NULL || len == NULL) {
        ocidump_puts("(nil)");
    } else if (status != 0) {
        ocidump_puts("[skip]");
    } else {
        ub4 idx;
        putc_unlocked('[', ocidump_logfp);
        for (idx = 0; idx < array_size; idx++) {
            if (idx != 0) {
                putc_unlocked(',', ocidump_logfp);
            }
            ocidump_string_with_length(str[idx], len[idx]);
        }
        putc_unlocked(']', ocidump_logfp);
    }
}

void ocidump_array_of_string_with_ub1length(text **str, ub1 *len, const ub4 array_size, sword status)
{
    if (str == NULL) {
        ocidump_puts("(nil)");
    } else if (len == NULL || status != 0) {
        ocidump_puts("[skip]");
    } else {
        ub4 idx;
        putc_unlocked('[', ocidump_logfp);
        for (idx = 0; idx < array_size; idx++) {
            if (idx != 0) {
                putc_unlocked(',', ocidump_logfp);
            }
            ocidump_string_with_length(str[idx], len[idx]);
        }
        putc_unlocked(']', ocidump_logfp);
    }
}

void ocidump_array_of_null_terminated_string(text **str, const ub4 array_size, sword status)
{
    if (str == NULL) {
        ocidump_puts("(nil)");
    } else if (status != 0) {
        ocidump_puts("[skip]");
    } else {
        ub4 idx;
        putc_unlocked('[', ocidump_logfp);
        for (idx = 0; idx < array_size; idx++) {
            if (idx != 0) {
                putc_unlocked(',', ocidump_logfp);
            }
            ocidump_string(str[idx]);
        }
        putc_unlocked(']', ocidump_logfp);
    }
}
