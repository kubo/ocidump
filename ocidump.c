#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "ocidump.h"

int ocidump_hide_string = 0;

static FILE *logfp;

void ocidump_init(void)
{
    char *val = getenv("OCIDUMP_HIDE_STRING");
    if (val != NULL) {
        ocidump_hide_string = atoi(val);
    }
    val = getenv("OCIDUMP_LOGFILE");
    if (val != NULL) {
        logfp = fopen(val, "a");
    }
    if (logfp == NULL) {
        logfp = stderr;
    }
    val = getenv("OCIDUMP_CONFIG");
    if (val != NULL) {
        FILE *fp = fopen(val, "r");
        if (fp != NULL) {
            char buf[256];
            int i;

            /* clear all targets */
            for (i = 0; ocidump_targets[i].name != NULL; i++) {
                *ocidump_targets[i].target = 0;
            }

            while (fgets(buf, sizeof(buf), fp) != NULL) {
                size_t len = strlen(buf);
                while (len > 0 && (buf[len - 1] == '\n' || buf[len - 1] == '\r')) {
                    buf[len - 1] = '\0';
                }
                for (i = 0; ocidump_targets[i].name != NULL; i++) {
                    if (strcmp(ocidump_targets[i].name, buf) == 0) {
                        *ocidump_targets[i].target = 1;
                        break;
                    }
                }
            }
            fclose(fp);
        }
    }
}

const char *ocidump_status2name(sword status, char *buf)
{
    switch (status) {
    case OCI_SUCCESS: return "OCI_SUCCESS";
    case OCI_SUCCESS_WITH_INFO: return "OCI_SUCCESS_WITH_INFO";
    case OCI_NO_DATA: return "OCI_NO_DATA";
    case OCI_ERROR: return "OCI_ERROR";
    case OCI_INVALID_HANDLE: return "OCI_INVALID_HANDLE";
    case OCI_NEED_DATA: return "OCI_NEED_DATA";
    case OCI_STILL_EXECUTING: return "OCI_STILL_EXECUTING";
    }
    sprintf(buf, "%d", status);
    return buf;
}

const char *ocidump_htype2name(ub4 htype, char *buf)
{
    switch (htype) {
    case OCI_HTYPE_ENV: return "OCI_HTYPE_ENV";
    case OCI_HTYPE_ERROR: return "OCI_HTYPE_ERROR";
    case OCI_HTYPE_SVCCTX: return "OCI_HTYPE_SVCCTX";
    case OCI_HTYPE_STMT: return "OCI_HTYPE_STMT";
    case OCI_HTYPE_BIND: return "OCI_HTYPE_BIND";
    case OCI_HTYPE_DEFINE: return "OCI_HTYPE_DEFINE";
    case OCI_HTYPE_DESCRIBE: return "OCI_HTYPE_DESCRIBE";
    case OCI_HTYPE_SERVER: return "OCI_HTYPE_SERVER";
    case OCI_HTYPE_SESSION: return "OCI_HTYPE_SESSION";
    case OCI_HTYPE_TRANS: return "OCI_HTYPE_TRANS";
    case OCI_HTYPE_COMPLEXOBJECT: return "OCI_HTYPE_COMPLEXOBJECT";
    case OCI_HTYPE_SECURITY: return "OCI_HTYPE_SECURITY";
    case OCI_HTYPE_SUBSCRIPTION: return "OCI_HTYPE_SUBSCRIPTION";
    case OCI_HTYPE_DIRPATH_CTX: return "OCI_HTYPE_DIRPATH_CTX";
    case OCI_HTYPE_DIRPATH_COLUMN_ARRAY: return "OCI_HTYPE_DIRPATH_COLUMN_ARRAY";
    case OCI_HTYPE_DIRPATH_STREAM: return "OCI_HTYPE_DIRPATH_STREAM";
    case OCI_HTYPE_PROC: return "OCI_HTYPE_PROC";
    case OCI_HTYPE_DIRPATH_FN_CTX: return "OCI_HTYPE_DIRPATH_FN_CTX";
    case OCI_HTYPE_DIRPATH_FN_COL_ARRAY: return "OCI_HTYPE_DIRPATH_FN_COL_ARRAY";
    case OCI_HTYPE_XADSESSION: return "OCI_HTYPE_XADSESSION";
    case OCI_HTYPE_XADTABLE: return "OCI_HTYPE_XADTABLE";
    case OCI_HTYPE_XADFIELD: return "OCI_HTYPE_XADFIELD";
    case OCI_HTYPE_XADGRANULE: return "OCI_HTYPE_XADGRANULE";
    case OCI_HTYPE_XADRECORD: return "OCI_HTYPE_XADRECORD";
    case OCI_HTYPE_XADIO: return "OCI_HTYPE_XADIO";
    case OCI_HTYPE_CPOOL: return "OCI_HTYPE_CPOOL";
    case OCI_HTYPE_SPOOL: return "OCI_HTYPE_SPOOL";
    case OCI_HTYPE_ADMIN: return "OCI_HTYPE_ADMIN";
    case OCI_HTYPE_EVENT: return "OCI_HTYPE_EVENT";
    case OCI_DTYPE_LOB: return "OCI_DTYPE_LOB";
    case OCI_DTYPE_SNAP: return "OCI_DTYPE_SNAP";
    case OCI_DTYPE_RSET: return "OCI_DTYPE_RSET";
    case OCI_DTYPE_PARAM: return "OCI_DTYPE_PARAM";
    case OCI_DTYPE_ROWID: return "OCI_DTYPE_ROWID";
    case OCI_DTYPE_COMPLEXOBJECTCOMP: return "OCI_DTYPE_COMPLEXOBJECTCOMP";
    case OCI_DTYPE_FILE: return "OCI_DTYPE_FILE";
    case OCI_DTYPE_AQENQ_OPTIONS: return "OCI_DTYPE_AQENQ_OPTIONS";
    case OCI_DTYPE_AQDEQ_OPTIONS: return "OCI_DTYPE_AQDEQ_OPTIONS";
    case OCI_DTYPE_AQMSG_PROPERTIES: return "OCI_DTYPE_AQMSG_PROPERTIES";
    case OCI_DTYPE_AQAGENT: return "OCI_DTYPE_AQAGENT";
    case OCI_DTYPE_LOCATOR: return "OCI_DTYPE_LOCATOR";
    case OCI_DTYPE_INTERVAL_YM: return "OCI_DTYPE_INTERVAL_YM";
    case OCI_DTYPE_INTERVAL_DS: return "OCI_DTYPE_INTERVAL_DS";
    case OCI_DTYPE_AQNFY_DESCRIPTOR: return "OCI_DTYPE_AQNFY_DESCRIPTOR";
    case OCI_DTYPE_DATE: return "OCI_DTYPE_DATE";
    case OCI_DTYPE_TIME: return "OCI_DTYPE_TIME";
    case OCI_DTYPE_TIME_TZ: return "OCI_DTYPE_TIME_TZ";
    case OCI_DTYPE_TIMESTAMP: return "OCI_DTYPE_TIMESTAMP";
    case OCI_DTYPE_TIMESTAMP_TZ: return "OCI_DTYPE_TIMESTAMP_TZ";
    case OCI_DTYPE_TIMESTAMP_LTZ: return "OCI_DTYPE_TIMESTAMP_LTZ";
    case OCI_DTYPE_UCB: return "OCI_DTYPE_UCB";
    case OCI_DTYPE_SRVDN: return "OCI_DTYPE_SRVDN";
    case OCI_DTYPE_SIGNATURE: return "OCI_DTYPE_SIGNATURE";
    case OCI_DTYPE_AQLIS_OPTIONS: return "OCI_DTYPE_AQLIS_OPTIONS";
    case OCI_DTYPE_AQLIS_MSG_PROPERTIES: return "OCI_DTYPE_AQLIS_MSG_PROPERTIES";
#ifdef OCI_DTYPE_CHDES
    case OCI_DTYPE_CHDES: return "OCI_DTYPE_CHDES";
#endif
#ifdef OCI_DTYPE_TABLE_CHDES
    case OCI_DTYPE_TABLE_CHDES: return "OCI_DTYPE_TABLE_CHDES";
#endif
#ifdef OCI_DTYPE_ROW_CHDES
    case OCI_DTYPE_ROW_CHDES: return "OCI_DTYPE_ROW_CHDES";
#endif
#ifdef OCI_DTYPE_CQDES
    case OCI_DTYPE_CQDES: return "OCI_DTYPE_CQDES";
#endif
#ifdef OCI_DTYPE_LOB_REGION
    case OCI_DTYPE_LOB_REGION: return "OCI_DTYPE_LOB_REGION";
#endif
    }
    sprintf(buf, "%u", htype);
    return buf;
}

