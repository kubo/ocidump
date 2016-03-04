#ifndef OCIHANDLE_H
#define OCIHANDLE_H 1

typedef struct ocihandle {
    ub4 type;
    ub4 id;
} ocihandle_t;

#ifdef _WIN32
void ocihandle_init(void);
#endif
const ocihandle_t *ocihandle_add(const void *addr, ub4 type, const void *parent);
const ocihandle_t *ocihandle_find(const void *addr);
int ocihandle_del(const ocihandle_t *hndl);
void ocihandle_print(const void *addr, ub4 type, ub4 type2, ub4 type3, const ocihandle_t *hndl);
void ocidump_dump_hash_table(void);

#endif
