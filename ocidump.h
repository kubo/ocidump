#ifndef OCIDUMP_H
#define OCIDUMP_H 1
#include <ociap.h>
#include <orid.h>
#include <orl.h>
#include <oro.h>
#include <ort.h>

#ifdef __GNUC__
#define PRINTF_FMT(x, y) __attribute__((format (printf, x, y)))
#else
#define PRINTF_FMT(x, y)
#endif

#define OCIDUMP_SHORT_BUF_SIZE 32
#define OCIDUMP_OCINUMBER_BUF_SIZE 99

#ifdef __LP64__
#define OCIDUMP_SIZET_FMT "lu"
#define OCIDUMP_UB8_FMT "lu"
#else
#define OCIDUMP_SIZET_FMT "u"
#define OCIDUMP_UB8_FMT "llu"
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
const char *ocidump_ocinumber(char *buf, const OCINumber *n);
const char *ocidump_quotestring(char **buf, const OraText *str, ub4 len);
const char *ocidump_quotestring2(char **buf, OraText **str, ub4 *len);
const char *ocidump_sprintf(char *buf, const char *fmt, ...) PRINTF_FMT(2, 3);
const char *ocidump_asprintf(char **buf, const char *fmt, ...) PRINTF_FMT(2, 3);
void ocidump_log(const char *fmt, ...) PRINTF_FMT(1, 2);

#endif /* OCIDUMP_H */
