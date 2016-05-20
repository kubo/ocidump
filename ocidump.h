#ifndef OCIDUMP_H
#define OCIDUMP_H 1
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#define pthread_key_t DWORD
#define pthread_getspecific TlsGetValue
#define pthread_setspecific TlsSetValue
#else
#include <pthread.h>
#endif

typedef unsigned char ub1;
typedef   signed char sb1;
typedef unsigned short ub2;
typedef   signed short sb2;
typedef unsigned int ub4;
typedef   signed int sb4;
#if defined _WIN32
typedef unsigned __int64 oraub8;
typedef   signed __int64 orasb8;
#elif defined __LP64__
typedef unsigned long oraub8;
typedef   signed long orasb8;
#else
typedef unsigned long long oraub8;
typedef   signed long long orasb8;
#endif
#define ub8 oraub8
#define sb8 orasb8
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

#if !defined putc_unlocked && (defined _putc_nolock || defined _putchar_nolock)
#define putc_unlocked _putc_nolock
#endif

#define OCIDUMP_SHORT_BUF_SIZE 32
#define OCIDUMP_OCINUMBER_BUF_SIZE 99

#if defined _WIN64
#define SIZEOF_SIZE_T 8
#define SIZEOF_LONG 4
#define OCIDUMP_SIZET_FMT "I64u"
#define OCIDUMP_UB8_FMT "I64u"
#define OCIDUMP_SB8_FMT "I64d"
#elif defined _WIN32
#define SIZEOF_SIZE_T 4
#define SIZEOF_LONG 4
#define OCIDUMP_SIZET_FMT "u"
#define OCIDUMP_UB8_FMT "I64u"
#define OCIDUMP_SB8_FMT "I64d"
#elif defined __LP64__
#define SIZEOF_SIZE_T 8
#define SIZEOF_LONG 8
#define OCIDUMP_SIZET_FMT "lu"
#define OCIDUMP_UB8_FMT "lu"
#define OCIDUMP_SB8_FMT "ld"
#else
#define SIZEOF_SIZE_T 4
#define SIZEOF_LONG 4
#define OCIDUMP_SIZET_FMT "u"
#define OCIDUMP_UB8_FMT "llu"
#define OCIDUMP_SB8_FMT "lld"
#endif

#define OCIDUMP_HOOK_ENTRY   (1u << 0)
#define OCIDUMP_HOOK_EXIT    (1u << 1)

#define OCIDUMP_LOG_ALL      (0xffffffff)
#define OCIDUMP_LOG_HOOK     (1u << 0)

typedef struct {
    const char *name;
    void *hook_func;
    void **orig_func;
    unsigned int *flags;
} ocidump_hook_t;

/* ociattr.c */
void ocidump_attrtype(ub4 attrtype, ub4 htype);
void ocidump_read_attrval(dvoid *val, ub4 htype, ub4 attrtype, ub4 *sizep, sword status);
void ocidump_write_attrval(dvoid *val, ub4 htype, ub4 attrtype, ub4 size);

/* ocifunc.c */
extern ocidump_hook_t ocidump_hooks[];
extern int ocidump_hook_cnt;

/* ocidump.c */
extern int ocidump_hide_string;
extern int ocidump_trace_handle;
extern int ocidump_is_initialized;
extern FILE *ocidump_logfp;
extern pthread_key_t ocidump_tls_key;
void ocidump_init(void);
void ocidump_log_start(const char *funcname);
void ocidump_log_end(void);
void ocidump_log(unsigned int flags, const char *fmt, ...) PRINTF_FMT(2, 3);

/* the following functions don't lock the log file stream.
 * Use these between ocidump_log_start() and ocidump_log_end().
 */
#define ocidump_putc(chr) putc_unlocked((chr), ocidump_logfp)
#define ocidump_boolean(num) ocidump_long(num)
#define ocidump_sb1(num) ocidump_long(num)
#define ocidump_ub1(num) ocidump_ulong(num)
#define ocidump_sb2(num) ocidump_long(num)
#define ocidump_ub2(num) ocidump_ulong(num)
#define ocidump_sb4(num) ocidump_long(num)
#define ocidump_ub4(num) ocidump_ulong(num)
#define ocidump_ub4_hex(num) ocidump_hex(num)
#define ocidump_sword(num) ocidump_long(num)
#define ocidump_uword(num) ocidump_ulong(num)
#if SIZEOF_SIZE_T == SIZEOF_LONG
#define ocidump_size_t(num) ocidump_ulong(num)
#else
#define ocidump_size_t(num) ocidump_ub8(num)
#endif
void ocidump_puts(const char *str);
void ocidump_pointer(const void *ptr);
void ocidump_function_pointer(void *addr);
void ocidump_long(const signed long sl);
void ocidump_ulong(const unsigned long ul);
#if SIZEOF_LONG == 4
void ocidump_ub8(const ub8 ul);
void ocidump_sb8(const sb8 ul);
#else
#define ocidump_ub8(val) ocidump_ulong(val)
#define ocidump_sb8(val) ocidump_long(val)
#endif
void ocidump_hex(const unsigned long ul);
void ocidump_string(const text *str);
void ocidump_string_with_length(const text *str, ub4 len);
void ocidump_string_with_signed_length(const text *str, sb4 len);
void ocidump_string_with_maxlen(const text *str, ub4 len);
void ocidump_OCIDate(const OCIDate *date);
void ocidump_OCINumber(const OCINumber *num);
void ocidump_raw_OCINumber(const void *addr, ub4 size);

