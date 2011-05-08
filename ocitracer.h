#ifndef OCITRACER_H
#define OCITRACER_H 1
#include <oci.h>

#ifdef __GNUC__
#define PRINTF_FMT(x, y) __attribute__((format (printf, x, y)))
#else
#define PRINTF_FMT(x, y)
#endif

#define OCITRACER_NAME_BUF_SIZE 32

#ifdef __LP64__
#define OCITRACER_SIZET_FMT "lu"
#else
#define OCITRACER_SIZET_FMT "u"
#endif

typedef struct {
    const char *name;
    int *target;
} ocitracer_target_t;

extern ocitracer_target_t ocitracer_targets[];

extern int ocitracer_hide_string;
void ocitracer_init(void);
const char *ocitracer_status2name(sword status, char *buf);
const char *ocitracer_htype2name(ub4 htype, char *buf);
const char *ocitracer_attrtype2name(ub4 htype, ub4 attrtype, char *buf);
const char *ocitracer_sprintf(char *buf, const char *fmt, ...) PRINTF_FMT(2, 3);
void ocitracer_log(const char *fmt, ...) PRINTF_FMT(1, 2);

#endif /* OCITRACER_H */
