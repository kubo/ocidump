#ifndef OCIDUMP_H
#define OCIDUMP_H 1

typedef unsigned char ub1;
typedef   signed char sb1;
typedef unsigned char ub2;
typedef   signed char sb2;
typedef unsigned int ub4;
typedef   signed int sb4;
#ifdef __LP64__
typedef unsigned long oraub8;
typedef   signed long orasb8;
#else
typedef unsigned long long oraub8;
typedef   signed long long orasb8;
#endif
typedef unsigned int uword;
typedef   signed int sword;
typedef          int eword;

typedef unsigned char OraText;
typedef unsigned char oratext;
typedef unsigned char text;

typedef ub2 OCITypeCode;
typedef ub2 OCIDuration;

typedef sb2 OCIInd;
typedef ub1 OCIObjectPropId;

#include "ocidefs.h"

/* The followings are not correct, but work in ocidump. */
typedef void * OCICallbackInBind;
typedef void * OCICallbackOutBind;
typedef void * OCICallbackLobGetDeduplicateRegions;
typedef void * OCICallbackDefine;
typedef void * OCICallbackLobArrayRead;
typedef void * OCICallbackLobArrayWrite;
typedef void * OCICallbackLobRead;
typedef void * OCICallbackLobRead2;
typedef void * OCICallbackLobWrite;
typedef void * OCICallbackLobWrite2;
typedef void * OCIEnvCallbackType;

typedef struct OCIDate {
    sb2 OCIDateYYYY;
    ub1 OCIDateMM;
    ub1 OCIDateDD;
    struct {
        ub1 OCITimeHH;
        ub1 OCITimeMI;
        ub1 OCITimeSS;
    } OCIDateTime;
} OCIDate;

#define boolean int
#define dvoid void
#define CONST const

#define OCI_DTYPE_FIRST 50

typedef struct OCINumber {
  ub1 OCINumberPart[22];
} OCINumber;

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