void ocidump_pointer_to_null_indicator(void *ind, OCITypeCode tc, int is_input);
void ocidump_pointer_or_pointer_to_pointer(void *val, int is_pointer);
void ocidump_pointer_to_int_with_length(const void *val, uword length, uword flag);
void ocidump_pointer_to_real_with_length(const void *val, uword length, ub4 cnt, sword status);
void ocidump_pointer_to_string_with_length(text **str, ub4 *len, sword status);
void ocidump_pointer_to_raw_OCINumber(const void **addr, ub4 size, sword status);
void ocidump_pointer_to_attr_precision(const void *ptr);
void ocidump_pointer_to_desc_obj(const void *objptr, ub4 objnm_len, ub1 objptr_typ);
void ocidump_pointer_to_version_number(const ub4 *val);

void ocidump_pointer_to_ub1(const ub1 *val);
void ocidump_pointer_to_sb1(const sb1 *val);
void ocidump_pointer_to_ub2(const ub2 *val);
void ocidump_pointer_to_sb2(const sb2 *val);
void ocidump_pointer_to_ub4(const ub4 *val);
void ocidump_pointer_to_sb4(const sb4 *val);
void ocidump_pointer_to_ub8(const ub8 *val);
void ocidump_pointer_to_sb8(const sb8 *val);
void ocidump_pointer_to_uword(const uword *val);
void ocidump_pointer_to_sword(const sword *val);
void ocidump_pointer_to_size_t(const size_t *val);
void ocidump_pointer_to_boolean(const boolean *val);
void ocidump_pointer_to_OCIDuration(const OCIDuration *dur);
void ocidump_pointer_to_OCIInd(const OCIInd *val);
void ocidump_pointer_to_OCITypeCode(const OCITypeCode *tc);
void ocidump_pointer_to_OCITypeEncap(const OCITypeEncap *val);
void ocidump_pointer_to_OCITypeParamMode(const enum OCITypeParamMode *val);
void ocidump_pointer_to_OCI_PIECE(const ub1 *val);
void ocidump_pointer_to_OCI_PTYPE(const ub1 *val);
void ocidump_pointer_to_SQLT(const OCITypeCode *val);
void ocidump_pointer_to_htype(const ub4 *val);
void ocidump_pointer_to_SQLCS(const ub1 *val);
void ocidump_pointer_to_SQLFNCODE(const ub2 *val);
void ocidump_pointer_to_pointer(const void **ptr);

void ocidump_array_of_pointer(const void **val, const ub4 array_size, sword status);
void ocidump_array_of_ub1(const ub1 *val, const ub4 array_size, sword status);
void ocidump_array_of_ub4(const ub4 *val, const ub4 array_size, sword status);
void ocidump_array_of_OCINumber(const OCINumber **val, const ub4 array_size, sword status);
void ocidump_array_of_string_with_length(text **str, ub4 *len, const ub4 array_size, sword status);
void ocidump_array_of_const_string_with_length(const text **str, const ub4 *len, const ub4 array_size, sword status);
void ocidump_array_of_string_with_ub1length(text **str, ub1 *len, const ub4 array_size, sword status);
void ocidump_array_of_null_terminated_string(text **str, const ub4 array_size, sword status);

void ocidump_OCIEnv(const OCIEnv *envhp);
void ocidump_OCIError(const OCIError *errhp);
void ocidump_OCISvcCtx(const OCISvcCtx *svchp);
void ocidump_OCIServer(const OCIServer *srvhp);
void ocidump_OCISession(const OCISession *seshp);
void ocidump_OCIDateTime(const OCIDateTime *dttm);
void ocidump_OCIInterval(const OCIInterval *intvl);

void ocidump_ocihandle(const void *hndl, ub4 type, ub4 type2, ub4 type3);
void ocidump_pointer_to_ocihandle(const void **hndl, ub4 type, const void *parent, sword status);
void ocidump_ocihandle_free(const void *hndl, ub4 type);

#ifdef _WIN32
/* win32.c */
extern BOOL forward_only;
extern BOOL ocidump_use_dbghelp;
extern CRITICAL_SECTION ocidump_dbghelp_lock;
void ocidump_init_win32(void);
#endif

#endif /* OCIDUMP_H */
