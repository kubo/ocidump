#ifndef OCIDUMP_H
#define OCIDUMP_H 1
#include <oci.h>

#ifdef __GNUC__
#define PRINTF_FMT(x, y) __attribute__((format (printf, x, y)))
#else
#define PRINTF_FMT(x, y)
#endif

#define OCIDUMP_NAME_BUF_SIZE 32

#ifdef __LP64__
#define OCIDUMP_SIZET_FMT "lu"
#else
#define OCIDUMP_SIZET_FMT "u"
#endif

typedef struct {
    const char *name;
    int *target;
} ocidump_target_t;

extern ocidump_target_t ocidump_targets[];

extern int ocidump_hide_string;
void ocidump_init(void);
const char *ocidump_status2name(sword status, char *buf);
const char *ocidump_htype2name(ub4 htype, char *buf);
const char *ocidump_attrtype2name(ub4 htype, ub4 attrtype, char *buf);
const char *ocidump_sprintf(char *buf, const char *fmt, ...) PRINTF_FMT(2, 3);
void ocidump_log(const char *fmt, ...) PRINTF_FMT(1, 2);

#endif /* OCIDUMP_H */