const char *ocidump_attrtype2name(ub4 htype, ub4 attrtype, char *buf)
{
    if (htype >= OCI_DTYPE_FIRST) {
        switch (attrtype) {
        case OCI_ATTR_DATA_SIZE: return "OCI_ATTR_DATA_SIZE";         /* 1 */
        case OCI_ATTR_DATA_TYPE: return "OCI_ATTR_DATA_TYPE";         /* 2 */
        case OCI_ATTR_DISP_SIZE: return "OCI_ATTR_DISP_SIZE";         /* 3 */
        case OCI_ATTR_NAME: return "OCI_ATTR_NAME";                   /* 4 */
        case OCI_ATTR_PRECISION: return "OCI_ATTR_PRECISION";         /* 5 */
        case OCI_ATTR_SCALE: return "OCI_ATTR_SCALE";                 /* 6 */
        case OCI_ATTR_IS_NULL: return "OCI_ATTR_IS_NULL";             /* 7 */
        case OCI_ATTR_TYPE_NAME: return "OCI_ATTR_TYPE_NAME";         /* 8 */
        case OCI_ATTR_SCHEMA_NAME: return "OCI_ATTR_SCHEMA_NAME";     /* 9 */
        case OCI_ATTR_SUB_NAME: return "OCI_ATTR_SUB_NAME";           /* 10 */
        case OCI_ATTR_POSITION: return "OCI_ATTR_POSITION";           /* 11 */
        case OCI_ATTR_COMPLEXOBJECTCOMP_TYPE: return "OCI_ATTR_COMPLEXOBJECTCOMP_TYPE"; /* 50 */
        case OCI_ATTR_COMPLEXOBJECTCOMP_TYPE_LEVEL: return "OCI_ATTR_COMPLEXOBJECTCOMP_TYPE_LEVEL"; /* 51 */
        case OCI_ATTR_COMPLEXOBJECT_LEVEL: return "OCI_ATTR_COMPLEXOBJECT_LEVEL"; /* 52 */
        case OCI_ATTR_COMPLEXOBJECT_COLL_OUTOFLINE: return "OCI_ATTR_COMPLEXOBJECT_COLL_OUTOFLINE"; /* 53 */
        case OCI_ATTR_DISP_NAME: return "OCI_ATTR_DISP_NAME";         /* 100 */
        case OCI_ATTR_ENCC_SIZE: return "OCI_ATTR_ENCC_SIZE";         /* 101 */
        case OCI_ATTR_COL_ENC: return "OCI_ATTR_COL_ENC";             /* 102 */
        case OCI_ATTR_COL_ENC_SALT: return "OCI_ATTR_COL_ENC_SALT";   /* 103 */
        case OCI_ATTR_OVERLOAD: return "OCI_ATTR_OVERLOAD";           /* 210 */
        case OCI_ATTR_LEVEL: return "OCI_ATTR_LEVEL";                 /* 211 */
        case OCI_ATTR_HAS_DEFAULT: return "OCI_ATTR_HAS_DEFAULT";     /* 212 */
        case OCI_ATTR_IOMODE: return "OCI_ATTR_IOMODE";               /* 213 */
        case OCI_ATTR_RADIX: return "OCI_ATTR_RADIX";                 /* 214 */
        case OCI_ATTR_NUM_ARGS: return "OCI_ATTR_NUM_ARGS";           /* 215 */
        case OCI_ATTR_TYPECODE: return "OCI_ATTR_TYPECODE";           /* 216 */
        case OCI_ATTR_COLLECTION_TYPECODE: return "OCI_ATTR_COLLECTION_TYPECODE"; /* 217 */
        case OCI_ATTR_VERSION: return "OCI_ATTR_VERSION";             /* 218 */
        case OCI_ATTR_IS_INCOMPLETE_TYPE: return "OCI_ATTR_IS_INCOMPLETE_TYPE"; /* 219 */
        case OCI_ATTR_IS_SYSTEM_TYPE: return "OCI_ATTR_IS_SYSTEM_TYPE"; /* 220 */
        case OCI_ATTR_IS_PREDEFINED_TYPE: return "OCI_ATTR_IS_PREDEFINED_TYPE"; /* 221 */
        case OCI_ATTR_IS_TRANSIENT_TYPE: return "OCI_ATTR_IS_TRANSIENT_TYPE"; /* 222 */
        case OCI_ATTR_IS_SYSTEM_GENERATED_TYPE: return "OCI_ATTR_IS_SYSTEM_GENERATED_TYPE"; /* 223 */
        case OCI_ATTR_HAS_NESTED_TABLE: return "OCI_ATTR_HAS_NESTED_TABLE"; /* 224 */
        case OCI_ATTR_HAS_LOB: return "OCI_ATTR_HAS_LOB";             /* 225 */
        case OCI_ATTR_HAS_FILE: return "OCI_ATTR_HAS_FILE";           /* 226 */
        case OCI_ATTR_COLLECTION_ELEMENT: return "OCI_ATTR_COLLECTION_ELEMENT"; /* 227 */
        case OCI_ATTR_NUM_TYPE_ATTRS: return "OCI_ATTR_NUM_TYPE_ATTRS"; /* 228 */
        case OCI_ATTR_LIST_TYPE_ATTRS: return "OCI_ATTR_LIST_TYPE_ATTRS"; /* 229 */
        case OCI_ATTR_NUM_TYPE_METHODS: return "OCI_ATTR_NUM_TYPE_METHODS"; /* 230 */
        case OCI_ATTR_LIST_TYPE_METHODS: return "OCI_ATTR_LIST_TYPE_METHODS"; /* 231 */
        case OCI_ATTR_MAP_METHOD: return "OCI_ATTR_MAP_METHOD";       /* 232 */
        case OCI_ATTR_ORDER_METHOD: return "OCI_ATTR_ORDER_METHOD";   /* 233 */
        case OCI_ATTR_NUM_ELEMS: return "OCI_ATTR_NUM_ELEMS";         /* 234 */
        case OCI_ATTR_ENCAPSULATION: return "OCI_ATTR_ENCAPSULATION"; /* 235 */
        case OCI_ATTR_IS_SELFISH: return "OCI_ATTR_IS_SELFISH";       /* 236 */
        case OCI_ATTR_IS_VIRTUAL: return "OCI_ATTR_IS_VIRTUAL";       /* 237 */
        case OCI_ATTR_IS_INLINE: return "OCI_ATTR_IS_INLINE";         /* 238 */
        case OCI_ATTR_IS_CONSTANT: return "OCI_ATTR_IS_CONSTANT";     /* 239 */
        case OCI_ATTR_HAS_RESULT: return "OCI_ATTR_HAS_RESULT";       /* 240 */
        case OCI_ATTR_IS_CONSTRUCTOR: return "OCI_ATTR_IS_CONSTRUCTOR"; /* 241 */
        case OCI_ATTR_IS_DESTRUCTOR: return "OCI_ATTR_IS_DESTRUCTOR"; /* 242 */
        case OCI_ATTR_IS_OPERATOR: return "OCI_ATTR_IS_OPERATOR";     /* 243 */
        case OCI_ATTR_IS_MAP: return "OCI_ATTR_IS_MAP";               /* 244 */
        case OCI_ATTR_IS_ORDER: return "OCI_ATTR_IS_ORDER";           /* 245 */
        case OCI_ATTR_IS_RNDS: return "OCI_ATTR_IS_RNDS";             /* 246 */
        case OCI_ATTR_IS_RNPS: return "OCI_ATTR_IS_RNPS";             /* 247 */
        case OCI_ATTR_IS_WNDS: return "OCI_ATTR_IS_WNDS";             /* 248 */
        case OCI_ATTR_IS_WNPS: return "OCI_ATTR_IS_WNPS";             /* 249 */
        case OCI_ATTR_DESC_PUBLIC: return "OCI_ATTR_DESC_PUBLIC";     /* 250 */
        case OCI_ATTR_CACHE_CLIENT_CONTEXT: return "OCI_ATTR_CACHE_CLIENT_CONTEXT"; /* 251 */
        case OCI_ATTR_UCI_CONSTRUCT: return "OCI_ATTR_UCI_CONSTRUCT"; /* 252 */
        case OCI_ATTR_UCI_DESTRUCT: return "OCI_ATTR_UCI_DESTRUCT";   /* 253 */
        case OCI_ATTR_UCI_COPY: return "OCI_ATTR_UCI_COPY";           /* 254 */
        case OCI_ATTR_UCI_PICKLE: return "OCI_ATTR_UCI_PICKLE";       /* 255 */
        case OCI_ATTR_UCI_UNPICKLE: return "OCI_ATTR_UCI_UNPICKLE";   /* 256 */
        case OCI_ATTR_UCI_REFRESH: return "OCI_ATTR_UCI_REFRESH";     /* 257 */
        case OCI_ATTR_IS_SUBTYPE: return "OCI_ATTR_IS_SUBTYPE";       /* 258 */
        case OCI_ATTR_SUPERTYPE_SCHEMA_NAME: return "OCI_ATTR_SUPERTYPE_SCHEMA_NAME"; /* 259 */
        case OCI_ATTR_SUPERTYPE_NAME: return "OCI_ATTR_SUPERTYPE_NAME"; /* 260 */
        case OCI_ATTR_LIST_OBJECTS: return "OCI_ATTR_LIST_OBJECTS";   /* 261 */
        case OCI_ATTR_NCHARSET_ID: return "OCI_ATTR_NCHARSET_ID";     /* 262 */
        case OCI_ATTR_LIST_SCHEMAS: return "OCI_ATTR_LIST_SCHEMAS";   /* 263 */
        case OCI_ATTR_MAX_PROC_LEN: return "OCI_ATTR_MAX_PROC_LEN";   /* 264 */
        case OCI_ATTR_MAX_COLUMN_LEN: return "OCI_ATTR_MAX_COLUMN_LEN"; /* 265 */
        case OCI_ATTR_CURSOR_COMMIT_BEHAVIOR: return "OCI_ATTR_CURSOR_COMMIT_BEHAVIOR"; /* 266 */
        case OCI_ATTR_MAX_CATALOG_NAMELEN: return "OCI_ATTR_MAX_CATALOG_NAMELEN"; /* 267 */
        case OCI_ATTR_CATALOG_LOCATION: return "OCI_ATTR_CATALOG_LOCATION"; /* 268 */
        case OCI_ATTR_SAVEPOINT_SUPPORT: return "OCI_ATTR_SAVEPOINT_SUPPORT"; /* 269 */
        case OCI_ATTR_NOWAIT_SUPPORT: return "OCI_ATTR_NOWAIT_SUPPORT"; /* 270 */
        case OCI_ATTR_AUTOCOMMIT_DDL: return "OCI_ATTR_AUTOCOMMIT_DDL"; /* 271 */
        case OCI_ATTR_LOCKING_MODE: return "OCI_ATTR_LOCKING_MODE";   /* 272 */
        case OCI_ATTR_APPCTX_SIZE: return "OCI_ATTR_APPCTX_SIZE";     /* 273 */
        case OCI_ATTR_APPCTX_LIST: return "OCI_ATTR_APPCTX_LIST";     /* 274 */
        case OCI_ATTR_APPCTX_NAME: return "OCI_ATTR_APPCTX_NAME";     /* 275 */
        case OCI_ATTR_APPCTX_ATTR: return "OCI_ATTR_APPCTX_ATTR";     /* 276 */
        case OCI_ATTR_APPCTX_VALUE: return "OCI_ATTR_APPCTX_VALUE";   /* 277 */
        case OCI_ATTR_CLIENT_IDENTIFIER: return "OCI_ATTR_CLIENT_IDENTIFIER"; /* 278 */
        case OCI_ATTR_IS_FINAL_TYPE: return "OCI_ATTR_IS_FINAL_TYPE"; /* 279 */
        case OCI_ATTR_IS_INSTANTIABLE_TYPE: return "OCI_ATTR_IS_INSTANTIABLE_TYPE"; /* 280 */
        case OCI_ATTR_IS_FINAL_METHOD: return "OCI_ATTR_IS_FINAL_METHOD"; /* 281 */
        case OCI_ATTR_IS_INSTANTIABLE_METHOD: return "OCI_ATTR_IS_INSTANTIABLE_METHOD"; /* 282 */
        case OCI_ATTR_IS_OVERRIDING_METHOD: return "OCI_ATTR_IS_OVERRIDING_METHOD"; /* 283 */
        case OCI_ATTR_DESC_SYNBASE: return "OCI_ATTR_DESC_SYNBASE";   /* 284 */
        case OCI_ATTR_CHAR_USED: return "OCI_ATTR_CHAR_USED";         /* 285 */
        case OCI_ATTR_CHAR_SIZE: return "OCI_ATTR_CHAR_SIZE";         /* 286 */
        case OCI_ATTR_IS_JAVA_TYPE: return "OCI_ATTR_IS_JAVA_TYPE";   /* 287 */
        case OCI_ATTR_DISTINGUISHED_NAME: return "OCI_ATTR_DISTINGUISHED_NAME"; /* 300 */
        case OCI_ATTR_KERBEROS_TICKET: return "OCI_ATTR_KERBEROS_TICKET"; /* 301 */
        case OCI_ATTR_ORA_DEBUG_JDWP: return "OCI_ATTR_ORA_DEBUG_JDWP"; /* 302 */
#ifdef OCI_ATTR_EDITION
        case OCI_ATTR_EDITION: return "OCI_ATTR_EDITION";             /* 288 */
#endif
        }
    }
    switch (attrtype) {
    case OCI_ATTR_FNCODE: return "OCI_ATTR_FNCODE";                   /* 1 */
    case OCI_ATTR_OBJECT: return "OCI_ATTR_OBJECT";                   /* 2 */
    case OCI_ATTR_NONBLOCKING_MODE: return "OCI_ATTR_NONBLOCKING_MODE"; /* 3 */
    case OCI_ATTR_SQLCODE: return "OCI_ATTR_SQLCODE";                 /* 4 */
    case OCI_ATTR_ENV: return "OCI_ATTR_ENV";                         /* 5 */
    case OCI_ATTR_SERVER: return "OCI_ATTR_SERVER";                   /* 6 */
    case OCI_ATTR_SESSION: return "OCI_ATTR_SESSION";                 /* 7 */
    case OCI_ATTR_TRANS: return "OCI_ATTR_TRANS";                     /* 8 */
    case OCI_ATTR_ROW_COUNT: return "OCI_ATTR_ROW_COUNT";             /* 9 */
    case OCI_ATTR_SQLFNCODE: return "OCI_ATTR_SQLFNCODE";             /* 10 */
    case OCI_ATTR_PREFETCH_ROWS: return "OCI_ATTR_PREFETCH_ROWS";     /* 11 */
    case OCI_ATTR_NESTED_PREFETCH_ROWS: return "OCI_ATTR_NESTED_PREFETCH_ROWS"; /* 12 */
    case OCI_ATTR_PREFETCH_MEMORY: return "OCI_ATTR_PREFETCH_MEMORY"; /* 13 */
    case OCI_ATTR_NESTED_PREFETCH_MEMORY: return "OCI_ATTR_NESTED_PREFETCH_MEMORY"; /* 14 */
    case OCI_ATTR_CHAR_COUNT: return "OCI_ATTR_CHAR_COUNT";           /* 15 */
    case OCI_ATTR_PDSCL: return "OCI_ATTR_PDSCL or OCI_ATTR_FSPRECISION"; /* 16 */
    case OCI_ATTR_PDPRC: return "OCI_ATTR_PDPRC or OCI_ATTR_LFPRECISION"; /* 17 */
    case OCI_ATTR_PARAM_COUNT: return "OCI_ATTR_PARAM_COUNT";         /* 18 */
    case OCI_ATTR_ROWID: return "OCI_ATTR_ROWID";                     /* 19 */
    case OCI_ATTR_CHARSET: return "OCI_ATTR_CHARSET";                 /* 20 */
    case OCI_ATTR_NCHAR: return "OCI_ATTR_NCHAR";                     /* 21 */
    case OCI_ATTR_USERNAME: return "OCI_ATTR_USERNAME";               /* 22 */
    case OCI_ATTR_PASSWORD: return "OCI_ATTR_PASSWORD";               /* 23 */
    case OCI_ATTR_STMT_TYPE: return "OCI_ATTR_STMT_TYPE";             /* 24 */
    case OCI_ATTR_INTERNAL_NAME: return "OCI_ATTR_INTERNAL_NAME";     /* 25 */
    case OCI_ATTR_EXTERNAL_NAME: return "OCI_ATTR_EXTERNAL_NAME";     /* 26 */
    case OCI_ATTR_XID: return "OCI_ATTR_XID";                         /* 27 */
    case OCI_ATTR_TRANS_LOCK: return "OCI_ATTR_TRANS_LOCK";           /* 28 */
    case OCI_ATTR_TRANS_NAME: return "OCI_ATTR_TRANS_NAME";           /* 29 */
    case OCI_ATTR_HEAPALLOC: return "OCI_ATTR_HEAPALLOC";             /* 30 */
    case OCI_ATTR_CHARSET_ID: return "OCI_ATTR_CHARSET_ID or OCI_ATTR_ENV_CHARSET_ID"; /* 31 */
    case OCI_ATTR_CHARSET_FORM: return "OCI_ATTR_CHARSET_FORM";       /* 32 */
    case OCI_ATTR_MAXDATA_SIZE: return "OCI_ATTR_MAXDATA_SIZE";       /* 33 */
    case OCI_ATTR_CACHE_OPT_SIZE: return "OCI_ATTR_CACHE_OPT_SIZE";   /* 34 */
    case OCI_ATTR_CACHE_MAX_SIZE: return "OCI_ATTR_CACHE_MAX_SIZE";   /* 35 */
    case OCI_ATTR_PINOPTION: return "OCI_ATTR_PINOPTION";             /* 36 */
    case OCI_ATTR_ALLOC_DURATION: return "OCI_ATTR_ALLOC_DURATION";   /* 37 */
    case OCI_ATTR_PIN_DURATION: return "OCI_ATTR_PIN_DURATION";       /* 38 */
    case OCI_ATTR_FDO: return "OCI_ATTR_FDO";                         /* 39 */
    case OCI_ATTR_POSTPROCESSING_CALLBACK: return "OCI_ATTR_POSTPROCESSING_CALLBACK"; /* 40 */
    case OCI_ATTR_POSTPROCESSING_CONTEXT: return "OCI_ATTR_POSTPROCESSING_CONTEXT"; /* 41 */
    case OCI_ATTR_ROWS_RETURNED: return "OCI_ATTR_ROWS_RETURNED";     /* 42 */
    case OCI_ATTR_FOCBK: return "OCI_ATTR_FOCBK";                     /* 43 */
    case OCI_ATTR_IN_V8_MODE: return "OCI_ATTR_IN_V8_MODE";           /* 44 */
    case OCI_ATTR_LOBEMPTY: return "OCI_ATTR_LOBEMPTY";               /* 45 */
    case OCI_ATTR_SESSLANG: return "OCI_ATTR_SESSLANG";               /* 46 */
    case OCI_ATTR_VISIBILITY: return "OCI_ATTR_VISIBILITY";           /* 47 */
    case OCI_ATTR_RELATIVE_MSGID: return "OCI_ATTR_RELATIVE_MSGID";   /* 48 */
    case OCI_ATTR_SEQUENCE_DEVIATION: return "OCI_ATTR_SEQUENCE_DEVIATION"; /* 49 */
    case OCI_ATTR_CONSUMER_NAME: return "OCI_ATTR_CONSUMER_NAME";     /* 50 */
    case OCI_ATTR_DEQ_MODE: return "OCI_ATTR_DEQ_MODE";               /* 51 */
    case OCI_ATTR_NAVIGATION: return "OCI_ATTR_NAVIGATION";           /* 52 */
    case OCI_ATTR_WAIT: return "OCI_ATTR_WAIT";                       /* 53 */
    case OCI_ATTR_DEQ_MSGID: return "OCI_ATTR_DEQ_MSGID";             /* 54 */
    case OCI_ATTR_PRIORITY: return "OCI_ATTR_PRIORITY";               /* 55 */
    case OCI_ATTR_DELAY: return "OCI_ATTR_DELAY";                     /* 56 */
    case OCI_ATTR_EXPIRATION: return "OCI_ATTR_EXPIRATION";           /* 57 */
    case OCI_ATTR_CORRELATION: return "OCI_ATTR_CORRELATION";         /* 58 */
    case OCI_ATTR_ATTEMPTS: return "OCI_ATTR_ATTEMPTS";               /* 59 */
    case OCI_ATTR_RECIPIENT_LIST: return "OCI_ATTR_RECIPIENT_LIST";   /* 60 */
    case OCI_ATTR_EXCEPTION_QUEUE: return "OCI_ATTR_EXCEPTION_QUEUE"; /* 61 */
    case OCI_ATTR_ENQ_TIME: return "OCI_ATTR_ENQ_TIME";               /* 62 */
    case OCI_ATTR_MSG_STATE: return "OCI_ATTR_MSG_STATE";             /* 63 */
    case OCI_ATTR_AGENT_NAME: return "OCI_ATTR_AGENT_NAME";           /* 64 */
    case OCI_ATTR_AGENT_ADDRESS: return "OCI_ATTR_AGENT_ADDRESS";     /* 65 */
    case OCI_ATTR_AGENT_PROTOCOL: return "OCI_ATTR_AGENT_PROTOCOL";   /* 66 */
    case OCI_ATTR_USER_PROPERTY: return "OCI_ATTR_USER_PROPERTY";     /* 67 */
    case OCI_ATTR_SENDER_ID: return "OCI_ATTR_SENDER_ID";             /* 68 */
    case OCI_ATTR_ORIGINAL_MSGID: return "OCI_ATTR_ORIGINAL_MSGID";   /* 69 */
    case OCI_ATTR_QUEUE_NAME: return "OCI_ATTR_QUEUE_NAME";           /* 70 */
    case OCI_ATTR_NFY_MSGID: return "OCI_ATTR_NFY_MSGID";             /* 71 */
    case OCI_ATTR_MSG_PROP: return "OCI_ATTR_MSG_PROP";               /* 72 */
    case OCI_ATTR_NUM_DML_ERRORS: return "OCI_ATTR_NUM_DML_ERRORS or OCI_ATTR_AQ_NUM_ERRORS"; /* 73 */
    case OCI_ATTR_DML_ROW_OFFSET: return "OCI_ATTR_DML_ROW_OFFSET or OCI_ATTR_AQ_ERROR_INDEX"; /* 74 */
    case OCI_ATTR_DATEFORMAT: return "OCI_ATTR_DATEFORMAT";           /* 75 */
    case OCI_ATTR_BUF_ADDR: return "OCI_ATTR_BUF_ADDR";               /* 76 */
    case OCI_ATTR_BUF_SIZE: return "OCI_ATTR_BUF_SIZE";               /* 77 */
    case OCI_ATTR_DIRPATH_MODE: return "OCI_ATTR_DIRPATH_MODE";       /* 78 */
    case OCI_ATTR_DIRPATH_NOLOG: return "OCI_ATTR_DIRPATH_NOLOG";     /* 79 */
    case OCI_ATTR_DIRPATH_PARALLEL: return "OCI_ATTR_DIRPATH_PARALLEL"; /* 80 */
    case OCI_ATTR_NUM_ROWS: return "OCI_ATTR_NUM_ROWS";               /* 81 */
    case OCI_ATTR_COL_COUNT: return "OCI_ATTR_COL_COUNT";             /* 82 */
    case OCI_ATTR_STREAM_OFFSET: return "OCI_ATTR_STREAM_OFFSET";     /* 83 */
    case OCI_ATTR_SHARED_HEAPALLOC: return "OCI_ATTR_SHARED_HEAPALLOC"; /* 84 */
    case OCI_ATTR_SERVER_GROUP: return "OCI_ATTR_SERVER_GROUP";       /* 85 */
    case OCI_ATTR_MIGSESSION: return "OCI_ATTR_MIGSESSION";           /* 86 */
    case OCI_ATTR_NOCACHE: return "OCI_ATTR_NOCACHE";                 /* 87 */
    case OCI_ATTR_MEMPOOL_SIZE: return "OCI_ATTR_MEMPOOL_SIZE";       /* 88 */
    case OCI_ATTR_MEMPOOL_INSTNAME: return "OCI_ATTR_MEMPOOL_INSTNAME"; /* 89 */
    case OCI_ATTR_MEMPOOL_APPNAME: return "OCI_ATTR_MEMPOOL_APPNAME"; /* 90 */
    case OCI_ATTR_MEMPOOL_HOMENAME: return "OCI_ATTR_MEMPOOL_HOMENAME"; /* 91 */
    case OCI_ATTR_MEMPOOL_MODEL: return "OCI_ATTR_MEMPOOL_MODEL";     /* 92 */
    case OCI_ATTR_MODES: return "OCI_ATTR_MODES";                     /* 93 */
    case OCI_ATTR_SUBSCR_NAME: return "OCI_ATTR_SUBSCR_NAME";         /* 94 */
    case OCI_ATTR_SUBSCR_CALLBACK: return "OCI_ATTR_SUBSCR_CALLBACK"; /* 95 */
    case OCI_ATTR_SUBSCR_CTX: return "OCI_ATTR_SUBSCR_CTX";           /* 96 */
    case OCI_ATTR_SUBSCR_PAYLOAD: return "OCI_ATTR_SUBSCR_PAYLOAD";   /* 97 */
    case OCI_ATTR_SUBSCR_NAMESPACE: return "OCI_ATTR_SUBSCR_NAMESPACE"; /* 98 */
    case OCI_ATTR_PROXY_CREDENTIALS: return "OCI_ATTR_PROXY_CREDENTIALS"; /* 99 */
    case OCI_ATTR_INITIAL_CLIENT_ROLES: return "OCI_ATTR_INITIAL_CLIENT_ROLES"; /* 100 */
    case OCI_ATTR_UNK: return "OCI_ATTR_UNK";                         /* 101 */
    case OCI_ATTR_NUM_COLS: return "OCI_ATTR_NUM_COLS";               /* 102 */
    case OCI_ATTR_LIST_COLUMNS: return "OCI_ATTR_LIST_COLUMNS";       /* 103 */
    case OCI_ATTR_RDBA: return "OCI_ATTR_RDBA";                       /* 104 */
    case OCI_ATTR_CLUSTERED: return "OCI_ATTR_CLUSTERED";             /* 105 */
    case OCI_ATTR_PARTITIONED: return "OCI_ATTR_PARTITIONED";         /* 106 */
    case OCI_ATTR_INDEX_ONLY: return "OCI_ATTR_INDEX_ONLY";           /* 107 */
    case OCI_ATTR_LIST_ARGUMENTS: return "OCI_ATTR_LIST_ARGUMENTS";   /* 108 */
    case OCI_ATTR_LIST_SUBPROGRAMS: return "OCI_ATTR_LIST_SUBPROGRAMS"; /* 109 */
    case OCI_ATTR_REF_TDO: return "OCI_ATTR_REF_TDO";                 /* 110 */
    case OCI_ATTR_LINK: return "OCI_ATTR_LINK";                       /* 111 */
    case OCI_ATTR_MIN: return "OCI_ATTR_MIN";                         /* 112 */
    case OCI_ATTR_MAX: return "OCI_ATTR_MAX";                         /* 113 */
    case OCI_ATTR_INCR: return "OCI_ATTR_INCR";                       /* 114 */
    case OCI_ATTR_CACHE: return "OCI_ATTR_CACHE";                     /* 115 */
    case OCI_ATTR_ORDER: return "OCI_ATTR_ORDER";                     /* 116 */
    case OCI_ATTR_HW_MARK: return "OCI_ATTR_HW_MARK";                 /* 117 */
    case OCI_ATTR_TYPE_SCHEMA: return "OCI_ATTR_TYPE_SCHEMA";         /* 118 */
    case OCI_ATTR_TIMESTAMP: return "OCI_ATTR_TIMESTAMP";             /* 119 */
    case OCI_ATTR_NUM_ATTRS: return "OCI_ATTR_NUM_ATTRS";             /* 120 */
    case OCI_ATTR_NUM_PARAMS: return "OCI_ATTR_NUM_PARAMS";           /* 121 */
    case OCI_ATTR_OBJID: return "OCI_ATTR_OBJID";                     /* 122 */
    case OCI_ATTR_PTYPE: return "OCI_ATTR_PTYPE";                     /* 123 */
    case OCI_ATTR_PARAM: return "OCI_ATTR_PARAM";                     /* 124 */
    case OCI_ATTR_OVERLOAD_ID: return "OCI_ATTR_OVERLOAD_ID";         /* 125 */
    case OCI_ATTR_TABLESPACE: return "OCI_ATTR_TABLESPACE";           /* 126 */
    case OCI_ATTR_TDO: return "OCI_ATTR_TDO";                         /* 127 */
    case OCI_ATTR_LTYPE: return "OCI_ATTR_LTYPE";                     /* 128 */
    case OCI_ATTR_PARSE_ERROR_OFFSET: return "OCI_ATTR_PARSE_ERROR_OFFSET"; /* 129 */
    case OCI_ATTR_IS_TEMPORARY: return "OCI_ATTR_IS_TEMPORARY";       /* 130 */
    case OCI_ATTR_IS_TYPED: return "OCI_ATTR_IS_TYPED";               /* 131 */
    case OCI_ATTR_DURATION: return "OCI_ATTR_DURATION";               /* 132 */
    case OCI_ATTR_IS_INVOKER_RIGHTS: return "OCI_ATTR_IS_INVOKER_RIGHTS"; /* 133 */
    case OCI_ATTR_OBJ_NAME: return "OCI_ATTR_OBJ_NAME";               /* 134 */
    case OCI_ATTR_OBJ_SCHEMA: return "OCI_ATTR_OBJ_SCHEMA";           /* 135 */
    case OCI_ATTR_OBJ_ID: return "OCI_ATTR_OBJ_ID";                   /* 136 */
    case OCI_ATTR_DIRPATH_SORTED_INDEX: return "OCI_ATTR_DIRPATH_SORTED_INDEX"; /* 137 */
    case OCI_ATTR_DIRPATH_INDEX_MAINT_METHOD: return "OCI_ATTR_DIRPATH_INDEX_MAINT_METHOD"; /* 138 */
    case OCI_ATTR_DIRPATH_FILE: return "OCI_ATTR_DIRPATH_FILE";       /* 139 */
    case OCI_ATTR_DIRPATH_STORAGE_INITIAL: return "OCI_ATTR_DIRPATH_STORAGE_INITIAL"; /* 140 */
    case OCI_ATTR_DIRPATH_STORAGE_NEXT: return "OCI_ATTR_DIRPATH_STORAGE_NEXT"; /* 141 */
    case OCI_ATTR_TRANS_TIMEOUT: return "OCI_ATTR_TRANS_TIMEOUT";     /* 142 */
    case OCI_ATTR_SERVER_STATUS: return "OCI_ATTR_SERVER_STATUS";     /* 143 */
    case OCI_ATTR_STATEMENT: return "OCI_ATTR_STATEMENT";             /* 144 */
    case OCI_ATTR_DIRPATH_SKIPINDEX_METHOD: return "OCI_ATTR_DIRPATH_SKIPINDEX_METHOD"; /* 145 */
    case OCI_ATTR_DEQCOND: return "OCI_ATTR_DEQCOND";                 /* 146 */
    case OCI_ATTR_SUBSCR_RECPT: return "OCI_ATTR_SUBSCR_RECPT";       /* 148 */
    case OCI_ATTR_SUBSCR_RECPTPROTO: return "OCI_ATTR_SUBSCR_RECPTPROTO"; /* 149 */
    case OCI_ATTR_DIRPATH_EXPR_TYPE: return "OCI_ATTR_DIRPATH_EXPR_TYPE"; /* 150 */
    case OCI_ATTR_DIRPATH_INPUT: return "OCI_ATTR_DIRPATH_INPUT";     /* 151 */
    case OCI_ATTR_LDAP_HOST: return "OCI_ATTR_LDAP_HOST";             /* 153 */
    case OCI_ATTR_LDAP_PORT: return "OCI_ATTR_LDAP_PORT";             /* 154 */
    case OCI_ATTR_BIND_DN: return "OCI_ATTR_BIND_DN";                 /* 155 */
    case OCI_ATTR_LDAP_CRED: return "OCI_ATTR_LDAP_CRED";             /* 156 */
    case OCI_ATTR_WALL_LOC: return "OCI_ATTR_WALL_LOC";               /* 157 */
    case OCI_ATTR_LDAP_AUTH: return "OCI_ATTR_LDAP_AUTH";             /* 158 */
    case OCI_ATTR_LDAP_CTX: return "OCI_ATTR_LDAP_CTX";               /* 159 */
    case OCI_ATTR_SERVER_DNS: return "OCI_ATTR_SERVER_DNS";           /* 160 */
    case OCI_ATTR_DN_COUNT: return "OCI_ATTR_DN_COUNT";               /* 161 */
    case OCI_ATTR_SERVER_DN: return "OCI_ATTR_SERVER_DN";             /* 162 */
    case OCI_ATTR_MAXCHAR_SIZE: return "OCI_ATTR_MAXCHAR_SIZE";       /* 163 */
    case OCI_ATTR_CURRENT_POSITION: return "OCI_ATTR_CURRENT_POSITION"; /* 164 */
    case OCI_ATTR_DIRPATH_FN_CTX: return "OCI_ATTR_DIRPATH_FN_CTX";   /* 167 */
    case OCI_ATTR_DIGEST_ALGO: return "OCI_ATTR_DIGEST_ALGO";         /* 168 */
    case OCI_ATTR_CERTIFICATE: return "OCI_ATTR_CERTIFICATE";         /* 169 */
    case OCI_ATTR_SIGNATURE_ALGO: return "OCI_ATTR_SIGNATURE_ALGO";   /* 170 */
    case OCI_ATTR_CANONICAL_ALGO: return "OCI_ATTR_CANONICAL_ALGO";   /* 171 */
    case OCI_ATTR_PRIVATE_KEY: return "OCI_ATTR_PRIVATE_KEY";         /* 172 */
    case OCI_ATTR_DIGEST_VALUE: return "OCI_ATTR_DIGEST_VALUE";       /* 173 */
    case OCI_ATTR_SIGNATURE_VAL: return "OCI_ATTR_SIGNATURE_VAL";     /* 174 */
    case OCI_ATTR_SIGNATURE: return "OCI_ATTR_SIGNATURE";             /* 175 */
    case OCI_ATTR_STMTCACHESIZE: return "OCI_ATTR_STMTCACHESIZE";     /* 176 */
    case OCI_ATTR_CONN_NOWAIT: return "OCI_ATTR_CONN_NOWAIT";         /* 178 */
    case OCI_ATTR_CONN_BUSY_COUNT: return "OCI_ATTR_CONN_BUSY_COUNT"; /* 179 */
    case OCI_ATTR_CONN_OPEN_COUNT: return "OCI_ATTR_CONN_OPEN_COUNT"; /* 180 */
    case OCI_ATTR_CONN_TIMEOUT: return "OCI_ATTR_CONN_TIMEOUT";       /* 181 */
    case OCI_ATTR_STMT_STATE: return "OCI_ATTR_STMT_STATE";           /* 182 */
    case OCI_ATTR_CONN_MIN: return "OCI_ATTR_CONN_MIN";               /* 183 */
    case OCI_ATTR_CONN_MAX: return "OCI_ATTR_CONN_MAX";               /* 184 */
    case OCI_ATTR_CONN_INCR: return "OCI_ATTR_CONN_INCR";             /* 185 */
    case OCI_ATTR_DIRPATH_OID: return "OCI_ATTR_DIRPATH_OID";         /* 187 */
    case OCI_ATTR_NUM_OPEN_STMTS: return "OCI_ATTR_NUM_OPEN_STMTS";   /* 188 */
    case OCI_ATTR_DESCRIBE_NATIVE: return "OCI_ATTR_DESCRIBE_NATIVE"; /* 189 */
    case OCI_ATTR_BIND_COUNT: return "OCI_ATTR_BIND_COUNT";           /* 190 */
    case OCI_ATTR_HANDLE_POSITION: return "OCI_ATTR_HANDLE_POSITION"; /* 191 */
    case OCI_ATTR_SERVER_BUSY: return "OCI_ATTR_SERVER_BUSY";         /* 193 */
    case OCI_ATTR_DIRPATH_SID: return "OCI_ATTR_DIRPATH_SID";         /* 194 */
    case OCI_ATTR_SUBSCR_RECPTPRES: return "OCI_ATTR_SUBSCR_RECPTPRES"; /* 195 */
    case OCI_ATTR_TRANSFORMATION: return "OCI_ATTR_TRANSFORMATION";   /* 196 */
    case OCI_ATTR_ROWS_FETCHED: return "OCI_ATTR_ROWS_FETCHED";       /* 197 */
    case OCI_ATTR_SCN_BASE: return "OCI_ATTR_SCN_BASE";               /* 198 */
    case OCI_ATTR_SCN_WRAP: return "OCI_ATTR_SCN_WRAP";               /* 199 */
    case OCI_ATTR_READONLY_TXN: return "OCI_ATTR_READONLY_TXN";       /* 201 */
    case OCI_ATTR_ERRONEOUS_COLUMN: return "OCI_ATTR_ERRONEOUS_COLUMN"; /* 203 */
#ifdef OCI_ATTR_ASM_VOL_SPRT
    case OCI_ATTR_ASM_VOL_SPRT: return "OCI_ATTR_ASM_VOL_SPRT";       /* 205 */
#endif
    case OCI_ATTR_DIRPATH_OBJ_CONSTR: return "OCI_ATTR_DIRPATH_OBJ_CONSTR"; /* 206 */
    case OCI_ATTR_INST_TYPE: return "OCI_ATTR_INST_TYPE";             /* 207 */
    case OCI_ATTR_SPOOL_STMTCACHESIZE: return "OCI_ATTR_SPOOL_STMTCACHESIZE"; /* 208 */
    case OCI_ATTR_ENV_UTF16: return "OCI_ATTR_ENV_UTF16";             /* 209 */
    case OCI_ATTR_DIRPATH_STREAM_VERSION: return "OCI_ATTR_DIRPATH_STREAM_VERSION"; /* 212 */
    case OCIP_ATTR_DIRPATH_VARRAY_INDEX: return "OCIP_ATTR_DIRPATH_VARRAY_INDEX"; /* 213 */
    case OCI_ATTR_IS_EXTERNAL: return "OCI_ATTR_IS_EXTERNAL";         /* 216 */
    case OCI_ATTR_STMT_IS_RETURNING: return "OCI_ATTR_STMT_IS_RETURNING"; /* 218 */
    case OCI_ATTR_CURRENT_SCHEMA: return "OCI_ATTR_CURRENT_SCHEMA";   /* 224 */
    case OCI_ATTR_SUBSCR_QOSFLAGS: return "OCI_ATTR_SUBSCR_QOSFLAGS"; /* 225 */
    case OCI_ATTR_SUBSCR_PAYLOADCBK: return "OCI_ATTR_SUBSCR_PAYLOADCBK"; /* 226 */
    case OCI_ATTR_SUBSCR_TIMEOUT: return "OCI_ATTR_SUBSCR_TIMEOUT";   /* 227 */
    case OCI_ATTR_SUBSCR_NAMESPACE_CTX: return "OCI_ATTR_SUBSCR_NAMESPACE_CTX"; /* 228 */
#ifdef OCI_ATTR_SUBSCR_CQ_QOSFLAGS
    case OCI_ATTR_SUBSCR_CQ_QOSFLAGS: return "OCI_ATTR_SUBSCR_CQ_QOSFLAGS"; /* 229 */
#endif
#ifdef OCI_ATTR_SUBSCR_CQ_REGID
    case OCI_ATTR_SUBSCR_CQ_REGID: return "OCI_ATTR_SUBSCR_CQ_REGID"; /* 230 */
#endif
#ifdef OCI_ATTR_SUBSCR_NTFN_GROUPING_CLASS
    case OCI_ATTR_SUBSCR_NTFN_GROUPING_CLASS: return "OCI_ATTR_SUBSCR_NTFN_GROUPING_CLASS"; /* 231 */
#endif
#ifdef OCI_ATTR_SUBSCR_NTFN_GROUPING_VALUE
    case OCI_ATTR_SUBSCR_NTFN_GROUPING_VALUE: return "OCI_ATTR_SUBSCR_NTFN_GROUPING_VALUE"; /* 232 */
#endif
#ifdef OCI_ATTR_SUBSCR_NTFN_GROUPING_TYPE
    case OCI_ATTR_SUBSCR_NTFN_GROUPING_TYPE: return "OCI_ATTR_SUBSCR_NTFN_GROUPING_TYPE"; /* 233 */
#endif
#ifdef OCI_ATTR_SUBSCR_NTFN_GROUPING_START_TIME
    case OCI_ATTR_SUBSCR_NTFN_GROUPING_START_TIME: return "OCI_ATTR_SUBSCR_NTFN_GROUPING_START_TIME"; /* 234 */
#endif
#ifdef OCI_ATTR_SUBSCR_NTFN_GROUPING_REPEAT_COUNT
    case OCI_ATTR_SUBSCR_NTFN_GROUPING_REPEAT_COUNT: return "OCI_ATTR_SUBSCR_NTFN_GROUPING_REPEAT_COUNT"; /* 235 */
#endif
#ifdef OCI_ATTR_AQ_NTFN_GROUPING_MSGID_ARRAY
    case OCI_ATTR_AQ_NTFN_GROUPING_MSGID_ARRAY: return "OCI_ATTR_AQ_NTFN_GROUPING_MSGID_ARRAY"; /* 236 */
#endif
#ifdef OCI_ATTR_AQ_NTFN_GROUPING_COUNT
    case OCI_ATTR_AQ_NTFN_GROUPING_COUNT: return "OCI_ATTR_AQ_NTFN_GROUPING_COUNT"; /* 237 */
#endif
    case OCI_ATTR_BIND_ROWCBK: return "OCI_ATTR_BIND_ROWCBK";         /* 301 */
    case OCI_ATTR_BIND_ROWCTX: return "OCI_ATTR_BIND_ROWCTX";         /* 302 */
    case OCI_ATTR_SKIP_BUFFER: return "OCI_ATTR_SKIP_BUFFER or OCI_ATTR_DIRPATH_DCACHE_NUM"; /* 303 */
    case OCI_ATTR_EVTCBK: return "OCI_ATTR_EVTCBK or OCI_ATTR_DIRPATH_DCACHE_SIZE or OCI_ATTR_CQ_QUERYID"; /* 304 */
    case OCI_ATTR_EVTCTX: return "OCI_ATTR_EVTCTX or OCI_ATTR_DIRPATH_DCACHE_MISSES"; /* 305 */
    case OCI_ATTR_USER_MEMORY: return "OCI_ATTR_USER_MEMORY or OCI_ATTR_DIRPATH_DCACHE_HITS"; /* 306 */
    case OCI_ATTR_DIRPATH_DCACHE_DISABLE: return "OCI_ATTR_DIRPATH_DCACHE_DISABLE or OCI_ATTR_ACCESS_BANNER"; /* 307 */
    case OCI_ATTR_SUBSCR_PORTNO: return "OCI_ATTR_SUBSCR_PORTNO or OCI_ATTR_HOSTNAME"; /* 390 */
    case OCI_ATTR_SPOOL_TIMEOUT: return "OCI_ATTR_SPOOL_TIMEOUT or OCI_ATTR_AUDIT_BANNER"; /* 308 */
    case OCI_ATTR_SPOOL_GETMODE: return "OCI_ATTR_SPOOL_GETMODE";     /* 309 */
    case OCI_ATTR_SPOOL_BUSY_COUNT: return "OCI_ATTR_SPOOL_BUSY_COUNT"; /* 310 */
    case OCI_ATTR_SPOOL_OPEN_COUNT: return "OCI_ATTR_SPOOL_OPEN_COUNT"; /* 311 */
    case OCI_ATTR_SPOOL_MIN: return "OCI_ATTR_SPOOL_MIN";             /* 312 */
    case OCI_ATTR_SPOOL_MAX: return "OCI_ATTR_SPOOL_MAX";             /* 313 */
    case OCI_ATTR_SPOOL_INCR: return "OCI_ATTR_SPOOL_INCR";           /* 314 */
    case OCI_ATTR_IS_XMLTYPE: return "OCI_ATTR_IS_XMLTYPE";           /* 315 */
    case OCI_ATTR_XMLSCHEMA_NAME: return "OCI_ATTR_XMLSCHEMA_NAME";   /* 316 */
    case OCI_ATTR_XMLELEMENT_NAME: return "OCI_ATTR_XMLELEMENT_NAME"; /* 317 */
    case OCI_ATTR_XMLSQLTYPSCH_NAME: return "OCI_ATTR_XMLSQLTYPSCH_NAME"; /* 318 */
    case OCI_ATTR_XMLSQLTYPE_NAME: return "OCI_ATTR_XMLSQLTYPE_NAME"; /* 319 */
    case OCI_ATTR_XMLTYPE_STORED_OBJ: return "OCI_ATTR_XMLTYPE_STORED_OBJ"; /* 320 */
    case OCI_ATTR_HAS_SUBTYPES: return "OCI_ATTR_HAS_SUBTYPES";       /* 321 */
    case OCI_ATTR_NUM_SUBTYPES: return "OCI_ATTR_NUM_SUBTYPES";       /* 322 */
    case OCI_ATTR_LIST_SUBTYPES: return "OCI_ATTR_LIST_SUBTYPES";     /* 323 */
    case OCI_ATTR_XML_HRCHY_ENABLED: return "OCI_ATTR_XML_HRCHY_ENABLED"; /* 324 */
    case OCI_ATTR_IS_OVERRIDDEN_METHOD: return "OCI_ATTR_IS_OVERRIDDEN_METHOD"; /* 325 */
    case OCI_ATTR_DIRPATH_CONVERT: return "OCI_ATTR_DIRPATH_CONVERT"; /* 328 */
    case OCI_ATTR_DIRPATH_BADROW: return "OCI_ATTR_DIRPATH_BADROW";   /* 329 */
    case OCI_ATTR_DIRPATH_BADROW_LENGTH: return "OCI_ATTR_DIRPATH_BADROW_LENGTH"; /* 330 */
    case OCI_ATTR_DIRPATH_WRITE_ORDER: return "OCI_ATTR_DIRPATH_WRITE_ORDER"; /* 331 */
    case OCI_ATTR_DIRPATH_GRANULE_SIZE: return "OCI_ATTR_DIRPATH_GRANULE_SIZE"; /* 332 */
    case OCI_ATTR_DIRPATH_GRANULE_OFFSET: return "OCI_ATTR_DIRPATH_GRANULE_OFFSET"; /* 333 */
    case OCI_ATTR_OBJ_SUBS: return "OCI_ATTR_OBJ_SUBS";               /* 336 */
    case OCI_ATTR_KERBEROS_CID: return "OCI_ATTR_KERBEROS_CID";       /* 341 */
    case OCI_ATTR_CONDITION: return "OCI_ATTR_CONDITION";             /* 342 */
    case OCI_ATTR_COMMENT: return "OCI_ATTR_COMMENT";                 /* 343 */
    case OCI_ATTR_VALUE: return "OCI_ATTR_VALUE";                     /* 344 */
    case OCI_ATTR_EVAL_CONTEXT_OWNER: return "OCI_ATTR_EVAL_CONTEXT_OWNER"; /* 345 */
    case OCI_ATTR_EVAL_CONTEXT_NAME: return "OCI_ATTR_EVAL_CONTEXT_NAME"; /* 346 */
    case OCI_ATTR_EVALUATION_FUNCTION: return "OCI_ATTR_EVALUATION_FUNCTION"; /* 347 */
    case OCI_ATTR_VAR_TYPE: return "OCI_ATTR_VAR_TYPE";               /* 348 */
    case OCI_ATTR_VAR_VALUE_FUNCTION: return "OCI_ATTR_VAR_VALUE_FUNCTION"; /* 349 */
    case OCI_ATTR_VAR_METHOD_FUNCTION: return "OCI_ATTR_VAR_METHOD_FUNCTION"; /* 350 */
    case OCI_ATTR_ACTION_CONTEXT: return "OCI_ATTR_ACTION_CONTEXT"; /* 351 */
    case OCI_ATTR_LIST_TABLE_ALIASES: return "OCI_ATTR_LIST_TABLE_ALIASES"; /* 352 */
    case OCI_ATTR_LIST_VARIABLE_TYPES: return "OCI_ATTR_LIST_VARIABLE_TYPES"; /* 353 */
    case OCI_ATTR_TABLE_NAME: return "OCI_ATTR_TABLE_NAME";           /* 356 */
    case OCI_ATTR_DIRPATH_LOCK_WAIT: return "OCI_ATTR_DIRPATH_LOCK_WAIT"; /* 359 */
    case OCI_ATTR_MESSAGE_CSCN: return "OCI_ATTR_MESSAGE_CSCN";       /* 360 */
    case OCI_ATTR_MESSAGE_DSCN: return "OCI_ATTR_MESSAGE_DSCN";       /* 361 */
    case OCI_ATTR_AUDIT_SESSION_ID: return "OCI_ATTR_AUDIT_SESSION_ID"; /* 362 */
    case OCI_ATTR_KERBEROS_KEY: return "OCI_ATTR_KERBEROS_KEY";       /* 363 */
    case OCI_ATTR_KERBEROS_CID_KEY: return "OCI_ATTR_KERBEROS_CID_KEY"; /* 364 */
    case OCI_ATTR_TRANSACTION_NO: return "OCI_ATTR_TRANSACTION_NO";   /* 365 */
    case OCI_ATTR_MODULE: return "OCI_ATTR_MODULE";                   /* 366 */
    case OCI_ATTR_ACTION: return "OCI_ATTR_ACTION";                   /* 367 */
    case OCI_ATTR_CLIENT_INFO: return "OCI_ATTR_CLIENT_INFO";         /* 368 */
    case OCI_ATTR_COLLECT_CALL_TIME: return "OCI_ATTR_COLLECT_CALL_TIME"; /* 369 */
    case OCI_ATTR_CALL_TIME: return "OCI_ATTR_CALL_TIME";             /* 370 */
    case OCI_ATTR_ECONTEXT_ID: return "OCI_ATTR_ECONTEXT_ID";         /* 371 */
    case OCI_ATTR_ECONTEXT_SEQ: return "OCI_ATTR_ECONTEXT_SEQ";       /* 372 */
    case OCI_ATTR_SESSION_STATE: return "OCI_ATTR_SESSION_STATE";     /* 373 */
    case OCI_ATTR_SESSION_STATETYPE: return "OCI_ATTR_SESSION_STATETYPE"; /* 374 */
    case OCI_ATTR_SESSION_STATE_CLEARED: return "OCI_ATTR_SESSION_STATE_CLEARED"; /* 376 */
    case OCI_ATTR_SESSION_MIGRATED: return "OCI_ATTR_SESSION_MIGRATED"; /* 377 */
    case OCI_ATTR_SESSION_PRESERVE_STATE: return "OCI_ATTR_SESSION_PRESERVE_STATE"; /* 388 */
    case OCI_ATTR_ADMIN_PFILE: return "OCI_ATTR_ADMIN_PFILE";         /* 389 */
    case OCI_ATTR_DBNAME: return "OCI_ATTR_DBNAME";                   /* 391 */
    case OCI_ATTR_INSTNAME: return "OCI_ATTR_INSTNAME";               /* 392 */
    case OCI_ATTR_SERVICENAME: return "OCI_ATTR_SERVICENAME";         /* 393 */
    case OCI_ATTR_INSTSTARTTIME: return "OCI_ATTR_INSTSTARTTIME";     /* 394 */
    case OCI_ATTR_HA_TIMESTAMP: return "OCI_ATTR_HA_TIMESTAMP";       /* 395 */
    case OCI_ATTR_DBDOMAIN: return "OCI_ATTR_DBDOMAIN";               /* 399 */
    case OCI_ATTR_EVENTTYPE: return "OCI_ATTR_EVENTTYPE";             /* 400 */
    case OCI_ATTR_CHNF_TABLENAMES: return "OCI_ATTR_CHNF_TABLENAMES or OCI_ATTR_HA_SOURCE"; /* 401 */
    case OCI_ATTR_CHNF_ROWIDS: return "OCI_ATTR_CHNF_ROWIDS or OCI_ATTR_HA_STATUS"; /* 402 */
    case OCI_ATTR_CHNF_OPERATIONS: return "OCI_ATTR_CHNF_OPERATIONS or OCI_ATTR_HA_SRVFIRST"; /* 403 */
    case OCI_ATTR_CHNF_CHANGELAG: return "OCI_ATTR_CHNF_CHANGELAG or OCI_ATTR_HA_SRVNEXT"; /* 404 */
    case OCI_ATTR_CHDES_DBNAME: return "OCI_ATTR_CHDES_DBNAME or OCI_ATTR_TAF_ENABLED"; /* 405 */
    case OCI_ATTR_CHDES_NFYTYPE: return "OCI_ATTR_CHDES_NFYTYPE or OCI_ATTR_NFY_FLAGS"; /* 406 */
    case OCI_ATTR_CHDES_XID: return "OCI_ATTR_CHDES_XID or OCI_ATTR_MSG_DELIVERY_MODE"; /* 407 */
    case OCI_ATTR_CHDES_TABLE_CHANGES: return "OCI_ATTR_CHDES_TABLE_CHANGES"; /* 408 */
    case OCI_ATTR_CHDES_TABLE_NAME: return "OCI_ATTR_CHDES_TABLE_NAME"; /* 409 */
    case OCI_ATTR_CHDES_TABLE_OPFLAGS: return "OCI_ATTR_CHDES_TABLE_OPFLAGS"; /* 410 */
    case OCI_ATTR_CHDES_TABLE_ROW_CHANGES: return "OCI_ATTR_CHDES_TABLE_ROW_CHANGES"; /* 411 */
    case OCI_ATTR_CHDES_ROW_ROWID: return "OCI_ATTR_CHDES_ROW_ROWID";                        /* 412 */
    case OCI_ATTR_CHDES_ROW_OPFLAGS: return "OCI_ATTR_CHDES_ROW_OPFLAGS"; /* 413 */
    case OCI_ATTR_CHNF_REGHANDLE: return "OCI_ATTR_CHNF_REGHANDLE";   /* 414 */
#ifdef OCI_ATTR_NETWORK_FILE_DESC
    case OCI_ATTR_NETWORK_FILE_DESC: return "OCI_ATTR_NETWORK_FILE_DESC"; /* 415 */
#endif
    case OCI_ATTR_PROXY_CLIENT: return "OCI_ATTR_PROXY_CLIENT or OCI_ATTR_DB_CHARSET_ID"; /* 416 */
    case OCI_ATTR_TABLE_ENC: return "OCI_ATTR_TABLE_ENC or OCI_ATTR_DB_NCHARSET_ID"; /* 417 */
    case OCI_ATTR_TABLE_ENC_ALG: return "OCI_ATTR_TABLE_ENC_ALG";                        /* 418 */
    case OCI_ATTR_TABLE_ENC_ALG_ID: return "OCI_ATTR_TABLE_ENC_ALG_ID"; /* 419 */
    case OCI_ATTR_STMTCACHE_CBKCTX: return "OCI_ATTR_STMTCACHE_CBKCTX"; /* 420 */
    case OCI_ATTR_STMTCACHE_CBK: return "OCI_ATTR_STMTCACHE_CBK";                        /* 421 */
#if defined OCI_ATTR_CQDES_OPERATION || defined OCI_ATTR_XMLTYPE_BINARY_XML
    case OCI_ATTR_CQDES_OPERATION: return "OCI_ATTR_CQDES_OPERATION or OCI_ATTR_XMLTYPE_BINARY_XML"; /* 422 */
#endif
#if defined OCI_ATTR_CQDES_TABLE_CHANGES || defined OCI_ATTR_FLOW_CONTROL_TIMEOUT
    case OCI_ATTR_CQDES_TABLE_CHANGES: return "OCI_ATTR_CQDES_TABLE_CHANGES or OCI_ATTR_FLOW_CONTROL_TIMEOUT"; /* 423 */
#endif
#if defined OCI_ATTR_CQDES_QUERYID || defined OCI_ATTR_DRIVER_NAME
    case OCI_ATTR_CQDES_QUERYID: return "OCI_ATTR_CQDES_QUERYID or OCI_ATTR_DRIVER_NAME"; /* 424 */
#endif
#if defined OCI_ATTR_CHDES_QUERIES || defined OCI_ATTR_CONNECTION_CLASS
    case OCI_ATTR_CHDES_QUERIES: return "OCI_ATTR_CHDES_QUERIES or OCI_ATTR_CONNECTION_CLASS"; /* 425 */
#endif
#ifdef OCI_ATTR_PURITY
    case OCI_ATTR_PURITY: return "OCI_ATTR_PURITY";                   /* 426 */
#endif
#ifdef OCI_ATTR_SEND_TIMEOUT
    case OCI_ATTR_SEND_TIMEOUT: return "OCI_ATTR_SEND_TIMEOUT";       /* 435 */
#endif
#ifdef OCI_ATTR_RECEIVE_TIMEOUT
    case OCI_ATTR_RECEIVE_TIMEOUT: return "OCI_ATTR_RECEIVE_TIMEOUT"; /* 436 */
#endif
#ifdef OCI_ATTR_DEFAULT_LOBPREFETCH_SIZE
    case OCI_ATTR_DEFAULT_LOBPREFETCH_SIZE: return "OCI_ATTR_DEFAULT_LOBPREFETCH_SIZE"; /* 438 */
#endif
#ifdef OCI_ATTR_LOBPREFETCH_SIZE
    case OCI_ATTR_LOBPREFETCH_SIZE: return "OCI_ATTR_LOBPREFETCH_SIZE"; /* 439 */
#endif
#ifdef OCI_ATTR_LOBPREFETCH_LENGTH
    case OCI_ATTR_LOBPREFETCH_LENGTH: return "OCI_ATTR_LOBPREFETCH_LENGTH"; /* 440 */
#endif
#ifdef OCI_ATTR_LOB_REGION_PRIMARY
    case OCI_ATTR_LOB_REGION_PRIMARY: return "OCI_ATTR_LOB_REGION_PRIMARY"; /* 442 */
#endif
#ifdef OCI_ATTR_LOB_REGION_PRIMOFF
    case OCI_ATTR_LOB_REGION_PRIMOFF: return "OCI_ATTR_LOB_REGION_PRIMOFF"; /* 443 */
#endif
#ifdef OCI_ATTR_LOB_REGION_OFFSET
    case OCI_ATTR_LOB_REGION_OFFSET: return "OCI_ATTR_LOB_REGION_OFFSET"; /* 445 */
#endif
#ifdef OCI_ATTR_LOB_REGION_LENGTH
    case OCI_ATTR_LOB_REGION_LENGTH: return "OCI_ATTR_LOB_REGION_LENGTH"; /* 446 */
#endif
#ifdef OCI_ATTR_LOB_REGION_MIME
    case OCI_ATTR_LOB_REGION_MIME: return "OCI_ATTR_LOB_REGION_MIME"; /* 447 */
#endif
#ifdef OCI_ATTR_FETCH_ROWID
    case OCI_ATTR_FETCH_ROWID: return "OCI_ATTR_FETCH_ROWID";         /* 448 */
#endif
    case OCI_ATTR_CURRENT_ERRCOL: return "OCI_ATTR_CURRENT_ERRCOL";   /* 2003 */
#ifdef OCI_ATTR_DIRPATH_SUBTYPE_INDEX
    case OCI_ATTR_DIRPATH_SUBTYPE_INDEX: return "OCI_ATTR_DIRPATH_SUBTYPE_INDEX"; /* 2004 */
#endif
    }
    sprintf(buf, "%u", attrtype);
    return buf;
}

const char *ocidump_sprintf(char *buf, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vsprintf(buf, fmt, ap);
    va_end(ap);
    return buf;
}

void ocidump_log(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(logfp, fmt, ap);
    va_end(ap);
}
