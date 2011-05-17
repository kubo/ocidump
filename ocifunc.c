/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/*
 * This file was created by mkocifunc.rb
 * Don't edit this file manually.
 */
#include <stdlib.h>
#include <dlfcn.h>
#include <pthread.h>
#include "ocidump.h"

static int is_initialized;
static void initialize(void);


typedef sword (*OCIAnyDataAccess_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCIAnyData *sdata, OCITypeCode tc, OCIType *type, void *ind, void *attr_val, ub4 *length);
static OCIAnyDataAccess_func_t OCIAnyDataAccess_func;
static int trace_OCIAnyDataAccess = 1;

sword OCIAnyDataAccess(OCISvcCtx *svchp, OCIError *errhp, OCIAnyData *sdata, OCITypeCode tc, OCIType *type, void *ind, void *attr_val, ub4 *length)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIAnyDataAccess_func(svchp, errhp, sdata, tc, type, ind, attr_val, length);
    if (trace_OCIAnyDataAccess) {
        ocidump_log("%0*lX: OCIAnyDataAccess(%p, %p, %p, %u, %p, %p, %p, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     sdata,
                     tc,
                     type,
                     ind,
                     attr_val,
                     length ? ocidump_sprintf(buf1, "[%u]", *length) : "(nil)",
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCIAnyDataAttrGet_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCIAnyData *sdata, OCITypeCode tc, OCIType *type, void *ind, void *attr_val, ub4 *length, boolean is_any);
static OCIAnyDataAttrGet_func_t OCIAnyDataAttrGet_func;
static int trace_OCIAnyDataAttrGet = 1;

sword OCIAnyDataAttrGet(OCISvcCtx *svchp, OCIError *errhp, OCIAnyData *sdata, OCITypeCode tc, OCIType *type, void *ind, void *attr_val, ub4 *length, boolean is_any)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIAnyDataAttrGet_func(svchp, errhp, sdata, tc, type, ind, attr_val, length, is_any);
    if (trace_OCIAnyDataAttrGet) {
        ocidump_log("%0*lX: OCIAnyDataAttrGet(%p, %p, %p, %u, %p, %p, %p, %s, %d) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     sdata,
                     tc,
                     type,
                     ind,
                     attr_val,
                     length ? ocidump_sprintf(buf1, "[%u]", *length) : "(nil)",
                     is_any,
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCIAnyDataAttrSet_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCIAnyData *sdata, OCITypeCode tc, OCIType *type, void *ind, void *attr_val, ub4 length, boolean is_any);
static OCIAnyDataAttrSet_func_t OCIAnyDataAttrSet_func;
static int trace_OCIAnyDataAttrSet = 1;

sword OCIAnyDataAttrSet(OCISvcCtx *svchp, OCIError *errhp, OCIAnyData *sdata, OCITypeCode tc, OCIType *type, void *ind, void *attr_val, ub4 length, boolean is_any)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIAnyDataAttrSet_func(svchp, errhp, sdata, tc, type, ind, attr_val, length, is_any);
    if (trace_OCIAnyDataAttrSet) {
        ocidump_log("%0*lX: OCIAnyDataAttrSet(%p, %p, %p, %u, %p, %p, %p, %u, %d) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     sdata,
                     tc,
                     type,
                     ind,
                     attr_val,
                     length,
                     is_any,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIAnyDataBeginCreate_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCITypeCode tc, OCIType *type, OCIDuration dur, OCIAnyData **sdata);
static OCIAnyDataBeginCreate_func_t OCIAnyDataBeginCreate_func;
static int trace_OCIAnyDataBeginCreate = 1;

sword OCIAnyDataBeginCreate(OCISvcCtx *svchp, OCIError *errhp, OCITypeCode tc, OCIType *type, OCIDuration dur, OCIAnyData **sdata)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIAnyDataBeginCreate_func(svchp, errhp, tc, type, dur, sdata);
    if (trace_OCIAnyDataBeginCreate) {
        ocidump_log("%0*lX: OCIAnyDataBeginCreate(%p, %p, %u, %p, %u, [%p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     tc,
                     type,
                     dur,
                     *sdata,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIAnyDataCollAddElem_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCIAnyData *sdata, OCITypeCode tc, OCIType *type, void *ind, void *attr_val, ub4 length, boolean is_any, boolean last_elem);
static OCIAnyDataCollAddElem_func_t OCIAnyDataCollAddElem_func;
static int trace_OCIAnyDataCollAddElem = 1;

sword OCIAnyDataCollAddElem(OCISvcCtx *svchp, OCIError *errhp, OCIAnyData *sdata, OCITypeCode tc, OCIType *type, void *ind, void *attr_val, ub4 length, boolean is_any, boolean last_elem)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIAnyDataCollAddElem_func(svchp, errhp, sdata, tc, type, ind, attr_val, length, is_any, last_elem);
    if (trace_OCIAnyDataCollAddElem) {
        ocidump_log("%0*lX: OCIAnyDataCollAddElem(%p, %p, %p, %u, %p, %p, %p, %u, %d, %d) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     sdata,
                     tc,
                     type,
                     ind,
                     attr_val,
                     length,
                     is_any,
                     last_elem,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIAnyDataCollGetElem_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCIAnyData *sdata, OCITypeCode tc, OCIType *type, void *ind, void *celem_val, ub4 *length, boolean is_any);
static OCIAnyDataCollGetElem_func_t OCIAnyDataCollGetElem_func;
static int trace_OCIAnyDataCollGetElem = 1;

sword OCIAnyDataCollGetElem(OCISvcCtx *svchp, OCIError *errhp, OCIAnyData *sdata, OCITypeCode tc, OCIType *type, void *ind, void *celem_val, ub4 *length, boolean is_any)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIAnyDataCollGetElem_func(svchp, errhp, sdata, tc, type, ind, celem_val, length, is_any);
    if (trace_OCIAnyDataCollGetElem) {
        ocidump_log("%0*lX: OCIAnyDataCollGetElem(%p, %p, %p, %u, %p, %p, %p, %s, %d) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     sdata,
                     tc,
                     type,
                     ind,
                     celem_val,
                     length ? ocidump_sprintf(buf1, "[%u]", *length) : "(nil)",
                     is_any,
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCIAnyDataConvert_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCITypeCode tc, OCIType *type, OCIDuration dur, void *ind, void *data_val, ub4 len, OCIAnyData **sdata);
static OCIAnyDataConvert_func_t OCIAnyDataConvert_func;
static int trace_OCIAnyDataConvert = 1;

sword OCIAnyDataConvert(OCISvcCtx *svchp, OCIError *errhp, OCITypeCode tc, OCIType *type, OCIDuration dur, void *ind, void *data_val, ub4 len, OCIAnyData **sdata)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    OCIAnyData *old_sdata = *sdata;

    if (!is_initialized) {
        initialize();
    }
    ret = OCIAnyDataConvert_func(svchp, errhp, tc, type, dur, ind, data_val, len, sdata);
    if (trace_OCIAnyDataConvert) {
        ocidump_log("%0*lX: OCIAnyDataConvert(%p, %p, %u, %p, %u, %p, %p, %u, [%p -> %p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     tc,
                     type,
                     dur,
                     ind,
                     data_val,
                     len,
                     old_sdata, *sdata,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIAnyDataDestroy_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCIAnyData *sdata);
static OCIAnyDataDestroy_func_t OCIAnyDataDestroy_func;
static int trace_OCIAnyDataDestroy = 1;

sword OCIAnyDataDestroy(OCISvcCtx *svchp, OCIError *errhp, OCIAnyData *sdata)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIAnyDataDestroy_func(svchp, errhp, sdata);
    if (trace_OCIAnyDataDestroy) {
        ocidump_log("%0*lX: OCIAnyDataDestroy(%p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     sdata,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIAnyDataEndCreate_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCIAnyData *sdata);
static OCIAnyDataEndCreate_func_t OCIAnyDataEndCreate_func;
static int trace_OCIAnyDataEndCreate = 1;

sword OCIAnyDataEndCreate(OCISvcCtx *svchp, OCIError *errhp, OCIAnyData *sdata)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIAnyDataEndCreate_func(svchp, errhp, sdata);
    if (trace_OCIAnyDataEndCreate) {
        ocidump_log("%0*lX: OCIAnyDataEndCreate(%p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     sdata,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIAnyDataGetCurrAttrNum_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCIAnyData *sdata, ub4 *attrnum);
static OCIAnyDataGetCurrAttrNum_func_t OCIAnyDataGetCurrAttrNum_func;
static int trace_OCIAnyDataGetCurrAttrNum = 1;

sword OCIAnyDataGetCurrAttrNum(OCISvcCtx *svchp, OCIError *errhp, OCIAnyData *sdata, ub4 *attrnum)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIAnyDataGetCurrAttrNum_func(svchp, errhp, sdata, attrnum);
    if (trace_OCIAnyDataGetCurrAttrNum) {
        ocidump_log("%0*lX: OCIAnyDataGetCurrAttrNum(%p, %p, %p, [%u]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     sdata,
                     *attrnum,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIAnyDataGetType_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCIAnyData *sdata, OCITypeCode *tc, OCIType **type);
static OCIAnyDataGetType_func_t OCIAnyDataGetType_func;
static int trace_OCIAnyDataGetType = 1;

sword OCIAnyDataGetType(OCISvcCtx *svchp, OCIError *errhp, OCIAnyData *sdata, OCITypeCode *tc, OCIType **type)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIAnyDataGetType_func(svchp, errhp, sdata, tc, type);
    if (trace_OCIAnyDataGetType) {
        ocidump_log("%0*lX: OCIAnyDataGetType(%p, %p, %p, [%u], [%p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     sdata,
                     *tc,
                     *type,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIAnyDataIsNull_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCIAnyData *sdata, boolean *isnull);
static OCIAnyDataIsNull_func_t OCIAnyDataIsNull_func;
static int trace_OCIAnyDataIsNull = 1;

sword OCIAnyDataIsNull(OCISvcCtx *svchp, OCIError *errhp, OCIAnyData *sdata, boolean *isnull)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIAnyDataIsNull_func(svchp, errhp, sdata, isnull);
    if (trace_OCIAnyDataIsNull) {
        ocidump_log("%0*lX: OCIAnyDataIsNull(%p, %p, %p, [%d]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     sdata,
                     *isnull,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIAnyDataSetAddInstance_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCIAnyDataSet *data_set, OCIAnyData **data);
static OCIAnyDataSetAddInstance_func_t OCIAnyDataSetAddInstance_func;
static int trace_OCIAnyDataSetAddInstance = 1;

sword OCIAnyDataSetAddInstance(OCISvcCtx *svchp, OCIError *errhp, OCIAnyDataSet *data_set, OCIAnyData **data)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    OCIAnyData *old_data = *data;

    if (!is_initialized) {
        initialize();
    }
    ret = OCIAnyDataSetAddInstance_func(svchp, errhp, data_set, data);
    if (trace_OCIAnyDataSetAddInstance) {
        ocidump_log("%0*lX: OCIAnyDataSetAddInstance(%p, %p, %p, [%p -> %p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     data_set,
                     old_data, *data,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIAnyDataSetBeginCreate_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCITypeCode typecode, const OCIType *type, OCIDuration dur, OCIAnyDataSet ** data_set);
static OCIAnyDataSetBeginCreate_func_t OCIAnyDataSetBeginCreate_func;
static int trace_OCIAnyDataSetBeginCreate = 1;

sword OCIAnyDataSetBeginCreate(OCISvcCtx *svchp, OCIError *errhp, OCITypeCode typecode, const OCIType *type, OCIDuration dur, OCIAnyDataSet ** data_set)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIAnyDataSetBeginCreate_func(svchp, errhp, typecode, type, dur, data_set);
    if (trace_OCIAnyDataSetBeginCreate) {
        ocidump_log("%0*lX: OCIAnyDataSetBeginCreate(%p, %p, %u, %p, %u, [%p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     typecode,
                     type,
                     dur,
                     *data_set,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIAnyDataSetDestroy_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCIAnyDataSet *data_set);
static OCIAnyDataSetDestroy_func_t OCIAnyDataSetDestroy_func;
static int trace_OCIAnyDataSetDestroy = 1;

sword OCIAnyDataSetDestroy(OCISvcCtx *svchp, OCIError *errhp, OCIAnyDataSet *data_set)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIAnyDataSetDestroy_func(svchp, errhp, data_set);
    if (trace_OCIAnyDataSetDestroy) {
        ocidump_log("%0*lX: OCIAnyDataSetDestroy(%p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     data_set,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIAnyDataSetEndCreate_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCIAnyDataSet *data_set);
static OCIAnyDataSetEndCreate_func_t OCIAnyDataSetEndCreate_func;
static int trace_OCIAnyDataSetEndCreate = 1;

sword OCIAnyDataSetEndCreate(OCISvcCtx *svchp, OCIError *errhp, OCIAnyDataSet *data_set)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIAnyDataSetEndCreate_func(svchp, errhp, data_set);
    if (trace_OCIAnyDataSetEndCreate) {
        ocidump_log("%0*lX: OCIAnyDataSetEndCreate(%p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     data_set,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIAnyDataSetGetCount_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCIAnyDataSet *data_set, ub4 *count);
static OCIAnyDataSetGetCount_func_t OCIAnyDataSetGetCount_func;
static int trace_OCIAnyDataSetGetCount = 1;

sword OCIAnyDataSetGetCount(OCISvcCtx *svchp, OCIError *errhp, OCIAnyDataSet *data_set, ub4 *count)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIAnyDataSetGetCount_func(svchp, errhp, data_set, count);
    if (trace_OCIAnyDataSetGetCount) {
        ocidump_log("%0*lX: OCIAnyDataSetGetCount(%p, %p, %p, [%u]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     data_set,
                     *count,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIAnyDataSetGetInstance_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCIAnyDataSet *data_set, OCIAnyData **data);
static OCIAnyDataSetGetInstance_func_t OCIAnyDataSetGetInstance_func;
static int trace_OCIAnyDataSetGetInstance = 1;

sword OCIAnyDataSetGetInstance(OCISvcCtx *svchp, OCIError *errhp, OCIAnyDataSet *data_set, OCIAnyData **data)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    OCIAnyData *old_data = *data;

    if (!is_initialized) {
        initialize();
    }
    ret = OCIAnyDataSetGetInstance_func(svchp, errhp, data_set, data);
    if (trace_OCIAnyDataSetGetInstance) {
        ocidump_log("%0*lX: OCIAnyDataSetGetInstance(%p, %p, %p, [%p -> %p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     data_set,
                     old_data, *data,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIAnyDataSetGetType_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCIAnyDataSet *data_set, OCITypeCode *tc, OCIType **type);
static OCIAnyDataSetGetType_func_t OCIAnyDataSetGetType_func;
static int trace_OCIAnyDataSetGetType = 1;

sword OCIAnyDataSetGetType(OCISvcCtx *svchp, OCIError *errhp, OCIAnyDataSet *data_set, OCITypeCode *tc, OCIType **type)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIAnyDataSetGetType_func(svchp, errhp, data_set, tc, type);
    if (trace_OCIAnyDataSetGetType) {
        ocidump_log("%0*lX: OCIAnyDataSetGetType(%p, %p, %p, [%u], [%p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     data_set,
                     *tc,
                     *type,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIAppCtxClearAll_func_t)(void *sesshndl, void *nsptr, ub4 nsptrlen, OCIError *errhp, ub4 mode);
static OCIAppCtxClearAll_func_t OCIAppCtxClearAll_func;
static int trace_OCIAppCtxClearAll = 1;

sword OCIAppCtxClearAll(void *sesshndl, void *nsptr, ub4 nsptrlen, OCIError *errhp, ub4 mode)
{
    sword ret;
    char *buf1 = NULL;
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIAppCtxClearAll_func(sesshndl, nsptr, nsptrlen, errhp, mode);
    if (trace_OCIAppCtxClearAll) {
        ocidump_log("%0*lX: OCIAppCtxClearAll(%p, %s, %u, %p, 0x%x) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     sesshndl,
                     ocidump_quotestring(&buf1, nsptr, nsptrlen),
                     nsptrlen,
                     errhp,
                     mode,
                     ocidump_status2name(ret, buf2));
    }
    free(buf1);
    return ret;
}

typedef sword (*OCIAppCtxSet_func_t)(void *sesshndl, void *nsptr, ub4 nsptrlen, void *attrptr, ub4 attrptrlen, void *valueptr, ub4 valueptrlen, OCIError *errhp, ub4 mode);
static OCIAppCtxSet_func_t OCIAppCtxSet_func;
static int trace_OCIAppCtxSet = 1;

sword OCIAppCtxSet(void *sesshndl, void *nsptr, ub4 nsptrlen, void *attrptr, ub4 attrptrlen, void *valueptr, ub4 valueptrlen, OCIError *errhp, ub4 mode)
{
    sword ret;
    char *buf1 = NULL;
    char *buf2 = NULL;
    char *buf3 = NULL;
    char buf4[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIAppCtxSet_func(sesshndl, nsptr, nsptrlen, attrptr, attrptrlen, valueptr, valueptrlen, errhp, mode);
    if (trace_OCIAppCtxSet) {
        ocidump_log("%0*lX: OCIAppCtxSet(%p, %s, %u, %s, %u, %s, %u, %p, 0x%x) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     sesshndl,
                     ocidump_quotestring(&buf1, nsptr, nsptrlen),
                     nsptrlen,
                     ocidump_quotestring(&buf2, attrptr, attrptrlen),
                     attrptrlen,
                     ocidump_quotestring(&buf3, valueptr, valueptrlen),
                     valueptrlen,
                     errhp,
                     mode,
                     ocidump_status2name(ret, buf4));
    }
    free(buf1);
    free(buf2);
    free(buf3);
    return ret;
}

typedef sword (*OCIArrayDescriptorAlloc_func_t)(const void *parenth, void **descpp, const ub4 type, ub4 array_size, const size_t xtramem_sz, void **usrmempp);
static OCIArrayDescriptorAlloc_func_t OCIArrayDescriptorAlloc_func;
static int trace_OCIArrayDescriptorAlloc = 1;

sword OCIArrayDescriptorAlloc(const void *parenth, void **descpp, const ub4 type, ub4 array_size, const size_t xtramem_sz, void **usrmempp)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIArrayDescriptorAlloc_func(parenth, descpp, type, array_size, xtramem_sz, usrmempp);
    if (trace_OCIArrayDescriptorAlloc) {
        ocidump_log("%0*lX: OCIArrayDescriptorAlloc(%p, %p([%p, ...]), %s, %u, %" OCIDUMP_SIZET_FMT ", %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     parenth,
                     descpp, *descpp,
                     ocidump_htype2name(type, buf1),
                     array_size,
                     xtramem_sz,
                     usrmempp,
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCIArrayDescriptorFree_func_t)(void **descp, const ub4 type);
static OCIArrayDescriptorFree_func_t OCIArrayDescriptorFree_func;
static int trace_OCIArrayDescriptorFree = 1;

sword OCIArrayDescriptorFree(void **descp, const ub4 type)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIArrayDescriptorFree_func(descp, type);
    if (trace_OCIArrayDescriptorFree) {
        ocidump_log("%0*lX: OCIArrayDescriptorFree(%p([%p, ...]), %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     descp, *descp,
                     ocidump_htype2name(type, buf1),
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCIAttrGet_func_t)(const dvoid *trgthndlp, ub4 trghndltyp, dvoid *attributep, ub4 *sizep, ub4 attrtype, OCIError *errhp);
static OCIAttrGet_func_t OCIAttrGet_func;
static int trace_OCIAttrGet = 1;

sword OCIAttrGet(const dvoid *trgthndlp, ub4 trghndltyp, dvoid *attributep, ub4 *sizep, ub4 attrtype, OCIError *errhp)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    char buf3[OCIDUMP_SHORT_BUF_SIZE];
    char buf4[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIAttrGet_func(trgthndlp, trghndltyp, attributep, sizep, attrtype, errhp);
    if (trace_OCIAttrGet) {
        ocidump_log("%0*lX: OCIAttrGet(%p, %s, %p, %s, %s, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     trgthndlp,
                     ocidump_htype2name(trghndltyp, buf1),
                     attributep,
                     sizep ? ocidump_sprintf(buf2, "[%u]", *sizep) : "(nil)",
                     ocidump_attrtype2name(trghndltyp, attrtype, buf3),
                     errhp,
                     ocidump_status2name(ret, buf4));
    }
    return ret;
}

typedef sword (*OCIAttrSet_func_t)(dvoid *trgthndlp, ub4 trghndltyp, dvoid *attributep, ub4 size, ub4 attrtype, OCIError *errhp);
static OCIAttrSet_func_t OCIAttrSet_func;
static int trace_OCIAttrSet = 1;

sword OCIAttrSet(dvoid *trgthndlp, ub4 trghndltyp, dvoid *attributep, ub4 size, ub4 attrtype, OCIError *errhp)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    char buf3[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIAttrSet_func(trgthndlp, trghndltyp, attributep, size, attrtype, errhp);
    if (trace_OCIAttrSet) {
        ocidump_log("%0*lX: OCIAttrSet(%p, %s, %p, %u, %s, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     trgthndlp,
                     ocidump_htype2name(trghndltyp, buf1),
                     attributep,
                     size,
                     ocidump_attrtype2name(trghndltyp, attrtype, buf2),
                     errhp,
                     ocidump_status2name(ret, buf3));
    }
    return ret;
}

typedef sword (*OCIBindArrayOfStruct_func_t)(OCIBind *bindp, OCIError *errhp, ub4 pvskip, ub4 indskip, ub4 alskip, ub4 rcskip);
static OCIBindArrayOfStruct_func_t OCIBindArrayOfStruct_func;
static int trace_OCIBindArrayOfStruct = 1;

sword OCIBindArrayOfStruct(OCIBind *bindp, OCIError *errhp, ub4 pvskip, ub4 indskip, ub4 alskip, ub4 rcskip)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIBindArrayOfStruct_func(bindp, errhp, pvskip, indskip, alskip, rcskip);
    if (trace_OCIBindArrayOfStruct) {
        ocidump_log("%0*lX: OCIBindArrayOfStruct(%p, %p, %u, %u, %u, %u) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     bindp,
                     errhp,
                     pvskip,
                     indskip,
                     alskip,
                     rcskip,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIBindByName_func_t)(OCIStmt *stmtp, OCIBind **bindp, OCIError *errhp, const text *placeholder, sb4 placeh_len, dvoid *valuep, sb4 value_sz, ub2 dty, dvoid *indp, ub2 *alenp, ub2 *rcodep, ub4 maxarr_len, ub4 *curelep, ub4 mode);
static OCIBindByName_func_t OCIBindByName_func;
static int trace_OCIBindByName = 1;

sword OCIBindByName(OCIStmt *stmtp, OCIBind **bindp, OCIError *errhp, const text *placeholder, sb4 placeh_len, dvoid *valuep, sb4 value_sz, ub2 dty, dvoid *indp, ub2 *alenp, ub2 *rcodep, ub4 maxarr_len, ub4 *curelep, ub4 mode)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIBindByName_func(stmtp, bindp, errhp, placeholder, placeh_len, valuep, value_sz, dty, indp, alenp, rcodep, maxarr_len, curelep, mode);
    if (trace_OCIBindByName) {
        if (ocidump_hide_string) {
            placeh_len = 6;
            placeholder = (OraText*)"hidden";
        }
        ocidump_log("%0*lX: OCIBindByName(%p, [%p], %p, \"%.*s\", %d, %p, %d, %u, %p, %p, %p, %u, %p, 0x%x) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     stmtp,
                     *bindp,
                     errhp,
                     placeh_len, placeholder,
                     placeh_len,
                     valuep,
                     value_sz,
                     dty,
                     indp,
                     alenp,
                     rcodep,
                     maxarr_len,
                     curelep,
                     mode,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIBindByPos_func_t)(OCIStmt *stmtp, OCIBind **bindp, OCIError *errhp, ub4 position, dvoid *valuep, sb4 value_sz, ub2 dty, dvoid *indp, ub2 *alenp, ub2 *rcodep, ub4 maxarr_len, ub4 *curelep, ub4 mode);
static OCIBindByPos_func_t OCIBindByPos_func;
static int trace_OCIBindByPos = 1;

sword OCIBindByPos(OCIStmt *stmtp, OCIBind **bindp, OCIError *errhp, ub4 position, dvoid *valuep, sb4 value_sz, ub2 dty, dvoid *indp, ub2 *alenp, ub2 *rcodep, ub4 maxarr_len, ub4 *curelep, ub4 mode)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIBindByPos_func(stmtp, bindp, errhp, position, valuep, value_sz, dty, indp, alenp, rcodep, maxarr_len, curelep, mode);
    if (trace_OCIBindByPos) {
        ocidump_log("%0*lX: OCIBindByPos(%p, [%p], %p, %u, %p, %d, %d, %p, %p, %p, %u, %p, 0x%x) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     stmtp,
                     *bindp,
                     errhp,
                     position,
                     valuep,
                     value_sz,
                     dty,
                     indp,
                     alenp,
                     rcodep,
                     maxarr_len,
                     curelep,
                     mode,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIBindDynamic_func_t)(OCIBind *bindp, OCIError *errhp, void *ictxp, OCICallbackInBind icbfp, void *octxp, OCICallbackOutBind ocbfp);
static OCIBindDynamic_func_t OCIBindDynamic_func;
static int trace_OCIBindDynamic = 1;

sword OCIBindDynamic(OCIBind *bindp, OCIError *errhp, void *ictxp, OCICallbackInBind icbfp, void *octxp, OCICallbackOutBind ocbfp)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIBindDynamic_func(bindp, errhp, ictxp, icbfp, octxp, ocbfp);
    if (trace_OCIBindDynamic) {
        ocidump_log("%0*lX: OCIBindDynamic(%p, %p, %p, %p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     bindp,
                     errhp,
                     ictxp,
                     icbfp,
                     octxp,
                     ocbfp,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIBindObject_func_t)(OCIBind *bindp, OCIError *errhp, const OCIType *type, dvoid **pgvpp, ub4 *pvszsp, dvoid **indpp, ub4 *indszp);
static OCIBindObject_func_t OCIBindObject_func;
static int trace_OCIBindObject = 1;

sword OCIBindObject(OCIBind *bindp, OCIError *errhp, const OCIType *type, dvoid **pgvpp, ub4 *pvszsp, dvoid **indpp, ub4 *indszp)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIBindObject_func(bindp, errhp, type, pgvpp, pvszsp, indpp, indszp);
    if (trace_OCIBindObject) {
        ocidump_log("%0*lX: OCIBindObject(%p, %p, %p, %p, %p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     bindp,
                     errhp,
                     type,
                     pgvpp,
                     pvszsp,
                     indpp,
                     indszp,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIBreak_func_t)(dvoid *hndlp, OCIError *errhp);
static OCIBreak_func_t OCIBreak_func;
static int trace_OCIBreak = 1;

sword OCIBreak(dvoid *hndlp, OCIError *errhp)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIBreak_func(hndlp, errhp);
    if (trace_OCIBreak) {
        ocidump_log("%0*lX: OCIBreak(%p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndlp,
                     errhp,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCICacheFlush_func_t)(OCIEnv *env, OCIError *err, const OCISvcCtx *svc, void *context, OCIRef *(*get)(void *context, ub1 *last), OCIRef **ref);
static OCICacheFlush_func_t OCICacheFlush_func;
static int trace_OCICacheFlush = 1;

sword OCICacheFlush(OCIEnv *env, OCIError *err, const OCISvcCtx *svc, void *context, OCIRef *(*get)(void *context, ub1 *last), OCIRef **ref)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCICacheFlush_func(env, err, svc, context, get, ref);
    if (trace_OCICacheFlush) {
        ocidump_log("%0*lX: OCICacheFlush(%p, %p, %p, %p, %p, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     svc,
                     context,
                     get,
                     ret ? ocidump_sprintf(buf1, "[%p]", *ref) : "(nil)",
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCICacheFlushRefresh_func_t)(OCIEnv *env, OCIError *err, const OCISvcCtx *svc, void *context, OCIRef *(*get)(void *context, ub1 *last), OCIRef **ref);
static OCICacheFlushRefresh_func_t OCICacheFlushRefresh_func;
static int trace_OCICacheFlushRefresh = 1;

sword OCICacheFlushRefresh(OCIEnv *env, OCIError *err, const OCISvcCtx *svc, void *context, OCIRef *(*get)(void *context, ub1 *last), OCIRef **ref)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCICacheFlushRefresh_func(env, err, svc, context, get, ref);
    if (trace_OCICacheFlushRefresh) {
        ocidump_log("%0*lX: OCICacheFlushRefresh(%p, %p, %p, %p, %p, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     svc,
                     context,
                     get,
                     ret ? ocidump_sprintf(buf1, "[%p]", *ref) : "(nil)",
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCICacheFree_func_t)(OCIEnv *env, OCIError *err, const OCISvcCtx *svc);
static OCICacheFree_func_t OCICacheFree_func;
static int trace_OCICacheFree = 1;

sword OCICacheFree(OCIEnv *env, OCIError *err, const OCISvcCtx *svc)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCICacheFree_func(env, err, svc);
    if (trace_OCICacheFree) {
        ocidump_log("%0*lX: OCICacheFree(%p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     svc,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCICacheGetObjects_func_t)(OCIEnv *env, OCIError *err, const OCISvcCtx *svc, OCIObjectProperty property, void *client_context, void (*client_callback)(void *client_context, void *object));
static OCICacheGetObjects_func_t OCICacheGetObjects_func;
static int trace_OCICacheGetObjects = 1;

sword OCICacheGetObjects(OCIEnv *env, OCIError *err, const OCISvcCtx *svc, OCIObjectProperty property, void *client_context, void (*client_callback)(void *client_context, void *object))
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCICacheGetObjects_func(env, err, svc, property, client_context, client_callback);
    if (trace_OCICacheGetObjects) {
        ocidump_log("%0*lX: OCICacheGetObjects(%p, %p, %p, %d, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     svc,
                     property,
                     client_context,
                     client_callback,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCICacheRefresh_func_t)(OCIEnv *env, OCIError *err, const OCISvcCtx *svc, OCIRefreshOpt option, void *context, OCIRef *(*get)(void *context), OCIRef **ref);
static OCICacheRefresh_func_t OCICacheRefresh_func;
static int trace_OCICacheRefresh = 1;

sword OCICacheRefresh(OCIEnv *env, OCIError *err, const OCISvcCtx *svc, OCIRefreshOpt option, void *context, OCIRef *(*get)(void *context), OCIRef **ref)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCICacheRefresh_func(env, err, svc, option, context, get, ref);
    if (trace_OCICacheRefresh) {
        ocidump_log("%0*lX: OCICacheRefresh(%p, %p, %p, %d, %p, %p, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     svc,
                     option,
                     context,
                     get,
                     ret ? ocidump_sprintf(buf1, "[%p]", *ref) : "(nil)",
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCICacheRegister_func_t)(OCIEnv *env, OCIError *err, OCIObjectEvent event, void *client_context, void (*client_callback)(void *client_context, OCIObjectEvent event, void *object));
static OCICacheRegister_func_t OCICacheRegister_func;
static int trace_OCICacheRegister = 1;

sword OCICacheRegister(OCIEnv *env, OCIError *err, OCIObjectEvent event, void *client_context, void (*client_callback)(void *client_context, OCIObjectEvent event, void *object))
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCICacheRegister_func(env, err, event, client_context, client_callback);
    if (trace_OCICacheRegister) {
        ocidump_log("%0*lX: OCICacheRegister(%p, %p, %d, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     event,
                     client_context,
                     client_callback,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCICacheUnmark_func_t)(OCIEnv *env, OCIError *err, const OCISvcCtx *svc);
static OCICacheUnmark_func_t OCICacheUnmark_func;
static int trace_OCICacheUnmark = 1;

sword OCICacheUnmark(OCIEnv *env, OCIError *err, const OCISvcCtx *svc)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCICacheUnmark_func(env, err, svc);
    if (trace_OCICacheUnmark) {
        ocidump_log("%0*lX: OCICacheUnmark(%p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     svc,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCICacheUnpin_func_t)(OCIEnv *env, OCIError *err, const OCISvcCtx *svc);
static OCICacheUnpin_func_t OCICacheUnpin_func;
static int trace_OCICacheUnpin = 1;

sword OCICacheUnpin(OCIEnv *env, OCIError *err, const OCISvcCtx *svc)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCICacheUnpin_func(env, err, svc);
    if (trace_OCICacheUnpin) {
        ocidump_log("%0*lX: OCICacheUnpin(%p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     svc,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef boolean (*OCICharSetConversionIsReplacementUsed_func_t)(void *envhp);
static OCICharSetConversionIsReplacementUsed_func_t OCICharSetConversionIsReplacementUsed_func;
static int trace_OCICharSetConversionIsReplacementUsed = 1;

boolean OCICharSetConversionIsReplacementUsed(void *envhp)
{
    boolean ret;
    if (!is_initialized) {
        initialize();
    }
    ret = OCICharSetConversionIsReplacementUsed_func(envhp);
    if (trace_OCICharSetConversionIsReplacementUsed) {
        ocidump_log("%0*lX: OCICharSetConversionIsReplacementUsed(%p) => %d\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     envhp,
                     ret);
    }
    return ret;
}

typedef void (*OCIClientVersion_func_t)(sword *major_version, sword *minor_version, sword *update_num, sword *patch_num, sword *port_update_num);
static OCIClientVersion_func_t OCIClientVersion_func;
static int trace_OCIClientVersion = 1;

void OCIClientVersion(sword *major_version, sword *minor_version, sword *update_num, sword *patch_num, sword *port_update_num)
{
    if (!is_initialized) {
        initialize();
    }
    OCIClientVersion_func(major_version, minor_version, update_num, patch_num, port_update_num);
    if (trace_OCIClientVersion) {
        ocidump_log("%0*lX: OCIClientVersion([%d], [%d], [%d], [%d], [%d])\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     *major_version,
                     *minor_version,
                     *update_num,
                     *patch_num,
                     *port_update_num);
    }
}

typedef sword (*OCICollAppend_func_t)(OCIEnv *env, OCIError *err, const dvoid *elem, const dvoid *elemind, OCIColl *coll);
static OCICollAppend_func_t OCICollAppend_func;
static int trace_OCICollAppend = 1;

sword OCICollAppend(OCIEnv *env, OCIError *err, const dvoid *elem, const dvoid *elemind, OCIColl *coll)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCICollAppend_func(env, err, elem, elemind, coll);
    if (trace_OCICollAppend) {
        ocidump_log("%0*lX: OCICollAppend(%p, %p, %p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     elem,
                     elemind,
                     coll,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCICollAssign_func_t)(OCIEnv *env, OCIError *err, const OCIColl *rhs, OCIColl *lhs);
static OCICollAssign_func_t OCICollAssign_func;
static int trace_OCICollAssign = 1;

sword OCICollAssign(OCIEnv *env, OCIError *err, const OCIColl *rhs, OCIColl *lhs)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCICollAssign_func(env, err, rhs, lhs);
    if (trace_OCICollAssign) {
        ocidump_log("%0*lX: OCICollAssign(%p, %p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     rhs,
                     lhs,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCICollAssignElem_func_t)(OCIEnv *env, OCIError *err, sb4 index, const dvoid *elem, const dvoid *elemind, OCIColl *coll);
static OCICollAssignElem_func_t OCICollAssignElem_func;
static int trace_OCICollAssignElem = 1;

sword OCICollAssignElem(OCIEnv *env, OCIError *err, sb4 index, const dvoid *elem, const dvoid *elemind, OCIColl *coll)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCICollAssignElem_func(env, err, index, elem, elemind, coll);
    if (trace_OCICollAssignElem) {
        ocidump_log("%0*lX: OCICollAssignElem(%p, %p, %d, %p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     index,
                     elem,
                     elemind,
                     coll,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCICollGetElem_func_t)(OCIEnv *env, OCIError *err, const OCIColl *coll, sb4 index, boolean *exists, dvoid **elem, dvoid **elemind);
static OCICollGetElem_func_t OCICollGetElem_func;
static int trace_OCICollGetElem = 1;

sword OCICollGetElem(OCIEnv *env, OCIError *err, const OCIColl *coll, sb4 index, boolean *exists, dvoid **elem, dvoid **elemind)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCICollGetElem_func(env, err, coll, index, exists, elem, elemind);
    if (trace_OCICollGetElem) {
        ocidump_log("%0*lX: OCICollGetElem(%p, %p, %p, %d, [%d], [%p], %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     coll,
                     index,
                     *exists,
                     *elem,
                     elemind ? ocidump_sprintf(buf1, "[%p]", *elemind) : "(nil)",
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCICollGetElemArray_func_t)(OCIEnv *env, OCIError *err, const OCIColl *coll, sb4 index, boolean *exists, void  **elem, void  **elemind, uword *nelems);
static OCICollGetElemArray_func_t OCICollGetElemArray_func;
static int trace_OCICollGetElemArray = 1;

sword OCICollGetElemArray(OCIEnv *env, OCIError *err, const OCIColl *coll, sb4 index, boolean *exists, void  **elem, void  **elemind, uword *nelems)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    uword old_nelems = *nelems;

    if (!is_initialized) {
        initialize();
    }
    ret = OCICollGetElemArray_func(env, err, coll, index, exists, elem, elemind, nelems);
    if (trace_OCICollGetElemArray) {
        ocidump_log("%0*lX: OCICollGetElemArray(%p, %p, %p, %d, [%d], [%p, ...], %s, [%u -> %u]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     coll,
                     index,
                     *exists,
                     *elem,
                     elemind ? ocidump_sprintf(buf1, "[%p, ...]", *elemind) : "(nil)",
                     old_nelems, *nelems,
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCICollIsLocator_func_t)(OCIEnv *env, OCIError *err, const OCIColl *coll, boolean *result);
static OCICollIsLocator_func_t OCICollIsLocator_func;
static int trace_OCICollIsLocator = 1;

sword OCICollIsLocator(OCIEnv *env, OCIError *err, const OCIColl *coll, boolean *result)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCICollIsLocator_func(env, err, coll, result);
    if (trace_OCICollIsLocator) {
        ocidump_log("%0*lX: OCICollIsLocator(%p, %p, %p, [%d]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     coll,
                     *result,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sb4 (*OCICollMax_func_t)(OCIEnv *env, const OCIColl *coll);
static OCICollMax_func_t OCICollMax_func;
static int trace_OCICollMax = 1;

sb4 OCICollMax(OCIEnv *env, const OCIColl *coll)
{
    sb4 ret;
    if (!is_initialized) {
        initialize();
    }
    ret = OCICollMax_func(env, coll);
    if (trace_OCICollMax) {
        ocidump_log("%0*lX: OCICollMax(%p, %p) => %d\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     coll,
                     ret);
    }
    return ret;
}

typedef sword (*OCICollSize_func_t)(OCIEnv *env, OCIError *err, const OCIColl *coll, sb4 *size);
static OCICollSize_func_t OCICollSize_func;
static int trace_OCICollSize = 1;

sword OCICollSize(OCIEnv *env, OCIError *err, const OCIColl *coll, sb4 *size)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCICollSize_func(env, err, coll, size);
    if (trace_OCICollSize) {
        ocidump_log("%0*lX: OCICollSize(%p, %p, %p, [%d]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     coll,
                     *size,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCICollTrim_func_t)(OCIEnv *env, OCIError *err, sb4 trim_num, OCIColl *coll);
static OCICollTrim_func_t OCICollTrim_func;
static int trace_OCICollTrim = 1;

sword OCICollTrim(OCIEnv *env, OCIError *err, sb4 trim_num, OCIColl *coll)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCICollTrim_func(env, err, trim_num, coll);
    if (trace_OCICollTrim) {
        ocidump_log("%0*lX: OCICollTrim(%p, %p, %d, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     trim_num,
                     coll,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIConnectionPoolCreate_func_t)(OCIEnv *envhp, OCIError *errhp, OCICPool *poolhp, OraText **poolName, sb4 *poolNameLen, const OraText *dblink, sb4 dblinkLen, ub4 connMin, ub4 connMax, ub4 connIncr, const OraText *poolUserName, sb4 poolUserLen, const OraText *poolPassword, sb4 poolPassLen, ub4 mode);
static OCIConnectionPoolCreate_func_t OCIConnectionPoolCreate_func;
static int trace_OCIConnectionPoolCreate = 1;

sword OCIConnectionPoolCreate(OCIEnv *envhp, OCIError *errhp, OCICPool *poolhp, OraText **poolName, sb4 *poolNameLen, const OraText *dblink, sb4 dblinkLen, ub4 connMin, ub4 connMax, ub4 connIncr, const OraText *poolUserName, sb4 poolUserLen, const OraText *poolPassword, sb4 poolPassLen, ub4 mode)
{
    sword ret;
    char *buf1 = NULL;
    char *buf2 = NULL;
    char *buf3 = NULL;
    char buf4[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIConnectionPoolCreate_func(envhp, errhp, poolhp, poolName, poolNameLen, dblink, dblinkLen, connMin, connMax, connIncr, poolUserName, poolUserLen, poolPassword, poolPassLen, mode);
    if (trace_OCIConnectionPoolCreate) {
        ocidump_log("%0*lX: OCIConnectionPoolCreate(%p, %p, %p, [\"%.*s\"], [%d], %s, %d, %u, %u, %u, %s, %d, %s, %d, 0x%x) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     envhp,
                     errhp,
                     poolhp,
                     ret ? 0 : *poolNameLen, *poolName,
                     *poolNameLen,
                     ocidump_quotestring(&buf1, dblink, dblinkLen),
                     dblinkLen,
                     connMin,
                     connMax,
                     connIncr,
                     ocidump_quotestring(&buf2, poolUserName, poolUserLen),
                     poolUserLen,
                     ocidump_quotestring(&buf3, poolPassword, poolPassLen),
                     poolPassLen,
                     mode,
                     ocidump_status2name(ret, buf4));
    }
    free(buf1);
    free(buf2);
    free(buf3);
    return ret;
}

typedef sword (*OCIConnectionPoolDestroy_func_t)(OCICPool *poolhp, OCIError *errhp, ub4 mode);
static OCIConnectionPoolDestroy_func_t OCIConnectionPoolDestroy_func;
static int trace_OCIConnectionPoolDestroy = 1;

sword OCIConnectionPoolDestroy(OCICPool *poolhp, OCIError *errhp, ub4 mode)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIConnectionPoolDestroy_func(poolhp, errhp, mode);
    if (trace_OCIConnectionPoolDestroy) {
        ocidump_log("%0*lX: OCIConnectionPoolDestroy(%p, %p, 0x%x) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     poolhp,
                     errhp,
                     mode,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDBShutdown_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCIAdmin *admhp, ub4 mode);
static OCIDBShutdown_func_t OCIDBShutdown_func;
static int trace_OCIDBShutdown = 1;

sword OCIDBShutdown(OCISvcCtx *svchp, OCIError *errhp, OCIAdmin *admhp, ub4 mode)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDBShutdown_func(svchp, errhp, admhp, mode);
    if (trace_OCIDBShutdown) {
        ocidump_log("%0*lX: OCIDBShutdown(%p, %p, %p, %u) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     admhp,
                     mode,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDBStartup_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCIAdmin *admhp, ub4 mode, ub4 flags);
static OCIDBStartup_func_t OCIDBStartup_func;
static int trace_OCIDBStartup = 1;

sword OCIDBStartup(OCISvcCtx *svchp, OCIError *errhp, OCIAdmin *admhp, ub4 mode, ub4 flags)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDBStartup_func(svchp, errhp, admhp, mode, flags);
    if (trace_OCIDBStartup) {
        ocidump_log("%0*lX: OCIDBStartup(%p, %p, %p, %u, 0x%x) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     admhp,
                     mode,
                     flags,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDateAddDays_func_t)(OCIError *err, const OCIDate *date, sb4 num_days, OCIDate *result);
static OCIDateAddDays_func_t OCIDateAddDays_func;
static int trace_OCIDateAddDays = 1;

sword OCIDateAddDays(OCIError *err, const OCIDate *date, sb4 num_days, OCIDate *result)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDateAddDays_func(err, date, num_days, result);
    if (trace_OCIDateAddDays) {
        ocidump_log("%0*lX: OCIDateAddDays(%p, {%04d-%02u-%02u %02u:%02u:%02u}, %d, {%04d-%02u-%02u %02u:%02u:%02u}) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     date->OCIDateYYYY, date->OCIDateMM, date->OCIDateDD, date->OCIDateTime.OCITimeHH, date->OCIDateTime.OCITimeMI, date->OCIDateTime.OCITimeSS,
                     num_days,
                     result->OCIDateYYYY, result->OCIDateMM, result->OCIDateDD, result->OCIDateTime.OCITimeHH, result->OCIDateTime.OCITimeMI, result->OCIDateTime.OCITimeSS,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDateAddMonths_func_t)(OCIError *err, const OCIDate *date, sb4 num_months, OCIDate *result);
static OCIDateAddMonths_func_t OCIDateAddMonths_func;
static int trace_OCIDateAddMonths = 1;

sword OCIDateAddMonths(OCIError *err, const OCIDate *date, sb4 num_months, OCIDate *result)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDateAddMonths_func(err, date, num_months, result);
    if (trace_OCIDateAddMonths) {
        ocidump_log("%0*lX: OCIDateAddMonths(%p, {%04d-%02u-%02u %02u:%02u:%02u}, %d, {%04d-%02u-%02u %02u:%02u:%02u}) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     date->OCIDateYYYY, date->OCIDateMM, date->OCIDateDD, date->OCIDateTime.OCITimeHH, date->OCIDateTime.OCITimeMI, date->OCIDateTime.OCITimeSS,
                     num_months,
                     result->OCIDateYYYY, result->OCIDateMM, result->OCIDateDD, result->OCIDateTime.OCITimeHH, result->OCIDateTime.OCITimeMI, result->OCIDateTime.OCITimeSS,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDateAssign_func_t)(OCIError *err, const OCIDate *from, OCIDate *to);
static OCIDateAssign_func_t OCIDateAssign_func;
static int trace_OCIDateAssign = 1;

sword OCIDateAssign(OCIError *err, const OCIDate *from, OCIDate *to)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDateAssign_func(err, from, to);
    if (trace_OCIDateAssign) {
        ocidump_log("%0*lX: OCIDateAssign(%p, {%04d-%02u-%02u %02u:%02u:%02u}, {%04d-%02u-%02u %02u:%02u:%02u}) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     from->OCIDateYYYY, from->OCIDateMM, from->OCIDateDD, from->OCIDateTime.OCITimeHH, from->OCIDateTime.OCITimeMI, from->OCIDateTime.OCITimeSS,
                     to->OCIDateYYYY, to->OCIDateMM, to->OCIDateDD, to->OCIDateTime.OCITimeHH, to->OCIDateTime.OCITimeMI, to->OCIDateTime.OCITimeSS,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDateCheck_func_t)(OCIError *err, const OCIDate *date, uword *valid);
static OCIDateCheck_func_t OCIDateCheck_func;
static int trace_OCIDateCheck = 1;

sword OCIDateCheck(OCIError *err, const OCIDate *date, uword *valid)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDateCheck_func(err, date, valid);
    if (trace_OCIDateCheck) {
        ocidump_log("%0*lX: OCIDateCheck(%p, {%04d-%02u-%02u %02u:%02u:%02u}, [0x%x]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     date->OCIDateYYYY, date->OCIDateMM, date->OCIDateDD, date->OCIDateTime.OCITimeHH, date->OCIDateTime.OCITimeMI, date->OCIDateTime.OCITimeSS,
                     *valid,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDateCompare_func_t)(OCIError *err, const OCIDate *date1, const OCIDate *date2, sword *result);
static OCIDateCompare_func_t OCIDateCompare_func;
static int trace_OCIDateCompare = 1;

sword OCIDateCompare(OCIError *err, const OCIDate *date1, const OCIDate *date2, sword *result)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDateCompare_func(err, date1, date2, result);
    if (trace_OCIDateCompare) {
        ocidump_log("%0*lX: OCIDateCompare(%p, {%04d-%02u-%02u %02u:%02u:%02u}, {%04d-%02u-%02u %02u:%02u:%02u}, [%d]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     date1->OCIDateYYYY, date1->OCIDateMM, date1->OCIDateDD, date1->OCIDateTime.OCITimeHH, date1->OCIDateTime.OCITimeMI, date1->OCIDateTime.OCITimeSS,
                     date2->OCIDateYYYY, date2->OCIDateMM, date2->OCIDateDD, date2->OCIDateTime.OCITimeHH, date2->OCIDateTime.OCITimeMI, date2->OCIDateTime.OCITimeSS,
                     *result,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDateDaysBetween_func_t)(OCIError *err, const OCIDate *date1, const OCIDate *date2, sb4 *num_days);
static OCIDateDaysBetween_func_t OCIDateDaysBetween_func;
static int trace_OCIDateDaysBetween = 1;

sword OCIDateDaysBetween(OCIError *err, const OCIDate *date1, const OCIDate *date2, sb4 *num_days)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDateDaysBetween_func(err, date1, date2, num_days);
    if (trace_OCIDateDaysBetween) {
        ocidump_log("%0*lX: OCIDateDaysBetween(%p, {%04d-%02u-%02u %02u:%02u:%02u}, {%04d-%02u-%02u %02u:%02u:%02u}, [%d]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     date1->OCIDateYYYY, date1->OCIDateMM, date1->OCIDateDD, date1->OCIDateTime.OCITimeHH, date1->OCIDateTime.OCITimeMI, date1->OCIDateTime.OCITimeSS,
                     date2->OCIDateYYYY, date2->OCIDateMM, date2->OCIDateDD, date2->OCIDateTime.OCITimeHH, date2->OCIDateTime.OCITimeMI, date2->OCIDateTime.OCITimeSS,
                     *num_days,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDateFromText_func_t)(OCIError *err, const oratext *date_str, ub4 d_str_length, const oratext *fmt, ub1 fmt_length, const oratext *lang_name, ub4 lang_length, OCIDate *date);
static OCIDateFromText_func_t OCIDateFromText_func;
static int trace_OCIDateFromText = 1;

sword OCIDateFromText(OCIError *err, const oratext *date_str, ub4 d_str_length, const oratext *fmt, ub1 fmt_length, const oratext *lang_name, ub4 lang_length, OCIDate *date)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDateFromText_func(err, date_str, d_str_length, fmt, fmt_length, lang_name, lang_length, date);
    if (trace_OCIDateFromText) {
        if (ocidump_hide_string) {
            d_str_length = 6;
            date_str = (OraText*)"hidden";
            fmt_length = 6;
            fmt = (OraText*)"hidden";
            lang_length = 6;
            lang_name = (OraText*)"hidden";
        }
        ocidump_log("%0*lX: OCIDateFromText(%p, \"%.*s\", %u, \"%.*s\", %u, \"%.*s\", %u, {%04d-%02u-%02u %02u:%02u:%02u}) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     d_str_length, date_str,
                     d_str_length,
                     fmt_length, fmt,
                     fmt_length,
                     lang_length, lang_name,
                     lang_length,
                     date->OCIDateYYYY, date->OCIDateMM, date->OCIDateDD, date->OCIDateTime.OCITimeHH, date->OCIDateTime.OCITimeMI, date->OCIDateTime.OCITimeSS,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDateLastDay_func_t)(OCIError *err, const OCIDate *date, OCIDate *last_day);
static OCIDateLastDay_func_t OCIDateLastDay_func;
static int trace_OCIDateLastDay = 1;

sword OCIDateLastDay(OCIError *err, const OCIDate *date, OCIDate *last_day)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDateLastDay_func(err, date, last_day);
    if (trace_OCIDateLastDay) {
        ocidump_log("%0*lX: OCIDateLastDay(%p, {%04d-%02u-%02u %02u:%02u:%02u}, {%04d-%02u-%02u %02u:%02u:%02u}) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     date->OCIDateYYYY, date->OCIDateMM, date->OCIDateDD, date->OCIDateTime.OCITimeHH, date->OCIDateTime.OCITimeMI, date->OCIDateTime.OCITimeSS,
                     last_day->OCIDateYYYY, last_day->OCIDateMM, last_day->OCIDateDD, last_day->OCIDateTime.OCITimeHH, last_day->OCIDateTime.OCITimeMI, last_day->OCIDateTime.OCITimeSS,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDateNextDay_func_t)(OCIError *err, const OCIDate *date, const oratext *day_p, ub4 day_length, OCIDate *next_day);
static OCIDateNextDay_func_t OCIDateNextDay_func;
static int trace_OCIDateNextDay = 1;

sword OCIDateNextDay(OCIError *err, const OCIDate *date, const oratext *day_p, ub4 day_length, OCIDate *next_day)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDateNextDay_func(err, date, day_p, day_length, next_day);
    if (trace_OCIDateNextDay) {
        if (ocidump_hide_string) {
            day_length = 6;
            day_p = (OraText*)"hidden";
        }
        ocidump_log("%0*lX: OCIDateNextDay(%p, {%04d-%02u-%02u %02u:%02u:%02u}, \"%.*s\", %u, {%04d-%02u-%02u %02u:%02u:%02u}) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     date->OCIDateYYYY, date->OCIDateMM, date->OCIDateDD, date->OCIDateTime.OCITimeHH, date->OCIDateTime.OCITimeMI, date->OCIDateTime.OCITimeSS,
                     day_length, day_p,
                     day_length,
                     next_day->OCIDateYYYY, next_day->OCIDateMM, next_day->OCIDateDD, next_day->OCIDateTime.OCITimeHH, next_day->OCIDateTime.OCITimeMI, next_day->OCIDateTime.OCITimeSS,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDateSysDate_func_t)(OCIError *err, OCIDate *sys_date);
static OCIDateSysDate_func_t OCIDateSysDate_func;
static int trace_OCIDateSysDate = 1;

sword OCIDateSysDate(OCIError *err, OCIDate *sys_date)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDateSysDate_func(err, sys_date);
    if (trace_OCIDateSysDate) {
        ocidump_log("%0*lX: OCIDateSysDate(%p, {%04d-%02u-%02u %02u:%02u:%02u}) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     sys_date->OCIDateYYYY, sys_date->OCIDateMM, sys_date->OCIDateDD, sys_date->OCIDateTime.OCITimeHH, sys_date->OCIDateTime.OCITimeMI, sys_date->OCIDateTime.OCITimeSS,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDateTimeAssign_func_t)(void *hndl, OCIError *err, const OCIDateTime *from, OCIDateTime *to);
static OCIDateTimeAssign_func_t OCIDateTimeAssign_func;
static int trace_OCIDateTimeAssign = 1;

sword OCIDateTimeAssign(void *hndl, OCIError *err, const OCIDateTime *from, OCIDateTime *to)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDateTimeAssign_func(hndl, err, from, to);
    if (trace_OCIDateTimeAssign) {
        ocidump_log("%0*lX: OCIDateTimeAssign(%p, %p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndl,
                     err,
                     from,
                     to,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDateTimeCheck_func_t)(void *hndl, OCIError *err, const OCIDateTime *date, ub4 *valid);
static OCIDateTimeCheck_func_t OCIDateTimeCheck_func;
static int trace_OCIDateTimeCheck = 1;

sword OCIDateTimeCheck(void *hndl, OCIError *err, const OCIDateTime *date, ub4 *valid)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDateTimeCheck_func(hndl, err, date, valid);
    if (trace_OCIDateTimeCheck) {
        ocidump_log("%0*lX: OCIDateTimeCheck(%p, %p, %p, [0x%x]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndl,
                     err,
                     date,
                     *valid,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDateTimeCompare_func_t)(void *hndl, OCIError *err, const OCIDateTime *date1, const OCIDateTime *date2, sword *result);
static OCIDateTimeCompare_func_t OCIDateTimeCompare_func;
static int trace_OCIDateTimeCompare = 1;

sword OCIDateTimeCompare(void *hndl, OCIError *err, const OCIDateTime *date1, const OCIDateTime *date2, sword *result)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDateTimeCompare_func(hndl, err, date1, date2, result);
    if (trace_OCIDateTimeCompare) {
        ocidump_log("%0*lX: OCIDateTimeCompare(%p, %p, %p, %p, [%d]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndl,
                     err,
                     date1,
                     date2,
                     *result,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDateTimeConstruct_func_t)(void *hndl, OCIError *err, OCIDateTime *datetime, sb2 yr, ub1 mnth, ub1 dy, ub1 hr, ub1 mm, ub1 ss, ub4 fsec, OraText *timezone, size_t timezone_length);
static OCIDateTimeConstruct_func_t OCIDateTimeConstruct_func;
static int trace_OCIDateTimeConstruct = 1;

sword OCIDateTimeConstruct(void *hndl, OCIError *err, OCIDateTime *datetime, sb2 yr, ub1 mnth, ub1 dy, ub1 hr, ub1 mm, ub1 ss, ub4 fsec, OraText *timezone, size_t timezone_length)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDateTimeConstruct_func(hndl, err, datetime, yr, mnth, dy, hr, mm, ss, fsec, timezone, timezone_length);
    if (trace_OCIDateTimeConstruct) {
        if (ocidump_hide_string) {
            timezone_length = 6;
            timezone = (OraText*)"hidden";
        }
        ocidump_log("%0*lX: OCIDateTimeConstruct(%p, %p, %p, %d, %u, %u, %u, %u, %u, %u, \"%.*s\", %" OCIDUMP_SIZET_FMT ") => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndl,
                     err,
                     datetime,
                     yr,
                     mnth,
                     dy,
                     hr,
                     mm,
                     ss,
                     fsec,
                     (int)timezone_length, timezone,
                     timezone_length,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDateTimeConvert_func_t)(void *hndl, OCIError *err, OCIDateTime *indate, OCIDateTime *outdate);
static OCIDateTimeConvert_func_t OCIDateTimeConvert_func;
static int trace_OCIDateTimeConvert = 1;

sword OCIDateTimeConvert(void *hndl, OCIError *err, OCIDateTime *indate, OCIDateTime *outdate)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDateTimeConvert_func(hndl, err, indate, outdate);
    if (trace_OCIDateTimeConvert) {
        ocidump_log("%0*lX: OCIDateTimeConvert(%p, %p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndl,
                     err,
                     indate,
                     outdate,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDateTimeFromArray_func_t)(void *hndl, OCIError *err, ub1 *inarray, ub4 len, ub1 type, OCIDateTime *datetime, const OCIInterval *reftz, ub1 fsprec);
static OCIDateTimeFromArray_func_t OCIDateTimeFromArray_func;
static int trace_OCIDateTimeFromArray = 1;

sword OCIDateTimeFromArray(void *hndl, OCIError *err, ub1 *inarray, ub4 len, ub1 type, OCIDateTime *datetime, const OCIInterval *reftz, ub1 fsprec)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDateTimeFromArray_func(hndl, err, inarray, len, type, datetime, reftz, fsprec);
    if (trace_OCIDateTimeFromArray) {
        ocidump_log("%0*lX: OCIDateTimeFromArray(%p, %p, %p, %u, %u, %p, %p, %u) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndl,
                     err,
                     inarray,
                     len,
                     type,
                     datetime,
                     reftz,
                     fsprec,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDateTimeFromText_func_t)(void *hndl, OCIError *err, const OraText *date_str, size_t dstr_length, const OraText *fmt, ub1 fmt_length, const OraText *lang_name, size_t lang_length, OCIDateTime *date);
static OCIDateTimeFromText_func_t OCIDateTimeFromText_func;
static int trace_OCIDateTimeFromText = 1;

sword OCIDateTimeFromText(void *hndl, OCIError *err, const OraText *date_str, size_t dstr_length, const OraText *fmt, ub1 fmt_length, const OraText *lang_name, size_t lang_length, OCIDateTime *date)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDateTimeFromText_func(hndl, err, date_str, dstr_length, fmt, fmt_length, lang_name, lang_length, date);
    if (trace_OCIDateTimeFromText) {
        if (ocidump_hide_string) {
            dstr_length = 6;
            date_str = (OraText*)"hidden";
            fmt_length = 6;
            fmt = (OraText*)"hidden";
            lang_length = 6;
            lang_name = (OraText*)"hidden";
        }
        ocidump_log("%0*lX: OCIDateTimeFromText(%p, %p, \"%.*s\", %" OCIDUMP_SIZET_FMT ", \"%.*s\", %u, \"%.*s\", %" OCIDUMP_SIZET_FMT ", %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndl,
                     err,
                     (int)dstr_length, date_str,
                     dstr_length,
                     (int)fmt_length, fmt,
                     fmt_length,
                     (int)lang_length, lang_name,
                     lang_length,
                     date,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDateTimeGetDate_func_t)(void *hndl, OCIError *err, const OCIDateTime *date, sb2 *yr, ub1 *mnth, ub1 *dy);
static OCIDateTimeGetDate_func_t OCIDateTimeGetDate_func;
static int trace_OCIDateTimeGetDate = 1;

sword OCIDateTimeGetDate(void *hndl, OCIError *err, const OCIDateTime *date, sb2 *yr, ub1 *mnth, ub1 *dy)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDateTimeGetDate_func(hndl, err, date, yr, mnth, dy);
    if (trace_OCIDateTimeGetDate) {
        ocidump_log("%0*lX: OCIDateTimeGetDate(%p, %p, %p, [%d], [%u], [%u]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndl,
                     err,
                     date,
                     *yr,
                     *mnth,
                     *dy,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDateTimeGetTime_func_t)(void *hndl, OCIError *err, OCIDateTime *datetime, ub1 *hr, ub1 *mm, ub1 *ss, ub4 *fsec);
static OCIDateTimeGetTime_func_t OCIDateTimeGetTime_func;
static int trace_OCIDateTimeGetTime = 1;

sword OCIDateTimeGetTime(void *hndl, OCIError *err, OCIDateTime *datetime, ub1 *hr, ub1 *mm, ub1 *ss, ub4 *fsec)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDateTimeGetTime_func(hndl, err, datetime, hr, mm, ss, fsec);
    if (trace_OCIDateTimeGetTime) {
        ocidump_log("%0*lX: OCIDateTimeGetTime(%p, %p, %p, [%u], [%u], [%u], [%u]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndl,
                     err,
                     datetime,
                     *hr,
                     *mm,
                     *ss,
                     *fsec,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDateTimeGetTimeZoneName_func_t)(void *hndl, OCIError *err, const OCIDateTime *datetime, ub1 *buf, ub4 *buflen);
static OCIDateTimeGetTimeZoneName_func_t OCIDateTimeGetTimeZoneName_func;
static int trace_OCIDateTimeGetTimeZoneName = 1;

sword OCIDateTimeGetTimeZoneName(void *hndl, OCIError *err, const OCIDateTime *datetime, ub1 *buf, ub4 *buflen)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    ub4 old_blen = *buflen;

    if (!is_initialized) {
        initialize();
    }
    ret = OCIDateTimeGetTimeZoneName_func(hndl, err, datetime, buf, buflen);
    if (trace_OCIDateTimeGetTimeZoneName) {
        ub4 blen = *buflen;

        if (ocidump_hide_string) {
            blen = 6;
            buf = (OraText*)"hidden";
        }
        ocidump_log("%0*lX: OCIDateTimeGetTimeZoneName(%p, %p, %p, \"%.*s\", [%d -> %d]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndl,
                     err,
                     datetime,
                     blen, buf,
                     old_blen, blen,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDateTimeGetTimeZoneOffset_func_t)(void *hndl, OCIError *err, const OCIDateTime *datetime, sb1 *hr, sb1 *mm);
static OCIDateTimeGetTimeZoneOffset_func_t OCIDateTimeGetTimeZoneOffset_func;
static int trace_OCIDateTimeGetTimeZoneOffset = 1;

sword OCIDateTimeGetTimeZoneOffset(void *hndl, OCIError *err, const OCIDateTime *datetime, sb1 *hr, sb1 *mm)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDateTimeGetTimeZoneOffset_func(hndl, err, datetime, hr, mm);
    if (trace_OCIDateTimeGetTimeZoneOffset) {
        ocidump_log("%0*lX: OCIDateTimeGetTimeZoneOffset(%p, %p, %p, [%d], [%d]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndl,
                     err,
                     datetime,
                     *hr,
                     *mm,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDateTimeIntervalAdd_func_t)(void *hndl, OCIError *err, OCIDateTime *datetime, OCIInterval *inter, OCIDateTime *outdatetime);
static OCIDateTimeIntervalAdd_func_t OCIDateTimeIntervalAdd_func;
static int trace_OCIDateTimeIntervalAdd = 1;

sword OCIDateTimeIntervalAdd(void *hndl, OCIError *err, OCIDateTime *datetime, OCIInterval *inter, OCIDateTime *outdatetime)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDateTimeIntervalAdd_func(hndl, err, datetime, inter, outdatetime);
    if (trace_OCIDateTimeIntervalAdd) {
        ocidump_log("%0*lX: OCIDateTimeIntervalAdd(%p, %p, %p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndl,
                     err,
                     datetime,
                     inter,
                     outdatetime,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDateTimeIntervalSub_func_t)(void *hndl, OCIError *err, OCIDateTime *datetime, OCIInterval *inter, OCIDateTime *outdatetime);
static OCIDateTimeIntervalSub_func_t OCIDateTimeIntervalSub_func;
static int trace_OCIDateTimeIntervalSub = 1;

sword OCIDateTimeIntervalSub(void *hndl, OCIError *err, OCIDateTime *datetime, OCIInterval *inter, OCIDateTime *outdatetime)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDateTimeIntervalSub_func(hndl, err, datetime, inter, outdatetime);
    if (trace_OCIDateTimeIntervalSub) {
        ocidump_log("%0*lX: OCIDateTimeIntervalSub(%p, %p, %p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndl,
                     err,
                     datetime,
                     inter,
                     outdatetime,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDateTimeSubtract_func_t)(void *hndl, OCIError *err, OCIDateTime *indate1, OCIDateTime *indate2, OCIInterval *inter);
static OCIDateTimeSubtract_func_t OCIDateTimeSubtract_func;
static int trace_OCIDateTimeSubtract = 1;

sword OCIDateTimeSubtract(void *hndl, OCIError *err, OCIDateTime *indate1, OCIDateTime *indate2, OCIInterval *inter)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDateTimeSubtract_func(hndl, err, indate1, indate2, inter);
    if (trace_OCIDateTimeSubtract) {
        ocidump_log("%0*lX: OCIDateTimeSubtract(%p, %p, %p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndl,
                     err,
                     indate1,
                     indate2,
                     inter,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDateTimeSysTimeStamp_func_t)(void *hndl, OCIError *err, OCIDateTime *sys_date);
static OCIDateTimeSysTimeStamp_func_t OCIDateTimeSysTimeStamp_func;
static int trace_OCIDateTimeSysTimeStamp = 1;

sword OCIDateTimeSysTimeStamp(void *hndl, OCIError *err, OCIDateTime *sys_date)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDateTimeSysTimeStamp_func(hndl, err, sys_date);
    if (trace_OCIDateTimeSysTimeStamp) {
        ocidump_log("%0*lX: OCIDateTimeSysTimeStamp(%p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndl,
                     err,
                     sys_date,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDateTimeToArray_func_t)(void *hndl, OCIError *err, const OCIDateTime *datetime, const OCIInterval *reftz, ub1 *outarray, ub4 *len, ub1 fsprec);
static OCIDateTimeToArray_func_t OCIDateTimeToArray_func;
static int trace_OCIDateTimeToArray = 1;

sword OCIDateTimeToArray(void *hndl, OCIError *err, const OCIDateTime *datetime, const OCIInterval *reftz, ub1 *outarray, ub4 *len, ub1 fsprec)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDateTimeToArray_func(hndl, err, datetime, reftz, outarray, len, fsprec);
    if (trace_OCIDateTimeToArray) {
        ocidump_log("%0*lX: OCIDateTimeToArray(%p, %p, %p, %p, %p, [%u], %u) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndl,
                     err,
                     datetime,
                     reftz,
                     outarray,
                     *len,
                     fsprec,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDateTimeToText_func_t)(void *hndl, OCIError *err, const OCIDateTime *date, const OraText *fmt, ub1 fmt_length, ub1 fsprec, const OraText *lang_name, size_t lang_length, ub4 *buf_size, OraText *buf);
static OCIDateTimeToText_func_t OCIDateTimeToText_func;
static int trace_OCIDateTimeToText = 1;

sword OCIDateTimeToText(void *hndl, OCIError *err, const OCIDateTime *date, const OraText *fmt, ub1 fmt_length, ub1 fsprec, const OraText *lang_name, size_t lang_length, ub4 *buf_size, OraText *buf)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    ub4 old_bsize = *buf_size;

    if (!is_initialized) {
        initialize();
    }
    ret = OCIDateTimeToText_func(hndl, err, date, fmt, fmt_length, fsprec, lang_name, lang_length, buf_size, buf);
    if (trace_OCIDateTimeToText) {
        ub4 new_bsize = *buf_size;

        if (ocidump_hide_string) {
            fmt_length = 6;
            fmt = (OraText*)"hidden";
            lang_length = 6;
            lang_name = (OraText*)"hidden";
            new_bsize = 6;
            buf = (OraText*)"hidden";
        }
        ocidump_log("%0*lX: OCIDateTimeToText(%p, %p, %p, \"%.*s\", %u, %u, \"%.*s\", %" OCIDUMP_SIZET_FMT ", [%u -> %u], \"%.*s\") => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndl,
                     err,
                     date,
                     fmt_length, fmt,
                     fmt_length,
                     fsprec,
                     (int)lang_length, lang_name,
                     lang_length,
                     old_bsize, new_bsize,
                     new_bsize, buf,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDateToText_func_t)(OCIError *err, const OCIDate *date, const oratext *fmt, ub1 fmt_length, const oratext *lang_name, ub4 lang_length, ub4 *buf_size, oratext *buf);
static OCIDateToText_func_t OCIDateToText_func;
static int trace_OCIDateToText = 1;

sword OCIDateToText(OCIError *err, const OCIDate *date, const oratext *fmt, ub1 fmt_length, const oratext *lang_name, ub4 lang_length, ub4 *buf_size, oratext *buf)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    ub4 old_bsize = *buf_size;

    if (!is_initialized) {
        initialize();
    }
    ret = OCIDateToText_func(err, date, fmt, fmt_length, lang_name, lang_length, buf_size, buf);
    if (trace_OCIDateToText) {
        ub4 new_bsize = *buf_size;

        if (ocidump_hide_string) {
            fmt_length = 6;
            fmt = (OraText*)"hidden";
            lang_length = 6;
            lang_name = (OraText*)"hidden";
            new_bsize = 6;
            buf = (OraText*)"hidden";
        }
        ocidump_log("%0*lX: OCIDateToText(%p, {%04d-%02u-%02u %02u:%02u:%02u}, \"%.*s\", %u, \"%.*s\", %u, [%u -> %u], \"%.*s\") => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     date->OCIDateYYYY, date->OCIDateMM, date->OCIDateDD, date->OCIDateTime.OCITimeHH, date->OCIDateTime.OCITimeMI, date->OCIDateTime.OCITimeSS,
                     fmt_length, fmt,
                     fmt_length,
                     lang_length, lang_name,
                     lang_length,
                     old_bsize, new_bsize,
                     new_bsize, buf,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDateZoneToZone_func_t)(OCIError *err, const OCIDate *date1, const oratext *zon1, ub4 zon1_length, const oratext *zon2, ub4 zon2_length, OCIDate *date2);
static OCIDateZoneToZone_func_t OCIDateZoneToZone_func;
static int trace_OCIDateZoneToZone = 1;

sword OCIDateZoneToZone(OCIError *err, const OCIDate *date1, const oratext *zon1, ub4 zon1_length, const oratext *zon2, ub4 zon2_length, OCIDate *date2)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDateZoneToZone_func(err, date1, zon1, zon1_length, zon2, zon2_length, date2);
    if (trace_OCIDateZoneToZone) {
        if (ocidump_hide_string) {
            zon1_length = 6;
            zon1 = (OraText*)"hidden";
            zon2_length = 6;
            zon2 = (OraText*)"hidden";
        }
        ocidump_log("%0*lX: OCIDateZoneToZone(%p, {%04d-%02u-%02u %02u:%02u:%02u}, \"%.*s\", %u, \"%.*s\", %u, {%04d-%02u-%02u %02u:%02u:%02u}) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     date1->OCIDateYYYY, date1->OCIDateMM, date1->OCIDateDD, date1->OCIDateTime.OCITimeHH, date1->OCIDateTime.OCITimeMI, date1->OCIDateTime.OCITimeSS,
                     zon1_length, zon1,
                     zon1_length,
                     zon2_length, zon2,
                     zon2_length,
                     date2->OCIDateYYYY, date2->OCIDateMM, date2->OCIDateDD, date2->OCIDateTime.OCITimeHH, date2->OCIDateTime.OCITimeMI, date2->OCIDateTime.OCITimeSS,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDefineArrayOfStruct_func_t)(OCIDefine *defnp, OCIError *errhp, ub4 pvskip, ub4 indskip, ub4 rlskip, ub4 rcskip);
static OCIDefineArrayOfStruct_func_t OCIDefineArrayOfStruct_func;
static int trace_OCIDefineArrayOfStruct = 1;

sword OCIDefineArrayOfStruct(OCIDefine *defnp, OCIError *errhp, ub4 pvskip, ub4 indskip, ub4 rlskip, ub4 rcskip)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDefineArrayOfStruct_func(defnp, errhp, pvskip, indskip, rlskip, rcskip);
    if (trace_OCIDefineArrayOfStruct) {
        ocidump_log("%0*lX: OCIDefineArrayOfStruct(%p, %p, %u, %u, %u, %u) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     defnp,
                     errhp,
                     pvskip,
                     indskip,
                     rlskip,
                     rcskip,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDefineByPos_func_t)(OCIStmt *stmtp, OCIDefine **defnp, OCIError *errhp, ub4 position, dvoid *valuep, sb4 value_sz, ub2 dty, dvoid *indp, ub2 *rlenp, ub2 *rcodep, ub4 mode);
static OCIDefineByPos_func_t OCIDefineByPos_func;
static int trace_OCIDefineByPos = 1;

sword OCIDefineByPos(OCIStmt *stmtp, OCIDefine **defnp, OCIError *errhp, ub4 position, dvoid *valuep, sb4 value_sz, ub2 dty, dvoid *indp, ub2 *rlenp, ub2 *rcodep, ub4 mode)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDefineByPos_func(stmtp, defnp, errhp, position, valuep, value_sz, dty, indp, rlenp, rcodep, mode);
    if (trace_OCIDefineByPos) {
        ocidump_log("%0*lX: OCIDefineByPos(%p, [%p], %p, %u, %p, %d, %u, %p, %p, %p, 0x%x) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     stmtp,
                     *defnp,
                     errhp,
                     position,
                     valuep,
                     value_sz,
                     dty,
                     indp,
                     rlenp,
                     rcodep,
                     mode,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDefineDynamic_func_t)(OCIDefine *defnp, OCIError *errhp, void  *octxp, OCICallbackDefine ocbfp);
static OCIDefineDynamic_func_t OCIDefineDynamic_func;
static int trace_OCIDefineDynamic = 1;

sword OCIDefineDynamic(OCIDefine *defnp, OCIError *errhp, void  *octxp, OCICallbackDefine ocbfp)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDefineDynamic_func(defnp, errhp, octxp, ocbfp);
    if (trace_OCIDefineDynamic) {
        ocidump_log("%0*lX: OCIDefineDynamic(%p, %p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     defnp,
                     errhp,
                     octxp,
                     ocbfp,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDefineObject_func_t)(OCIDefine *defnp, OCIError *errhp, const OCIType *type, dvoid **pgvpp, ub4 *pvszsp, dvoid **indpp, ub4 *indszp);
static OCIDefineObject_func_t OCIDefineObject_func;
static int trace_OCIDefineObject = 1;

sword OCIDefineObject(OCIDefine *defnp, OCIError *errhp, const OCIType *type, dvoid **pgvpp, ub4 *pvszsp, dvoid **indpp, ub4 *indszp)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDefineObject_func(defnp, errhp, type, pgvpp, pvszsp, indpp, indszp);
    if (trace_OCIDefineObject) {
        ocidump_log("%0*lX: OCIDefineObject(%p, %p, %p, %p, %p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     defnp,
                     errhp,
                     type,
                     pgvpp,
                     pvszsp,
                     indpp,
                     indszp,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDescribeAny_func_t)(OCISvcCtx *svchp, OCIError *errhp, dvoid *objptr, ub4 objnm_len, ub1 objptr_typ, ub1 info_level, ub1 objtyp, OCIDescribe *dschp);
static OCIDescribeAny_func_t OCIDescribeAny_func;
static int trace_OCIDescribeAny = 1;

sword OCIDescribeAny(OCISvcCtx *svchp, OCIError *errhp, dvoid *objptr, ub4 objnm_len, ub1 objptr_typ, ub1 info_level, ub1 objtyp, OCIDescribe *dschp)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDescribeAny_func(svchp, errhp, objptr, objnm_len, objptr_typ, info_level, objtyp, dschp);
    if (trace_OCIDescribeAny) {
        ocidump_log("%0*lX: OCIDescribeAny(%p, %p, %p, %u, %u, %u, %u, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     objptr,
                     objnm_len,
                     objptr_typ,
                     info_level,
                     objtyp,
                     dschp,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDescriptorAlloc_func_t)(const dvoid *parenth, dvoid **descpp, ub4 type, size_t xtramem_sz, dvoid **usrmempp);
static OCIDescriptorAlloc_func_t OCIDescriptorAlloc_func;
static int trace_OCIDescriptorAlloc = 1;

sword OCIDescriptorAlloc(const dvoid *parenth, dvoid **descpp, ub4 type, size_t xtramem_sz, dvoid **usrmempp)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDescriptorAlloc_func(parenth, descpp, type, xtramem_sz, usrmempp);
    if (trace_OCIDescriptorAlloc) {
        ocidump_log("%0*lX: OCIDescriptorAlloc(%p, [%p], %s, %" OCIDUMP_SIZET_FMT ", %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     parenth,
                     *descpp,
                     ocidump_htype2name(type, buf1),
                     xtramem_sz,
                     usrmempp,
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCIDescriptorFree_func_t)(dvoid *descp, ub4 type);
static OCIDescriptorFree_func_t OCIDescriptorFree_func;
static int trace_OCIDescriptorFree = 1;

sword OCIDescriptorFree(dvoid *descp, ub4 type)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDescriptorFree_func(descp, type);
    if (trace_OCIDescriptorFree) {
        ocidump_log("%0*lX: OCIDescriptorFree(%p, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     descp,
                     ocidump_htype2name(type, buf1),
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCIDurationBegin_func_t)(OCIEnv *env, OCIError *err, const OCISvcCtx *svc, OCIDuration parent, OCIDuration *dur);
static OCIDurationBegin_func_t OCIDurationBegin_func;
static int trace_OCIDurationBegin = 1;

sword OCIDurationBegin(OCIEnv *env, OCIError *err, const OCISvcCtx *svc, OCIDuration parent, OCIDuration *dur)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDurationBegin_func(env, err, svc, parent, dur);
    if (trace_OCIDurationBegin) {
        ocidump_log("%0*lX: OCIDurationBegin(%p, %p, %p, %u, [%u]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     svc,
                     parent,
                     *dur,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDurationEnd_func_t)(OCIEnv *env, OCIError *err, const OCISvcCtx *svc, OCIDuration duration);
static OCIDurationEnd_func_t OCIDurationEnd_func;
static int trace_OCIDurationEnd = 1;

sword OCIDurationEnd(OCIEnv *env, OCIError *err, const OCISvcCtx *svc, OCIDuration duration)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDurationEnd_func(env, err, svc, duration);
    if (trace_OCIDurationEnd) {
        ocidump_log("%0*lX: OCIDurationEnd(%p, %p, %p, %u) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     svc,
                     duration,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIDurationGetParent_func_t)(OCIEnv *env, OCIError *err, OCIDuration duration, OCIDuration *parent);
static OCIDurationGetParent_func_t OCIDurationGetParent_func;
static int trace_OCIDurationGetParent = 1;

sword OCIDurationGetParent(OCIEnv *env, OCIError *err, OCIDuration duration, OCIDuration *parent)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIDurationGetParent_func(env, err, duration, parent);
    if (trace_OCIDurationGetParent) {
        ocidump_log("%0*lX: OCIDurationGetParent(%p, %p, %u, [%u]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     duration,
                     *parent,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIEnvCreate_func_t)(OCIEnv **envp, ub4 mode, dvoid *ctxp, dvoid *(*malocfp)(dvoid *ctxp, size_t size), dvoid *(*ralocfp)(dvoid *ctxp, dvoid *memptr, size_t newsize), void   (*mfreefp)(dvoid *ctxp, dvoid *memptr), size_t xtramem_sz, dvoid **usrmempp);
static OCIEnvCreate_func_t OCIEnvCreate_func;
static int trace_OCIEnvCreate = 1;

sword OCIEnvCreate(OCIEnv **envp, ub4 mode, dvoid *ctxp, dvoid *(*malocfp)(dvoid *ctxp, size_t size), dvoid *(*ralocfp)(dvoid *ctxp, dvoid *memptr, size_t newsize), void   (*mfreefp)(dvoid *ctxp, dvoid *memptr), size_t xtramem_sz, dvoid **usrmempp)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIEnvCreate_func(envp, mode, ctxp, malocfp, ralocfp, mfreefp, xtramem_sz, usrmempp);
    if (trace_OCIEnvCreate) {
        ocidump_log("%0*lX: OCIEnvCreate([%p], 0x%x, %p, %p, %p, %p, %" OCIDUMP_SIZET_FMT ", %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     *envp,
                     mode,
                     ctxp,
                     malocfp,
                     ralocfp,
                     mfreefp,
                     xtramem_sz,
                     usrmempp,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIEnvInit_func_t)(OCIEnv **envp, ub4 mode, size_t xtramem_sz, dvoid **usrmempp);
static OCIEnvInit_func_t OCIEnvInit_func;
static int trace_OCIEnvInit = 1;

sword OCIEnvInit(OCIEnv **envp, ub4 mode, size_t xtramem_sz, dvoid **usrmempp)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIEnvInit_func(envp, mode, xtramem_sz, usrmempp);
    if (trace_OCIEnvInit) {
        ocidump_log("%0*lX: OCIEnvInit([%p], 0x%x, %" OCIDUMP_SIZET_FMT ", %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     *envp,
                     mode,
                     xtramem_sz,
                     usrmempp,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIEnvNlsCreate_func_t)(OCIEnv **envhpp, ub4 mode, void *ctxp, void *(*malocfp)(void *ctxp, size_t size), void *(*ralocfp)(void *ctxp, void *memptr, size_t newsize), void (*mfreefp)(void *ctxp, void *memptr), size_t xtramemsz, void **usrmempp, ub2 charset, ub2 ncharset);
static OCIEnvNlsCreate_func_t OCIEnvNlsCreate_func;
static int trace_OCIEnvNlsCreate = 1;

sword OCIEnvNlsCreate(OCIEnv **envhpp, ub4 mode, void *ctxp, void *(*malocfp)(void *ctxp, size_t size), void *(*ralocfp)(void *ctxp, void *memptr, size_t newsize), void (*mfreefp)(void *ctxp, void *memptr), size_t xtramemsz, void **usrmempp, ub2 charset, ub2 ncharset)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIEnvNlsCreate_func(envhpp, mode, ctxp, malocfp, ralocfp, mfreefp, xtramemsz, usrmempp, charset, ncharset);
    if (trace_OCIEnvNlsCreate) {
        ocidump_log("%0*lX: OCIEnvNlsCreate([%p], 0x%x, %p, %p, %p, %p, %" OCIDUMP_SIZET_FMT ", %p, %u, %u) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     *envhpp,
                     mode,
                     ctxp,
                     malocfp,
                     ralocfp,
                     mfreefp,
                     xtramemsz,
                     usrmempp,
                     charset,
                     ncharset,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIErrorGet_func_t)(dvoid *hndlp, ub4 recordno, text *sqlstate, sb4 *errcodep, text *bufp, ub4 bufsiz, ub4 type);
static OCIErrorGet_func_t OCIErrorGet_func;
static int trace_OCIErrorGet = 1;

sword OCIErrorGet(dvoid *hndlp, ub4 recordno, text *sqlstate, sb4 *errcodep, text *bufp, ub4 bufsiz, ub4 type)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIErrorGet_func(hndlp, recordno, sqlstate, errcodep, bufp, bufsiz, type);
    if (trace_OCIErrorGet) {
        if (ocidump_hide_string) {
            bufsiz = 6;
            bufp = (OraText*)"hidden";
        }
        ocidump_log("%0*lX: OCIErrorGet(%p, %u, %p, [%d], \"%.*s\", %u, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndlp,
                     recordno,
                     sqlstate,
                     *errcodep,
                     bufsiz, bufp,
                     bufsiz,
                     ocidump_htype2name(type, buf1),
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCIFEnvCreate_func_t)(OCIEnv **envp, ub4 mode, void *ctxp, void *(*malocfp)(void  *ctxp, size_t size), void *(*ralocfp)(void  *ctxp, void  *memptr, size_t newsize), void  (*mfreefp)(void  *ctxp, void  *memptr), size_t xtramem_sz, void  **usrmempp, void  *fupg);
static OCIFEnvCreate_func_t OCIFEnvCreate_func;
static int trace_OCIFEnvCreate = 1;

sword OCIFEnvCreate(OCIEnv **envp, ub4 mode, void *ctxp, void *(*malocfp)(void  *ctxp, size_t size), void *(*ralocfp)(void  *ctxp, void  *memptr, size_t newsize), void  (*mfreefp)(void  *ctxp, void  *memptr), size_t xtramem_sz, void  **usrmempp, void  *fupg)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIFEnvCreate_func(envp, mode, ctxp, malocfp, ralocfp, mfreefp, xtramem_sz, usrmempp, fupg);
    if (trace_OCIFEnvCreate) {
        ocidump_log("%0*lX: OCIFEnvCreate([%p], 0x%x, %p, %p, %p, %p, %" OCIDUMP_SIZET_FMT ", %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     *envp,
                     mode,
                     ctxp,
                     malocfp,
                     ralocfp,
                     mfreefp,
                     xtramem_sz,
                     usrmempp,
                     fupg,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIHandleAlloc_func_t)(const dvoid *parenth, dvoid **hndlpp, ub4 type, size_t xtramem_sz, dvoid **usrmempp);
static OCIHandleAlloc_func_t OCIHandleAlloc_func;
static int trace_OCIHandleAlloc = 1;

sword OCIHandleAlloc(const dvoid *parenth, dvoid **hndlpp, ub4 type, size_t xtramem_sz, dvoid **usrmempp)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIHandleAlloc_func(parenth, hndlpp, type, xtramem_sz, usrmempp);
    if (trace_OCIHandleAlloc) {
        ocidump_log("%0*lX: OCIHandleAlloc(%p, [%p], %s, %" OCIDUMP_SIZET_FMT ", %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     parenth,
                     *hndlpp,
                     ocidump_htype2name(type, buf1),
                     xtramem_sz,
                     usrmempp,
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCIHandleFree_func_t)(dvoid *hndlp, ub4 type);
static OCIHandleFree_func_t OCIHandleFree_func;
static int trace_OCIHandleFree = 1;

sword OCIHandleFree(dvoid *hndlp, ub4 type)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIHandleFree_func(hndlp, type);
    if (trace_OCIHandleFree) {
        ocidump_log("%0*lX: OCIHandleFree(%p, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndlp,
                     ocidump_htype2name(type, buf1),
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCIInitialize_func_t)(ub4 mode, dvoid *ctxp, dvoid *(*malocfp)(dvoid *ctxp, size_t size), dvoid *(*ralocfp)(dvoid *ctxp, dvoid *memptr, size_t newsize), void   (*mfreefp)(dvoid *ctxp, dvoid *memptr));
static OCIInitialize_func_t OCIInitialize_func;
static int trace_OCIInitialize = 1;

sword OCIInitialize(ub4 mode, dvoid *ctxp, dvoid *(*malocfp)(dvoid *ctxp, size_t size), dvoid *(*ralocfp)(dvoid *ctxp, dvoid *memptr, size_t newsize), void   (*mfreefp)(dvoid *ctxp, dvoid *memptr))
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIInitialize_func(mode, ctxp, malocfp, ralocfp, mfreefp);
    if (trace_OCIInitialize) {
        ocidump_log("%0*lX: OCIInitialize(0x%x, %p, %p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     mode,
                     ctxp,
                     malocfp,
                     ralocfp,
                     mfreefp,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIIntervalAdd_func_t)(void *hndl, OCIError *err, OCIInterval *addend1, OCIInterval *addend2, OCIInterval *result);
static OCIIntervalAdd_func_t OCIIntervalAdd_func;
static int trace_OCIIntervalAdd = 1;

sword OCIIntervalAdd(void *hndl, OCIError *err, OCIInterval *addend1, OCIInterval *addend2, OCIInterval *result)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIIntervalAdd_func(hndl, err, addend1, addend2, result);
    if (trace_OCIIntervalAdd) {
        ocidump_log("%0*lX: OCIIntervalAdd(%p, %p, %p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndl,
                     err,
                     addend1,
                     addend2,
                     result,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIIntervalAssign_func_t)(void *hndl, OCIError *err, const OCIInterval *ininter, OCIInterval *outinter);
static OCIIntervalAssign_func_t OCIIntervalAssign_func;
static int trace_OCIIntervalAssign = 1;

sword OCIIntervalAssign(void *hndl, OCIError *err, const OCIInterval *ininter, OCIInterval *outinter)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIIntervalAssign_func(hndl, err, ininter, outinter);
    if (trace_OCIIntervalAssign) {
        ocidump_log("%0*lX: OCIIntervalAssign(%p, %p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndl,
                     err,
                     ininter,
                     outinter,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIIntervalCheck_func_t)(void *hndl, OCIError *err, const OCIInterval *interval, ub4 *valid);
static OCIIntervalCheck_func_t OCIIntervalCheck_func;
static int trace_OCIIntervalCheck = 1;

sword OCIIntervalCheck(void *hndl, OCIError *err, const OCIInterval *interval, ub4 *valid)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIIntervalCheck_func(hndl, err, interval, valid);
    if (trace_OCIIntervalCheck) {
        ocidump_log("%0*lX: OCIIntervalCheck(%p, %p, %p, [0x%x]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndl,
                     err,
                     interval,
                     *valid,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIIntervalCompare_func_t)(void *hndl, OCIError *err, OCIInterval *inter1, OCIInterval *inter2, sword *result);
static OCIIntervalCompare_func_t OCIIntervalCompare_func;
static int trace_OCIIntervalCompare = 1;

sword OCIIntervalCompare(void *hndl, OCIError *err, OCIInterval *inter1, OCIInterval *inter2, sword *result)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIIntervalCompare_func(hndl, err, inter1, inter2, result);
    if (trace_OCIIntervalCompare) {
        ocidump_log("%0*lX: OCIIntervalCompare(%p, %p, %p, %p, [%d]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndl,
                     err,
                     inter1,
                     inter2,
                     *result,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIIntervalDivide_func_t)(void *hndl, OCIError *err, OCIInterval *dividend, OCINumber *divisor, OCIInterval *result);
static OCIIntervalDivide_func_t OCIIntervalDivide_func;
static int trace_OCIIntervalDivide = 1;

sword OCIIntervalDivide(void *hndl, OCIError *err, OCIInterval *dividend, OCINumber *divisor, OCIInterval *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIIntervalDivide_func(hndl, err, dividend, divisor, result);
    if (trace_OCIIntervalDivide) {
        ocidump_log("%0*lX: OCIIntervalDivide(%p, %p, %p, %s, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndl,
                     err,
                     dividend,
                     ocidump_ocinumber(buf1, divisor),
                     result,
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCIIntervalFromNumber_func_t)(void *hndl, OCIError *err, OCIInterval *inter, OCINumber *number);
static OCIIntervalFromNumber_func_t OCIIntervalFromNumber_func;
static int trace_OCIIntervalFromNumber = 1;

sword OCIIntervalFromNumber(void *hndl, OCIError *err, OCIInterval *inter, OCINumber *number)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIIntervalFromNumber_func(hndl, err, inter, number);
    if (trace_OCIIntervalFromNumber) {
        ocidump_log("%0*lX: OCIIntervalFromNumber(%p, %p, %p, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndl,
                     err,
                     inter,
                     ocidump_ocinumber(buf1, number),
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCIIntervalFromTZ_func_t)(void *hndl, OCIError *err, const oratext *inpstring, size_t str_len, OCIInterval *result);
static OCIIntervalFromTZ_func_t OCIIntervalFromTZ_func;
static int trace_OCIIntervalFromTZ = 1;

sword OCIIntervalFromTZ(void *hndl, OCIError *err, const oratext *inpstring, size_t str_len, OCIInterval *result)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIIntervalFromTZ_func(hndl, err, inpstring, str_len, result);
    if (trace_OCIIntervalFromTZ) {
        if (ocidump_hide_string) {
            str_len = 6;
            inpstring = (OraText*)"hidden";
        }
        ocidump_log("%0*lX: OCIIntervalFromTZ(%p, %p, \"%.*s\", %" OCIDUMP_SIZET_FMT ", %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndl,
                     err,
                     (int)str_len, inpstring,
                     str_len,
                     result,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIIntervalFromText_func_t)(void *hndl, OCIError *err, const OraText *inpstr, size_t str_len, OCIInterval *result);
static OCIIntervalFromText_func_t OCIIntervalFromText_func;
static int trace_OCIIntervalFromText = 1;

sword OCIIntervalFromText(void *hndl, OCIError *err, const OraText *inpstr, size_t str_len, OCIInterval *result)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIIntervalFromText_func(hndl, err, inpstr, str_len, result);
    if (trace_OCIIntervalFromText) {
        if (ocidump_hide_string) {
            str_len = 6;
            inpstr = (OraText*)"hidden";
        }
        ocidump_log("%0*lX: OCIIntervalFromText(%p, %p, \"%.*s\", %" OCIDUMP_SIZET_FMT ", %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndl,
                     err,
                     (int)str_len, inpstr,
                     str_len,
                     result,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIIntervalGetDaySecond_func_t)(void *hndl, OCIError *err, sb4 *dy, sb4 *hr, sb4 *mm, sb4 *ss, sb4 *fsec, const OCIInterval *result);
static OCIIntervalGetDaySecond_func_t OCIIntervalGetDaySecond_func;
static int trace_OCIIntervalGetDaySecond = 1;

sword OCIIntervalGetDaySecond(void *hndl, OCIError *err, sb4 *dy, sb4 *hr, sb4 *mm, sb4 *ss, sb4 *fsec, const OCIInterval *result)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIIntervalGetDaySecond_func(hndl, err, dy, hr, mm, ss, fsec, result);
    if (trace_OCIIntervalGetDaySecond) {
        ocidump_log("%0*lX: OCIIntervalGetDaySecond(%p, %p, [%d], [%d], [%d], [%d], [%d], %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndl,
                     err,
                     *dy,
                     *hr,
                     *mm,
                     *ss,
                     *fsec,
                     result,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIIntervalGetYearMonth_func_t)(void *hndl, OCIError *err, sb4 *yr, sb4 *mnth, const OCIInterval *result);
static OCIIntervalGetYearMonth_func_t OCIIntervalGetYearMonth_func;
static int trace_OCIIntervalGetYearMonth = 1;

sword OCIIntervalGetYearMonth(void *hndl, OCIError *err, sb4 *yr, sb4 *mnth, const OCIInterval *result)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIIntervalGetYearMonth_func(hndl, err, yr, mnth, result);
    if (trace_OCIIntervalGetYearMonth) {
        ocidump_log("%0*lX: OCIIntervalGetYearMonth(%p, %p, [%d], [%d], %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndl,
                     err,
                     *yr,
                     *mnth,
                     result,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIIntervalMultiply_func_t)(void *hndl, OCIError *err, const OCIInterval *inter, OCINumber *nfactor, OCIInterval *result);
static OCIIntervalMultiply_func_t OCIIntervalMultiply_func;
static int trace_OCIIntervalMultiply = 1;

sword OCIIntervalMultiply(void *hndl, OCIError *err, const OCIInterval *inter, OCINumber *nfactor, OCIInterval *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIIntervalMultiply_func(hndl, err, inter, nfactor, result);
    if (trace_OCIIntervalMultiply) {
        ocidump_log("%0*lX: OCIIntervalMultiply(%p, %p, %p, %s, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndl,
                     err,
                     inter,
                     ocidump_ocinumber(buf1, nfactor),
                     result,
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCIIntervalSetDaySecond_func_t)(void *hndl, OCIError *err, sb4 dy, sb4 hr, sb4 mm, sb4 ss, sb4 fsec, OCIInterval *result);
static OCIIntervalSetDaySecond_func_t OCIIntervalSetDaySecond_func;
static int trace_OCIIntervalSetDaySecond = 1;

sword OCIIntervalSetDaySecond(void *hndl, OCIError *err, sb4 dy, sb4 hr, sb4 mm, sb4 ss, sb4 fsec, OCIInterval *result)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIIntervalSetDaySecond_func(hndl, err, dy, hr, mm, ss, fsec, result);
    if (trace_OCIIntervalSetDaySecond) {
        ocidump_log("%0*lX: OCIIntervalSetDaySecond(%p, %p, %d, %d, %d, %d, %d, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndl,
                     err,
                     dy,
                     hr,
                     mm,
                     ss,
                     fsec,
                     result,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIIntervalSetYearMonth_func_t)(void *hndl, OCIError *err, sb4 yr, sb4 mnth, OCIInterval *result);
static OCIIntervalSetYearMonth_func_t OCIIntervalSetYearMonth_func;
static int trace_OCIIntervalSetYearMonth = 1;

sword OCIIntervalSetYearMonth(void *hndl, OCIError *err, sb4 yr, sb4 mnth, OCIInterval *result)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIIntervalSetYearMonth_func(hndl, err, yr, mnth, result);
    if (trace_OCIIntervalSetYearMonth) {
        ocidump_log("%0*lX: OCIIntervalSetYearMonth(%p, %p, %d, %d, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndl,
                     err,
                     yr,
                     mnth,
                     result,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIIntervalSubtract_func_t)(void *hndl, OCIError *err, OCIInterval *minuend, OCIInterval *subtrahend, OCIInterval *result);
static OCIIntervalSubtract_func_t OCIIntervalSubtract_func;
static int trace_OCIIntervalSubtract = 1;

sword OCIIntervalSubtract(void *hndl, OCIError *err, OCIInterval *minuend, OCIInterval *subtrahend, OCIInterval *result)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIIntervalSubtract_func(hndl, err, minuend, subtrahend, result);
    if (trace_OCIIntervalSubtract) {
        ocidump_log("%0*lX: OCIIntervalSubtract(%p, %p, %p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndl,
                     err,
                     minuend,
                     subtrahend,
                     result,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIIntervalToNumber_func_t)(void *hndl, OCIError *err, const OCIInterval *inter, OCINumber *number);
static OCIIntervalToNumber_func_t OCIIntervalToNumber_func;
static int trace_OCIIntervalToNumber = 1;

sword OCIIntervalToNumber(void *hndl, OCIError *err, const OCIInterval *inter, OCINumber *number)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIIntervalToNumber_func(hndl, err, inter, number);
    if (trace_OCIIntervalToNumber) {
        ocidump_log("%0*lX: OCIIntervalToNumber(%p, %p, %p, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndl,
                     err,
                     inter,
                     ocidump_ocinumber(buf1, number),
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCIIntervalToText_func_t)(void *hndl, OCIError *err, const OCIInterval *inter, ub1 lfprec, ub1 fsprec, OraText *buffer, size_t buflen, size_t *resultlen);
static OCIIntervalToText_func_t OCIIntervalToText_func;
static int trace_OCIIntervalToText = 1;

sword OCIIntervalToText(void *hndl, OCIError *err, const OCIInterval *inter, ub1 lfprec, ub1 fsprec, OraText *buffer, size_t buflen, size_t *resultlen)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIIntervalToText_func(hndl, err, inter, lfprec, fsprec, buffer, buflen, resultlen);
    if (trace_OCIIntervalToText) {
        size_t rlen = *resultlen;

        if (ocidump_hide_string) {
            rlen = 6;
            buffer = (OraText*)"hidden";
        }
        ocidump_log("%0*lX: OCIIntervalToText(%p, %p, %p, %u, %u, \"%.*s\", %" OCIDUMP_SIZET_FMT ", [%" OCIDUMP_SIZET_FMT "]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndl,
                     err,
                     inter,
                     lfprec,
                     fsprec,
                     (int)rlen, buffer,
                     buflen,
                     *resultlen,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIIterCreate_func_t)(OCIEnv *env, OCIError *err, const OCIColl *coll, OCIIter **itr);
static OCIIterCreate_func_t OCIIterCreate_func;
static int trace_OCIIterCreate = 1;

sword OCIIterCreate(OCIEnv *env, OCIError *err, const OCIColl *coll, OCIIter **itr)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIIterCreate_func(env, err, coll, itr);
    if (trace_OCIIterCreate) {
        ocidump_log("%0*lX: OCIIterCreate(%p, %p, %p, [%p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     coll,
                     *itr,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIIterDelete_func_t)(OCIEnv *env, OCIError *err, OCIIter **itr);
static OCIIterDelete_func_t OCIIterDelete_func;
static int trace_OCIIterDelete = 1;

sword OCIIterDelete(OCIEnv *env, OCIError *err, OCIIter **itr)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    OCIIter *old_itr = *itr;

    if (!is_initialized) {
        initialize();
    }
    ret = OCIIterDelete_func(env, err, itr);
    if (trace_OCIIterDelete) {
        ocidump_log("%0*lX: OCIIterDelete(%p, %p, [%p -> %p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     old_itr, *itr,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIIterGetCurrent_func_t)(OCIEnv *env, OCIError *err, const OCIIter *itr, void **elem, void **elemind);
static OCIIterGetCurrent_func_t OCIIterGetCurrent_func;
static int trace_OCIIterGetCurrent = 1;

sword OCIIterGetCurrent(OCIEnv *env, OCIError *err, const OCIIter *itr, void **elem, void **elemind)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIIterGetCurrent_func(env, err, itr, elem, elemind);
    if (trace_OCIIterGetCurrent) {
        ocidump_log("%0*lX: OCIIterGetCurrent(%p, %p, %p, [%p], %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     itr,
                     *elem,
                     elemind ? ocidump_sprintf(buf1, "[%p]", *elemind) : "(nil)",
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCIIterInit_func_t)(OCIEnv *env, OCIError *err, const OCIColl *coll, OCIIter *itr);
static OCIIterInit_func_t OCIIterInit_func;
static int trace_OCIIterInit = 1;

sword OCIIterInit(OCIEnv *env, OCIError *err, const OCIColl *coll, OCIIter *itr)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIIterInit_func(env, err, coll, itr);
    if (trace_OCIIterInit) {
        ocidump_log("%0*lX: OCIIterInit(%p, %p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     coll,
                     itr,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIIterNext_func_t)(OCIEnv *env, OCIError *err, OCIIter *itr, void **elem, void **elemind, boolean *eoc);
static OCIIterNext_func_t OCIIterNext_func;
static int trace_OCIIterNext = 1;

sword OCIIterNext(OCIEnv *env, OCIError *err, OCIIter *itr, void **elem, void **elemind, boolean *eoc)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIIterNext_func(env, err, itr, elem, elemind, eoc);
    if (trace_OCIIterNext) {
        ocidump_log("%0*lX: OCIIterNext(%p, %p, %p, [%p], %s, [%d]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     itr,
                     *elem,
                     elemind ? ocidump_sprintf(buf1, "[%p]", *elemind) : "(nil)",
                     *eoc,
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCIIterPrev_func_t)(OCIEnv *env, OCIError *err, OCIIter *itr, void **elem, void **elemind, boolean *boc);
static OCIIterPrev_func_t OCIIterPrev_func;
static int trace_OCIIterPrev = 1;

sword OCIIterPrev(OCIEnv *env, OCIError *err, OCIIter *itr, void **elem, void **elemind, boolean *boc)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIIterPrev_func(env, err, itr, elem, elemind, boc);
    if (trace_OCIIterPrev) {
        ocidump_log("%0*lX: OCIIterPrev(%p, %p, %p, [%p], %s, [%d]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     itr,
                     *elem,
                     elemind ? ocidump_sprintf(buf1, "[%p]", *elemind) : "(nil)",
                     *boc,
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCILobAppend_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *dst_locp, OCILobLocator *src_locp);
static OCILobAppend_func_t OCILobAppend_func;
static int trace_OCILobAppend = 1;

sword OCILobAppend(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *dst_locp, OCILobLocator *src_locp)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILobAppend_func(svchp, errhp, dst_locp, src_locp);
    if (trace_OCILobAppend) {
        ocidump_log("%0*lX: OCILobAppend(%p, %p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     dst_locp,
                     src_locp,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobArrayRead_func_t)(OCISvcCtx *svchp, OCIError *errhp, ub4 *array_iter, OCILobLocator **lobp_arr, oraub8 *byte_amt_arr, oraub8 *char_amt_arr, oraub8 *offset_arr, void  **bufp_arr, oraub8 *bufl_arr, ub1 piece, void *ctxp, OCICallbackLobArrayRead cbfp, ub2 csid, ub1 csfrm);
static OCILobArrayRead_func_t OCILobArrayRead_func;
static int trace_OCILobArrayRead = 1;

sword OCILobArrayRead(OCISvcCtx *svchp, OCIError *errhp, ub4 *array_iter, OCILobLocator **lobp_arr, oraub8 *byte_amt_arr, oraub8 *char_amt_arr, oraub8 *offset_arr, void  **bufp_arr, oraub8 *bufl_arr, ub1 piece, void *ctxp, OCICallbackLobArrayRead cbfp, ub2 csid, ub1 csfrm)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    ub4 old_array_iter = array_iter ? *array_iter : 0;

    if (!is_initialized) {
        initialize();
    }
    ret = OCILobArrayRead_func(svchp, errhp, array_iter, lobp_arr, byte_amt_arr, char_amt_arr, offset_arr, bufp_arr, bufl_arr, piece, ctxp, cbfp, csid, csfrm);
    if (trace_OCILobArrayRead) {
        ocidump_log("%0*lX: OCILobArrayRead(%p, %p, %s, %p, %p, %p, %p, %p, %p, %u, %p, %p, %u, %u) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     array_iter ? ocidump_sprintf(buf1, "[%u -> %u]", old_array_iter, *array_iter) : "(nil)",
                     lobp_arr,
                     byte_amt_arr,
                     char_amt_arr,
                     offset_arr,
                     bufp_arr,
                     bufl_arr,
                     piece,
                     ctxp,
                     cbfp,
                     csid,
                     csfrm,
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCILobArrayWrite_func_t)(OCISvcCtx *svchp, OCIError *errhp, ub4 *array_iter, OCILobLocator **lobp_arr, oraub8 *byte_amt_arr, oraub8 *char_amt_arr, oraub8 *offset_arr, void **bufp_arr, oraub8 *bufl_arr, ub1 piece, void *ctxp, OCICallbackLobArrayWrite cbfp, ub2 csid, ub1 csfrm);
static OCILobArrayWrite_func_t OCILobArrayWrite_func;
static int trace_OCILobArrayWrite = 1;

sword OCILobArrayWrite(OCISvcCtx *svchp, OCIError *errhp, ub4 *array_iter, OCILobLocator **lobp_arr, oraub8 *byte_amt_arr, oraub8 *char_amt_arr, oraub8 *offset_arr, void **bufp_arr, oraub8 *bufl_arr, ub1 piece, void *ctxp, OCICallbackLobArrayWrite cbfp, ub2 csid, ub1 csfrm)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    ub4 old_array_iter = array_iter ? *array_iter : 0;

    if (!is_initialized) {
        initialize();
    }
    ret = OCILobArrayWrite_func(svchp, errhp, array_iter, lobp_arr, byte_amt_arr, char_amt_arr, offset_arr, bufp_arr, bufl_arr, piece, ctxp, cbfp, csid, csfrm);
    if (trace_OCILobArrayWrite) {
        ocidump_log("%0*lX: OCILobArrayWrite(%p, %p, %s, %p, %p, %p, %p, %p, %p, %u, %p, %p, %u, %u) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     array_iter ? ocidump_sprintf(buf1, "[%u -> %u]", old_array_iter, *array_iter) : "(nil)",
                     lobp_arr,
                     byte_amt_arr,
                     char_amt_arr,
                     offset_arr,
                     bufp_arr,
                     bufl_arr,
                     piece,
                     ctxp,
                     cbfp,
                     csid,
                     csfrm,
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCILobAssign_func_t)(OCIEnv *envhp, OCIError *errhp, const OCILobLocator *src_locp, OCILobLocator **dst_locpp);
static OCILobAssign_func_t OCILobAssign_func;
static int trace_OCILobAssign = 1;

sword OCILobAssign(OCIEnv *envhp, OCIError *errhp, const OCILobLocator *src_locp, OCILobLocator **dst_locpp)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    OCILobLocator *old_dst_locpp = *dst_locpp;

    if (!is_initialized) {
        initialize();
    }
    ret = OCILobAssign_func(envhp, errhp, src_locp, dst_locpp);
    if (trace_OCILobAssign) {
        ocidump_log("%0*lX: OCILobAssign(%p, %p, %p, [%p -> %p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     envhp,
                     errhp,
                     src_locp,
                     old_dst_locpp, *dst_locpp,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobCharSetForm_func_t)(OCIEnv *envhp, OCIError *errhp, const OCILobLocator *locp, ub1 *csfrm);
static OCILobCharSetForm_func_t OCILobCharSetForm_func;
static int trace_OCILobCharSetForm = 1;

sword OCILobCharSetForm(OCIEnv *envhp, OCIError *errhp, const OCILobLocator *locp, ub1 *csfrm)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILobCharSetForm_func(envhp, errhp, locp, csfrm);
    if (trace_OCILobCharSetForm) {
        ocidump_log("%0*lX: OCILobCharSetForm(%p, %p, %p, [%u]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     envhp,
                     errhp,
                     locp,
                     *csfrm,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobCharSetId_func_t)(OCIEnv *envhp, OCIError *errhp, const OCILobLocator *locp, ub2 *csid);
static OCILobCharSetId_func_t OCILobCharSetId_func;
static int trace_OCILobCharSetId = 1;

sword OCILobCharSetId(OCIEnv *envhp, OCIError *errhp, const OCILobLocator *locp, ub2 *csid)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILobCharSetId_func(envhp, errhp, locp, csid);
    if (trace_OCILobCharSetId) {
        ocidump_log("%0*lX: OCILobCharSetId(%p, %p, %p, [%u]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     envhp,
                     errhp,
                     locp,
                     *csid,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobClose_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp);
static OCILobClose_func_t OCILobClose_func;
static int trace_OCILobClose = 1;

sword OCILobClose(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILobClose_func(svchp, errhp, locp);
    if (trace_OCILobClose) {
        ocidump_log("%0*lX: OCILobClose(%p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     locp,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobCopy_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *dst_locp, OCILobLocator *src_locp, ub4 amount, ub4 dst_offset, ub4 src_offset);
static OCILobCopy_func_t OCILobCopy_func;
static int trace_OCILobCopy = 1;

sword OCILobCopy(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *dst_locp, OCILobLocator *src_locp, ub4 amount, ub4 dst_offset, ub4 src_offset)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILobCopy_func(svchp, errhp, dst_locp, src_locp, amount, dst_offset, src_offset);
    if (trace_OCILobCopy) {
        ocidump_log("%0*lX: OCILobCopy(%p, %p, dst_locp, src_locp, %u, %u, %u) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     amount,
                     dst_offset,
                     src_offset,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobCopy2_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *dst_locp, OCILobLocator *src_locp, oraub8 amount, oraub8 dst_offset, oraub8 src_offset);
static OCILobCopy2_func_t OCILobCopy2_func;
static int trace_OCILobCopy2 = 1;

sword OCILobCopy2(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *dst_locp, OCILobLocator *src_locp, oraub8 amount, oraub8 dst_offset, oraub8 src_offset)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILobCopy2_func(svchp, errhp, dst_locp, src_locp, amount, dst_offset, src_offset);
    if (trace_OCILobCopy2) {
        ocidump_log("%0*lX: OCILobCopy2(%p, %p, dst_locp, src_locp, %" OCIDUMP_UB8_FMT ", %" OCIDUMP_UB8_FMT ", %" OCIDUMP_UB8_FMT ") => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     amount,
                     dst_offset,
                     src_offset,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobCreateTemporary_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, ub2 csid, ub1 csfrm, ub1 lobtype, boolean cache, OCIDuration duration);
static OCILobCreateTemporary_func_t OCILobCreateTemporary_func;
static int trace_OCILobCreateTemporary = 1;

sword OCILobCreateTemporary(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, ub2 csid, ub1 csfrm, ub1 lobtype, boolean cache, OCIDuration duration)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILobCreateTemporary_func(svchp, errhp, locp, csid, csfrm, lobtype, cache, duration);
    if (trace_OCILobCreateTemporary) {
        ocidump_log("%0*lX: OCILobCreateTemporary(%p, %p, %p, %d, %u, %u, %d, %u) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     locp,
                     csid,
                     csfrm,
                     lobtype,
                     cache,
                     duration,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobDisableBuffering_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp);
static OCILobDisableBuffering_func_t OCILobDisableBuffering_func;
static int trace_OCILobDisableBuffering = 1;

sword OCILobDisableBuffering(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILobDisableBuffering_func(svchp, errhp, locp);
    if (trace_OCILobDisableBuffering) {
        ocidump_log("%0*lX: OCILobDisableBuffering(%p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     locp,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobEnableBuffering_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp);
static OCILobEnableBuffering_func_t OCILobEnableBuffering_func;
static int trace_OCILobEnableBuffering = 1;

sword OCILobEnableBuffering(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILobEnableBuffering_func(svchp, errhp, locp);
    if (trace_OCILobEnableBuffering) {
        ocidump_log("%0*lX: OCILobEnableBuffering(%p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     locp,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobErase_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, ub4 *amount, ub4 offset);
static OCILobErase_func_t OCILobErase_func;
static int trace_OCILobErase = 1;

sword OCILobErase(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, ub4 *amount, ub4 offset)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    ub4 old_amount = *amount;

    if (!is_initialized) {
        initialize();
    }
    ret = OCILobErase_func(svchp, errhp, locp, amount, offset);
    if (trace_OCILobErase) {
        ocidump_log("%0*lX: OCILobErase(%p, %p, %p, [%u -> %u], %u) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     locp,
                     old_amount, *amount,
                     offset,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobErase2_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, oraub8 *amount, oraub8 offset);
static OCILobErase2_func_t OCILobErase2_func;
static int trace_OCILobErase2 = 1;

sword OCILobErase2(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, oraub8 *amount, oraub8 offset)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    oraub8 old_amount = *amount;

    if (!is_initialized) {
        initialize();
    }
    ret = OCILobErase2_func(svchp, errhp, locp, amount, offset);
    if (trace_OCILobErase2) {
        ocidump_log("%0*lX: OCILobErase2(%p, %p, %p, [%" OCIDUMP_UB8_FMT " -> %" OCIDUMP_UB8_FMT "], %" OCIDUMP_UB8_FMT ") => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     locp,
                     old_amount, *amount,
                     offset,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobFileClose_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *filep);
static OCILobFileClose_func_t OCILobFileClose_func;
static int trace_OCILobFileClose = 1;

sword OCILobFileClose(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *filep)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILobFileClose_func(svchp, errhp, filep);
    if (trace_OCILobFileClose) {
        ocidump_log("%0*lX: OCILobFileClose(%p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     filep,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobFileCloseAll_func_t)(OCISvcCtx *svchp, OCIError *errhp);
static OCILobFileCloseAll_func_t OCILobFileCloseAll_func;
static int trace_OCILobFileCloseAll = 1;

sword OCILobFileCloseAll(OCISvcCtx *svchp, OCIError *errhp)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILobFileCloseAll_func(svchp, errhp);
    if (trace_OCILobFileCloseAll) {
        ocidump_log("%0*lX: OCILobFileCloseAll(%p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobFileExists_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *filep, boolean *flag);
static OCILobFileExists_func_t OCILobFileExists_func;
static int trace_OCILobFileExists = 1;

sword OCILobFileExists(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *filep, boolean *flag)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILobFileExists_func(svchp, errhp, filep, flag);
    if (trace_OCILobFileExists) {
        ocidump_log("%0*lX: OCILobFileExists(%p, %p, %p, [%d]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     filep,
                     *flag,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobFileGetName_func_t)(OCIEnv *envhp, OCIError *errhp, const OCILobLocator *filep, text *dir_alias, ub2 *d_length, text *filename, ub2 *f_length);
static OCILobFileGetName_func_t OCILobFileGetName_func;
static int trace_OCILobFileGetName = 1;

sword OCILobFileGetName(OCIEnv *envhp, OCIError *errhp, const OCILobLocator *filep, text *dir_alias, ub2 *d_length, text *filename, ub2 *f_length)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILobFileGetName_func(envhp, errhp, filep, dir_alias, d_length, filename, f_length);
    if (trace_OCILobFileGetName) {
        ub2 dlen = *d_length;
        ub2 flen = *f_length;

        if (ocidump_hide_string) {
            dlen = 6;
            dir_alias = (OraText*)"hidden";
            flen = 6;
            filename = (OraText*)"hidden";
        }
        ocidump_log("%0*lX: OCILobFileGetName(%p, %p, %p, \"%.*s\", [%u], \"%.*s\", [%u]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     envhp,
                     errhp,
                     filep,
                     dlen, dir_alias,
                     dlen,
                     flen, filename,
                     flen,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobFileIsOpen_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *filep, boolean *flag);
static OCILobFileIsOpen_func_t OCILobFileIsOpen_func;
static int trace_OCILobFileIsOpen = 1;

sword OCILobFileIsOpen(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *filep, boolean *flag)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILobFileIsOpen_func(svchp, errhp, filep, flag);
    if (trace_OCILobFileIsOpen) {
        ocidump_log("%0*lX: OCILobFileIsOpen(%p, %p, %p, [%d]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     filep,
                     *flag,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobFileOpen_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *filep, ub1 mode);
static OCILobFileOpen_func_t OCILobFileOpen_func;
static int trace_OCILobFileOpen = 1;

sword OCILobFileOpen(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *filep, ub1 mode)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILobFileOpen_func(svchp, errhp, filep, mode);
    if (trace_OCILobFileOpen) {
        ocidump_log("%0*lX: OCILobFileOpen(%p, %p, %p, %u) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     filep,
                     mode,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobFileSetName_func_t)(OCIEnv *envhp, OCIError *errhp, OCILobLocator **filepp, const text *dir_alias, ub2 d_length, const text *filename, ub2 f_length);
static OCILobFileSetName_func_t OCILobFileSetName_func;
static int trace_OCILobFileSetName = 1;

sword OCILobFileSetName(OCIEnv *envhp, OCIError *errhp, OCILobLocator **filepp, const text *dir_alias, ub2 d_length, const text *filename, ub2 f_length)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILobFileSetName_func(envhp, errhp, filepp, dir_alias, d_length, filename, f_length);
    if (trace_OCILobFileSetName) {
        if (ocidump_hide_string) {
            d_length = 6;
            dir_alias = (OraText*)"hidden";
            f_length = 6;
            filename = (OraText*)"hidden";
        }
        ocidump_log("%0*lX: OCILobFileSetName(%p, %p, [%p], \"%.*s\", %u, \"%.*s\", %u) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     envhp,
                     errhp,
                     *filepp,
                     d_length, dir_alias,
                     d_length,
                     f_length, filename,
                     f_length,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobFlushBuffer_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, ub4 flag);
static OCILobFlushBuffer_func_t OCILobFlushBuffer_func;
static int trace_OCILobFlushBuffer = 1;

sword OCILobFlushBuffer(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, ub4 flag)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILobFlushBuffer_func(svchp, errhp, locp, flag);
    if (trace_OCILobFlushBuffer) {
        ocidump_log("%0*lX: OCILobFlushBuffer(%p, %p, %p, %u) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     locp,
                     flag,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobFreeTemporary_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp);
static OCILobFreeTemporary_func_t OCILobFreeTemporary_func;
static int trace_OCILobFreeTemporary = 1;

sword OCILobFreeTemporary(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILobFreeTemporary_func(svchp, errhp, locp);
    if (trace_OCILobFreeTemporary) {
        ocidump_log("%0*lX: OCILobFreeTemporary(%p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     locp,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobGetChunkSize_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, ub4 *chunksizep);
static OCILobGetChunkSize_func_t OCILobGetChunkSize_func;
static int trace_OCILobGetChunkSize = 1;

sword OCILobGetChunkSize(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, ub4 *chunksizep)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILobGetChunkSize_func(svchp, errhp, locp, chunksizep);
    if (trace_OCILobGetChunkSize) {
        ocidump_log("%0*lX: OCILobGetChunkSize(%p, %p, %p, [%u]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     locp,
                     *chunksizep,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobGetContentType_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *lobp, oratext *contenttypep, ub4 *contenttypelenp, ub4 mode);
static OCILobGetContentType_func_t OCILobGetContentType_func;
static int trace_OCILobGetContentType = 1;

sword OCILobGetContentType(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *lobp, oratext *contenttypep, ub4 *contenttypelenp, ub4 mode)
{
    sword ret;
    char *buf1 = NULL;
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    ub4 old_contenttypelen = *contenttypelenp;

    if (!is_initialized) {
        initialize();
    }
    ret = OCILobGetContentType_func(svchp, errhp, lobp, contenttypep, contenttypelenp, mode);
    if (trace_OCILobGetContentType) {
        ocidump_log("%0*lX: OCILobGetContentType(%p, %p, %p, %s, [%u -> %u], 0x%x) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     lobp,
                     ocidump_quotestring(&buf1, contenttypep, *contenttypelenp),
                     old_contenttypelen, *contenttypelenp,
                     mode,
                     ocidump_status2name(ret, buf2));
    }
    free(buf1);
    return ret;
}

typedef sword (*OCILobGetDeduplicateRegions_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, OCILobRegion *regp, ub4 *count, ub1 piece, void *ctxp, OCICallbackLobGetDeduplicateRegions cbfp);
static OCILobGetDeduplicateRegions_func_t OCILobGetDeduplicateRegions_func;
static int trace_OCILobGetDeduplicateRegions = 1;

sword OCILobGetDeduplicateRegions(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, OCILobRegion *regp, ub4 *count, ub1 piece, void *ctxp, OCICallbackLobGetDeduplicateRegions cbfp)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    ub4 old_count = *count;

    if (!is_initialized) {
        initialize();
    }
    ret = OCILobGetDeduplicateRegions_func(svchp, errhp, locp, regp, count, piece, ctxp, cbfp);
    if (trace_OCILobGetDeduplicateRegions) {
        ocidump_log("%0*lX: OCILobGetDeduplicateRegions(%p, %p, %p, %p, [%u -> %u], %u, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     locp,
                     regp,
                     old_count, *count,
                     piece,
                     ctxp,
                     cbfp,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobGetLength_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, ub4 *lenp);
static OCILobGetLength_func_t OCILobGetLength_func;
static int trace_OCILobGetLength = 1;

sword OCILobGetLength(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, ub4 *lenp)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILobGetLength_func(svchp, errhp, locp, lenp);
    if (trace_OCILobGetLength) {
        ocidump_log("%0*lX: OCILobGetLength(%p, %p, %p, [%u]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     locp,
                     *lenp,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobGetLength2_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, oraub8 *lenp);
static OCILobGetLength2_func_t OCILobGetLength2_func;
static int trace_OCILobGetLength2 = 1;

sword OCILobGetLength2(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, oraub8 *lenp)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILobGetLength2_func(svchp, errhp, locp, lenp);
    if (trace_OCILobGetLength2) {
        ocidump_log("%0*lX: OCILobGetLength2(%p, %p, %p, [%" OCIDUMP_UB8_FMT "]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     locp,
                     *lenp,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobGetOptions_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *lobp, ub4 optypes, void *optionsp, ub4 *optionslenp, ub4 mode);
static OCILobGetOptions_func_t OCILobGetOptions_func;
static int trace_OCILobGetOptions = 1;

sword OCILobGetOptions(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *lobp, ub4 optypes, void *optionsp, ub4 *optionslenp, ub4 mode)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILobGetOptions_func(svchp, errhp, lobp, optypes, optionsp, optionslenp, mode);
    if (trace_OCILobGetOptions) {
        ocidump_log("%0*lX: OCILobGetOptions(%p, %p, %p, 0x%x, [0x%x], [%u], 0x%x) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     lobp,
                     optypes,
                     *(ub4*)optionsp,
                     *optionslenp,
                     mode,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobGetStorageLimit_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *lobp, oraub8 *limitp);
static OCILobGetStorageLimit_func_t OCILobGetStorageLimit_func;
static int trace_OCILobGetStorageLimit = 1;

sword OCILobGetStorageLimit(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *lobp, oraub8 *limitp)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILobGetStorageLimit_func(svchp, errhp, lobp, limitp);
    if (trace_OCILobGetStorageLimit) {
        ocidump_log("%0*lX: OCILobGetStorageLimit(%p, %p, %p, [%" OCIDUMP_UB8_FMT "]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     lobp,
                     *limitp,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobIsEqual_func_t)(OCIEnv *envhp, const OCILobLocator *x, const OCILobLocator *y, boolean *is_equal);
static OCILobIsEqual_func_t OCILobIsEqual_func;
static int trace_OCILobIsEqual = 1;

sword OCILobIsEqual(OCIEnv *envhp, const OCILobLocator *x, const OCILobLocator *y, boolean *is_equal)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILobIsEqual_func(envhp, x, y, is_equal);
    if (trace_OCILobIsEqual) {
        ocidump_log("%0*lX: OCILobIsEqual(%p, %p, %p, [%d]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     envhp,
                     x,
                     y,
                     *is_equal,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobIsOpen_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, boolean *flag);
static OCILobIsOpen_func_t OCILobIsOpen_func;
static int trace_OCILobIsOpen = 1;

sword OCILobIsOpen(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, boolean *flag)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILobIsOpen_func(svchp, errhp, locp, flag);
    if (trace_OCILobIsOpen) {
        ocidump_log("%0*lX: OCILobIsOpen(%p, %p, %p, [%d]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     locp,
                     *flag,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobIsTemporary_func_t)(OCIEnv *envhp, OCIError *errhp, OCILobLocator *locp, boolean *is_temporary);
static OCILobIsTemporary_func_t OCILobIsTemporary_func;
static int trace_OCILobIsTemporary = 1;

sword OCILobIsTemporary(OCIEnv *envhp, OCIError *errhp, OCILobLocator *locp, boolean *is_temporary)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILobIsTemporary_func(envhp, errhp, locp, is_temporary);
    if (trace_OCILobIsTemporary) {
        ocidump_log("%0*lX: OCILobIsTemporary(%p, %p, %p, [%d]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     envhp,
                     errhp,
                     locp,
                     *is_temporary,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobLoadFromFile_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *dst_locp, OCILobLocator *src_filep, ub4 amount, ub4 dst_offset, ub4 src_offset);
static OCILobLoadFromFile_func_t OCILobLoadFromFile_func;
static int trace_OCILobLoadFromFile = 1;

sword OCILobLoadFromFile(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *dst_locp, OCILobLocator *src_filep, ub4 amount, ub4 dst_offset, ub4 src_offset)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILobLoadFromFile_func(svchp, errhp, dst_locp, src_filep, amount, dst_offset, src_offset);
    if (trace_OCILobLoadFromFile) {
        ocidump_log("%0*lX: OCILobLoadFromFile(%p, %p, %p, %p, %u, %u, %u) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     dst_locp,
                     src_filep,
                     amount,
                     dst_offset,
                     src_offset,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobLoadFromFile2_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *dst_locp, OCILobLocator *src_filep, oraub8 amount, oraub8 dst_offset, oraub8 src_offset);
static OCILobLoadFromFile2_func_t OCILobLoadFromFile2_func;
static int trace_OCILobLoadFromFile2 = 1;

sword OCILobLoadFromFile2(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *dst_locp, OCILobLocator *src_filep, oraub8 amount, oraub8 dst_offset, oraub8 src_offset)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILobLoadFromFile2_func(svchp, errhp, dst_locp, src_filep, amount, dst_offset, src_offset);
    if (trace_OCILobLoadFromFile2) {
        ocidump_log("%0*lX: OCILobLoadFromFile2(%p, %p, %p, %p, %" OCIDUMP_UB8_FMT ", %" OCIDUMP_UB8_FMT ", %" OCIDUMP_UB8_FMT ") => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     dst_locp,
                     src_filep,
                     amount,
                     dst_offset,
                     src_offset,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobLocatorAssign_func_t)(OCISvcCtx *svchp, OCIError *errhp, const OCILobLocator *src_locp, OCILobLocator **dst_locpp);
static OCILobLocatorAssign_func_t OCILobLocatorAssign_func;
static int trace_OCILobLocatorAssign = 1;

sword OCILobLocatorAssign(OCISvcCtx *svchp, OCIError *errhp, const OCILobLocator *src_locp, OCILobLocator **dst_locpp)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    OCILobLocator *old_dst_locpp = *dst_locpp;

    if (!is_initialized) {
        initialize();
    }
    ret = OCILobLocatorAssign_func(svchp, errhp, src_locp, dst_locpp);
    if (trace_OCILobLocatorAssign) {
        ocidump_log("%0*lX: OCILobLocatorAssign(%p, %p, %p, [%p -> %p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     src_locp,
                     old_dst_locpp, *dst_locpp,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobLocatorIsInit_func_t)(OCIEnv *envhp, OCIError *errhp, const OCILobLocator *locp, boolean *is_initialized);
static OCILobLocatorIsInit_func_t OCILobLocatorIsInit_func;
static int trace_OCILobLocatorIsInit = 1;

sword OCILobLocatorIsInit(OCIEnv *envhp, OCIError *errhp, const OCILobLocator *locp, boolean *is_initialized)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILobLocatorIsInit_func(envhp, errhp, locp, is_initialized);
    if (trace_OCILobLocatorIsInit) {
        ocidump_log("%0*lX: OCILobLocatorIsInit(%p, %p, %p, [%d]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     envhp,
                     errhp,
                     locp,
                     *is_initialized,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobOpen_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, ub1 mode);
static OCILobOpen_func_t OCILobOpen_func;
static int trace_OCILobOpen = 1;

sword OCILobOpen(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, ub1 mode)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILobOpen_func(svchp, errhp, locp, mode);
    if (trace_OCILobOpen) {
        ocidump_log("%0*lX: OCILobOpen(%p, %p, %p, %u) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     locp,
                     mode,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobRead_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, ub4 *amtp, ub4 offset, dvoid *bufp, ub4 bufl, dvoid *ctxp, OCICallbackLobRead cbfp, ub2 csid, ub1 csfrm);
static OCILobRead_func_t OCILobRead_func;
static int trace_OCILobRead = 1;

sword OCILobRead(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, ub4 *amtp, ub4 offset, dvoid *bufp, ub4 bufl, dvoid *ctxp, OCICallbackLobRead cbfp, ub2 csid, ub1 csfrm)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    ub4 old_amt = *amtp;

    if (!is_initialized) {
        initialize();
    }
    ret = OCILobRead_func(svchp, errhp, locp, amtp, offset, bufp, bufl, ctxp, cbfp, csid, csfrm);
    if (trace_OCILobRead) {
        ocidump_log("%0*lX: OCILobRead(%p, %p, %p, [%u -> %u], %u, %p, %u, %p, %p, %u, %u) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     locp,
                     old_amt, *amtp,
                     offset,
                     bufp,
                     bufl,
                     ctxp,
                     cbfp,
                     csid,
                     csfrm,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobRead2_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, oraub8 *byte_amtp, oraub8 *char_amtp, oraub8 offset, dvoid *bufp, oraub8 bufl, ub1 piece, dvoid *ctxp, OCICallbackLobRead2 cbfp, ub2 csid, ub1 csfrm);
static OCILobRead2_func_t OCILobRead2_func;
static int trace_OCILobRead2 = 1;

sword OCILobRead2(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, oraub8 *byte_amtp, oraub8 *char_amtp, oraub8 offset, dvoid *bufp, oraub8 bufl, ub1 piece, dvoid *ctxp, OCICallbackLobRead2 cbfp, ub2 csid, ub1 csfrm)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    oraub8 old_byte_amt = *byte_amtp;
    oraub8 old_char_amt = *char_amtp;

    if (!is_initialized) {
        initialize();
    }
    ret = OCILobRead2_func(svchp, errhp, locp, byte_amtp, char_amtp, offset, bufp, bufl, piece, ctxp, cbfp, csid, csfrm);
    if (trace_OCILobRead2) {
        ocidump_log("%0*lX: OCILobRead2(%p, %p, %p, [%" OCIDUMP_UB8_FMT " -> %" OCIDUMP_UB8_FMT "], [%" OCIDUMP_UB8_FMT " -> %" OCIDUMP_UB8_FMT "], %" OCIDUMP_UB8_FMT ", %p, %" OCIDUMP_UB8_FMT ", %u, %p, %p, %u, %u) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     locp,
                     old_byte_amt, *byte_amtp,
                     old_char_amt, *char_amtp,
                     offset,
                     bufp,
                     bufl,
                     piece,
                     ctxp,
                     cbfp,
                     csid,
                     csfrm,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobSetContentType_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *lobp, const oratext *contenttypep, ub4 contenttypelen, ub4 mode);
static OCILobSetContentType_func_t OCILobSetContentType_func;
static int trace_OCILobSetContentType = 1;

sword OCILobSetContentType(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *lobp, const oratext *contenttypep, ub4 contenttypelen, ub4 mode)
{
    sword ret;
    char *buf1 = NULL;
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILobSetContentType_func(svchp, errhp, lobp, contenttypep, contenttypelen, mode);
    if (trace_OCILobSetContentType) {
        ocidump_log("%0*lX: OCILobSetContentType(%p, %p, %p, %s, %u, 0x%x) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     lobp,
                     ocidump_quotestring(&buf1, contenttypep, contenttypelen),
                     contenttypelen,
                     mode,
                     ocidump_status2name(ret, buf2));
    }
    free(buf1);
    return ret;
}

typedef sword (*OCILobSetOptions_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *lobp, ub4 optypes, void *optionsp, ub4 optionslen, ub4 mode);
static OCILobSetOptions_func_t OCILobSetOptions_func;
static int trace_OCILobSetOptions = 1;

sword OCILobSetOptions(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *lobp, ub4 optypes, void *optionsp, ub4 optionslen, ub4 mode)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILobSetOptions_func(svchp, errhp, lobp, optypes, optionsp, optionslen, mode);
    if (trace_OCILobSetOptions) {
        ocidump_log("%0*lX: OCILobSetOptions(%p, %p, %p, 0x%x, [0x%x], %u, 0x%x) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     lobp,
                     optypes,
                     *(ub4*)optionsp,
                     optionslen,
                     mode,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobTrim_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, ub4 newlen);
static OCILobTrim_func_t OCILobTrim_func;
static int trace_OCILobTrim = 1;

sword OCILobTrim(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, ub4 newlen)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILobTrim_func(svchp, errhp, locp, newlen);
    if (trace_OCILobTrim) {
        ocidump_log("%0*lX: OCILobTrim(%p, %p, %p, %u) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     locp,
                     newlen,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobTrim2_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, oraub8 newlen);
static OCILobTrim2_func_t OCILobTrim2_func;
static int trace_OCILobTrim2 = 1;

sword OCILobTrim2(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, oraub8 newlen)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILobTrim2_func(svchp, errhp, locp, newlen);
    if (trace_OCILobTrim2) {
        ocidump_log("%0*lX: OCILobTrim2(%p, %p, %p, %" OCIDUMP_UB8_FMT ") => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     locp,
                     newlen,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobWrite_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, ub4 *amtp, ub4 offset, dvoid *bufp, ub4 buflen, ub1 piece, dvoid *ctxp, OCICallbackLobWrite cbfp, ub2 csid, ub1 csfrm);
static OCILobWrite_func_t OCILobWrite_func;
static int trace_OCILobWrite = 1;

sword OCILobWrite(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, ub4 *amtp, ub4 offset, dvoid *bufp, ub4 buflen, ub1 piece, dvoid *ctxp, OCICallbackLobWrite cbfp, ub2 csid, ub1 csfrm)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    ub4 old_amt = *amtp;

    if (!is_initialized) {
        initialize();
    }
    ret = OCILobWrite_func(svchp, errhp, locp, amtp, offset, bufp, buflen, piece, ctxp, cbfp, csid, csfrm);
    if (trace_OCILobWrite) {
        ocidump_log("%0*lX: OCILobWrite(%p, %p, %p, [%u -> %u], %u, %p, %u, %u, %p, %p, %u, %u) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     locp,
                     old_amt, *amtp,
                     offset,
                     bufp,
                     buflen,
                     piece,
                     ctxp,
                     cbfp,
                     csid,
                     csfrm,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobWrite2_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, oraub8 *byte_amtp, oraub8 *char_amtp, oraub8 offset, dvoid *bufp, oraub8 buflen, ub1 piece, dvoid *ctxp, OCICallbackLobWrite2 cbfp, ub2 csid, ub1 csfrm);
static OCILobWrite2_func_t OCILobWrite2_func;
static int trace_OCILobWrite2 = 1;

sword OCILobWrite2(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, oraub8 *byte_amtp, oraub8 *char_amtp, oraub8 offset, dvoid *bufp, oraub8 buflen, ub1 piece, dvoid *ctxp, OCICallbackLobWrite2 cbfp, ub2 csid, ub1 csfrm)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    oraub8 old_byte_amt = *byte_amtp;
    oraub8 old_char_amt = *char_amtp;

    if (!is_initialized) {
        initialize();
    }
    ret = OCILobWrite2_func(svchp, errhp, locp, byte_amtp, char_amtp, offset, bufp, buflen, piece, ctxp, cbfp, csid, csfrm);
    if (trace_OCILobWrite2) {
        ocidump_log("%0*lX: OCILobWrite2(%p, %p, %p, [%" OCIDUMP_UB8_FMT " -> %" OCIDUMP_UB8_FMT "], [%" OCIDUMP_UB8_FMT " -> %" OCIDUMP_UB8_FMT "], %" OCIDUMP_UB8_FMT ", %p, %" OCIDUMP_UB8_FMT ", %u, %p, %p, %u, %u) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     locp,
                     old_byte_amt, *byte_amtp,
                     old_char_amt, *char_amtp,
                     offset,
                     bufp,
                     buflen,
                     piece,
                     ctxp,
                     cbfp,
                     csid,
                     csfrm,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobWriteAppend_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *lobp, ub4 *amtp, void *bufp, ub4 bufl, ub1 piece, void *ctxp, OCICallbackLobWrite cbfp, ub2 csid, ub1 csfrm);
static OCILobWriteAppend_func_t OCILobWriteAppend_func;
static int trace_OCILobWriteAppend = 1;

sword OCILobWriteAppend(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *lobp, ub4 *amtp, void *bufp, ub4 bufl, ub1 piece, void *ctxp, OCICallbackLobWrite cbfp, ub2 csid, ub1 csfrm)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    ub4 old_amt = *amtp;

    if (!is_initialized) {
        initialize();
    }
    ret = OCILobWriteAppend_func(svchp, errhp, lobp, amtp, bufp, bufl, piece, ctxp, cbfp, csid, csfrm);
    if (trace_OCILobWriteAppend) {
        ocidump_log("%0*lX: OCILobWriteAppend(%p, %p, %p, [%u -> %u], %p, %u, %u, %p, %p, %u, %u) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     lobp,
                     old_amt, *amtp,
                     bufp,
                     bufl,
                     piece,
                     ctxp,
                     cbfp,
                     csid,
                     csfrm,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILobWriteAppend2_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *lobp, oraub8 *byte_amtp, oraub8 *char_amtp, void  *bufp, oraub8 bufl, ub1 piece, void  *ctxp, OCICallbackLobWrite2 cbfp, ub2 csid, ub1 csfrm);
static OCILobWriteAppend2_func_t OCILobWriteAppend2_func;
static int trace_OCILobWriteAppend2 = 1;

sword OCILobWriteAppend2(OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *lobp, oraub8 *byte_amtp, oraub8 *char_amtp, void  *bufp, oraub8 bufl, ub1 piece, void  *ctxp, OCICallbackLobWrite2 cbfp, ub2 csid, ub1 csfrm)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    oraub8 old_byte_amt = *byte_amtp;
    oraub8 old_char_amt = *char_amtp;

    if (!is_initialized) {
        initialize();
    }
    ret = OCILobWriteAppend2_func(svchp, errhp, lobp, byte_amtp, char_amtp, bufp, bufl, piece, ctxp, cbfp, csid, csfrm);
    if (trace_OCILobWriteAppend2) {
        ocidump_log("%0*lX: OCILobWriteAppend2(%p, %p, %p, [%" OCIDUMP_UB8_FMT " -> %" OCIDUMP_UB8_FMT "], [%" OCIDUMP_UB8_FMT " -> %" OCIDUMP_UB8_FMT "], %p, %" OCIDUMP_UB8_FMT ", %u, %p, cbfp, %u, %u) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     lobp,
                     old_byte_amt, *byte_amtp,
                     old_char_amt, *char_amtp,
                     bufp,
                     bufl,
                     piece,
                     ctxp,
                     csid,
                     csfrm,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILogoff_func_t)(OCISvcCtx *svchp, OCIError *errhp);
static OCILogoff_func_t OCILogoff_func;
static int trace_OCILogoff = 1;

sword OCILogoff(OCISvcCtx *svchp, OCIError *errhp)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILogoff_func(svchp, errhp);
    if (trace_OCILogoff) {
        ocidump_log("%0*lX: OCILogoff(%p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCILogon_func_t)(OCIEnv *envhp, OCIError *errhp, OCISvcCtx **svchp, const text *username, ub4 uname_len, const text *password, ub4 passwd_len, const text *dbname, ub4 dbname_len);
static OCILogon_func_t OCILogon_func;
static int trace_OCILogon = 1;

sword OCILogon(OCIEnv *envhp, OCIError *errhp, OCISvcCtx **svchp, const text *username, ub4 uname_len, const text *password, ub4 passwd_len, const text *dbname, ub4 dbname_len)
{
    sword ret;
    char *buf1 = NULL;
    char *buf2 = NULL;
    char *buf3 = NULL;
    char buf4[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILogon_func(envhp, errhp, svchp, username, uname_len, password, passwd_len, dbname, dbname_len);
    if (trace_OCILogon) {
        ocidump_log("%0*lX: OCILogon(%p, %p, [%p], %s, %u, %s, %u, %s, %u) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     envhp,
                     errhp,
                     *svchp,
                     ocidump_quotestring(&buf1, username, uname_len),
                     uname_len,
                     ocidump_quotestring(&buf2, password, passwd_len),
                     passwd_len,
                     ocidump_quotestring(&buf3, dbname, dbname_len),
                     dbname_len,
                     ocidump_status2name(ret, buf4));
    }
    free(buf1);
    free(buf2);
    free(buf3);
    return ret;
}

typedef sword (*OCILogon2_func_t)(OCIEnv *envhp, OCIError *errhp, OCISvcCtx **svchp, const text *username, ub4 uname_len, const text *password, ub4 passwd_len, const text *dbname, ub4 dbname_len, ub4 mode);
static OCILogon2_func_t OCILogon2_func;
static int trace_OCILogon2 = 1;

sword OCILogon2(OCIEnv *envhp, OCIError *errhp, OCISvcCtx **svchp, const text *username, ub4 uname_len, const text *password, ub4 passwd_len, const text *dbname, ub4 dbname_len, ub4 mode)
{
    sword ret;
    char *buf1 = NULL;
    char *buf2 = NULL;
    char *buf3 = NULL;
    char buf4[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILogon2_func(envhp, errhp, svchp, username, uname_len, password, passwd_len, dbname, dbname_len, mode);
    if (trace_OCILogon2) {
        ocidump_log("%0*lX: OCILogon2(%p, %p, [%p], %s, %u, %s, %u, %s, %u, 0x%x) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     envhp,
                     errhp,
                     *svchp,
                     ocidump_quotestring(&buf1, username, uname_len),
                     uname_len,
                     ocidump_quotestring(&buf2, password, passwd_len),
                     passwd_len,
                     ocidump_quotestring(&buf3, dbname, dbname_len),
                     dbname_len,
                     mode,
                     ocidump_status2name(ret, buf4));
    }
    free(buf1);
    free(buf2);
    free(buf3);
    return ret;
}

typedef sword (*OCIMessageClose_func_t)(void  *envhp, OCIError *errhp, OCIMsg *msghp);
static OCIMessageClose_func_t OCIMessageClose_func;
static int trace_OCIMessageClose = 1;

sword OCIMessageClose(void  *envhp, OCIError *errhp, OCIMsg *msghp)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIMessageClose_func(envhp, errhp, msghp);
    if (trace_OCIMessageClose) {
        ocidump_log("%0*lX: OCIMessageClose(%p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     envhp,
                     errhp,
                     msghp,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef OraText * (*OCIMessageGet_func_t)(OCIMsg *msgh, ub4 msgno, OraText *msgbuf, size_t buflen);
static OCIMessageGet_func_t OCIMessageGet_func;
static int trace_OCIMessageGet = 1;

OraText * OCIMessageGet(OCIMsg *msgh, ub4 msgno, OraText *msgbuf, size_t buflen)
{
    OraText * ret;
    char *buf1 = NULL;
    if (!is_initialized) {
        initialize();
    }
    ret = OCIMessageGet_func(msgh, msgno, msgbuf, buflen);
    if (trace_OCIMessageGet) {
        if (ocidump_hide_string) {
            buflen = 6;
            msgbuf = (OraText*)"hidden";
        }
        ocidump_log("%0*lX: OCIMessageGet(%p, %u, \"%.*s\", %" OCIDUMP_SIZET_FMT ") => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     msgh,
                     msgno,
                     (int)buflen, msgbuf,
                     buflen,
                     ret ? ocidump_asprintf(&buf1, "\"%s\"", ret) : "(nil)");
    }
    free(buf1);
    return ret;
}

typedef sword (*OCIMessageOpen_func_t)(dvoid *envhp, OCIError *errhp, OCIMsg **msghp, const OraText *product, const OraText *facility, OCIDuration dur);
static OCIMessageOpen_func_t OCIMessageOpen_func;
static int trace_OCIMessageOpen = 1;

sword OCIMessageOpen(dvoid *envhp, OCIError *errhp, OCIMsg **msghp, const OraText *product, const OraText *facility, OCIDuration dur)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIMessageOpen_func(envhp, errhp, msghp, product, facility, dur);
    if (trace_OCIMessageOpen) {
        ocidump_log("%0*lX: OCIMessageOpen(%p, %p, [%p], \"%s\", \"%s\", %u) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     envhp,
                     errhp,
                     *msghp,
                     product,
                     facility,
                     dur,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCINlsCharSetIdToName_func_t)(dvoid *envhp, oratext *buf, size_t buflen, ub2 id);
static OCINlsCharSetIdToName_func_t OCINlsCharSetIdToName_func;
static int trace_OCINlsCharSetIdToName = 1;

sword OCINlsCharSetIdToName(dvoid *envhp, oratext *buf, size_t buflen, ub2 id)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINlsCharSetIdToName_func(envhp, buf, buflen, id);
    if (trace_OCINlsCharSetIdToName) {
        if (ocidump_hide_string) {
            buflen = 6;
            buf = (OraText*)"hidden";
        }
        ocidump_log("%0*lX: OCINlsCharSetIdToName(%p, \"%.*s\", %" OCIDUMP_SIZET_FMT ", %u) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     envhp,
                     (int)buflen, buf,
                     buflen,
                     id,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef ub2 (*OCINlsCharSetNameToId_func_t)(dvoid *envhp, const oratext *name);
static OCINlsCharSetNameToId_func_t OCINlsCharSetNameToId_func;
static int trace_OCINlsCharSetNameToId = 1;

ub2 OCINlsCharSetNameToId(dvoid *envhp, const oratext *name)
{
    ub2 ret;
    if (!is_initialized) {
        initialize();
    }
    ret = OCINlsCharSetNameToId_func(envhp, name);
    if (trace_OCINlsCharSetNameToId) {
        ocidump_log("%0*lX: OCINlsCharSetNameToId(%p, %s) => %u\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     envhp,
                     name,
                     ret);
    }
    return ret;
}

typedef sword (*OCINumberAbs_func_t)(OCIError *err, const OCINumber *number, OCINumber *result);
static OCINumberAbs_func_t OCINumberAbs_func;
static int trace_OCINumberAbs = 1;

sword OCINumberAbs(OCIError *err, const OCINumber *number, OCINumber *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberAbs_func(err, number, result);
    if (trace_OCINumberAbs) {
        ocidump_log("%0*lX: OCINumberAbs(%p, %p, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     number,
                     ocidump_ocinumber(buf1, result),
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCINumberAdd_func_t)(OCIError *err, const OCINumber *number1, const OCINumber *number2, OCINumber *result);
static OCINumberAdd_func_t OCINumberAdd_func;
static int trace_OCINumberAdd = 1;

sword OCINumberAdd(OCIError *err, const OCINumber *number1, const OCINumber *number2, OCINumber *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf3[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf4[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberAdd_func(err, number1, number2, result);
    if (trace_OCINumberAdd) {
        ocidump_log("%0*lX: OCINumberAdd(%p, %s, %s, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, number1),
                     ocidump_ocinumber(buf2, number2),
                     ocidump_ocinumber(buf3, result),
                     ocidump_status2name(ret, buf4));
    }
    return ret;
}

typedef sword (*OCINumberArcCos_func_t)(OCIError *err, const OCINumber *number, OCINumber *result);
static OCINumberArcCos_func_t OCINumberArcCos_func;
static int trace_OCINumberArcCos = 1;

sword OCINumberArcCos(OCIError *err, const OCINumber *number, OCINumber *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberArcCos_func(err, number, result);
    if (trace_OCINumberArcCos) {
        ocidump_log("%0*lX: OCINumberArcCos(%p, %p, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     number,
                     ocidump_ocinumber(buf1, result),
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCINumberArcSin_func_t)(OCIError *err, const OCINumber *number, OCINumber *result);
static OCINumberArcSin_func_t OCINumberArcSin_func;
static int trace_OCINumberArcSin = 1;

sword OCINumberArcSin(OCIError *err, const OCINumber *number, OCINumber *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf3[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberArcSin_func(err, number, result);
    if (trace_OCINumberArcSin) {
        ocidump_log("%0*lX: OCINumberArcSin(%p, %s, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, number),
                     ocidump_ocinumber(buf2, result),
                     ocidump_status2name(ret, buf3));
    }
    return ret;
}

typedef sword (*OCINumberArcTan_func_t)(OCIError *err, const OCINumber *number, OCINumber *result);
static OCINumberArcTan_func_t OCINumberArcTan_func;
static int trace_OCINumberArcTan = 1;

sword OCINumberArcTan(OCIError *err, const OCINumber *number, OCINumber *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf3[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberArcTan_func(err, number, result);
    if (trace_OCINumberArcTan) {
        ocidump_log("%0*lX: OCINumberArcTan(%p, %s, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, number),
                     ocidump_ocinumber(buf2, result),
                     ocidump_status2name(ret, buf3));
    }
    return ret;
}

typedef sword (*OCINumberArcTan2_func_t)(OCIError *err, const OCINumber *number1, const OCINumber *number2, OCINumber *result);
static OCINumberArcTan2_func_t OCINumberArcTan2_func;
static int trace_OCINumberArcTan2 = 1;

sword OCINumberArcTan2(OCIError *err, const OCINumber *number1, const OCINumber *number2, OCINumber *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf3[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf4[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberArcTan2_func(err, number1, number2, result);
    if (trace_OCINumberArcTan2) {
        ocidump_log("%0*lX: OCINumberArcTan2(%p, %s, %s, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, number1),
                     ocidump_ocinumber(buf2, number2),
                     ocidump_ocinumber(buf3, result),
                     ocidump_status2name(ret, buf4));
    }
    return ret;
}

typedef sword (*OCINumberAssign_func_t)(OCIError *err, const OCINumber *from, OCINumber *to);
static OCINumberAssign_func_t OCINumberAssign_func;
static int trace_OCINumberAssign = 1;

sword OCINumberAssign(OCIError *err, const OCINumber *from, OCINumber *to)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf3[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberAssign_func(err, from, to);
    if (trace_OCINumberAssign) {
        ocidump_log("%0*lX: OCINumberAssign(%p, %s, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, from),
                     ocidump_ocinumber(buf2, to),
                     ocidump_status2name(ret, buf3));
    }
    return ret;
}

typedef sword (*OCINumberCeil_func_t)(OCIError *err, const OCINumber *number, OCINumber *result);
static OCINumberCeil_func_t OCINumberCeil_func;
static int trace_OCINumberCeil = 1;

sword OCINumberCeil(OCIError *err, const OCINumber *number, OCINumber *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf3[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberCeil_func(err, number, result);
    if (trace_OCINumberCeil) {
        ocidump_log("%0*lX: OCINumberCeil(%p, %s, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, number),
                     ocidump_ocinumber(buf2, result),
                     ocidump_status2name(ret, buf3));
    }
    return ret;
}

typedef sword (*OCINumberCmp_func_t)(OCIError *err, const OCINumber *number1, const OCINumber *number2, sword *result);
static OCINumberCmp_func_t OCINumberCmp_func;
static int trace_OCINumberCmp = 1;

sword OCINumberCmp(OCIError *err, const OCINumber *number1, const OCINumber *number2, sword *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf3[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberCmp_func(err, number1, number2, result);
    if (trace_OCINumberCmp) {
        ocidump_log("%0*lX: OCINumberCmp(%p, %s, %s, [%d]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, number1),
                     ocidump_ocinumber(buf2, number2),
                     *result,
                     ocidump_status2name(ret, buf3));
    }
    return ret;
}

typedef sword (*OCINumberCos_func_t)(OCIError *err, const OCINumber *number, OCINumber *result);
static OCINumberCos_func_t OCINumberCos_func;
static int trace_OCINumberCos = 1;

sword OCINumberCos(OCIError *err, const OCINumber *number, OCINumber *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf3[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberCos_func(err, number, result);
    if (trace_OCINumberCos) {
        ocidump_log("%0*lX: OCINumberCos(%p, %s, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, number),
                     ocidump_ocinumber(buf2, result),
                     ocidump_status2name(ret, buf3));
    }
    return ret;
}

typedef sword (*OCINumberDec_func_t)(OCIError *err, OCINumber *number);
static OCINumberDec_func_t OCINumberDec_func;
static int trace_OCINumberDec = 1;

sword OCINumberDec(OCIError *err, OCINumber *number)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberDec_func(err, number);
    if (trace_OCINumberDec) {
        ocidump_log("%0*lX: OCINumberDec(%p, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, number),
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCINumberDiv_func_t)(OCIError *err, const OCINumber *number1, const OCINumber *number2, OCINumber *result);
static OCINumberDiv_func_t OCINumberDiv_func;
static int trace_OCINumberDiv = 1;

sword OCINumberDiv(OCIError *err, const OCINumber *number1, const OCINumber *number2, OCINumber *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf3[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf4[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberDiv_func(err, number1, number2, result);
    if (trace_OCINumberDiv) {
        ocidump_log("%0*lX: OCINumberDiv(%p, %s, %s, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, number1),
                     ocidump_ocinumber(buf2, number2),
                     ocidump_ocinumber(buf3, result),
                     ocidump_status2name(ret, buf4));
    }
    return ret;
}

typedef sword (*OCINumberExp_func_t)(OCIError *err, const OCINumber *number, OCINumber *result);
static OCINumberExp_func_t OCINumberExp_func;
static int trace_OCINumberExp = 1;

sword OCINumberExp(OCIError *err, const OCINumber *number, OCINumber *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf3[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberExp_func(err, number, result);
    if (trace_OCINumberExp) {
        ocidump_log("%0*lX: OCINumberExp(%p, %s, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, number),
                     ocidump_ocinumber(buf2, result),
                     ocidump_status2name(ret, buf3));
    }
    return ret;
}

typedef sword (*OCINumberFloor_func_t)(OCIError *err, const OCINumber *number, OCINumber *result);
static OCINumberFloor_func_t OCINumberFloor_func;
static int trace_OCINumberFloor = 1;

sword OCINumberFloor(OCIError *err, const OCINumber *number, OCINumber *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf3[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberFloor_func(err, number, result);
    if (trace_OCINumberFloor) {
        ocidump_log("%0*lX: OCINumberFloor(%p, %s, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, number),
                     ocidump_ocinumber(buf2, result),
                     ocidump_status2name(ret, buf3));
    }
    return ret;
}

typedef sword (*OCINumberFromInt_func_t)(OCIError *err, const dvoid *inum, uword inum_length, uword inum_s_flag, OCINumber *number);
static OCINumberFromInt_func_t OCINumberFromInt_func;
static int trace_OCINumberFromInt = 1;

sword OCINumberFromInt(OCIError *err, const dvoid *inum, uword inum_length, uword inum_s_flag, OCINumber *number)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberFromInt_func(err, inum, inum_length, inum_s_flag, number);
    if (trace_OCINumberFromInt) {
        ocidump_log("%0*lX: OCINumberFromInt(%p, %p, %u, %u, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     inum,
                     inum_length,
                     inum_s_flag,
                     ocidump_ocinumber(buf1, number),
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCINumberFromReal_func_t)(OCIError *err, const dvoid *rnum, uword rnum_length, OCINumber *number);
static OCINumberFromReal_func_t OCINumberFromReal_func;
static int trace_OCINumberFromReal = 1;

sword OCINumberFromReal(OCIError *err, const dvoid *rnum, uword rnum_length, OCINumber *number)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberFromReal_func(err, rnum, rnum_length, number);
    if (trace_OCINumberFromReal) {
        ocidump_log("%0*lX: OCINumberFromReal(%p, %p, %u, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     rnum,
                     rnum_length,
                     ocidump_ocinumber(buf1, number),
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCINumberFromText_func_t)(OCIError *err, const text *str, ub4 str_length, const text *fmt, ub4 fmt_length, const text *nls_params, ub4 nls_p_length, OCINumber *number);
static OCINumberFromText_func_t OCINumberFromText_func;
static int trace_OCINumberFromText = 1;

sword OCINumberFromText(OCIError *err, const text *str, ub4 str_length, const text *fmt, ub4 fmt_length, const text *nls_params, ub4 nls_p_length, OCINumber *number)
{
    sword ret;
    char *buf1 = NULL;
    char *buf2 = NULL;
    char *buf3 = NULL;
    char buf4[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf5[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberFromText_func(err, str, str_length, fmt, fmt_length, nls_params, nls_p_length, number);
    if (trace_OCINumberFromText) {
        ocidump_log("%0*lX: OCINumberFromText(%p, %s, %u, %s, %u, %s, %u, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_quotestring(&buf1, str, str_length),
                     str_length,
                     ocidump_quotestring(&buf2, fmt, fmt_length),
                     fmt_length,
                     ocidump_quotestring(&buf3, nls_params, nls_p_length),
                     nls_p_length,
                     ocidump_ocinumber(buf4, number),
                     ocidump_status2name(ret, buf5));
    }
    free(buf1);
    free(buf2);
    free(buf3);
    return ret;
}

typedef sword (*OCINumberHypCos_func_t)(OCIError *err, const OCINumber *number, OCINumber *result);
static OCINumberHypCos_func_t OCINumberHypCos_func;
static int trace_OCINumberHypCos = 1;

sword OCINumberHypCos(OCIError *err, const OCINumber *number, OCINumber *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf3[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberHypCos_func(err, number, result);
    if (trace_OCINumberHypCos) {
        ocidump_log("%0*lX: OCINumberHypCos(%p, %s, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, number),
                     ocidump_ocinumber(buf2, result),
                     ocidump_status2name(ret, buf3));
    }
    return ret;
}

typedef sword (*OCINumberHypSin_func_t)(OCIError *err, const OCINumber *number, OCINumber *result);
static OCINumberHypSin_func_t OCINumberHypSin_func;
static int trace_OCINumberHypSin = 1;

sword OCINumberHypSin(OCIError *err, const OCINumber *number, OCINumber *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf3[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberHypSin_func(err, number, result);
    if (trace_OCINumberHypSin) {
        ocidump_log("%0*lX: OCINumberHypSin(%p, %s, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, number),
                     ocidump_ocinumber(buf2, result),
                     ocidump_status2name(ret, buf3));
    }
    return ret;
}

typedef sword (*OCINumberHypTan_func_t)(OCIError *err, const OCINumber *number, OCINumber *result);
static OCINumberHypTan_func_t OCINumberHypTan_func;
static int trace_OCINumberHypTan = 1;

sword OCINumberHypTan(OCIError *err, const OCINumber *number, OCINumber *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf3[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberHypTan_func(err, number, result);
    if (trace_OCINumberHypTan) {
        ocidump_log("%0*lX: OCINumberHypTan(%p, %s, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, number),
                     ocidump_ocinumber(buf2, result),
                     ocidump_status2name(ret, buf3));
    }
    return ret;
}

typedef sword (*OCINumberInc_func_t)(OCIError *err, OCINumber *number);
static OCINumberInc_func_t OCINumberInc_func;
static int trace_OCINumberInc = 1;

sword OCINumberInc(OCIError *err, OCINumber *number)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberInc_func(err, number);
    if (trace_OCINumberInc) {
        ocidump_log("%0*lX: OCINumberInc(%p, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, number),
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCINumberIntPower_func_t)(OCIError *err, const OCINumber *base, const sword exp, OCINumber *result);
static OCINumberIntPower_func_t OCINumberIntPower_func;
static int trace_OCINumberIntPower = 1;

sword OCINumberIntPower(OCIError *err, const OCINumber *base, const sword exp, OCINumber *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf3[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberIntPower_func(err, base, exp, result);
    if (trace_OCINumberIntPower) {
        ocidump_log("%0*lX: OCINumberIntPower(%p, %s, %d, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, base),
                     exp,
                     ocidump_ocinumber(buf2, result),
                     ocidump_status2name(ret, buf3));
    }
    return ret;
}

typedef sword (*OCINumberIsInt_func_t)(OCIError *err, const OCINumber *number, boolean *result);
static OCINumberIsInt_func_t OCINumberIsInt_func;
static int trace_OCINumberIsInt = 1;

sword OCINumberIsInt(OCIError *err, const OCINumber *number, boolean *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberIsInt_func(err, number, result);
    if (trace_OCINumberIsInt) {
        ocidump_log("%0*lX: OCINumberIsInt(%p, %s, [%d]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, number),
                     *result,
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCINumberIsZero_func_t)(OCIError *err, const OCINumber *number, boolean *result);
static OCINumberIsZero_func_t OCINumberIsZero_func;
static int trace_OCINumberIsZero = 1;

sword OCINumberIsZero(OCIError *err, const OCINumber *number, boolean *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberIsZero_func(err, number, result);
    if (trace_OCINumberIsZero) {
        ocidump_log("%0*lX: OCINumberIsZero(%p, %s, [%d]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, number),
                     *result,
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCINumberLn_func_t)(OCIError *err, const OCINumber *number, OCINumber *result);
static OCINumberLn_func_t OCINumberLn_func;
static int trace_OCINumberLn = 1;

sword OCINumberLn(OCIError *err, const OCINumber *number, OCINumber *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf3[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberLn_func(err, number, result);
    if (trace_OCINumberLn) {
        ocidump_log("%0*lX: OCINumberLn(%p, %s, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, number),
                     ocidump_ocinumber(buf2, result),
                     ocidump_status2name(ret, buf3));
    }
    return ret;
}

typedef sword (*OCINumberLog_func_t)(OCIError *err, const OCINumber *base, const OCINumber *number, OCINumber *result);
static OCINumberLog_func_t OCINumberLog_func;
static int trace_OCINumberLog = 1;

sword OCINumberLog(OCIError *err, const OCINumber *base, const OCINumber *number, OCINumber *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf3[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf4[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberLog_func(err, base, number, result);
    if (trace_OCINumberLog) {
        ocidump_log("%0*lX: OCINumberLog(%p, %s, %s, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, base),
                     ocidump_ocinumber(buf2, number),
                     ocidump_ocinumber(buf3, result),
                     ocidump_status2name(ret, buf4));
    }
    return ret;
}

typedef sword (*OCINumberMod_func_t)(OCIError *err, const OCINumber *number1, const OCINumber *number2, OCINumber *result);
static OCINumberMod_func_t OCINumberMod_func;
static int trace_OCINumberMod = 1;

sword OCINumberMod(OCIError *err, const OCINumber *number1, const OCINumber *number2, OCINumber *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf3[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf4[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberMod_func(err, number1, number2, result);
    if (trace_OCINumberMod) {
        ocidump_log("%0*lX: OCINumberMod(%p, %s, %s, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, number1),
                     ocidump_ocinumber(buf2, number2),
                     ocidump_ocinumber(buf3, result),
                     ocidump_status2name(ret, buf4));
    }
    return ret;
}

typedef sword (*OCINumberMul_func_t)(OCIError *err, const OCINumber *number1, const OCINumber *number2, OCINumber *result);
static OCINumberMul_func_t OCINumberMul_func;
static int trace_OCINumberMul = 1;

sword OCINumberMul(OCIError *err, const OCINumber *number1, const OCINumber *number2, OCINumber *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf3[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf4[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberMul_func(err, number1, number2, result);
    if (trace_OCINumberMul) {
        ocidump_log("%0*lX: OCINumberMul(%p, %s, %s, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, number1),
                     ocidump_ocinumber(buf2, number2),
                     ocidump_ocinumber(buf3, result),
                     ocidump_status2name(ret, buf4));
    }
    return ret;
}

typedef sword (*OCINumberNeg_func_t)(OCIError *err, const OCINumber *number, OCINumber *result);
static OCINumberNeg_func_t OCINumberNeg_func;
static int trace_OCINumberNeg = 1;

sword OCINumberNeg(OCIError *err, const OCINumber *number, OCINumber *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf3[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberNeg_func(err, number, result);
    if (trace_OCINumberNeg) {
        ocidump_log("%0*lX: OCINumberNeg(%p, %s, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, number),
                     ocidump_ocinumber(buf2, result),
                     ocidump_status2name(ret, buf3));
    }
    return ret;
}

typedef sword (*OCINumberPower_func_t)(OCIError *err, const OCINumber *base, const OCINumber *number, OCINumber *result);
static OCINumberPower_func_t OCINumberPower_func;
static int trace_OCINumberPower = 1;

sword OCINumberPower(OCIError *err, const OCINumber *base, const OCINumber *number, OCINumber *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf3[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf4[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberPower_func(err, base, number, result);
    if (trace_OCINumberPower) {
        ocidump_log("%0*lX: OCINumberPower(%p, %s, %s, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, base),
                     ocidump_ocinumber(buf2, number),
                     ocidump_ocinumber(buf3, result),
                     ocidump_status2name(ret, buf4));
    }
    return ret;
}

typedef sword (*OCINumberPrec_func_t)(OCIError *err, const OCINumber *number, eword nDigs, OCINumber *result);
static OCINumberPrec_func_t OCINumberPrec_func;
static int trace_OCINumberPrec = 1;

sword OCINumberPrec(OCIError *err, const OCINumber *number, eword nDigs, OCINumber *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf3[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberPrec_func(err, number, nDigs, result);
    if (trace_OCINumberPrec) {
        ocidump_log("%0*lX: OCINumberPrec(%p, %s, %d, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, number),
                     nDigs,
                     ocidump_ocinumber(buf2, result),
                     ocidump_status2name(ret, buf3));
    }
    return ret;
}

typedef sword (*OCINumberRound_func_t)(OCIError *err, const OCINumber *number, sword decplace, OCINumber *result);
static OCINumberRound_func_t OCINumberRound_func;
static int trace_OCINumberRound = 1;

sword OCINumberRound(OCIError *err, const OCINumber *number, sword decplace, OCINumber *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf3[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberRound_func(err, number, decplace, result);
    if (trace_OCINumberRound) {
        ocidump_log("%0*lX: OCINumberRound(%p, %s, %d, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, number),
                     decplace,
                     ocidump_ocinumber(buf2, result),
                     ocidump_status2name(ret, buf3));
    }
    return ret;
}

typedef void (*OCINumberSetPi_func_t)(OCIError *err, OCINumber *num);
static OCINumberSetPi_func_t OCINumberSetPi_func;
static int trace_OCINumberSetPi = 1;

void OCINumberSetPi(OCIError *err, OCINumber *num)
{
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    OCINumberSetPi_func(err, num);
    if (trace_OCINumberSetPi) {
        ocidump_log("%0*lX: OCINumberSetPi(%p, %s)\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, num));
    }
}

typedef void (*OCINumberSetZero_func_t)(OCIError *err, OCINumber *num);
static OCINumberSetZero_func_t OCINumberSetZero_func;
static int trace_OCINumberSetZero = 1;

void OCINumberSetZero(OCIError *err, OCINumber *num)
{
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    OCINumberSetZero_func(err, num);
    if (trace_OCINumberSetZero) {
        ocidump_log("%0*lX: OCINumberSetZero(%p, %s)\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, num));
    }
}

typedef sword (*OCINumberShift_func_t)(OCIError *err, const OCINumber *number, const sword nDig, OCINumber *result);
static OCINumberShift_func_t OCINumberShift_func;
static int trace_OCINumberShift = 1;

sword OCINumberShift(OCIError *err, const OCINumber *number, const sword nDig, OCINumber *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf3[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberShift_func(err, number, nDig, result);
    if (trace_OCINumberShift) {
        ocidump_log("%0*lX: OCINumberShift(%p, %s, %d, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, number),
                     nDig,
                     ocidump_ocinumber(buf2, result),
                     ocidump_status2name(ret, buf3));
    }
    return ret;
}

typedef sword (*OCINumberSign_func_t)(OCIError *err, const OCINumber *number, sword *result);
static OCINumberSign_func_t OCINumberSign_func;
static int trace_OCINumberSign = 1;

sword OCINumberSign(OCIError *err, const OCINumber *number, sword *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberSign_func(err, number, result);
    if (trace_OCINumberSign) {
        ocidump_log("%0*lX: OCINumberSign(%p, %s, [%d]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, number),
                     *result,
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCINumberSin_func_t)(OCIError *err, const OCINumber *number, OCINumber *result);
static OCINumberSin_func_t OCINumberSin_func;
static int trace_OCINumberSin = 1;

sword OCINumberSin(OCIError *err, const OCINumber *number, OCINumber *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberSin_func(err, number, result);
    if (trace_OCINumberSin) {
        ocidump_log("%0*lX: OCINumberSin(%p, %s, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, number),
                     result,
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCINumberSqrt_func_t)(OCIError *err, const OCINumber *number, OCINumber *result);
static OCINumberSqrt_func_t OCINumberSqrt_func;
static int trace_OCINumberSqrt = 1;

sword OCINumberSqrt(OCIError *err, const OCINumber *number, OCINumber *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf3[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberSqrt_func(err, number, result);
    if (trace_OCINumberSqrt) {
        ocidump_log("%0*lX: OCINumberSqrt(%p, %s, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, number),
                     ocidump_ocinumber(buf2, result),
                     ocidump_status2name(ret, buf3));
    }
    return ret;
}

typedef sword (*OCINumberSub_func_t)(OCIError *err, const OCINumber *number1, const OCINumber *number2, OCINumber *result);
static OCINumberSub_func_t OCINumberSub_func;
static int trace_OCINumberSub = 1;

sword OCINumberSub(OCIError *err, const OCINumber *number1, const OCINumber *number2, OCINumber *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf3[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf4[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberSub_func(err, number1, number2, result);
    if (trace_OCINumberSub) {
        ocidump_log("%0*lX: OCINumberSub(%p, %s, %s, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, number1),
                     ocidump_ocinumber(buf2, number2),
                     ocidump_ocinumber(buf3, result),
                     ocidump_status2name(ret, buf4));
    }
    return ret;
}

typedef sword (*OCINumberTan_func_t)(OCIError *err, const OCINumber *number, OCINumber *result);
static OCINumberTan_func_t OCINumberTan_func;
static int trace_OCINumberTan = 1;

sword OCINumberTan(OCIError *err, const OCINumber *number, OCINumber *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf3[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberTan_func(err, number, result);
    if (trace_OCINumberTan) {
        ocidump_log("%0*lX: OCINumberTan(%p, %s, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, number),
                     ocidump_ocinumber(buf2, result),
                     ocidump_status2name(ret, buf3));
    }
    return ret;
}

typedef sword (*OCINumberToInt_func_t)(OCIError *err, const OCINumber *number, uword rsl_length, uword rsl_flag, dvoid *rsl);
static OCINumberToInt_func_t OCINumberToInt_func;
static int trace_OCINumberToInt = 1;

sword OCINumberToInt(OCIError *err, const OCINumber *number, uword rsl_length, uword rsl_flag, dvoid *rsl)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberToInt_func(err, number, rsl_length, rsl_flag, rsl);
    if (trace_OCINumberToInt) {
        ocidump_log("%0*lX: OCINumberToInt(%p, %s, %u, %u, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, number),
                     rsl_length,
                     rsl_flag,
                     rsl,
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCINumberToReal_func_t)(OCIError *err, const OCINumber *number, uword rsl_length, dvoid *rsl);
static OCINumberToReal_func_t OCINumberToReal_func;
static int trace_OCINumberToReal = 1;

sword OCINumberToReal(OCIError *err, const OCINumber *number, uword rsl_length, dvoid *rsl)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberToReal_func(err, number, rsl_length, rsl);
    if (trace_OCINumberToReal) {
        ocidump_log("%0*lX: OCINumberToReal(%p, %s, %u, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, number),
                     rsl_length,
                     rsl,
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCINumberToRealArray_func_t)(OCIError *err, const OCINumber **number, uword elems, uword rsl_length, dvoid *rsl);
static OCINumberToRealArray_func_t OCINumberToRealArray_func;
static int trace_OCINumberToRealArray = 1;

sword OCINumberToRealArray(OCIError *err, const OCINumber **number, uword elems, uword rsl_length, dvoid *rsl)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberToRealArray_func(err, number, elems, rsl_length, rsl);
    if (trace_OCINumberToRealArray) {
        ocidump_log("%0*lX: OCINumberToRealArray(%p, [%s, ...], %u, %u, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     elems ? ocidump_ocinumber(buf1, *number) : "",
                     elems,
                     rsl_length,
                     rsl,
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCINumberToText_func_t)(OCIError *err, const OCINumber *number, const text *fmt, ub4 fmt_length, const text *nls_params, ub4 nls_p_length, ub4 *buf_size, text *buf);
static OCINumberToText_func_t OCINumberToText_func;
static int trace_OCINumberToText = 1;

sword OCINumberToText(OCIError *err, const OCINumber *number, const text *fmt, ub4 fmt_length, const text *nls_params, ub4 nls_p_length, ub4 *buf_size, text *buf)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char *buf2 = NULL;
    char *buf3 = NULL;
    char *buf4 = NULL;
    char buf5[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberToText_func(err, number, fmt, fmt_length, nls_params, nls_p_length, buf_size, buf);
    if (trace_OCINumberToText) {
        ocidump_log("%0*lX: OCINumberToText(%p, %s, %s, %u, %s, %u, [%u], %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, number),
                     ocidump_quotestring(&buf2, fmt, fmt_length),
                     fmt_length,
                     ocidump_quotestring(&buf3, nls_params, nls_p_length),
                     nls_p_length,
                     *buf_size,
                     ret ? "" : ocidump_quotestring(&buf4, buf, *buf_size),
                     ocidump_status2name(ret, buf5));
    }
    free(buf2);
    free(buf3);
    free(buf4);
    return ret;
}

typedef sword (*OCINumberTrunc_func_t)(OCIError *err, const OCINumber *number, sword decplace, OCINumber *result);
static OCINumberTrunc_func_t OCINumberTrunc_func;
static int trace_OCINumberTrunc = 1;

sword OCINumberTrunc(OCIError *err, const OCINumber *number, sword decplace, OCINumber *result)
{
    sword ret;
    char buf1[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf2[OCIDUMP_OCINUMBER_BUF_SIZE];
    char buf3[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCINumberTrunc_func(err, number, decplace, result);
    if (trace_OCINumberTrunc) {
        ocidump_log("%0*lX: OCINumberTrunc(%p, %s, %d, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     err,
                     ocidump_ocinumber(buf1, number),
                     decplace,
                     ocidump_ocinumber(buf2, result),
                     ocidump_status2name(ret, buf3));
    }
    return ret;
}

typedef sword (*OCIObjectAlwaysLatest_func_t)(OCIEnv *env, OCIError *err, void  *object);
static OCIObjectAlwaysLatest_func_t OCIObjectAlwaysLatest_func;
static int trace_OCIObjectAlwaysLatest = 1;

sword OCIObjectAlwaysLatest(OCIEnv *env, OCIError *err, void  *object)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectAlwaysLatest_func(env, err, object);
    if (trace_OCIObjectAlwaysLatest) {
        ocidump_log("%0*lX: OCIObjectAlwaysLatest(%p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     object,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIObjectArrayPin_func_t)(OCIEnv *env, OCIError *err, OCIRef **ref_array, ub4 array_size, OCIComplexObject **cor_array, ub4 cor_array_size, OCIPinOpt pin_option, OCIDuration pin_duration, OCILockOpt lock, void **obj_array, ub4 *pos);
static OCIObjectArrayPin_func_t OCIObjectArrayPin_func;
static int trace_OCIObjectArrayPin = 1;

sword OCIObjectArrayPin(OCIEnv *env, OCIError *err, OCIRef **ref_array, ub4 array_size, OCIComplexObject **cor_array, ub4 cor_array_size, OCIPinOpt pin_option, OCIDuration pin_duration, OCILockOpt lock, void **obj_array, ub4 *pos)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    char buf3[OCIDUMP_SHORT_BUF_SIZE];
    char buf4[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectArrayPin_func(env, err, ref_array, array_size, cor_array, cor_array_size, pin_option, pin_duration, lock, obj_array, pos);
    if (trace_OCIObjectArrayPin) {
        ocidump_log("%0*lX: OCIObjectArrayPin(%p, %p, %s, %u, %s, %u, %d, %u, %d, %s, [%u]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     ref_array ? ocidump_sprintf(buf1, "[%p, ...]", *ref_array) : "(nil)",
                     array_size,
                     cor_array ? ocidump_sprintf(buf2, "[%p, ...]", *cor_array) : "(nil)",
                     cor_array_size,
                     pin_option,
                     pin_duration,
                     lock,
                     obj_array ? ocidump_sprintf(buf3, "[%p]", *obj_array) : "(nil)",
                     *pos,
                     ocidump_status2name(ret, buf4));
    }
    return ret;
}

typedef sword (*OCIObjectCopy_func_t)(OCIEnv *env, OCIError *err, const OCISvcCtx *svc, void *source, void *null_source, void *target, void *null_target, OCIType *tdo, OCIDuration duration, ub1 option);
static OCIObjectCopy_func_t OCIObjectCopy_func;
static int trace_OCIObjectCopy = 1;

sword OCIObjectCopy(OCIEnv *env, OCIError *err, const OCISvcCtx *svc, void *source, void *null_source, void *target, void *null_target, OCIType *tdo, OCIDuration duration, ub1 option)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectCopy_func(env, err, svc, source, null_source, target, null_target, tdo, duration, option);
    if (trace_OCIObjectCopy) {
        ocidump_log("%0*lX: OCIObjectCopy(%p, %p, %p, %p, %p, %p, %p, %p, %u, %u) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     svc,
                     source,
                     null_source,
                     target,
                     null_target,
                     tdo,
                     duration,
                     option,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIObjectExists_func_t)(OCIEnv *env, OCIError *err, void *ins, boolean *exist);
static OCIObjectExists_func_t OCIObjectExists_func;
static int trace_OCIObjectExists = 1;

sword OCIObjectExists(OCIEnv *env, OCIError *err, void *ins, boolean *exist)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectExists_func(env, err, ins, exist);
    if (trace_OCIObjectExists) {
        ocidump_log("%0*lX: OCIObjectExists(%p, %p, %p, [%d]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     ins,
                     *exist,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIObjectFlush_func_t)(OCIEnv *env, OCIError *err, void *object);
static OCIObjectFlush_func_t OCIObjectFlush_func;
static int trace_OCIObjectFlush = 1;

sword OCIObjectFlush(OCIEnv *env, OCIError *err, void *object)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectFlush_func(env, err, object);
    if (trace_OCIObjectFlush) {
        ocidump_log("%0*lX: OCIObjectFlush(%p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     object,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIObjectFlushRefresh_func_t)(OCIEnv *env, OCIError *err, void *object);
static OCIObjectFlushRefresh_func_t OCIObjectFlushRefresh_func;
static int trace_OCIObjectFlushRefresh = 1;

sword OCIObjectFlushRefresh(OCIEnv *env, OCIError *err, void *object)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectFlushRefresh_func(env, err, object);
    if (trace_OCIObjectFlushRefresh) {
        ocidump_log("%0*lX: OCIObjectFlushRefresh(%p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     object,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIObjectFree_func_t)(OCIEnv *env, OCIError *err, dvoid *instance, ub2 flags);
static OCIObjectFree_func_t OCIObjectFree_func;
static int trace_OCIObjectFree = 1;

sword OCIObjectFree(OCIEnv *env, OCIError *err, dvoid *instance, ub2 flags)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectFree_func(env, err, instance, flags);
    if (trace_OCIObjectFree) {
        ocidump_log("%0*lX: OCIObjectFree(%p, %p, %p, %u) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     instance,
                     flags,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIObjectGetAttr_func_t)(OCIEnv *env, OCIError *err, void *instance, void *null_struct, struct OCIType *tdo, const oratext **names, const ub4 *lengths, const ub4 name_count, const ub4 *indexes, const ub4 index_count, OCIInd *attr_null_status, void **attr_null_struct, void **attr_value, struct OCIType **attr_tdo);
static OCIObjectGetAttr_func_t OCIObjectGetAttr_func;
static int trace_OCIObjectGetAttr = 1;

sword OCIObjectGetAttr(OCIEnv *env, OCIError *err, void *instance, void *null_struct, struct OCIType *tdo, const oratext **names, const ub4 *lengths, const ub4 name_count, const ub4 *indexes, const ub4 index_count, OCIInd *attr_null_status, void **attr_null_struct, void **attr_value, struct OCIType **attr_tdo)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    char buf3[OCIDUMP_SHORT_BUF_SIZE];
    char buf4[OCIDUMP_SHORT_BUF_SIZE];
    char buf5[OCIDUMP_SHORT_BUF_SIZE];
    char buf6[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectGetAttr_func(env, err, instance, null_struct, tdo, names, lengths, name_count, indexes, index_count, attr_null_status, attr_null_struct, attr_value, attr_tdo);
    if (trace_OCIObjectGetAttr) {
        ocidump_log("%0*lX: OCIObjectGetAttr(%p, %p, %p, %p, %p, %s, %s, %u, %s, %u, %s, %s, [%p], [%p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     instance,
                     null_struct,
                     tdo,
                     names ? ocidump_sprintf(buf1, "[%p, ...]", *names) : "(nil)",
                     lengths ? ocidump_sprintf(buf2, "[%u, ...]", *lengths) : "(nil)",
                     name_count,
                     indexes ? ocidump_sprintf(buf3, "[%u, ...]", *indexes) : "(nil)",
                     index_count,
                     attr_null_status ? ocidump_sprintf(buf4, "[%d]", *attr_null_status) : "(nil)",
                     attr_null_struct ? ocidump_sprintf(buf5, "[%p]", *attr_null_struct) : "(nil)",
                     *attr_value,
                     *attr_tdo,
                     ocidump_status2name(ret, buf6));
    }
    return ret;
}

typedef sword (*OCIObjectGetInd_func_t)(OCIEnv *env, OCIError *err, dvoid *instance, dvoid **null_struct);
static OCIObjectGetInd_func_t OCIObjectGetInd_func;
static int trace_OCIObjectGetInd = 1;

sword OCIObjectGetInd(OCIEnv *env, OCIError *err, dvoid *instance, dvoid **null_struct)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectGetInd_func(env, err, instance, null_struct);
    if (trace_OCIObjectGetInd) {
        ocidump_log("%0*lX: OCIObjectGetInd(%p, %p, %p, [%p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     instance,
                     *null_struct,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIObjectGetNewOID_func_t)(OCIEnv *env, OCIError *err, OCISvcCtx *svc, ub1 *oid);
static OCIObjectGetNewOID_func_t OCIObjectGetNewOID_func;
static int trace_OCIObjectGetNewOID = 1;

sword OCIObjectGetNewOID(OCIEnv *env, OCIError *err, OCISvcCtx *svc, ub1 *oid)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectGetNewOID_func(env, err, svc, oid);
    if (trace_OCIObjectGetNewOID) {
        ocidump_log("%0*lX: OCIObjectGetNewOID(%p, %p, %p, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     svc,
                     oid ? ocidump_sprintf(buf1, "%u", *oid) : "(nil)",
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCIObjectGetObjectRef_func_t)(OCIEnv *env, OCIError *err, void *object, OCIRef *object_ref);
static OCIObjectGetObjectRef_func_t OCIObjectGetObjectRef_func;
static int trace_OCIObjectGetObjectRef = 1;

sword OCIObjectGetObjectRef(OCIEnv *env, OCIError *err, void *object, OCIRef *object_ref)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectGetObjectRef_func(env, err, object, object_ref);
    if (trace_OCIObjectGetObjectRef) {
        ocidump_log("%0*lX: OCIObjectGetObjectRef(%p, %p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     object,
                     object_ref,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIObjectGetPrimaryKeyTypeRef_func_t)(OCIEnv *env, OCIError *err, const OCISvcCtx *svc, void *table, OCIRef *type_ref);
static OCIObjectGetPrimaryKeyTypeRef_func_t OCIObjectGetPrimaryKeyTypeRef_func;
static int trace_OCIObjectGetPrimaryKeyTypeRef = 1;

sword OCIObjectGetPrimaryKeyTypeRef(OCIEnv *env, OCIError *err, const OCISvcCtx *svc, void *table, OCIRef *type_ref)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectGetPrimaryKeyTypeRef_func(env, err, svc, table, type_ref);
    if (trace_OCIObjectGetPrimaryKeyTypeRef) {
        ocidump_log("%0*lX: OCIObjectGetPrimaryKeyTypeRef(%p, %p, %p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     svc,
                     table,
                     type_ref,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIObjectGetProperty_func_t)(OCIEnv *env, OCIError *err, const void *obj, OCIObjectPropId propertyId, void *property, ub4 *size);
static OCIObjectGetProperty_func_t OCIObjectGetProperty_func;
static int trace_OCIObjectGetProperty = 1;

sword OCIObjectGetProperty(OCIEnv *env, OCIError *err, const void *obj, OCIObjectPropId propertyId, void *property, ub4 *size)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    ub4 old_size = *size;

    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectGetProperty_func(env, err, obj, propertyId, property, size);
    if (trace_OCIObjectGetProperty) {
        ocidump_log("%0*lX: OCIObjectGetProperty(%p, %p, %p, %u, %p, [%u -> %u]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     obj,
                     propertyId,
                     property,
                     old_size, *size,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIObjectGetTypeRef_func_t)(OCIEnv *env, OCIError *err, void *instance, OCIRef *type_ref);
static OCIObjectGetTypeRef_func_t OCIObjectGetTypeRef_func;
static int trace_OCIObjectGetTypeRef = 1;

sword OCIObjectGetTypeRef(OCIEnv *env, OCIError *err, void *instance, OCIRef *type_ref)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectGetTypeRef_func(env, err, instance, type_ref);
    if (trace_OCIObjectGetTypeRef) {
        ocidump_log("%0*lX: OCIObjectGetTypeRef(%p, %p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     instance,
                     type_ref,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIObjectIsDirtied_func_t)(OCIEnv *env, OCIError *err, void *ins, boolean *dirty);
static OCIObjectIsDirtied_func_t OCIObjectIsDirtied_func;
static int trace_OCIObjectIsDirtied = 1;

sword OCIObjectIsDirtied(OCIEnv *env, OCIError *err, void *ins, boolean *dirty)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectIsDirtied_func(env, err, ins, dirty);
    if (trace_OCIObjectIsDirtied) {
        ocidump_log("%0*lX: OCIObjectIsDirtied(%p, %p, %p, [%d]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     ins,
                     *dirty,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIObjectIsDirty_func_t)(OCIEnv *env, OCIError *err, void *ins, boolean *dirty);
static OCIObjectIsDirty_func_t OCIObjectIsDirty_func;
static int trace_OCIObjectIsDirty = 1;

sword OCIObjectIsDirty(OCIEnv *env, OCIError *err, void *ins, boolean *dirty)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectIsDirty_func(env, err, ins, dirty);
    if (trace_OCIObjectIsDirty) {
        ocidump_log("%0*lX: OCIObjectIsDirty(%p, %p, %p, [%d]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     ins,
                     *dirty,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIObjectIsLoaded_func_t)(OCIEnv *env, OCIError *err, void *ins, boolean *load);
static OCIObjectIsLoaded_func_t OCIObjectIsLoaded_func;
static int trace_OCIObjectIsLoaded = 1;

sword OCIObjectIsLoaded(OCIEnv *env, OCIError *err, void *ins, boolean *load)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectIsLoaded_func(env, err, ins, load);
    if (trace_OCIObjectIsLoaded) {
        ocidump_log("%0*lX: OCIObjectIsLoaded(%p, %p, %p, [%d]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     ins,
                     *load,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIObjectIsLocked_func_t)(OCIEnv *env, OCIError *err, void *ins, boolean *lock);
static OCIObjectIsLocked_func_t OCIObjectIsLocked_func;
static int trace_OCIObjectIsLocked = 1;

sword OCIObjectIsLocked(OCIEnv *env, OCIError *err, void *ins, boolean *lock)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectIsLocked_func(env, err, ins, lock);
    if (trace_OCIObjectIsLocked) {
        ocidump_log("%0*lX: OCIObjectIsLocked(%p, %p, %p, [%d]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     ins,
                     *lock,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIObjectLock_func_t)(OCIEnv *env, OCIError *err, void *object);
static OCIObjectLock_func_t OCIObjectLock_func;
static int trace_OCIObjectLock = 1;

sword OCIObjectLock(OCIEnv *env, OCIError *err, void *object)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectLock_func(env, err, object);
    if (trace_OCIObjectLock) {
        ocidump_log("%0*lX: OCIObjectLock(%p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     object,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIObjectLockNoWait_func_t)(OCIEnv *env, OCIError *err, void *object);
static OCIObjectLockNoWait_func_t OCIObjectLockNoWait_func;
static int trace_OCIObjectLockNoWait = 1;

sword OCIObjectLockNoWait(OCIEnv *env, OCIError *err, void *object)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectLockNoWait_func(env, err, object);
    if (trace_OCIObjectLockNoWait) {
        ocidump_log("%0*lX: OCIObjectLockNoWait(%p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     object,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIObjectMakeObjectRef_func_t)(OCIEnv *env, OCIError *err, const OCISvcCtx *svc, void *table, void **values, ub4 array_len, OCIRef *object_ref);
static OCIObjectMakeObjectRef_func_t OCIObjectMakeObjectRef_func;
static int trace_OCIObjectMakeObjectRef = 1;

sword OCIObjectMakeObjectRef(OCIEnv *env, OCIError *err, const OCISvcCtx *svc, void *table, void **values, ub4 array_len, OCIRef *object_ref)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectMakeObjectRef_func(env, err, svc, table, values, array_len, object_ref);
    if (trace_OCIObjectMakeObjectRef) {
        ocidump_log("%0*lX: OCIObjectMakeObjectRef(%p, %p, %p, %p, [%p, ...], %u, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     svc,
                     table,
                     *values,
                     array_len,
                     object_ref,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIObjectMarkDelete_func_t)(OCIEnv *env, OCIError *err, void *instance);
static OCIObjectMarkDelete_func_t OCIObjectMarkDelete_func;
static int trace_OCIObjectMarkDelete = 1;

sword OCIObjectMarkDelete(OCIEnv *env, OCIError *err, void *instance)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectMarkDelete_func(env, err, instance);
    if (trace_OCIObjectMarkDelete) {
        ocidump_log("%0*lX: OCIObjectMarkDelete(%p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     instance,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIObjectMarkDeleteByRef_func_t)(OCIEnv *env, OCIError *err, OCIRef *object_ref);
static OCIObjectMarkDeleteByRef_func_t OCIObjectMarkDeleteByRef_func;
static int trace_OCIObjectMarkDeleteByRef = 1;

sword OCIObjectMarkDeleteByRef(OCIEnv *env, OCIError *err, OCIRef *object_ref)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectMarkDeleteByRef_func(env, err, object_ref);
    if (trace_OCIObjectMarkDeleteByRef) {
        ocidump_log("%0*lX: OCIObjectMarkDeleteByRef(%p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     object_ref,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIObjectMarkUpdate_func_t)(OCIEnv *env, OCIError *err, void *object);
static OCIObjectMarkUpdate_func_t OCIObjectMarkUpdate_func;
static int trace_OCIObjectMarkUpdate = 1;

sword OCIObjectMarkUpdate(OCIEnv *env, OCIError *err, void *object)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectMarkUpdate_func(env, err, object);
    if (trace_OCIObjectMarkUpdate) {
        ocidump_log("%0*lX: OCIObjectMarkUpdate(%p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     object,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIObjectNew_func_t)(OCIEnv *env, OCIError *err, const OCISvcCtx *svc, OCITypeCode typecode, OCIType *tdo, dvoid *table, OCIDuration duration, boolean value, dvoid **instance);
static OCIObjectNew_func_t OCIObjectNew_func;
static int trace_OCIObjectNew = 1;

sword OCIObjectNew(OCIEnv *env, OCIError *err, const OCISvcCtx *svc, OCITypeCode typecode, OCIType *tdo, dvoid *table, OCIDuration duration, boolean value, dvoid **instance)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectNew_func(env, err, svc, typecode, tdo, table, duration, value, instance);
    if (trace_OCIObjectNew) {
        ocidump_log("%0*lX: OCIObjectNew(%p, %p, %p, %u, %p, %p, %u, %d, [%p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     svc,
                     typecode,
                     tdo,
                     table,
                     duration,
                     value,
                     *instance,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIObjectNotAlwaysLatest_func_t)(OCIEnv *env, OCIError *err, void *object);
static OCIObjectNotAlwaysLatest_func_t OCIObjectNotAlwaysLatest_func;
static int trace_OCIObjectNotAlwaysLatest = 1;

sword OCIObjectNotAlwaysLatest(OCIEnv *env, OCIError *err, void *object)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectNotAlwaysLatest_func(env, err, object);
    if (trace_OCIObjectNotAlwaysLatest) {
        ocidump_log("%0*lX: OCIObjectNotAlwaysLatest(%p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     object,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIObjectPin_func_t)(OCIEnv *env, OCIError *err, OCIRef *object_ref, OCIComplexObject *corhdl, OCIPinOpt pin_option, OCIDuration pin_duration, OCILockOpt lock_option, dvoid **object);
static OCIObjectPin_func_t OCIObjectPin_func;
static int trace_OCIObjectPin = 1;

sword OCIObjectPin(OCIEnv *env, OCIError *err, OCIRef *object_ref, OCIComplexObject *corhdl, OCIPinOpt pin_option, OCIDuration pin_duration, OCILockOpt lock_option, dvoid **object)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectPin_func(env, err, object_ref, corhdl, pin_option, pin_duration, lock_option, object);
    if (trace_OCIObjectPin) {
        ocidump_log("%0*lX: OCIObjectPin(%p, %p, %p, %p, %u, %u, %u, [%p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     object_ref,
                     corhdl,
                     pin_option,
                     pin_duration,
                     lock_option,
                     *object,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIObjectPinCountReset_func_t)(OCIEnv *env, OCIError *err, void *object);
static OCIObjectPinCountReset_func_t OCIObjectPinCountReset_func;
static int trace_OCIObjectPinCountReset = 1;

sword OCIObjectPinCountReset(OCIEnv *env, OCIError *err, void *object)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectPinCountReset_func(env, err, object);
    if (trace_OCIObjectPinCountReset) {
        ocidump_log("%0*lX: OCIObjectPinCountReset(%p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     object,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIObjectPinTable_func_t)(OCIEnv *env, OCIError *err, const OCISvcCtx *svc, const oratext *schema_name, ub4 s_n_length, const oratext *object_name, ub4 o_n_length, const OCIRef *scope_obj_ref, OCIDuration pin_duration, void **object);
static OCIObjectPinTable_func_t OCIObjectPinTable_func;
static int trace_OCIObjectPinTable = 1;

sword OCIObjectPinTable(OCIEnv *env, OCIError *err, const OCISvcCtx *svc, const oratext *schema_name, ub4 s_n_length, const oratext *object_name, ub4 o_n_length, const OCIRef *scope_obj_ref, OCIDuration pin_duration, void **object)
{
    sword ret;
    char *buf1 = NULL;
    char *buf2 = NULL;
    char buf3[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectPinTable_func(env, err, svc, schema_name, s_n_length, object_name, o_n_length, scope_obj_ref, pin_duration, object);
    if (trace_OCIObjectPinTable) {
        ocidump_log("%0*lX: OCIObjectPinTable(%p, %p, %p, %s, %u, %s, %u, %p, %u, [%p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     svc,
                     ocidump_quotestring(&buf1, schema_name, s_n_length),
                     s_n_length,
                     ocidump_quotestring(&buf2, object_name, o_n_length),
                     o_n_length,
                     scope_obj_ref,
                     pin_duration,
                     *object,
                     ocidump_status2name(ret, buf3));
    }
    free(buf1);
    free(buf2);
    return ret;
}

typedef sword (*OCIObjectRefresh_func_t)(OCIEnv *env, OCIError *err, void *object);
static OCIObjectRefresh_func_t OCIObjectRefresh_func;
static int trace_OCIObjectRefresh = 1;

sword OCIObjectRefresh(OCIEnv *env, OCIError *err, void *object)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectRefresh_func(env, err, object);
    if (trace_OCIObjectRefresh) {
        ocidump_log("%0*lX: OCIObjectRefresh(%p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     object,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIObjectSetAttr_func_t)(OCIEnv *env, OCIError *err, void *instance, void *null_struct, struct OCIType *tdo, const oratext **names, const ub4 *lengths, const ub4 name_count, const ub4 *indexes, const ub4 index_count, const OCIInd null_status, const void *attr_null_struct, const void *attr_value);
static OCIObjectSetAttr_func_t OCIObjectSetAttr_func;
static int trace_OCIObjectSetAttr = 1;

sword OCIObjectSetAttr(OCIEnv *env, OCIError *err, void *instance, void *null_struct, struct OCIType *tdo, const oratext **names, const ub4 *lengths, const ub4 name_count, const ub4 *indexes, const ub4 index_count, const OCIInd null_status, const void *attr_null_struct, const void *attr_value)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    char buf3[OCIDUMP_SHORT_BUF_SIZE];
    char buf4[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectSetAttr_func(env, err, instance, null_struct, tdo, names, lengths, name_count, indexes, index_count, null_status, attr_null_struct, attr_value);
    if (trace_OCIObjectSetAttr) {
        ocidump_log("%0*lX: OCIObjectSetAttr(%p, %p, %p, %p, %p, %p, %p, %u, %s, %u, %d, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     instance,
                     null_struct,
                     tdo,
                     names ? ocidump_sprintf(buf1, "[%p, ...]", *names) : "(nil)",
                     lengths ? ocidump_sprintf(buf2, "[%u, ...]", *lengths) : "(nil)",
                     name_count,
                     indexes ? ocidump_sprintf(buf3, "[%u, ...]", *indexes) : "(nil)",
                     index_count,
                     null_status,
                     attr_null_struct,
                     attr_value,
                     ocidump_status2name(ret, buf4));
    }
    return ret;
}

typedef sword (*OCIObjectSetData_func_t)(OCIEnv *env, OCIError *err, void *obj_hdr, void *data);
static OCIObjectSetData_func_t OCIObjectSetData_func;
static int trace_OCIObjectSetData = 1;

sword OCIObjectSetData(OCIEnv *env, OCIError *err, void *obj_hdr, void *data)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectSetData_func(env, err, obj_hdr, data);
    if (trace_OCIObjectSetData) {
        ocidump_log("%0*lX: OCIObjectSetData(%p, %p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     obj_hdr,
                     data,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIObjectUnmark_func_t)(OCIEnv *env, OCIError *err, void *object);
static OCIObjectUnmark_func_t OCIObjectUnmark_func;
static int trace_OCIObjectUnmark = 1;

sword OCIObjectUnmark(OCIEnv *env, OCIError *err, void *object)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectUnmark_func(env, err, object);
    if (trace_OCIObjectUnmark) {
        ocidump_log("%0*lX: OCIObjectUnmark(%p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     object,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIObjectUnmarkByRef_func_t)(OCIEnv *env, OCIError *err, OCIRef *ref);
static OCIObjectUnmarkByRef_func_t OCIObjectUnmarkByRef_func;
static int trace_OCIObjectUnmarkByRef = 1;

sword OCIObjectUnmarkByRef(OCIEnv *env, OCIError *err, OCIRef *ref)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectUnmarkByRef_func(env, err, ref);
    if (trace_OCIObjectUnmarkByRef) {
        ocidump_log("%0*lX: OCIObjectUnmarkByRef(%p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     ref,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIObjectUnpin_func_t)(OCIEnv *env, OCIError *err, dvoid *object);
static OCIObjectUnpin_func_t OCIObjectUnpin_func;
static int trace_OCIObjectUnpin = 1;

sword OCIObjectUnpin(OCIEnv *env, OCIError *err, dvoid *object)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIObjectUnpin_func(env, err, object);
    if (trace_OCIObjectUnpin) {
        ocidump_log("%0*lX: OCIObjectUnpin(%p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     object,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIParamGet_func_t)(const dvoid *hndlp, ub4 htype, OCIError *errhp, dvoid **parmdpp, ub4 pos);
static OCIParamGet_func_t OCIParamGet_func;
static int trace_OCIParamGet = 1;

sword OCIParamGet(const dvoid *hndlp, ub4 htype, OCIError *errhp, dvoid **parmdpp, ub4 pos)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIParamGet_func(hndlp, htype, errhp, parmdpp, pos);
    if (trace_OCIParamGet) {
        ocidump_log("%0*lX: OCIParamGet(%p, %s, %p, [%p], %u) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndlp,
                     ocidump_htype2name(htype, buf1),
                     errhp,
                     *parmdpp,
                     pos,
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCIPasswordChange_func_t)(OCISvcCtx *svchp, OCIError *errhp, const OraText *user_name, ub4 usernm_len, const OraText *opasswd, ub4 opasswd_len, const OraText *npasswd, ub4 npasswd_len, ub4 mode);
static OCIPasswordChange_func_t OCIPasswordChange_func;
static int trace_OCIPasswordChange = 1;

sword OCIPasswordChange(OCISvcCtx *svchp, OCIError *errhp, const OraText *user_name, ub4 usernm_len, const OraText *opasswd, ub4 opasswd_len, const OraText *npasswd, ub4 npasswd_len, ub4 mode)
{
    sword ret;
    char *buf1 = NULL;
    char *buf2 = NULL;
    char *buf3 = NULL;
    char buf4[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIPasswordChange_func(svchp, errhp, user_name, usernm_len, opasswd, opasswd_len, npasswd, npasswd_len, mode);
    if (trace_OCIPasswordChange) {
        ocidump_log("%0*lX: OCIPasswordChange(%p, %p, %s, %d, %s, %d, %s, %d, %d) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     ocidump_quotestring(&buf1, user_name, usernm_len),
                     usernm_len,
                     ocidump_quotestring(&buf2, opasswd, opasswd_len),
                     opasswd_len,
                     ocidump_quotestring(&buf3, npasswd, npasswd_len),
                     npasswd_len,
                     mode,
                     ocidump_status2name(ret, buf4));
    }
    free(buf1);
    free(buf2);
    free(buf3);
    return ret;
}

typedef sword (*OCIPing_func_t)(OCISvcCtx *svchp, OCIError *errhp, ub4 mode);
static OCIPing_func_t OCIPing_func;
static int trace_OCIPing = 1;

sword OCIPing(OCISvcCtx *svchp, OCIError *errhp, ub4 mode)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIPing_func(svchp, errhp, mode);
    if (trace_OCIPing) {
        ocidump_log("%0*lX: OCIPing(%p, %p, 0x%x) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     mode,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIRawAllocSize_func_t)(OCIEnv *env, OCIError *err, const OCIRaw *raw, ub4 *allocsize);
static OCIRawAllocSize_func_t OCIRawAllocSize_func;
static int trace_OCIRawAllocSize = 1;

sword OCIRawAllocSize(OCIEnv *env, OCIError *err, const OCIRaw *raw, ub4 *allocsize)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIRawAllocSize_func(env, err, raw, allocsize);
    if (trace_OCIRawAllocSize) {
        ocidump_log("%0*lX: OCIRawAllocSize(%p, %p, %p, [%u]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     raw,
                     *allocsize,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIRawAssignBytes_func_t)(OCIEnv *env, OCIError *err, const ub1 *rhs, ub4 rhs_len, OCIRaw **lhs);
static OCIRawAssignBytes_func_t OCIRawAssignBytes_func;
static int trace_OCIRawAssignBytes = 1;

sword OCIRawAssignBytes(OCIEnv *env, OCIError *err, const ub1 *rhs, ub4 rhs_len, OCIRaw **lhs)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    OCIRaw *old_lhs = *lhs;

    if (!is_initialized) {
        initialize();
    }
    ret = OCIRawAssignBytes_func(env, err, rhs, rhs_len, lhs);
    if (trace_OCIRawAssignBytes) {
        ocidump_log("%0*lX: OCIRawAssignBytes(%p, %p, %p, %u, [%p -> %p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     rhs,
                     rhs_len,
                     old_lhs, *lhs,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIRawAssignRaw_func_t)(OCIEnv *env, OCIError *err, const OCIRaw *rhs, OCIRaw **lhs);
static OCIRawAssignRaw_func_t OCIRawAssignRaw_func;
static int trace_OCIRawAssignRaw = 1;

sword OCIRawAssignRaw(OCIEnv *env, OCIError *err, const OCIRaw *rhs, OCIRaw **lhs)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    OCIRaw *old_lhs = *lhs;

    if (!is_initialized) {
        initialize();
    }
    ret = OCIRawAssignRaw_func(env, err, rhs, lhs);
    if (trace_OCIRawAssignRaw) {
        ocidump_log("%0*lX: OCIRawAssignRaw(%p, %p, %p, [%p -> %p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     rhs,
                     old_lhs, *lhs,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef ub1 * (*OCIRawPtr_func_t)(OCIEnv *env, const OCIRaw *raw);
static OCIRawPtr_func_t OCIRawPtr_func;
static int trace_OCIRawPtr = 1;

ub1 * OCIRawPtr(OCIEnv *env, const OCIRaw *raw)
{
    ub1 * ret;
    if (!is_initialized) {
        initialize();
    }
    ret = OCIRawPtr_func(env, raw);
    if (trace_OCIRawPtr) {
        ocidump_log("%0*lX: OCIRawPtr(%p, %p) => %p\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     raw,
                     ret);
    }
    return ret;
}

typedef sword (*OCIRawResize_func_t)(OCIEnv *env, OCIError *err, ub4 new_size, OCIRaw **raw);
static OCIRawResize_func_t OCIRawResize_func;
static int trace_OCIRawResize = 1;

sword OCIRawResize(OCIEnv *env, OCIError *err, ub4 new_size, OCIRaw **raw)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    OCIRaw *old_raw = *raw;

    if (!is_initialized) {
        initialize();
    }
    ret = OCIRawResize_func(env, err, new_size, raw);
    if (trace_OCIRawResize) {
        ocidump_log("%0*lX: OCIRawResize(%p, %p, %u, [%p -> %p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     new_size,
                     old_raw, *raw,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef ub4 (*OCIRawSize_func_t)(OCIEnv *env, const OCIRaw *raw);
static OCIRawSize_func_t OCIRawSize_func;
static int trace_OCIRawSize = 1;

ub4 OCIRawSize(OCIEnv *env, const OCIRaw *raw)
{
    ub4 ret;
    if (!is_initialized) {
        initialize();
    }
    ret = OCIRawSize_func(env, raw);
    if (trace_OCIRawSize) {
        ocidump_log("%0*lX: OCIRawSize(%p, %p) => %u\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     raw,
                     ret);
    }
    return ret;
}

typedef sword (*OCIRefAssign_func_t)(OCIEnv *env, OCIError *err, const OCIRef *source, OCIRef **target);
static OCIRefAssign_func_t OCIRefAssign_func;
static int trace_OCIRefAssign = 1;

sword OCIRefAssign(OCIEnv *env, OCIError *err, const OCIRef *source, OCIRef **target)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    OCIRef *old_target = *target;

    if (!is_initialized) {
        initialize();
    }
    ret = OCIRefAssign_func(env, err, source, target);
    if (trace_OCIRefAssign) {
        ocidump_log("%0*lX: OCIRefAssign(%p, %p, %p, [%p -> %p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     source,
                     old_target, *target,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef void (*OCIRefClear_func_t)(OCIEnv *env, OCIRef *ref);
static OCIRefClear_func_t OCIRefClear_func;
static int trace_OCIRefClear = 1;

void OCIRefClear(OCIEnv *env, OCIRef *ref)
{
    if (!is_initialized) {
        initialize();
    }
    OCIRefClear_func(env, ref);
    if (trace_OCIRefClear) {
        ocidump_log("%0*lX: OCIRefClear(%p, %p)\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     ref);
    }
}

typedef sword (*OCIRefFromHex_func_t)(OCIEnv *env, OCIError *err, const OCISvcCtx *svc, const oratext *hex, ub4 length, OCIRef **ref);
static OCIRefFromHex_func_t OCIRefFromHex_func;
static int trace_OCIRefFromHex = 1;

sword OCIRefFromHex(OCIEnv *env, OCIError *err, const OCISvcCtx *svc, const oratext *hex, ub4 length, OCIRef **ref)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    OCIRef *old_ref = *ref;

    if (!is_initialized) {
        initialize();
    }
    ret = OCIRefFromHex_func(env, err, svc, hex, length, ref);
    if (trace_OCIRefFromHex) {
        if (ocidump_hide_string) {
            length = 6;
            hex = (OraText*)"hidden";
        }
        ocidump_log("%0*lX: OCIRefFromHex(%p, %p, %p, \"%.*s\", %u, [%p -> %p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     svc,
                     length, hex,
                     length,
                     old_ref, *ref,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef ub4 (*OCIRefHexSize_func_t)(OCIEnv *env, const OCIRef *ref);
static OCIRefHexSize_func_t OCIRefHexSize_func;
static int trace_OCIRefHexSize = 1;

ub4 OCIRefHexSize(OCIEnv *env, const OCIRef *ref)
{
    ub4 ret;
    if (!is_initialized) {
        initialize();
    }
    ret = OCIRefHexSize_func(env, ref);
    if (trace_OCIRefHexSize) {
        ocidump_log("%0*lX: OCIRefHexSize(%p, %p) => %u\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     ref,
                     ret);
    }
    return ret;
}

typedef boolean (*OCIRefIsEqual_func_t)(OCIEnv *env, const OCIRef *x, const OCIRef *y);
static OCIRefIsEqual_func_t OCIRefIsEqual_func;
static int trace_OCIRefIsEqual = 1;

boolean OCIRefIsEqual(OCIEnv *env, const OCIRef *x, const OCIRef *y)
{
    boolean ret;
    if (!is_initialized) {
        initialize();
    }
    ret = OCIRefIsEqual_func(env, x, y);
    if (trace_OCIRefIsEqual) {
        ocidump_log("%0*lX: OCIRefIsEqual(%p, %p, %p) => %d\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     x,
                     y,
                     ret);
    }
    return ret;
}

typedef boolean (*OCIRefIsNull_func_t)(OCIEnv *env, const OCIRef *ref);
static OCIRefIsNull_func_t OCIRefIsNull_func;
static int trace_OCIRefIsNull = 1;

boolean OCIRefIsNull(OCIEnv *env, const OCIRef *ref)
{
    boolean ret;
    if (!is_initialized) {
        initialize();
    }
    ret = OCIRefIsNull_func(env, ref);
    if (trace_OCIRefIsNull) {
        ocidump_log("%0*lX: OCIRefIsNull(%p, %p) => %d\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     ref,
                     ret);
    }
    return ret;
}

typedef sword (*OCIRefToHex_func_t)(OCIEnv *env, OCIError *err, const OCIRef *ref, oratext *hex, ub4 *hex_length);
static OCIRefToHex_func_t OCIRefToHex_func;
static int trace_OCIRefToHex = 1;

sword OCIRefToHex(OCIEnv *env, OCIError *err, const OCIRef *ref, oratext *hex, ub4 *hex_length)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    ub4 old_hex_length = *hex_length;

    if (!is_initialized) {
        initialize();
    }
    ret = OCIRefToHex_func(env, err, ref, hex, hex_length);
    if (trace_OCIRefToHex) {
        ub4 new_hex_length = *hex_length;

        if (ocidump_hide_string) {
            new_hex_length = 6;
            hex = (OraText*)"hidden";
        }
        ocidump_log("%0*lX: OCIRefToHex(%p, %p, %p, \"%.*s\", [%u -> %u]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     ref,
                     new_hex_length, hex,
                     old_hex_length, *hex_length,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIReset_func_t)(dvoid *hndlp, OCIError *errhp);
static OCIReset_func_t OCIReset_func;
static int trace_OCIReset = 1;

sword OCIReset(dvoid *hndlp, OCIError *errhp)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIReset_func(hndlp, errhp);
    if (trace_OCIReset) {
        ocidump_log("%0*lX: OCIReset(%p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndlp,
                     errhp,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIResultSetToStmt_func_t)(OCIResult *rsetdp, OCIError *errhp);
static OCIResultSetToStmt_func_t OCIResultSetToStmt_func;
static int trace_OCIResultSetToStmt = 1;

sword OCIResultSetToStmt(OCIResult *rsetdp, OCIError *errhp)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIResultSetToStmt_func(rsetdp, errhp);
    if (trace_OCIResultSetToStmt) {
        ocidump_log("%0*lX: OCIResultSetToStmt(%p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     rsetdp,
                     errhp,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIRowidToChar_func_t)(OCIRowid *rowidDesc, OraText *outbfp, ub2 *outbflp, OCIError *errhp);
static OCIRowidToChar_func_t OCIRowidToChar_func;
static int trace_OCIRowidToChar = 1;

sword OCIRowidToChar(OCIRowid *rowidDesc, OraText *outbfp, ub2 *outbflp, OCIError *errhp)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIRowidToChar_func(rowidDesc, outbfp, outbflp, errhp);
    if (trace_OCIRowidToChar) {
        ub2 outbfl = (ret == 0) ? *outbflp : 0;

        if (ocidump_hide_string) {
            outbfl = 6;
            outbfp = (OraText*)"hidden";
        }
        ocidump_log("%0*lX: OCIRowidToChar(%p, \"%.*s\", [%u], %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     rowidDesc,
                     outbfl, outbfp,
                     outbfl,
                     errhp,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIServerAttach_func_t)(OCIServer *srvhp, OCIError *errhp, CONST text *dblink, sb4 dblink_len, ub4 mode);
static OCIServerAttach_func_t OCIServerAttach_func;
static int trace_OCIServerAttach = 1;

sword OCIServerAttach(OCIServer *srvhp, OCIError *errhp, CONST text *dblink, sb4 dblink_len, ub4 mode)
{
    sword ret;
    char *buf1 = NULL;
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIServerAttach_func(srvhp, errhp, dblink, dblink_len, mode);
    if (trace_OCIServerAttach) {
        ocidump_log("%0*lX: OCIServerAttach(%p, %p, %s, %d, 0x%x) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     srvhp,
                     errhp,
                     ocidump_quotestring(&buf1, dblink, dblink_len),
                     dblink_len,
                     mode,
                     ocidump_status2name(ret, buf2));
    }
    free(buf1);
    return ret;
}

typedef sword (*OCIServerDetach_func_t)(OCIServer *srvhp, OCIError *errhp, ub4 mode);
static OCIServerDetach_func_t OCIServerDetach_func;
static int trace_OCIServerDetach = 1;

sword OCIServerDetach(OCIServer *srvhp, OCIError *errhp, ub4 mode)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIServerDetach_func(srvhp, errhp, mode);
    if (trace_OCIServerDetach) {
        ocidump_log("%0*lX: OCIServerDetach(%p, %p, 0x%x) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     srvhp,
                     errhp,
                     mode,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIServerRelease_func_t)(dvoid *hndlp, OCIError *errhp, OraText *bufp, ub4 bufsz, ub1 hndltype, ub4 *version);
static OCIServerRelease_func_t OCIServerRelease_func;
static int trace_OCIServerRelease = 1;

sword OCIServerRelease(dvoid *hndlp, OCIError *errhp, OraText *bufp, ub4 bufsz, ub1 hndltype, ub4 *version)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIServerRelease_func(hndlp, errhp, bufp, bufsz, hndltype, version);
    if (trace_OCIServerRelease) {
        if (ocidump_hide_string) {
            bufsz = 6;
            bufp = (OraText*)"hidden";
        }
        ocidump_log("%0*lX: OCIServerRelease(%p, %p, \"%.*s\", %u, %s, [0x%08x]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndlp,
                     errhp,
                     bufsz, bufp,
                     bufsz,
                     ocidump_htype2name(hndltype, buf1),
                     version ? *version : 0,
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCIServerVersion_func_t)(dvoid *hndlp, OCIError *errhp, OraText *bufp, ub4 bufsz, ub1 hndltype);
static OCIServerVersion_func_t OCIServerVersion_func;
static int trace_OCIServerVersion = 1;

sword OCIServerVersion(dvoid *hndlp, OCIError *errhp, OraText *bufp, ub4 bufsz, ub1 hndltype)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIServerVersion_func(hndlp, errhp, bufp, bufsz, hndltype);
    if (trace_OCIServerVersion) {
        if (ocidump_hide_string) {
            bufsz = 6;
            bufp = (OraText*)"hidden";
        }
        ocidump_log("%0*lX: OCIServerVersion(%p, %p, \"%.*s\", %u, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndlp,
                     errhp,
                     bufsz, bufp,
                     bufsz,
                     ocidump_htype2name(hndltype, buf1),
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCISessionBegin_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCISession *usrhp, ub4 credt, ub4 mode);
static OCISessionBegin_func_t OCISessionBegin_func;
static int trace_OCISessionBegin = 1;

sword OCISessionBegin(OCISvcCtx *svchp, OCIError *errhp, OCISession *usrhp, ub4 credt, ub4 mode)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCISessionBegin_func(svchp, errhp, usrhp, credt, mode);
    if (trace_OCISessionBegin) {
        ocidump_log("%0*lX: OCISessionBegin(%p, %p, %p, %u, 0x%x) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     usrhp,
                     credt,
                     mode,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCISessionEnd_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCISession *usrhp, ub4 mode);
static OCISessionEnd_func_t OCISessionEnd_func;
static int trace_OCISessionEnd = 1;

sword OCISessionEnd(OCISvcCtx *svchp, OCIError *errhp, OCISession *usrhp, ub4 mode)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCISessionEnd_func(svchp, errhp, usrhp, mode);
    if (trace_OCISessionEnd) {
        ocidump_log("%0*lX: OCISessionEnd(%p, %p, %p, 0x%x) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     usrhp,
                     mode,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCISessionGet_func_t)(OCIEnv *envhp, OCIError *errhp, OCISvcCtx **svchp, OCIAuthInfo *authhp, OraText *poolName, ub4 poolName_len, const OraText *tagInfo, ub4 tagInfo_len, OraText **retTagInfo, ub4 *retTagInfo_len, boolean *found, ub4 mode);
static OCISessionGet_func_t OCISessionGet_func;
static int trace_OCISessionGet = 1;

sword OCISessionGet(OCIEnv *envhp, OCIError *errhp, OCISvcCtx **svchp, OCIAuthInfo *authhp, OraText *poolName, ub4 poolName_len, const OraText *tagInfo, ub4 tagInfo_len, OraText **retTagInfo, ub4 *retTagInfo_len, boolean *found, ub4 mode)
{
    sword ret;
    char *buf1 = NULL;
    char *buf2 = NULL;
    char *buf3 = NULL;
    char buf4[OCIDUMP_SHORT_BUF_SIZE];
    char buf5[OCIDUMP_SHORT_BUF_SIZE];
    char buf6[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCISessionGet_func(envhp, errhp, svchp, authhp, poolName, poolName_len, tagInfo, tagInfo_len, retTagInfo, retTagInfo_len, found, mode);
    if (trace_OCISessionGet) {
        ocidump_log("%0*lX: OCISessionGet(%p, %p, [%p], %p, %s, %u, %s, %u, %s, %s, %s, 0x%x) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     envhp,
                     errhp,
                     *svchp,
                     authhp,
                     ocidump_quotestring(&buf1, poolName, poolName_len),
                     poolName_len,
                     ocidump_quotestring(&buf2, tagInfo, tagInfo_len),
                     tagInfo_len,
                     ocidump_quotestring2(&buf3, retTagInfo, retTagInfo_len),
                     retTagInfo_len ? ocidump_sprintf(buf4, "[%u]", *retTagInfo_len) : "(nil)",
                     found ? ocidump_sprintf(buf5, "[%d]", *found) : "(nil)",
                     mode,
                     ocidump_status2name(ret, buf6));
    }
    free(buf1);
    free(buf2);
    free(buf3);
    return ret;
}

typedef sword (*OCISessionPoolCreate_func_t)(OCIEnv *envhp, OCIError *errhp, OCISPool *spoolhp, OraText **poolName, ub4 *poolNameLen, const OraText *connStr, ub4 connStrLen, ub4 sessMin, ub4 sessMax, ub4 sessIncr, OraText *userid, ub4 useridLen, OraText *password, ub4 passwordLen, ub4 mode);
static OCISessionPoolCreate_func_t OCISessionPoolCreate_func;
static int trace_OCISessionPoolCreate = 1;

sword OCISessionPoolCreate(OCIEnv *envhp, OCIError *errhp, OCISPool *spoolhp, OraText **poolName, ub4 *poolNameLen, const OraText *connStr, ub4 connStrLen, ub4 sessMin, ub4 sessMax, ub4 sessIncr, OraText *userid, ub4 useridLen, OraText *password, ub4 passwordLen, ub4 mode)
{
    sword ret;
    char *buf1 = NULL;
    char *buf2 = NULL;
    char *buf3 = NULL;
    char buf4[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCISessionPoolCreate_func(envhp, errhp, spoolhp, poolName, poolNameLen, connStr, connStrLen, sessMin, sessMax, sessIncr, userid, useridLen, password, passwordLen, mode);
    if (trace_OCISessionPoolCreate) {
        OraText *name = *poolName;
        ub4 len = (ret == 0) ? *poolNameLen : 0;

        ocidump_log("%0*lX: OCISessionPoolCreate(%p, %p, %p, [\"%.*s\"], [%u], %s, %u, %u, %u, %u, %s, %u, %s, %u, 0x%x) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     envhp,
                     errhp,
                     spoolhp,
                     len, name,
                     *poolNameLen,
                     ocidump_quotestring(&buf1, connStr, connStrLen),
                     connStrLen,
                     sessMin,
                     sessMax,
                     sessIncr,
                     ocidump_quotestring(&buf2, userid, useridLen),
                     useridLen,
                     ocidump_quotestring(&buf3, password, passwordLen),
                     passwordLen,
                     mode,
                     ocidump_status2name(ret, buf4));
    }
    free(buf1);
    free(buf2);
    free(buf3);
    return ret;
}

typedef sword (*OCISessionPoolDestroy_func_t)(OCISPool *spoolhp, OCIError *errhp, ub4 mode);
static OCISessionPoolDestroy_func_t OCISessionPoolDestroy_func;
static int trace_OCISessionPoolDestroy = 1;

sword OCISessionPoolDestroy(OCISPool *spoolhp, OCIError *errhp, ub4 mode)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCISessionPoolDestroy_func(spoolhp, errhp, mode);
    if (trace_OCISessionPoolDestroy) {
        ocidump_log("%0*lX: OCISessionPoolDestroy(%p, %p, 0x%x) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     spoolhp,
                     errhp,
                     mode,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCISessionRelease_func_t)(OCISvcCtx *svchp, OCIError *errhp, OraText *tag, ub4 tag_len, ub4 mode);
static OCISessionRelease_func_t OCISessionRelease_func;
static int trace_OCISessionRelease = 1;

sword OCISessionRelease(OCISvcCtx *svchp, OCIError *errhp, OraText *tag, ub4 tag_len, ub4 mode)
{
    sword ret;
    char *buf1 = NULL;
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCISessionRelease_func(svchp, errhp, tag, tag_len, mode);
    if (trace_OCISessionRelease) {
        ocidump_log("%0*lX: OCISessionRelease(%p, %p, %s, %u, 0x%x) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     ocidump_quotestring(&buf1, tag, tag_len),
                     tag_len,
                     mode,
                     ocidump_status2name(ret, buf2));
    }
    free(buf1);
    return ret;
}

typedef sword (*OCISharedLibInit_func_t)(void *metaCtx, void *libCtx, ub4 argfmt, sword argc, void **argv, OCIEnvCallbackType envCallback);
static OCISharedLibInit_func_t OCISharedLibInit_func;
static int trace_OCISharedLibInit = 1;

sword OCISharedLibInit(void *metaCtx, void *libCtx, ub4 argfmt, sword argc, void **argv, OCIEnvCallbackType envCallback)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCISharedLibInit_func(metaCtx, libCtx, argfmt, argc, argv, envCallback);
    if (trace_OCISharedLibInit) {
        ocidump_log("%0*lX: OCISharedLibInit(%p, %p, %u, %d, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     metaCtx,
                     libCtx,
                     argfmt,
                     argc,
                     argv,
                     envCallback,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIStmtExecute_func_t)(OCISvcCtx *svchp, OCIStmt *stmtp, OCIError *errhp, ub4 iters, ub4 rowoff, const OCISnapshot *snap_in, OCISnapshot *snap_out, ub4 mode);
static OCIStmtExecute_func_t OCIStmtExecute_func;
static int trace_OCIStmtExecute = 1;

sword OCIStmtExecute(OCISvcCtx *svchp, OCIStmt *stmtp, OCIError *errhp, ub4 iters, ub4 rowoff, const OCISnapshot *snap_in, OCISnapshot *snap_out, ub4 mode)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIStmtExecute_func(svchp, stmtp, errhp, iters, rowoff, snap_in, snap_out, mode);
    if (trace_OCIStmtExecute) {
        ocidump_log("%0*lX: OCIStmtExecute(%p, %p, %p, %u, %u, %p, %p, 0x%x) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     stmtp,
                     errhp,
                     iters,
                     rowoff,
                     snap_in,
                     snap_out,
                     mode,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIStmtFetch_func_t)(OCIStmt *stmtp, OCIError *errhp, ub4 nrows, ub2 orientation, ub4 mode);
static OCIStmtFetch_func_t OCIStmtFetch_func;
static int trace_OCIStmtFetch = 1;

sword OCIStmtFetch(OCIStmt *stmtp, OCIError *errhp, ub4 nrows, ub2 orientation, ub4 mode)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIStmtFetch_func(stmtp, errhp, nrows, orientation, mode);
    if (trace_OCIStmtFetch) {
        ocidump_log("%0*lX: OCIStmtFetch(%p, %p, %u, 0x%x, 0x%x) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     stmtp,
                     errhp,
                     nrows,
                     orientation,
                     mode,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIStmtFetch2_func_t)(OCIStmt *stmtp, OCIError *errhp, ub4 nrows, ub2 orientation, sb4 scrollOffset, ub4 mode);
static OCIStmtFetch2_func_t OCIStmtFetch2_func;
static int trace_OCIStmtFetch2 = 1;

sword OCIStmtFetch2(OCIStmt *stmtp, OCIError *errhp, ub4 nrows, ub2 orientation, sb4 scrollOffset, ub4 mode)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIStmtFetch2_func(stmtp, errhp, nrows, orientation, scrollOffset, mode);
    if (trace_OCIStmtFetch2) {
        ocidump_log("%0*lX: OCIStmtFetch2(%p, %p, %u, 0x%x, %d, 0x%x) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     stmtp,
                     errhp,
                     nrows,
                     orientation,
                     scrollOffset,
                     mode,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIStmtGetBindInfo_func_t)(OCIStmt *stmtp, OCIError *errhp, ub4 size, ub4 startloc, sb4 *found, OraText *bvnp[], ub1 bvnl[], OraText *invp[], ub1 inpl[], ub1 dupl[], OCIBind **hndl);
static OCIStmtGetBindInfo_func_t OCIStmtGetBindInfo_func;
static int trace_OCIStmtGetBindInfo = 1;

sword OCIStmtGetBindInfo(OCIStmt *stmtp, OCIError *errhp, ub4 size, ub4 startloc, sb4 *found, OraText *bvnp[], ub1 bvnl[], OraText *invp[], ub1 inpl[], ub1 dupl[], OCIBind **hndl)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIStmtGetBindInfo_func(stmtp, errhp, size, startloc, found, bvnp, bvnl, invp, inpl, dupl, hndl);
    if (trace_OCIStmtGetBindInfo) {
        ocidump_log("%0*lX: OCIStmtGetBindInfo(%p, %p, %u, %u, [%d], %p, %p, %p, %p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     stmtp,
                     errhp,
                     size,
                     startloc,
                     *found,
                     bvnp,
                     bvnl,
                     invp,
                     inpl,
                     dupl,
                     hndl,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIStmtGetPieceInfo_func_t)(OCIStmt *stmtp, OCIError *errhp, dvoid **hndlpp, ub4 *typep, ub1 *in_outp, ub4 *iterp, ub4 *idxp, ub1 *piecep);
static OCIStmtGetPieceInfo_func_t OCIStmtGetPieceInfo_func;
static int trace_OCIStmtGetPieceInfo = 1;

sword OCIStmtGetPieceInfo(OCIStmt *stmtp, OCIError *errhp, dvoid **hndlpp, ub4 *typep, ub1 *in_outp, ub4 *iterp, ub4 *idxp, ub1 *piecep)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIStmtGetPieceInfo_func(stmtp, errhp, hndlpp, typep, in_outp, iterp, idxp, piecep);
    if (trace_OCIStmtGetPieceInfo) {
        ocidump_log("%0*lX: OCIStmtGetPieceInfo(%p, %p, [%p], [%s], [%u], [%u], [%u], [%u]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     stmtp,
                     errhp,
                     *hndlpp,
                     ocidump_htype2name(*typep, buf1),
                     *in_outp,
                     *iterp,
                     *idxp,
                     *piecep,
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCIStmtPrepare_func_t)(OCIStmt *stmtp, OCIError *errhp, const OraText *stmt, ub4 stmt_len, ub4 language, ub4 mode);
static OCIStmtPrepare_func_t OCIStmtPrepare_func;
static int trace_OCIStmtPrepare = 1;

sword OCIStmtPrepare(OCIStmt *stmtp, OCIError *errhp, const OraText *stmt, ub4 stmt_len, ub4 language, ub4 mode)
{
    sword ret;
    char *buf1 = NULL;
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIStmtPrepare_func(stmtp, errhp, stmt, stmt_len, language, mode);
    if (trace_OCIStmtPrepare) {
        ocidump_log("%0*lX: OCIStmtPrepare(%p, %p, %s, %u, %u, 0x%x) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     stmtp,
                     errhp,
                     ocidump_quotestring(&buf1, stmt, stmt_len),
                     stmt_len,
                     language,
                     mode,
                     ocidump_status2name(ret, buf2));
    }
    free(buf1);
    return ret;
}

typedef sword (*OCIStmtPrepare2_func_t)(OCISvcCtx *svchp, OCIStmt **stmtp, OCIError *errhp, const OraText *stmt, ub4 stmt_len, const OraText *key, ub4 key_len, ub4 language, ub4 mode);
static OCIStmtPrepare2_func_t OCIStmtPrepare2_func;
static int trace_OCIStmtPrepare2 = 1;

sword OCIStmtPrepare2(OCISvcCtx *svchp, OCIStmt **stmtp, OCIError *errhp, const OraText *stmt, ub4 stmt_len, const OraText *key, ub4 key_len, ub4 language, ub4 mode)
{
    sword ret;
    char *buf1 = NULL;
    char *buf2 = NULL;
    char buf3[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIStmtPrepare2_func(svchp, stmtp, errhp, stmt, stmt_len, key, key_len, language, mode);
    if (trace_OCIStmtPrepare2) {
        ocidump_log("%0*lX: OCIStmtPrepare2(%p, [%p], %p, %s, %u, %s, %u, %u, 0x%x) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     *stmtp,
                     errhp,
                     ocidump_quotestring(&buf1, stmt, stmt_len),
                     stmt_len,
                     ocidump_quotestring(&buf2, key, key_len),
                     key_len,
                     language,
                     mode,
                     ocidump_status2name(ret, buf3));
    }
    free(buf1);
    free(buf2);
    return ret;
}

typedef sword (*OCIStmtRelease_func_t)(OCIStmt *stmtp, OCIError *errhp, const OraText *key, ub4 key_len, ub4 mode);
static OCIStmtRelease_func_t OCIStmtRelease_func;
static int trace_OCIStmtRelease = 1;

sword OCIStmtRelease(OCIStmt *stmtp, OCIError *errhp, const OraText *key, ub4 key_len, ub4 mode)
{
    sword ret;
    char *buf1 = NULL;
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIStmtRelease_func(stmtp, errhp, key, key_len, mode);
    if (trace_OCIStmtRelease) {
        ocidump_log("%0*lX: OCIStmtRelease(%p, %p, %s, %u, 0x%x) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     stmtp,
                     errhp,
                     ocidump_quotestring(&buf1, key, key_len),
                     key_len,
                     mode,
                     ocidump_status2name(ret, buf2));
    }
    free(buf1);
    return ret;
}

typedef sword (*OCIStmtSetPieceInfo_func_t)(dvoid *hndlp, ub4 type, OCIError *errhp, CONST dvoid *bufp, ub4 *alenp, ub1 piece, CONST dvoid *indp, ub2 *rcodep);
static OCIStmtSetPieceInfo_func_t OCIStmtSetPieceInfo_func;
static int trace_OCIStmtSetPieceInfo = 1;

sword OCIStmtSetPieceInfo(dvoid *hndlp, ub4 type, OCIError *errhp, CONST dvoid *bufp, ub4 *alenp, ub1 piece, CONST dvoid *indp, ub2 *rcodep)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIStmtSetPieceInfo_func(hndlp, type, errhp, bufp, alenp, piece, indp, rcodep);
    if (trace_OCIStmtSetPieceInfo) {
        ocidump_log("%0*lX: OCIStmtSetPieceInfo(%p, %s, %p, %p, %p, %u, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     hndlp,
                     ocidump_htype2name(type, buf1),
                     errhp,
                     bufp,
                     alenp,
                     piece,
                     indp,
                     rcodep,
                     ocidump_status2name(ret, buf2));
    }
    return ret;
}

typedef sword (*OCIStringAllocSize_func_t)(OCIEnv *env, OCIError *err, const OCIString *vs, ub4 *allocsize);
static OCIStringAllocSize_func_t OCIStringAllocSize_func;
static int trace_OCIStringAllocSize = 1;

sword OCIStringAllocSize(OCIEnv *env, OCIError *err, const OCIString *vs, ub4 *allocsize)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIStringAllocSize_func(env, err, vs, allocsize);
    if (trace_OCIStringAllocSize) {
        ocidump_log("%0*lX: OCIStringAllocSize(%p, %p, %p, [%u]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     vs,
                     *allocsize,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIStringAssign_func_t)(OCIEnv *env, OCIError *err, const OCIString *rhs, OCIString **lhs);
static OCIStringAssign_func_t OCIStringAssign_func;
static int trace_OCIStringAssign = 1;

sword OCIStringAssign(OCIEnv *env, OCIError *err, const OCIString *rhs, OCIString **lhs)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    OCIString *old_lhs = *lhs;

    if (!is_initialized) {
        initialize();
    }
    ret = OCIStringAssign_func(env, err, rhs, lhs);
    if (trace_OCIStringAssign) {
        ocidump_log("%0*lX: OCIStringAssign(%p, %p, %p, [%p -> %p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     rhs,
                     old_lhs, *lhs,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIStringAssignText_func_t)(OCIEnv *env, OCIError *err, const text *rhs, ub4 rhs_len, OCIString **lhs);
static OCIStringAssignText_func_t OCIStringAssignText_func;
static int trace_OCIStringAssignText = 1;

sword OCIStringAssignText(OCIEnv *env, OCIError *err, const text *rhs, ub4 rhs_len, OCIString **lhs)
{
    sword ret;
    char *buf1 = NULL;
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    OCIString *old_lhs = *lhs;

    if (!is_initialized) {
        initialize();
    }
    ret = OCIStringAssignText_func(env, err, rhs, rhs_len, lhs);
    if (trace_OCIStringAssignText) {
        ocidump_log("%0*lX: OCIStringAssignText(%p, %p, %s, %u, [%p -> %p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     ocidump_quotestring(&buf1, rhs, rhs_len),
                     rhs_len,
                     old_lhs, *lhs,
                     ocidump_status2name(ret, buf2));
    }
    free(buf1);
    return ret;
}

typedef text * (*OCIStringPtr_func_t)(OCIEnv *env, const OCIString *vs);
static OCIStringPtr_func_t OCIStringPtr_func;
static int trace_OCIStringPtr = 1;

text * OCIStringPtr(OCIEnv *env, const OCIString *vs)
{
    text * ret;
    if (!is_initialized) {
        initialize();
    }
    ret = OCIStringPtr_func(env, vs);
    if (trace_OCIStringPtr) {
        ocidump_log("%0*lX: OCIStringPtr(%p, %p) => %p\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     vs,
                     ret);
    }
    return ret;
}

typedef sword (*OCIStringResize_func_t)(OCIEnv *env, OCIError *err, ub4 new_size, OCIString **str);
static OCIStringResize_func_t OCIStringResize_func;
static int trace_OCIStringResize = 1;

sword OCIStringResize(OCIEnv *env, OCIError *err, ub4 new_size, OCIString **str)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    OCIString *old_str = *str;

    if (!is_initialized) {
        initialize();
    }
    ret = OCIStringResize_func(env, err, new_size, str);
    if (trace_OCIStringResize) {
        ocidump_log("%0*lX: OCIStringResize(%p, %p, %u, [%p -> %p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     new_size,
                     old_str, *str,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef ub4 (*OCIStringSize_func_t)(OCIEnv *env, const OCIString *vs);
static OCIStringSize_func_t OCIStringSize_func;
static int trace_OCIStringSize = 1;

ub4 OCIStringSize(OCIEnv *env, const OCIString *vs)
{
    ub4 ret;
    if (!is_initialized) {
        initialize();
    }
    ret = OCIStringSize_func(env, vs);
    if (trace_OCIStringSize) {
        ocidump_log("%0*lX: OCIStringSize(%p, %p) => %u\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     vs,
                     ret);
    }
    return ret;
}

typedef sword (*OCITableDelete_func_t)(OCIEnv *env, OCIError *err, sb4 index, OCITable *tbl);
static OCITableDelete_func_t OCITableDelete_func;
static int trace_OCITableDelete = 1;

sword OCITableDelete(OCIEnv *env, OCIError *err, sb4 index, OCITable *tbl)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITableDelete_func(env, err, index, tbl);
    if (trace_OCITableDelete) {
        ocidump_log("%0*lX: OCITableDelete(%p, %p, %d, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     index,
                     tbl,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCITableExists_func_t)(OCIEnv *env, OCIError *err, const OCITable *tbl, sb4 index, boolean *exists);
static OCITableExists_func_t OCITableExists_func;
static int trace_OCITableExists = 1;

sword OCITableExists(OCIEnv *env, OCIError *err, const OCITable *tbl, sb4 index, boolean *exists)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITableExists_func(env, err, tbl, index, exists);
    if (trace_OCITableExists) {
        ocidump_log("%0*lX: OCITableExists(%p, %p, %p, %d, [%d]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     tbl,
                     index,
                     *exists,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCITableFirst_func_t)(OCIEnv *env, OCIError *err, const OCITable *tbl, sb4 *index);
static OCITableFirst_func_t OCITableFirst_func;
static int trace_OCITableFirst = 1;

sword OCITableFirst(OCIEnv *env, OCIError *err, const OCITable *tbl, sb4 *index)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITableFirst_func(env, err, tbl, index);
    if (trace_OCITableFirst) {
        ocidump_log("%0*lX: OCITableFirst(%p, %p, %p, [%d]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     tbl,
                     *index,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCITableLast_func_t)(OCIEnv *env, OCIError *err, const OCITable *tbl, sb4 *index);
static OCITableLast_func_t OCITableLast_func;
static int trace_OCITableLast = 1;

sword OCITableLast(OCIEnv *env, OCIError *err, const OCITable *tbl, sb4 *index)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITableLast_func(env, err, tbl, index);
    if (trace_OCITableLast) {
        ocidump_log("%0*lX: OCITableLast(%p, %p, %p, [%d]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     tbl,
                     *index,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCITableNext_func_t)(OCIEnv *env, OCIError *err, sb4 index, const OCITable *tbl, sb4 *next_index, boolean *exists);
static OCITableNext_func_t OCITableNext_func;
static int trace_OCITableNext = 1;

sword OCITableNext(OCIEnv *env, OCIError *err, sb4 index, const OCITable *tbl, sb4 *next_index, boolean *exists)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITableNext_func(env, err, index, tbl, next_index, exists);
    if (trace_OCITableNext) {
        ocidump_log("%0*lX: OCITableNext(%p, %p, %d, %p, [%d], [%d]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     index,
                     tbl,
                     *next_index,
                     *exists,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCITablePrev_func_t)(OCIEnv *env, OCIError *err, sb4 index, const OCITable *tbl, sb4 *prev_index, boolean *exists);
static OCITablePrev_func_t OCITablePrev_func;
static int trace_OCITablePrev = 1;

sword OCITablePrev(OCIEnv *env, OCIError *err, sb4 index, const OCITable *tbl, sb4 *prev_index, boolean *exists)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITablePrev_func(env, err, index, tbl, prev_index, exists);
    if (trace_OCITablePrev) {
        ocidump_log("%0*lX: OCITablePrev(%p, %p, %d, %p, [%d], [%d]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     index,
                     tbl,
                     *prev_index,
                     *exists,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCITableSize_func_t)(OCIEnv *env, OCIError *err, const OCITable *tbl, sb4 *size);
static OCITableSize_func_t OCITableSize_func;
static int trace_OCITableSize = 1;

sword OCITableSize(OCIEnv *env, OCIError *err, const OCITable *tbl, sb4 *size)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITableSize_func(env, err, tbl, size);
    if (trace_OCITableSize) {
        ocidump_log("%0*lX: OCITableSize(%p, %p, %p, [%d]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     tbl,
                     *size,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCITransCommit_func_t)(OCISvcCtx *svchp, OCIError *errhp, ub4 flags);
static OCITransCommit_func_t OCITransCommit_func;
static int trace_OCITransCommit = 1;

sword OCITransCommit(OCISvcCtx *svchp, OCIError *errhp, ub4 flags)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITransCommit_func(svchp, errhp, flags);
    if (trace_OCITransCommit) {
        ocidump_log("%0*lX: OCITransCommit(%p, %p, 0x%x) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     flags,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCITransRollback_func_t)(OCISvcCtx *svchp, OCIError *errhp, ub4 flags);
static OCITransRollback_func_t OCITransRollback_func;
static int trace_OCITransRollback = 1;

sword OCITransRollback(OCISvcCtx *svchp, OCIError *errhp, ub4 flags)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITransRollback_func(svchp, errhp, flags);
    if (trace_OCITransRollback) {
        ocidump_log("%0*lX: OCITransRollback(%p, %p, 0x%x) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     flags,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCITypeAddAttr_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCIType *type, const oratext *a_name, ub4 a_length, OCIParam *attr_info);
static OCITypeAddAttr_func_t OCITypeAddAttr_func;
static int trace_OCITypeAddAttr = 1;

sword OCITypeAddAttr(OCISvcCtx *svchp, OCIError *errhp, OCIType *type, const oratext *a_name, ub4 a_length, OCIParam *attr_info)
{
    sword ret;
    char *buf1 = NULL;
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeAddAttr_func(svchp, errhp, type, a_name, a_length, attr_info);
    if (trace_OCITypeAddAttr) {
        ocidump_log("%0*lX: OCITypeAddAttr(%p, %p, %p, %s, %u, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     type,
                     ocidump_quotestring(&buf1, a_name, a_length),
                     a_length,
                     attr_info,
                     ocidump_status2name(ret, buf2));
    }
    free(buf1);
    return ret;
}

typedef sword (*OCITypeArrayByName_func_t)(OCIEnv *env, OCIError *err, const OCISvcCtx *svc, ub4 array_len, const oratext *schema_name[], ub4 s_length[], const oratext *type_name[], ub4 t_length[], const oratext *version_name[], ub4 v_length[], OCIDuration pin_duration, OCITypeGetOpt get_option, OCIType **tdo);
static OCITypeArrayByName_func_t OCITypeArrayByName_func;
static int trace_OCITypeArrayByName = 1;

sword OCITypeArrayByName(OCIEnv *env, OCIError *err, const OCISvcCtx *svc, ub4 array_len, const oratext *schema_name[], ub4 s_length[], const oratext *type_name[], ub4 t_length[], const oratext *version_name[], ub4 v_length[], OCIDuration pin_duration, OCITypeGetOpt get_option, OCIType **tdo)
{
    sword ret;
    char *buf1 = NULL;
    char *buf2 = NULL;
    char *buf3 = NULL;
    char *buf4 = NULL;
    char buf5[OCIDUMP_SHORT_BUF_SIZE];
    char buf6[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeArrayByName_func(env, err, svc, array_len, schema_name, s_length, type_name, t_length, version_name, v_length, pin_duration, get_option, tdo);
    if (trace_OCITypeArrayByName) {
        ocidump_log("%0*lX: OCITypeArrayByName(%p, %p, %p, %u, [%s, ...], [%u, ...], [%s, ...], [%u, ...], %s, %s, %u, %d, [%p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     svc,
                     array_len,
                     ocidump_quotestring(&buf1, schema_name[0], s_length[0]),
                     s_length[0],
                     ocidump_quotestring(&buf2, type_name[0], t_length[0]),
                     t_length[0],
                     version_name ? ocidump_asprintf(&buf3, "[%s, ...]", ocidump_quotestring(&buf4, version_name[0], v_length[0])) : "(nil)",
                     v_length ? ocidump_sprintf(buf5, "[%u, ...]", v_length[0]) : "(nil)",
                     pin_duration,
                     get_option,
                     *tdo,
                     ocidump_status2name(ret, buf6));
    }
    free(buf1);
    free(buf2);
    free(buf3);
    free(buf4);
    return ret;
}

typedef sword (*OCITypeArrayByRef_func_t)(OCIEnv *env, OCIError *err, ub4 array_len, const OCIRef **type_ref, OCIDuration pin_duration, OCITypeGetOpt get_option, OCIType **tdo);
static OCITypeArrayByRef_func_t OCITypeArrayByRef_func;
static int trace_OCITypeArrayByRef = 1;

sword OCITypeArrayByRef(OCIEnv *env, OCIError *err, ub4 array_len, const OCIRef **type_ref, OCIDuration pin_duration, OCITypeGetOpt get_option, OCIType **tdo)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeArrayByRef_func(env, err, array_len, type_ref, pin_duration, get_option, tdo);
    if (trace_OCITypeArrayByRef) {
        ocidump_log("%0*lX: OCITypeArrayByRef(%p, %p, %u, [%p, ...], %u, %d, [%p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     array_len,
                     *type_ref,
                     pin_duration,
                     get_option,
                     *tdo,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCITypeAttrByName_func_t)(OCIEnv *env, OCIError *err, const OCIType *tdo, const oratext *name, ub4 n_length, OCITypeElem **elem);
static OCITypeAttrByName_func_t OCITypeAttrByName_func;
static int trace_OCITypeAttrByName = 1;

sword OCITypeAttrByName(OCIEnv *env, OCIError *err, const OCIType *tdo, const oratext *name, ub4 n_length, OCITypeElem **elem)
{
    sword ret;
    char *buf1 = NULL;
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeAttrByName_func(env, err, tdo, name, n_length, elem);
    if (trace_OCITypeAttrByName) {
        ocidump_log("%0*lX: OCITypeAttrByName(%p, %p, %p, %s, %u, [%p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     tdo,
                     ocidump_quotestring(&buf1, name, n_length),
                     n_length,
                     *elem,
                     ocidump_status2name(ret, buf2));
    }
    free(buf1);
    return ret;
}

typedef sword (*OCITypeAttrNext_func_t)(OCIEnv *env, OCIError *err, OCITypeIter *iterator_ort, OCITypeElem **elem);
static OCITypeAttrNext_func_t OCITypeAttrNext_func;
static int trace_OCITypeAttrNext = 1;

sword OCITypeAttrNext(OCIEnv *env, OCIError *err, OCITypeIter *iterator_ort, OCITypeElem **elem)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeAttrNext_func(env, err, iterator_ort, elem);
    if (trace_OCITypeAttrNext) {
        ocidump_log("%0*lX: OCITypeAttrNext(%p, %p, %p, [%p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     iterator_ort,
                     *elem,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef ub4 (*OCITypeAttrs_func_t)(OCIEnv *env, OCIError *err, const OCIType *tdo);
static OCITypeAttrs_func_t OCITypeAttrs_func;
static int trace_OCITypeAttrs = 1;

ub4 OCITypeAttrs(OCIEnv *env, OCIError *err, const OCIType *tdo)
{
    ub4 ret;
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeAttrs_func(env, err, tdo);
    if (trace_OCITypeAttrs) {
        ocidump_log("%0*lX: OCITypeAttrs(%p, %p, %p) => %u\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     tdo,
                     ret);
    }
    return ret;
}

typedef sword (*OCITypeBeginCreate_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCITypeCode tc, OCIDuration dur, OCIType **type);
static OCITypeBeginCreate_func_t OCITypeBeginCreate_func;
static int trace_OCITypeBeginCreate = 1;

sword OCITypeBeginCreate(OCISvcCtx *svchp, OCIError *errhp, OCITypeCode tc, OCIDuration dur, OCIType **type)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeBeginCreate_func(svchp, errhp, tc, dur, type);
    if (trace_OCITypeBeginCreate) {
        ocidump_log("%0*lX: OCITypeBeginCreate(%p, %p, %u, %u, [%p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     tc,
                     dur,
                     *type,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCITypeByName_func_t)(OCIEnv *env, OCIError *err, const OCISvcCtx *svc, const oratext *schema_name, ub4 s_length, const oratext *type_name, ub4 t_length, const oratext *version_name, ub4 v_length, OCIDuration pin_duration, OCITypeGetOpt get_option, OCIType **tdo);
static OCITypeByName_func_t OCITypeByName_func;
static int trace_OCITypeByName = 1;

sword OCITypeByName(OCIEnv *env, OCIError *err, const OCISvcCtx *svc, const oratext *schema_name, ub4 s_length, const oratext *type_name, ub4 t_length, const oratext *version_name, ub4 v_length, OCIDuration pin_duration, OCITypeGetOpt get_option, OCIType **tdo)
{
    sword ret;
    char *buf1 = NULL;
    char *buf2 = NULL;
    char *buf3 = NULL;
    char buf4[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeByName_func(env, err, svc, schema_name, s_length, type_name, t_length, version_name, v_length, pin_duration, get_option, tdo);
    if (trace_OCITypeByName) {
        ocidump_log("%0*lX: OCITypeByName(%p, %p, %p, %s, %u, %s, %u, %s, %u, %u, %d, [%p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     svc,
                     ocidump_quotestring(&buf1, schema_name, s_length),
                     s_length,
                     ocidump_quotestring(&buf2, type_name, t_length),
                     t_length,
                     ocidump_quotestring(&buf3, version_name, v_length),
                     v_length,
                     pin_duration,
                     get_option,
                     *tdo,
                     ocidump_status2name(ret, buf4));
    }
    free(buf1);
    free(buf2);
    free(buf3);
    return ret;
}

typedef sword (*OCITypeByRef_func_t)(OCIEnv *env, OCIError *err, const OCIRef *type_ref, OCIDuration pin_duration, OCITypeGetOpt get_option, OCIType **tdo);
static OCITypeByRef_func_t OCITypeByRef_func;
static int trace_OCITypeByRef = 1;

sword OCITypeByRef(OCIEnv *env, OCIError *err, const OCIRef *type_ref, OCIDuration pin_duration, OCITypeGetOpt get_option, OCIType **tdo)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeByRef_func(env, err, type_ref, pin_duration, get_option, tdo);
    if (trace_OCITypeByRef) {
        ocidump_log("%0*lX: OCITypeByRef(%p, %p, %p, %u, %d, [%p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     type_ref,
                     pin_duration,
                     get_option,
                     *tdo,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCITypeCollElem_func_t)(OCIEnv *env, OCIError *err, const OCIType *tdo, OCITypeElem **element);
static OCITypeCollElem_func_t OCITypeCollElem_func;
static int trace_OCITypeCollElem = 1;

sword OCITypeCollElem(OCIEnv *env, OCIError *err, const OCIType *tdo, OCITypeElem **element)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeCollElem_func(env, err, tdo, element);
    if (trace_OCITypeCollElem) {
        ocidump_log("%0*lX: OCITypeCollElem(%p, %p, %p, [%p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     tdo,
                     *element,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCITypeCollExtTypeCode_func_t)(OCIEnv *env, OCIError *err, const OCIType *tdo, OCITypeCode *sqt_code);
static OCITypeCollExtTypeCode_func_t OCITypeCollExtTypeCode_func;
static int trace_OCITypeCollExtTypeCode = 1;

sword OCITypeCollExtTypeCode(OCIEnv *env, OCIError *err, const OCIType *tdo, OCITypeCode *sqt_code)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeCollExtTypeCode_func(env, err, tdo, sqt_code);
    if (trace_OCITypeCollExtTypeCode) {
        ocidump_log("%0*lX: OCITypeCollExtTypeCode(%p, %p, %p, [%u]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     tdo,
                     *sqt_code,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCITypeCollSize_func_t)(OCIEnv *env, OCIError *err, const OCIType *tdo, ub4 *num_elems);
static OCITypeCollSize_func_t OCITypeCollSize_func;
static int trace_OCITypeCollSize = 1;

sword OCITypeCollSize(OCIEnv *env, OCIError *err, const OCIType *tdo, ub4 *num_elems)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeCollSize_func(env, err, tdo, num_elems);
    if (trace_OCITypeCollSize) {
        ocidump_log("%0*lX: OCITypeCollSize(%p, %p, %p, [%u]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     tdo,
                     *num_elems,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef OCITypeCode (*OCITypeCollTypeCode_func_t)(OCIEnv *env, OCIError *err, const OCIType *tdo);
static OCITypeCollTypeCode_func_t OCITypeCollTypeCode_func;
static int trace_OCITypeCollTypeCode = 1;

OCITypeCode OCITypeCollTypeCode(OCIEnv *env, OCIError *err, const OCIType *tdo)
{
    OCITypeCode ret;
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeCollTypeCode_func(env, err, tdo);
    if (trace_OCITypeCollTypeCode) {
        ocidump_log("%0*lX: OCITypeCollTypeCode(%p, %p, %p) => %u\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     tdo,
                     ret);
    }
    return ret;
}

typedef ub2 (*OCITypeElemCharSetForm_func_t)(OCIEnv *env, OCIError *err, const OCITypeElem *elem);
static OCITypeElemCharSetForm_func_t OCITypeElemCharSetForm_func;
static int trace_OCITypeElemCharSetForm = 1;

ub2 OCITypeElemCharSetForm(OCIEnv *env, OCIError *err, const OCITypeElem *elem)
{
    ub2 ret;
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeElemCharSetForm_func(env, err, elem);
    if (trace_OCITypeElemCharSetForm) {
        ocidump_log("%0*lX: OCITypeElemCharSetForm(%p, %p, %p) => %u\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     elem,
                     ret);
    }
    return ret;
}

typedef ub2 (*OCITypeElemCharSetID_func_t)(OCIEnv *env, OCIError *err, const OCITypeElem *elem);
static OCITypeElemCharSetID_func_t OCITypeElemCharSetID_func;
static int trace_OCITypeElemCharSetID = 1;

ub2 OCITypeElemCharSetID(OCIEnv *env, OCIError *err, const OCITypeElem *elem)
{
    ub2 ret;
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeElemCharSetID_func(env, err, elem);
    if (trace_OCITypeElemCharSetID) {
        ocidump_log("%0*lX: OCITypeElemCharSetID(%p, %p, %p) => %u\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     elem,
                     ret);
    }
    return ret;
}

typedef oratext* (*OCITypeElemDefaultValue_func_t)(OCIEnv *env, OCIError *err, const OCITypeElem *elem, ub4 *d_v_length);
static OCITypeElemDefaultValue_func_t OCITypeElemDefaultValue_func;
static int trace_OCITypeElemDefaultValue = 1;

oratext* OCITypeElemDefaultValue(OCIEnv *env, OCIError *err, const OCITypeElem *elem, ub4 *d_v_length)
{
    oratext* ret;
    char *buf1 = NULL;
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeElemDefaultValue_func(env, err, elem, d_v_length);
    if (trace_OCITypeElemDefaultValue) {
        ocidump_log("%0*lX: OCITypeElemDefaultValue(%p, %p, %p, [%u]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     elem,
                     *d_v_length,
                     ocidump_quotestring(&buf1, ret, *d_v_length));
    }
    free(buf1);
    return ret;
}

typedef OCITypeCode (*OCITypeElemExtTypeCode_func_t)(OCIEnv *env, OCIError *err, const OCITypeElem *elem);
static OCITypeElemExtTypeCode_func_t OCITypeElemExtTypeCode_func;
static int trace_OCITypeElemExtTypeCode = 1;

OCITypeCode OCITypeElemExtTypeCode(OCIEnv *env, OCIError *err, const OCITypeElem *elem)
{
    OCITypeCode ret;
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeElemExtTypeCode_func(env, err, elem);
    if (trace_OCITypeElemExtTypeCode) {
        ocidump_log("%0*lX: OCITypeElemExtTypeCode(%p, %p, %p) => %u\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     elem,
                     ret);
    }
    return ret;
}

typedef ub4 (*OCITypeElemFlags_func_t)(OCIEnv *env, OCIError *err, const OCITypeElem *elem);
static OCITypeElemFlags_func_t OCITypeElemFlags_func;
static int trace_OCITypeElemFlags = 1;

ub4 OCITypeElemFlags(OCIEnv *env, OCIError *err, const OCITypeElem *elem)
{
    ub4 ret;
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeElemFlags_func(env, err, elem);
    if (trace_OCITypeElemFlags) {
        ocidump_log("%0*lX: OCITypeElemFlags(%p, %p, %p) => %u\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     elem,
                     ret);
    }
    return ret;
}

typedef ub4 (*OCITypeElemLength_func_t)(OCIEnv *env, OCIError *err, const OCITypeElem *elem);
static OCITypeElemLength_func_t OCITypeElemLength_func;
static int trace_OCITypeElemLength = 1;

ub4 OCITypeElemLength(OCIEnv *env, OCIError *err, const OCITypeElem *elem)
{
    ub4 ret;
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeElemLength_func(env, err, elem);
    if (trace_OCITypeElemLength) {
        ocidump_log("%0*lX: OCITypeElemLength(%p, %p, %p) => %u\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     elem,
                     ret);
    }
    return ret;
}

typedef oratext* (*OCITypeElemName_func_t)(OCIEnv *env, OCIError *err, const OCITypeElem *elem, ub4 *n_length);
static OCITypeElemName_func_t OCITypeElemName_func;
static int trace_OCITypeElemName = 1;

oratext* OCITypeElemName(OCIEnv *env, OCIError *err, const OCITypeElem *elem, ub4 *n_length)
{
    oratext* ret;
    char *buf1 = NULL;
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeElemName_func(env, err, elem, n_length);
    if (trace_OCITypeElemName) {
        ocidump_log("%0*lX: OCITypeElemName(%p, %p, %p, [%u]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     elem,
                     *n_length,
                     ocidump_quotestring(&buf1, ret, *n_length));
    }
    free(buf1);
    return ret;
}

typedef ub1 (*OCITypeElemNumPrec_func_t)(OCIEnv *env, OCIError *err, const OCITypeElem *elem);
static OCITypeElemNumPrec_func_t OCITypeElemNumPrec_func;
static int trace_OCITypeElemNumPrec = 1;

ub1 OCITypeElemNumPrec(OCIEnv *env, OCIError *err, const OCITypeElem *elem)
{
    ub1 ret;
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeElemNumPrec_func(env, err, elem);
    if (trace_OCITypeElemNumPrec) {
        ocidump_log("%0*lX: OCITypeElemNumPrec(%p, %p, %p) => %u\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     elem,
                     ret);
    }
    return ret;
}

typedef sb1 (*OCITypeElemNumScale_func_t)(OCIEnv *env, OCIError *err, const OCITypeElem *elem);
static OCITypeElemNumScale_func_t OCITypeElemNumScale_func;
static int trace_OCITypeElemNumScale = 1;

sb1 OCITypeElemNumScale(OCIEnv *env, OCIError *err, const OCITypeElem *elem)
{
    sb1 ret;
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeElemNumScale_func(env, err, elem);
    if (trace_OCITypeElemNumScale) {
        ocidump_log("%0*lX: OCITypeElemNumScale(%p, %p, %p) => %u\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     elem,
                     ret);
    }
    return ret;
}

typedef OCITypeParamMode (*OCITypeElemParamMode_func_t)(OCIEnv *env, OCIError *err, const OCITypeElem *elem);
static OCITypeElemParamMode_func_t OCITypeElemParamMode_func;
static int trace_OCITypeElemParamMode = 1;

OCITypeParamMode OCITypeElemParamMode(OCIEnv *env, OCIError *err, const OCITypeElem *elem)
{
    OCITypeParamMode ret;
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeElemParamMode_func(env, err, elem);
    if (trace_OCITypeElemParamMode) {
        ocidump_log("%0*lX: OCITypeElemParamMode(%p, %p, %p) => %d\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     elem,
                     ret);
    }
    return ret;
}

typedef sword (*OCITypeElemParameterizedType_func_t)(OCIEnv *env, OCIError *err, const OCITypeElem *elem, OCIType **type_stored);
static OCITypeElemParameterizedType_func_t OCITypeElemParameterizedType_func;
static int trace_OCITypeElemParameterizedType = 1;

sword OCITypeElemParameterizedType(OCIEnv *env, OCIError *err, const OCITypeElem *elem, OCIType **type_stored)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeElemParameterizedType_func(env, err, elem, type_stored);
    if (trace_OCITypeElemParameterizedType) {
        ocidump_log("%0*lX: OCITypeElemParameterizedType(%p, %p, %p, [%p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     elem,
                     *type_stored,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCITypeElemType_func_t)(OCIEnv *env, OCIError *err, const OCITypeElem *elem, OCIType **elem_tdo);
static OCITypeElemType_func_t OCITypeElemType_func;
static int trace_OCITypeElemType = 1;

sword OCITypeElemType(OCIEnv *env, OCIError *err, const OCITypeElem *elem, OCIType **elem_tdo)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeElemType_func(env, err, elem, elem_tdo);
    if (trace_OCITypeElemType) {
        ocidump_log("%0*lX: OCITypeElemType(%p, %p, %p, [%p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     elem,
                     *elem_tdo,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef OCITypeCode (*OCITypeElemTypeCode_func_t)(OCIEnv *env, OCIError *err, const OCITypeElem *elem);
static OCITypeElemTypeCode_func_t OCITypeElemTypeCode_func;
static int trace_OCITypeElemTypeCode = 1;

OCITypeCode OCITypeElemTypeCode(OCIEnv *env, OCIError *err, const OCITypeElem *elem)
{
    OCITypeCode ret;
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeElemTypeCode_func(env, err, elem);
    if (trace_OCITypeElemTypeCode) {
        ocidump_log("%0*lX: OCITypeElemTypeCode(%p, %p, %p) => %u\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     elem,
                     ret);
    }
    return ret;
}

typedef sword (*OCITypeEndCreate_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCIType *type);
static OCITypeEndCreate_func_t OCITypeEndCreate_func;
static int trace_OCITypeEndCreate = 1;

sword OCITypeEndCreate(OCISvcCtx *svchp, OCIError *errhp, OCIType *type)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeEndCreate_func(svchp, errhp, type);
    if (trace_OCITypeEndCreate) {
        ocidump_log("%0*lX: OCITypeEndCreate(%p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     type,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCITypeIterFree_func_t)(OCIEnv *env, OCIError *err, OCITypeIter *iterator_ort);
static OCITypeIterFree_func_t OCITypeIterFree_func;
static int trace_OCITypeIterFree = 1;

sword OCITypeIterFree(OCIEnv *env, OCIError *err, OCITypeIter *iterator_ort)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeIterFree_func(env, err, iterator_ort);
    if (trace_OCITypeIterFree) {
        ocidump_log("%0*lX: OCITypeIterFree(%p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     iterator_ort,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCITypeIterNew_func_t)(OCIEnv *env, OCIError *err, OCIType *tdo, OCITypeIter **iterator_ort);
static OCITypeIterNew_func_t OCITypeIterNew_func;
static int trace_OCITypeIterNew = 1;

sword OCITypeIterNew(OCIEnv *env, OCIError *err, OCIType *tdo, OCITypeIter **iterator_ort)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeIterNew_func(env, err, tdo, iterator_ort);
    if (trace_OCITypeIterNew) {
        ocidump_log("%0*lX: OCITypeIterNew(%p, %p, %p, [%p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     tdo,
                     *iterator_ort,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCITypeIterSet_func_t)(OCIEnv *env, OCIError *err, OCIType *tdo, OCITypeIter *iterator_ort);
static OCITypeIterSet_func_t OCITypeIterSet_func;
static int trace_OCITypeIterSet = 1;

sword OCITypeIterSet(OCIEnv *env, OCIError *err, OCIType *tdo, OCITypeIter *iterator_ort)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeIterSet_func(env, err, tdo, iterator_ort);
    if (trace_OCITypeIterSet) {
        ocidump_log("%0*lX: OCITypeIterSet(%p, %p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     tdo,
                     iterator_ort,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCITypeMethodByName_func_t)(OCIEnv *env, OCIError *err, const OCIType *tdo, const oratext *method_name, ub4 m_length, OCITypeMethod **mdos);
static OCITypeMethodByName_func_t OCITypeMethodByName_func;
static int trace_OCITypeMethodByName = 1;

sword OCITypeMethodByName(OCIEnv *env, OCIError *err, const OCIType *tdo, const oratext *method_name, ub4 m_length, OCITypeMethod **mdos)
{
    sword ret;
    char *buf1 = NULL;
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeMethodByName_func(env, err, tdo, method_name, m_length, mdos);
    if (trace_OCITypeMethodByName) {
        ocidump_log("%0*lX: OCITypeMethodByName(%p, %p, %p, %s, %u, [%p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     tdo,
                     ocidump_quotestring(&buf1, method_name, m_length),
                     m_length,
                     *mdos,
                     ocidump_status2name(ret, buf2));
    }
    free(buf1);
    return ret;
}

typedef OCITypeEncap (*OCITypeMethodEncap_func_t)(OCIEnv *env, OCIError *err, const OCITypeMethod *mdo);
static OCITypeMethodEncap_func_t OCITypeMethodEncap_func;
static int trace_OCITypeMethodEncap = 1;

OCITypeEncap OCITypeMethodEncap(OCIEnv *env, OCIError *err, const OCITypeMethod *mdo)
{
    OCITypeEncap ret;
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeMethodEncap_func(env, err, mdo);
    if (trace_OCITypeMethodEncap) {
        ocidump_log("%0*lX: OCITypeMethodEncap(%p, %p, %p) => %d\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     mdo,
                     ret);
    }
    return ret;
}

typedef OCITypeMethodFlag (*OCITypeMethodFlags_func_t)(OCIEnv *env, OCIError *err, const OCITypeMethod *mdo);
static OCITypeMethodFlags_func_t OCITypeMethodFlags_func;
static int trace_OCITypeMethodFlags = 1;

OCITypeMethodFlag OCITypeMethodFlags(OCIEnv *env, OCIError *err, const OCITypeMethod *mdo)
{
    OCITypeMethodFlag ret;
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeMethodFlags_func(env, err, mdo);
    if (trace_OCITypeMethodFlags) {
        ocidump_log("%0*lX: OCITypeMethodFlags(%p, %p, %p) => 0x%x\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     mdo,
                     ret);
    }
    return ret;
}

typedef sword (*OCITypeMethodMap_func_t)(OCIEnv *env, OCIError *err, const OCIType *tdo, OCITypeMethod **mdo);
static OCITypeMethodMap_func_t OCITypeMethodMap_func;
static int trace_OCITypeMethodMap = 1;

sword OCITypeMethodMap(OCIEnv *env, OCIError *err, const OCIType *tdo, OCITypeMethod **mdo)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeMethodMap_func(env, err, tdo, mdo);
    if (trace_OCITypeMethodMap) {
        ocidump_log("%0*lX: OCITypeMethodMap(%p, %p, %p, [%p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     tdo,
                     *mdo,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef oratext * (*OCITypeMethodName_func_t)(OCIEnv *env, OCIError *err, const OCITypeMethod *mdo, ub4 *n_length);
static OCITypeMethodName_func_t OCITypeMethodName_func;
static int trace_OCITypeMethodName = 1;

oratext * OCITypeMethodName(OCIEnv *env, OCIError *err, const OCITypeMethod *mdo, ub4 *n_length)
{
    oratext * ret;
    char *buf1 = NULL;
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeMethodName_func(env, err, mdo, n_length);
    if (trace_OCITypeMethodName) {
        ocidump_log("%0*lX: OCITypeMethodName(%p, %p, %p, [%u]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     mdo,
                     *n_length,
                     ocidump_quotestring(&buf1, ret, *n_length));
    }
    free(buf1);
    return ret;
}

typedef sword (*OCITypeMethodNext_func_t)(OCIEnv *env, OCIError *err, OCITypeIter *iterator_ort, OCITypeMethod **mdo);
static OCITypeMethodNext_func_t OCITypeMethodNext_func;
static int trace_OCITypeMethodNext = 1;

sword OCITypeMethodNext(OCIEnv *env, OCIError *err, OCITypeIter *iterator_ort, OCITypeMethod **mdo)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeMethodNext_func(env, err, iterator_ort, mdo);
    if (trace_OCITypeMethodNext) {
        ocidump_log("%0*lX: OCITypeMethodNext(%p, %p, %p, [%p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     iterator_ort,
                     *mdo,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCITypeMethodOrder_func_t)(OCIEnv *env, OCIError *err, const OCIType *tdo, OCITypeMethod **mdo);
static OCITypeMethodOrder_func_t OCITypeMethodOrder_func;
static int trace_OCITypeMethodOrder = 1;

sword OCITypeMethodOrder(OCIEnv *env, OCIError *err, const OCIType *tdo, OCITypeMethod **mdo)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeMethodOrder_func(env, err, tdo, mdo);
    if (trace_OCITypeMethodOrder) {
        ocidump_log("%0*lX: OCITypeMethodOrder(%p, %p, %p, [%p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     tdo,
                     *mdo,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef ub4 (*OCITypeMethodOverload_func_t)(OCIEnv *env, OCIError *err, const OCIType *tdo, const oratext *method_name, ub4 m_length);
static OCITypeMethodOverload_func_t OCITypeMethodOverload_func;
static int trace_OCITypeMethodOverload = 1;

ub4 OCITypeMethodOverload(OCIEnv *env, OCIError *err, const OCIType *tdo, const oratext *method_name, ub4 m_length)
{
    ub4 ret;
    char *buf1 = NULL;
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeMethodOverload_func(env, err, tdo, method_name, m_length);
    if (trace_OCITypeMethodOverload) {
        ocidump_log("%0*lX: OCITypeMethodOverload(%p, %p, %p, %s, %u) => %u\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     tdo,
                     ocidump_quotestring(&buf1, method_name, m_length),
                     m_length,
                     ret);
    }
    free(buf1);
    return ret;
}

typedef ub4 (*OCITypeMethodParams_func_t)(OCIEnv *env, OCIError *err, const OCITypeMethod *mdo);
static OCITypeMethodParams_func_t OCITypeMethodParams_func;
static int trace_OCITypeMethodParams = 1;

ub4 OCITypeMethodParams(OCIEnv *env, OCIError *err, const OCITypeMethod *mdo)
{
    ub4 ret;
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeMethodParams_func(env, err, mdo);
    if (trace_OCITypeMethodParams) {
        ocidump_log("%0*lX: OCITypeMethodParams(%p, %p, %p) => %u\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     mdo,
                     ret);
    }
    return ret;
}

typedef ub4 (*OCITypeMethods_func_t)(OCIEnv *env, OCIError *err, const OCIType *tdo);
static OCITypeMethods_func_t OCITypeMethods_func;
static int trace_OCITypeMethods = 1;

ub4 OCITypeMethods(OCIEnv *env, OCIError *err, const OCIType *tdo)
{
    ub4 ret;
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeMethods_func(env, err, tdo);
    if (trace_OCITypeMethods) {
        ocidump_log("%0*lX: OCITypeMethods(%p, %p, %p) => %u\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     tdo,
                     ret);
    }
    return ret;
}

typedef oratext * (*OCITypeName_func_t)(OCIEnv *env, OCIError *err, const OCIType *tdo, ub4 *n_length);
static OCITypeName_func_t OCITypeName_func;
static int trace_OCITypeName = 1;

oratext * OCITypeName(OCIEnv *env, OCIError *err, const OCIType *tdo, ub4 *n_length)
{
    oratext * ret;
    char *buf1 = NULL;
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeName_func(env, err, tdo, n_length);
    if (trace_OCITypeName) {
        ocidump_log("%0*lX: OCITypeName(%p, %p, %p, [%u]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     tdo,
                     *n_length,
                     ret ? ocidump_asprintf(&buf1, "\"%.*s\"", *n_length, ret) : "(nil)");
    }
    free(buf1);
    return ret;
}

typedef sword (*OCITypeParamByName_func_t)(OCIEnv *env, OCIError *err, const OCITypeMethod *mdo, const oratext *name, ub4 n_length, OCITypeElem **elem);
static OCITypeParamByName_func_t OCITypeParamByName_func;
static int trace_OCITypeParamByName = 1;

sword OCITypeParamByName(OCIEnv *env, OCIError *err, const OCITypeMethod *mdo, const oratext *name, ub4 n_length, OCITypeElem **elem)
{
    sword ret;
    char *buf1 = NULL;
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeParamByName_func(env, err, mdo, name, n_length, elem);
    if (trace_OCITypeParamByName) {
        ocidump_log("%0*lX: OCITypeParamByName(%p, %p, %p, %s, %u, [%p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     mdo,
                     ocidump_quotestring(&buf1, name, n_length),
                     n_length,
                     *elem,
                     ocidump_status2name(ret, buf2));
    }
    free(buf1);
    return ret;
}

typedef sword (*OCITypeParamByPos_func_t)(OCIEnv *env, OCIError *err, const OCITypeMethod *mdo, ub4 position, OCITypeElem **elem);
static OCITypeParamByPos_func_t OCITypeParamByPos_func;
static int trace_OCITypeParamByPos = 1;

sword OCITypeParamByPos(OCIEnv *env, OCIError *err, const OCITypeMethod *mdo, ub4 position, OCITypeElem **elem)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeParamByPos_func(env, err, mdo, position, elem);
    if (trace_OCITypeParamByPos) {
        ocidump_log("%0*lX: OCITypeParamByPos(%p, %p, %p, %u, [%p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     mdo,
                     position,
                     *elem,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCITypeParamPos_func_t)(OCIEnv *env, OCIError *err, const OCITypeMethod *mdo, const oratext *name, ub4 n_length, ub4 *position, OCITypeElem **elem);
static OCITypeParamPos_func_t OCITypeParamPos_func;
static int trace_OCITypeParamPos = 1;

sword OCITypeParamPos(OCIEnv *env, OCIError *err, const OCITypeMethod *mdo, const oratext *name, ub4 n_length, ub4 *position, OCITypeElem **elem)
{
    sword ret;
    char *buf1 = NULL;
    char buf2[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeParamPos_func(env, err, mdo, name, n_length, position, elem);
    if (trace_OCITypeParamPos) {
        ocidump_log("%0*lX: OCITypeParamPos(%p, %p, %p, %s, %u, [%u], [%p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     mdo,
                     ocidump_quotestring(&buf1, name, n_length),
                     n_length,
                     *position,
                     *elem,
                     ocidump_status2name(ret, buf2));
    }
    free(buf1);
    return ret;
}

typedef sword (*OCITypeResult_func_t)(OCIEnv *env, OCIError *err, const OCITypeMethod *mdo, OCITypeElem **elem);
static OCITypeResult_func_t OCITypeResult_func;
static int trace_OCITypeResult = 1;

sword OCITypeResult(OCIEnv *env, OCIError *err, const OCITypeMethod *mdo, OCITypeElem **elem)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeResult_func(env, err, mdo, elem);
    if (trace_OCITypeResult) {
        ocidump_log("%0*lX: OCITypeResult(%p, %p, %p, [%p]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     mdo,
                     *elem,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef oratext* (*OCITypeSchema_func_t)(OCIEnv *env, OCIError *err, const OCIType *tdo, ub4 *n_length);
static OCITypeSchema_func_t OCITypeSchema_func;
static int trace_OCITypeSchema = 1;

oratext* OCITypeSchema(OCIEnv *env, OCIError *err, const OCIType *tdo, ub4 *n_length)
{
    oratext* ret;
    char *buf1 = NULL;
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeSchema_func(env, err, tdo, n_length);
    if (trace_OCITypeSchema) {
        ocidump_log("%0*lX: OCITypeSchema(%p, %p, %p, [%u]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     tdo,
                     *n_length,
                     ocidump_quotestring(&buf1, ret, *n_length));
    }
    free(buf1);
    return ret;
}

typedef sword (*OCITypeSetBuiltin_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCIType *type, OCIParam *builtin_info);
static OCITypeSetBuiltin_func_t OCITypeSetBuiltin_func;
static int trace_OCITypeSetBuiltin = 1;

sword OCITypeSetBuiltin(OCISvcCtx *svchp, OCIError *errhp, OCIType *type, OCIParam *builtin_info)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeSetBuiltin_func(svchp, errhp, type, builtin_info);
    if (trace_OCITypeSetBuiltin) {
        ocidump_log("%0*lX: OCITypeSetBuiltin(%p, %p, %p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     type,
                     builtin_info,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCITypeSetCollection_func_t)(OCISvcCtx *svchp, OCIError *errhp, OCIType *type, OCIParam *collelem_info, ub4 coll_count);
static OCITypeSetCollection_func_t OCITypeSetCollection_func;
static int trace_OCITypeSetCollection = 1;

sword OCITypeSetCollection(OCISvcCtx *svchp, OCIError *errhp, OCIType *type, OCIParam *collelem_info, ub4 coll_count)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeSetCollection_func(svchp, errhp, type, collelem_info, coll_count);
    if (trace_OCITypeSetCollection) {
        ocidump_log("%0*lX: OCITypeSetCollection(%p, %p, %p, %p, %u) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     errhp,
                     type,
                     collelem_info,
                     coll_count,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef OCITypeCode (*OCITypeTypeCode_func_t)(OCIEnv *env, OCIError *err, const OCIType *tdo);
static OCITypeTypeCode_func_t OCITypeTypeCode_func;
static int trace_OCITypeTypeCode = 1;

OCITypeCode OCITypeTypeCode(OCIEnv *env, OCIError *err, const OCIType *tdo)
{
    OCITypeCode ret;
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeTypeCode_func(env, err, tdo);
    if (trace_OCITypeTypeCode) {
        ocidump_log("%0*lX: OCITypeTypeCode(%p, %p, %p) => %u\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     tdo,
                     ret);
    }
    return ret;
}

typedef sword (*OCITypeVTInit_func_t)(OCIEnv *env, OCIError *err);
static OCITypeVTInit_func_t OCITypeVTInit_func;
static int trace_OCITypeVTInit = 1;

sword OCITypeVTInit(OCIEnv *env, OCIError *err)
{
    sword ret;
    char buf1[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeVTInit_func(env, err);
    if (trace_OCITypeVTInit) {
        ocidump_log("%0*lX: OCITypeVTInit(%p, %p) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCITypeVTInsert_func_t)(OCIEnv *env, OCIError *err, const oratext *schema_name, ub4 s_n_length, const oratext *type_name, ub4 t_n_length, const oratext *user_version, ub4 u_v_length);
static OCITypeVTInsert_func_t OCITypeVTInsert_func;
static int trace_OCITypeVTInsert = 1;

sword OCITypeVTInsert(OCIEnv *env, OCIError *err, const oratext *schema_name, ub4 s_n_length, const oratext *type_name, ub4 t_n_length, const oratext *user_version, ub4 u_v_length)
{
    sword ret;
    char *buf1 = NULL;
    char *buf2 = NULL;
    char *buf3 = NULL;
    char buf4[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeVTInsert_func(env, err, schema_name, s_n_length, type_name, t_n_length, user_version, u_v_length);
    if (trace_OCITypeVTInsert) {
        ocidump_log("%0*lX: OCITypeVTInsert(%p, %p, %s, %u, %s, %u, %s, %u) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     ocidump_quotestring(&buf1, schema_name, s_n_length),
                     s_n_length,
                     ocidump_quotestring(&buf2, type_name, t_n_length),
                     t_n_length,
                     ocidump_quotestring(&buf3, user_version, u_v_length),
                     u_v_length,
                     ocidump_status2name(ret, buf4));
    }
    free(buf1);
    free(buf2);
    free(buf3);
    return ret;
}

typedef sword (*OCITypeVTSelect_func_t)(OCIEnv *env, OCIError *err, const oratext *schema_name, ub4 s_n_length, const oratext *type_name, ub4 t_n_length, oratext **user_version, ub4 *u_v_length, ub2 *version);
static OCITypeVTSelect_func_t OCITypeVTSelect_func;
static int trace_OCITypeVTSelect = 1;

sword OCITypeVTSelect(OCIEnv *env, OCIError *err, const oratext *schema_name, ub4 s_n_length, const oratext *type_name, ub4 t_n_length, oratext **user_version, ub4 *u_v_length, ub2 *version)
{
    sword ret;
    char *buf1 = NULL;
    char *buf2 = NULL;
    char *buf3 = NULL;
    char buf4[OCIDUMP_SHORT_BUF_SIZE];
    char buf5[OCIDUMP_SHORT_BUF_SIZE];
    char buf6[OCIDUMP_SHORT_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeVTSelect_func(env, err, schema_name, s_n_length, type_name, t_n_length, user_version, u_v_length, version);
    if (trace_OCITypeVTSelect) {
        ocidump_log("%0*lX: OCITypeVTSelect(%p, %p, %s, %u, %s, %u, %s, %s, %s) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     ocidump_quotestring(&buf1, schema_name, s_n_length),
                     s_n_length,
                     ocidump_quotestring(&buf2, type_name, t_n_length),
                     t_n_length,
                     ocidump_quotestring2(&buf3, user_version, u_v_length),
                     u_v_length ? ocidump_sprintf(buf4, "[%u]", *u_v_length) : "(nil)",
                     version ? ocidump_sprintf(buf5, "[%u]", *version) : "(nil)",
                     ocidump_status2name(ret, buf6));
    }
    free(buf1);
    free(buf2);
    free(buf3);
    return ret;
}

typedef oratext* (*OCITypeVersion_func_t)(OCIEnv *env, OCIError *err, const OCIType *tdo, ub4 *v_length);
static OCITypeVersion_func_t OCITypeVersion_func;
static int trace_OCITypeVersion = 1;

oratext* OCITypeVersion(OCIEnv *env, OCIError *err, const OCIType *tdo, ub4 *v_length)
{
    oratext* ret;
    char *buf1 = NULL;
    if (!is_initialized) {
        initialize();
    }
    ret = OCITypeVersion_func(env, err, tdo, v_length);
    if (trace_OCITypeVersion) {
        ocidump_log("%0*lX: OCITypeVersion(%p, %p, %p, [%u]) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     env,
                     err,
                     tdo,
                     *v_length,
                     ocidump_quotestring(&buf1, ret, *v_length));
    }
    free(buf1);
    return ret;
}

ocidump_target_t ocidump_targets[] = {
    {"OCIAnyDataAccess", &trace_OCIAnyDataAccess},
    {"OCIAnyDataAttrGet", &trace_OCIAnyDataAttrGet},
    {"OCIAnyDataAttrSet", &trace_OCIAnyDataAttrSet},
    {"OCIAnyDataBeginCreate", &trace_OCIAnyDataBeginCreate},
    {"OCIAnyDataCollAddElem", &trace_OCIAnyDataCollAddElem},
    {"OCIAnyDataCollGetElem", &trace_OCIAnyDataCollGetElem},
    {"OCIAnyDataConvert", &trace_OCIAnyDataConvert},
    {"OCIAnyDataDestroy", &trace_OCIAnyDataDestroy},
    {"OCIAnyDataEndCreate", &trace_OCIAnyDataEndCreate},
    {"OCIAnyDataGetCurrAttrNum", &trace_OCIAnyDataGetCurrAttrNum},
    {"OCIAnyDataGetType", &trace_OCIAnyDataGetType},
    {"OCIAnyDataIsNull", &trace_OCIAnyDataIsNull},
    {"OCIAnyDataSetAddInstance", &trace_OCIAnyDataSetAddInstance},
    {"OCIAnyDataSetBeginCreate", &trace_OCIAnyDataSetBeginCreate},
    {"OCIAnyDataSetDestroy", &trace_OCIAnyDataSetDestroy},
    {"OCIAnyDataSetEndCreate", &trace_OCIAnyDataSetEndCreate},
    {"OCIAnyDataSetGetCount", &trace_OCIAnyDataSetGetCount},
    {"OCIAnyDataSetGetInstance", &trace_OCIAnyDataSetGetInstance},
    {"OCIAnyDataSetGetType", &trace_OCIAnyDataSetGetType},
    {"OCIAppCtxClearAll", &trace_OCIAppCtxClearAll},
    {"OCIAppCtxSet", &trace_OCIAppCtxSet},
    {"OCIArrayDescriptorAlloc", &trace_OCIArrayDescriptorAlloc},
    {"OCIArrayDescriptorFree", &trace_OCIArrayDescriptorFree},
    {"OCIAttrGet", &trace_OCIAttrGet},
    {"OCIAttrSet", &trace_OCIAttrSet},
    {"OCIBindArrayOfStruct", &trace_OCIBindArrayOfStruct},
    {"OCIBindByName", &trace_OCIBindByName},
    {"OCIBindByPos", &trace_OCIBindByPos},
    {"OCIBindDynamic", &trace_OCIBindDynamic},
    {"OCIBindObject", &trace_OCIBindObject},
    {"OCIBreak", &trace_OCIBreak},
    {"OCICacheFlush", &trace_OCICacheFlush},
    {"OCICacheFlushRefresh", &trace_OCICacheFlushRefresh},
    {"OCICacheFree", &trace_OCICacheFree},
    {"OCICacheGetObjects", &trace_OCICacheGetObjects},
    {"OCICacheRefresh", &trace_OCICacheRefresh},
    {"OCICacheRegister", &trace_OCICacheRegister},
    {"OCICacheUnmark", &trace_OCICacheUnmark},
    {"OCICacheUnpin", &trace_OCICacheUnpin},
    {"OCICharSetConversionIsReplacementUsed", &trace_OCICharSetConversionIsReplacementUsed},
    {"OCIClientVersion", &trace_OCIClientVersion},
    {"OCICollAppend", &trace_OCICollAppend},
    {"OCICollAssign", &trace_OCICollAssign},
    {"OCICollAssignElem", &trace_OCICollAssignElem},
    {"OCICollGetElem", &trace_OCICollGetElem},
    {"OCICollGetElemArray", &trace_OCICollGetElemArray},
    {"OCICollIsLocator", &trace_OCICollIsLocator},
    {"OCICollMax", &trace_OCICollMax},
    {"OCICollSize", &trace_OCICollSize},
    {"OCICollTrim", &trace_OCICollTrim},
    {"OCIConnectionPoolCreate", &trace_OCIConnectionPoolCreate},
    {"OCIConnectionPoolDestroy", &trace_OCIConnectionPoolDestroy},
    {"OCIDBShutdown", &trace_OCIDBShutdown},
    {"OCIDBStartup", &trace_OCIDBStartup},
    {"OCIDateAddDays", &trace_OCIDateAddDays},
    {"OCIDateAddMonths", &trace_OCIDateAddMonths},
    {"OCIDateAssign", &trace_OCIDateAssign},
    {"OCIDateCheck", &trace_OCIDateCheck},
    {"OCIDateCompare", &trace_OCIDateCompare},
    {"OCIDateDaysBetween", &trace_OCIDateDaysBetween},
    {"OCIDateFromText", &trace_OCIDateFromText},
    {"OCIDateLastDay", &trace_OCIDateLastDay},
    {"OCIDateNextDay", &trace_OCIDateNextDay},
    {"OCIDateSysDate", &trace_OCIDateSysDate},
    {"OCIDateTimeAssign", &trace_OCIDateTimeAssign},
    {"OCIDateTimeCheck", &trace_OCIDateTimeCheck},
    {"OCIDateTimeCompare", &trace_OCIDateTimeCompare},
    {"OCIDateTimeConstruct", &trace_OCIDateTimeConstruct},
    {"OCIDateTimeConvert", &trace_OCIDateTimeConvert},
    {"OCIDateTimeFromArray", &trace_OCIDateTimeFromArray},
    {"OCIDateTimeFromText", &trace_OCIDateTimeFromText},
    {"OCIDateTimeGetDate", &trace_OCIDateTimeGetDate},
    {"OCIDateTimeGetTime", &trace_OCIDateTimeGetTime},
    {"OCIDateTimeGetTimeZoneName", &trace_OCIDateTimeGetTimeZoneName},
    {"OCIDateTimeGetTimeZoneOffset", &trace_OCIDateTimeGetTimeZoneOffset},
    {"OCIDateTimeIntervalAdd", &trace_OCIDateTimeIntervalAdd},
    {"OCIDateTimeIntervalSub", &trace_OCIDateTimeIntervalSub},
    {"OCIDateTimeSubtract", &trace_OCIDateTimeSubtract},
    {"OCIDateTimeSysTimeStamp", &trace_OCIDateTimeSysTimeStamp},
    {"OCIDateTimeToArray", &trace_OCIDateTimeToArray},
    {"OCIDateTimeToText", &trace_OCIDateTimeToText},
    {"OCIDateToText", &trace_OCIDateToText},
    {"OCIDateZoneToZone", &trace_OCIDateZoneToZone},
    {"OCIDefineArrayOfStruct", &trace_OCIDefineArrayOfStruct},
    {"OCIDefineByPos", &trace_OCIDefineByPos},
    {"OCIDefineDynamic", &trace_OCIDefineDynamic},
    {"OCIDefineObject", &trace_OCIDefineObject},
    {"OCIDescribeAny", &trace_OCIDescribeAny},
    {"OCIDescriptorAlloc", &trace_OCIDescriptorAlloc},
    {"OCIDescriptorFree", &trace_OCIDescriptorFree},
    {"OCIDurationBegin", &trace_OCIDurationBegin},
    {"OCIDurationEnd", &trace_OCIDurationEnd},
    {"OCIDurationGetParent", &trace_OCIDurationGetParent},
    {"OCIEnvCreate", &trace_OCIEnvCreate},
    {"OCIEnvInit", &trace_OCIEnvInit},
    {"OCIEnvNlsCreate", &trace_OCIEnvNlsCreate},
    {"OCIErrorGet", &trace_OCIErrorGet},
    {"OCIFEnvCreate", &trace_OCIFEnvCreate},
    {"OCIHandleAlloc", &trace_OCIHandleAlloc},
    {"OCIHandleFree", &trace_OCIHandleFree},
    {"OCIInitialize", &trace_OCIInitialize},
    {"OCIIntervalAdd", &trace_OCIIntervalAdd},
    {"OCIIntervalAssign", &trace_OCIIntervalAssign},
    {"OCIIntervalCheck", &trace_OCIIntervalCheck},
    {"OCIIntervalCompare", &trace_OCIIntervalCompare},
    {"OCIIntervalDivide", &trace_OCIIntervalDivide},
    {"OCIIntervalFromNumber", &trace_OCIIntervalFromNumber},
    {"OCIIntervalFromTZ", &trace_OCIIntervalFromTZ},
    {"OCIIntervalFromText", &trace_OCIIntervalFromText},
    {"OCIIntervalGetDaySecond", &trace_OCIIntervalGetDaySecond},
    {"OCIIntervalGetYearMonth", &trace_OCIIntervalGetYearMonth},
    {"OCIIntervalMultiply", &trace_OCIIntervalMultiply},
    {"OCIIntervalSetDaySecond", &trace_OCIIntervalSetDaySecond},
    {"OCIIntervalSetYearMonth", &trace_OCIIntervalSetYearMonth},
    {"OCIIntervalSubtract", &trace_OCIIntervalSubtract},
    {"OCIIntervalToNumber", &trace_OCIIntervalToNumber},
    {"OCIIntervalToText", &trace_OCIIntervalToText},
    {"OCIIterCreate", &trace_OCIIterCreate},
    {"OCIIterDelete", &trace_OCIIterDelete},
    {"OCIIterGetCurrent", &trace_OCIIterGetCurrent},
    {"OCIIterInit", &trace_OCIIterInit},
    {"OCIIterNext", &trace_OCIIterNext},
    {"OCIIterPrev", &trace_OCIIterPrev},
    {"OCILobAppend", &trace_OCILobAppend},
    {"OCILobArrayRead", &trace_OCILobArrayRead},
    {"OCILobArrayWrite", &trace_OCILobArrayWrite},
    {"OCILobAssign", &trace_OCILobAssign},
    {"OCILobCharSetForm", &trace_OCILobCharSetForm},
    {"OCILobCharSetId", &trace_OCILobCharSetId},
    {"OCILobClose", &trace_OCILobClose},
    {"OCILobCopy", &trace_OCILobCopy},
    {"OCILobCopy2", &trace_OCILobCopy2},
    {"OCILobCreateTemporary", &trace_OCILobCreateTemporary},
    {"OCILobDisableBuffering", &trace_OCILobDisableBuffering},
    {"OCILobEnableBuffering", &trace_OCILobEnableBuffering},
    {"OCILobErase", &trace_OCILobErase},
    {"OCILobErase2", &trace_OCILobErase2},
    {"OCILobFileClose", &trace_OCILobFileClose},
    {"OCILobFileCloseAll", &trace_OCILobFileCloseAll},
    {"OCILobFileExists", &trace_OCILobFileExists},
    {"OCILobFileGetName", &trace_OCILobFileGetName},
    {"OCILobFileIsOpen", &trace_OCILobFileIsOpen},
    {"OCILobFileOpen", &trace_OCILobFileOpen},
    {"OCILobFileSetName", &trace_OCILobFileSetName},
    {"OCILobFlushBuffer", &trace_OCILobFlushBuffer},
    {"OCILobFreeTemporary", &trace_OCILobFreeTemporary},
    {"OCILobGetChunkSize", &trace_OCILobGetChunkSize},
    {"OCILobGetContentType", &trace_OCILobGetContentType},
    {"OCILobGetDeduplicateRegions", &trace_OCILobGetDeduplicateRegions},
    {"OCILobGetLength", &trace_OCILobGetLength},
    {"OCILobGetLength2", &trace_OCILobGetLength2},
    {"OCILobGetOptions", &trace_OCILobGetOptions},
    {"OCILobGetStorageLimit", &trace_OCILobGetStorageLimit},
    {"OCILobIsEqual", &trace_OCILobIsEqual},
    {"OCILobIsOpen", &trace_OCILobIsOpen},
    {"OCILobIsTemporary", &trace_OCILobIsTemporary},
    {"OCILobLoadFromFile", &trace_OCILobLoadFromFile},
    {"OCILobLoadFromFile2", &trace_OCILobLoadFromFile2},
    {"OCILobLocatorAssign", &trace_OCILobLocatorAssign},
    {"OCILobLocatorIsInit", &trace_OCILobLocatorIsInit},
    {"OCILobOpen", &trace_OCILobOpen},
    {"OCILobRead", &trace_OCILobRead},
    {"OCILobRead2", &trace_OCILobRead2},
    {"OCILobSetContentType", &trace_OCILobSetContentType},
    {"OCILobSetOptions", &trace_OCILobSetOptions},
    {"OCILobTrim", &trace_OCILobTrim},
    {"OCILobTrim2", &trace_OCILobTrim2},
    {"OCILobWrite", &trace_OCILobWrite},
    {"OCILobWrite2", &trace_OCILobWrite2},
    {"OCILobWriteAppend", &trace_OCILobWriteAppend},
    {"OCILobWriteAppend2", &trace_OCILobWriteAppend2},
    {"OCILogoff", &trace_OCILogoff},
    {"OCILogon", &trace_OCILogon},
    {"OCILogon2", &trace_OCILogon2},
    {"OCIMessageClose", &trace_OCIMessageClose},
    {"OCIMessageGet", &trace_OCIMessageGet},
    {"OCIMessageOpen", &trace_OCIMessageOpen},
    {"OCINlsCharSetIdToName", &trace_OCINlsCharSetIdToName},
    {"OCINlsCharSetNameToId", &trace_OCINlsCharSetNameToId},
    {"OCINumberAbs", &trace_OCINumberAbs},
    {"OCINumberAdd", &trace_OCINumberAdd},
    {"OCINumberArcCos", &trace_OCINumberArcCos},
    {"OCINumberArcSin", &trace_OCINumberArcSin},
    {"OCINumberArcTan", &trace_OCINumberArcTan},
    {"OCINumberArcTan2", &trace_OCINumberArcTan2},
    {"OCINumberAssign", &trace_OCINumberAssign},
    {"OCINumberCeil", &trace_OCINumberCeil},
    {"OCINumberCmp", &trace_OCINumberCmp},
    {"OCINumberCos", &trace_OCINumberCos},
    {"OCINumberDec", &trace_OCINumberDec},
    {"OCINumberDiv", &trace_OCINumberDiv},
    {"OCINumberExp", &trace_OCINumberExp},
    {"OCINumberFloor", &trace_OCINumberFloor},
    {"OCINumberFromInt", &trace_OCINumberFromInt},
    {"OCINumberFromReal", &trace_OCINumberFromReal},
    {"OCINumberFromText", &trace_OCINumberFromText},
    {"OCINumberHypCos", &trace_OCINumberHypCos},
    {"OCINumberHypSin", &trace_OCINumberHypSin},
    {"OCINumberHypTan", &trace_OCINumberHypTan},
    {"OCINumberInc", &trace_OCINumberInc},
    {"OCINumberIntPower", &trace_OCINumberIntPower},
    {"OCINumberIsInt", &trace_OCINumberIsInt},
    {"OCINumberIsZero", &trace_OCINumberIsZero},
    {"OCINumberLn", &trace_OCINumberLn},
    {"OCINumberLog", &trace_OCINumberLog},
    {"OCINumberMod", &trace_OCINumberMod},
    {"OCINumberMul", &trace_OCINumberMul},
    {"OCINumberNeg", &trace_OCINumberNeg},
    {"OCINumberPower", &trace_OCINumberPower},
    {"OCINumberPrec", &trace_OCINumberPrec},
    {"OCINumberRound", &trace_OCINumberRound},
    {"OCINumberSetPi", &trace_OCINumberSetPi},
    {"OCINumberSetZero", &trace_OCINumberSetZero},
    {"OCINumberShift", &trace_OCINumberShift},
    {"OCINumberSign", &trace_OCINumberSign},
    {"OCINumberSin", &trace_OCINumberSin},
    {"OCINumberSqrt", &trace_OCINumberSqrt},
    {"OCINumberSub", &trace_OCINumberSub},
    {"OCINumberTan", &trace_OCINumberTan},
    {"OCINumberToInt", &trace_OCINumberToInt},
    {"OCINumberToReal", &trace_OCINumberToReal},
    {"OCINumberToRealArray", &trace_OCINumberToRealArray},
    {"OCINumberToText", &trace_OCINumberToText},
    {"OCINumberTrunc", &trace_OCINumberTrunc},
    {"OCIObjectAlwaysLatest", &trace_OCIObjectAlwaysLatest},
    {"OCIObjectArrayPin", &trace_OCIObjectArrayPin},
    {"OCIObjectCopy", &trace_OCIObjectCopy},
    {"OCIObjectExists", &trace_OCIObjectExists},
    {"OCIObjectFlush", &trace_OCIObjectFlush},
    {"OCIObjectFlushRefresh", &trace_OCIObjectFlushRefresh},
    {"OCIObjectFree", &trace_OCIObjectFree},
    {"OCIObjectGetAttr", &trace_OCIObjectGetAttr},
    {"OCIObjectGetInd", &trace_OCIObjectGetInd},
    {"OCIObjectGetNewOID", &trace_OCIObjectGetNewOID},
    {"OCIObjectGetObjectRef", &trace_OCIObjectGetObjectRef},
    {"OCIObjectGetPrimaryKeyTypeRef", &trace_OCIObjectGetPrimaryKeyTypeRef},
    {"OCIObjectGetProperty", &trace_OCIObjectGetProperty},
    {"OCIObjectGetTypeRef", &trace_OCIObjectGetTypeRef},
    {"OCIObjectIsDirtied", &trace_OCIObjectIsDirtied},
    {"OCIObjectIsDirty", &trace_OCIObjectIsDirty},
    {"OCIObjectIsLoaded", &trace_OCIObjectIsLoaded},
    {"OCIObjectIsLocked", &trace_OCIObjectIsLocked},
    {"OCIObjectLock", &trace_OCIObjectLock},
    {"OCIObjectLockNoWait", &trace_OCIObjectLockNoWait},
    {"OCIObjectMakeObjectRef", &trace_OCIObjectMakeObjectRef},
    {"OCIObjectMarkDelete", &trace_OCIObjectMarkDelete},
    {"OCIObjectMarkDeleteByRef", &trace_OCIObjectMarkDeleteByRef},
    {"OCIObjectMarkUpdate", &trace_OCIObjectMarkUpdate},
    {"OCIObjectNew", &trace_OCIObjectNew},
    {"OCIObjectNotAlwaysLatest", &trace_OCIObjectNotAlwaysLatest},
    {"OCIObjectPin", &trace_OCIObjectPin},
    {"OCIObjectPinCountReset", &trace_OCIObjectPinCountReset},
    {"OCIObjectPinTable", &trace_OCIObjectPinTable},
    {"OCIObjectRefresh", &trace_OCIObjectRefresh},
    {"OCIObjectSetAttr", &trace_OCIObjectSetAttr},
    {"OCIObjectSetData", &trace_OCIObjectSetData},
    {"OCIObjectUnmark", &trace_OCIObjectUnmark},
    {"OCIObjectUnmarkByRef", &trace_OCIObjectUnmarkByRef},
    {"OCIObjectUnpin", &trace_OCIObjectUnpin},
    {"OCIParamGet", &trace_OCIParamGet},
    {"OCIPasswordChange", &trace_OCIPasswordChange},
    {"OCIPing", &trace_OCIPing},
    {"OCIRawAllocSize", &trace_OCIRawAllocSize},
    {"OCIRawAssignBytes", &trace_OCIRawAssignBytes},
    {"OCIRawAssignRaw", &trace_OCIRawAssignRaw},
    {"OCIRawPtr", &trace_OCIRawPtr},
    {"OCIRawResize", &trace_OCIRawResize},
    {"OCIRawSize", &trace_OCIRawSize},
    {"OCIRefAssign", &trace_OCIRefAssign},
    {"OCIRefClear", &trace_OCIRefClear},
    {"OCIRefFromHex", &trace_OCIRefFromHex},
    {"OCIRefHexSize", &trace_OCIRefHexSize},
    {"OCIRefIsEqual", &trace_OCIRefIsEqual},
    {"OCIRefIsNull", &trace_OCIRefIsNull},
    {"OCIRefToHex", &trace_OCIRefToHex},
    {"OCIReset", &trace_OCIReset},
    {"OCIResultSetToStmt", &trace_OCIResultSetToStmt},
    {"OCIRowidToChar", &trace_OCIRowidToChar},
    {"OCIServerAttach", &trace_OCIServerAttach},
    {"OCIServerDetach", &trace_OCIServerDetach},
    {"OCIServerRelease", &trace_OCIServerRelease},
    {"OCIServerVersion", &trace_OCIServerVersion},
    {"OCISessionBegin", &trace_OCISessionBegin},
    {"OCISessionEnd", &trace_OCISessionEnd},
    {"OCISessionGet", &trace_OCISessionGet},
    {"OCISessionPoolCreate", &trace_OCISessionPoolCreate},
    {"OCISessionPoolDestroy", &trace_OCISessionPoolDestroy},
    {"OCISessionRelease", &trace_OCISessionRelease},
    {"OCISharedLibInit", &trace_OCISharedLibInit},
    {"OCIStmtExecute", &trace_OCIStmtExecute},
    {"OCIStmtFetch", &trace_OCIStmtFetch},
    {"OCIStmtFetch2", &trace_OCIStmtFetch2},
    {"OCIStmtGetBindInfo", &trace_OCIStmtGetBindInfo},
    {"OCIStmtGetPieceInfo", &trace_OCIStmtGetPieceInfo},
    {"OCIStmtPrepare", &trace_OCIStmtPrepare},
    {"OCIStmtPrepare2", &trace_OCIStmtPrepare2},
    {"OCIStmtRelease", &trace_OCIStmtRelease},
    {"OCIStmtSetPieceInfo", &trace_OCIStmtSetPieceInfo},
    {"OCIStringAllocSize", &trace_OCIStringAllocSize},
    {"OCIStringAssign", &trace_OCIStringAssign},
    {"OCIStringAssignText", &trace_OCIStringAssignText},
    {"OCIStringPtr", &trace_OCIStringPtr},
    {"OCIStringResize", &trace_OCIStringResize},
    {"OCIStringSize", &trace_OCIStringSize},
    {"OCITableDelete", &trace_OCITableDelete},
    {"OCITableExists", &trace_OCITableExists},
    {"OCITableFirst", &trace_OCITableFirst},
    {"OCITableLast", &trace_OCITableLast},
    {"OCITableNext", &trace_OCITableNext},
    {"OCITablePrev", &trace_OCITablePrev},
    {"OCITableSize", &trace_OCITableSize},
    {"OCITransCommit", &trace_OCITransCommit},
    {"OCITransRollback", &trace_OCITransRollback},
    {"OCITypeAddAttr", &trace_OCITypeAddAttr},
    {"OCITypeArrayByName", &trace_OCITypeArrayByName},
    {"OCITypeArrayByRef", &trace_OCITypeArrayByRef},
    {"OCITypeAttrByName", &trace_OCITypeAttrByName},
    {"OCITypeAttrNext", &trace_OCITypeAttrNext},
    {"OCITypeAttrs", &trace_OCITypeAttrs},
    {"OCITypeBeginCreate", &trace_OCITypeBeginCreate},
    {"OCITypeByName", &trace_OCITypeByName},
    {"OCITypeByRef", &trace_OCITypeByRef},
    {"OCITypeCollElem", &trace_OCITypeCollElem},
    {"OCITypeCollExtTypeCode", &trace_OCITypeCollExtTypeCode},
    {"OCITypeCollSize", &trace_OCITypeCollSize},
    {"OCITypeCollTypeCode", &trace_OCITypeCollTypeCode},
    {"OCITypeElemCharSetForm", &trace_OCITypeElemCharSetForm},
    {"OCITypeElemCharSetID", &trace_OCITypeElemCharSetID},
    {"OCITypeElemDefaultValue", &trace_OCITypeElemDefaultValue},
    {"OCITypeElemExtTypeCode", &trace_OCITypeElemExtTypeCode},
    {"OCITypeElemFlags", &trace_OCITypeElemFlags},
    {"OCITypeElemLength", &trace_OCITypeElemLength},
    {"OCITypeElemName", &trace_OCITypeElemName},
    {"OCITypeElemNumPrec", &trace_OCITypeElemNumPrec},
    {"OCITypeElemNumScale", &trace_OCITypeElemNumScale},
    {"OCITypeElemParamMode", &trace_OCITypeElemParamMode},
    {"OCITypeElemParameterizedType", &trace_OCITypeElemParameterizedType},
    {"OCITypeElemType", &trace_OCITypeElemType},
    {"OCITypeElemTypeCode", &trace_OCITypeElemTypeCode},
    {"OCITypeEndCreate", &trace_OCITypeEndCreate},
    {"OCITypeIterFree", &trace_OCITypeIterFree},
    {"OCITypeIterNew", &trace_OCITypeIterNew},
    {"OCITypeIterSet", &trace_OCITypeIterSet},
    {"OCITypeMethodByName", &trace_OCITypeMethodByName},
    {"OCITypeMethodEncap", &trace_OCITypeMethodEncap},
    {"OCITypeMethodFlags", &trace_OCITypeMethodFlags},
    {"OCITypeMethodMap", &trace_OCITypeMethodMap},
    {"OCITypeMethodName", &trace_OCITypeMethodName},
    {"OCITypeMethodNext", &trace_OCITypeMethodNext},
    {"OCITypeMethodOrder", &trace_OCITypeMethodOrder},
    {"OCITypeMethodOverload", &trace_OCITypeMethodOverload},
    {"OCITypeMethodParams", &trace_OCITypeMethodParams},
    {"OCITypeMethods", &trace_OCITypeMethods},
    {"OCITypeName", &trace_OCITypeName},
    {"OCITypeParamByName", &trace_OCITypeParamByName},
    {"OCITypeParamByPos", &trace_OCITypeParamByPos},
    {"OCITypeParamPos", &trace_OCITypeParamPos},
    {"OCITypeResult", &trace_OCITypeResult},
    {"OCITypeSchema", &trace_OCITypeSchema},
    {"OCITypeSetBuiltin", &trace_OCITypeSetBuiltin},
    {"OCITypeSetCollection", &trace_OCITypeSetCollection},
    {"OCITypeTypeCode", &trace_OCITypeTypeCode},
    {"OCITypeVTInit", &trace_OCITypeVTInit},
    {"OCITypeVTInsert", &trace_OCITypeVTInsert},
    {"OCITypeVTSelect", &trace_OCITypeVTSelect},
    {"OCITypeVersion", &trace_OCITypeVersion},
    {NULL, NULL},
};

static void initialize(void)
{
    OCIAnyDataAccess_func = (OCIAnyDataAccess_func_t)dlsym(RTLD_NEXT, "OCIAnyDataAccess");
    OCIAnyDataAttrGet_func = (OCIAnyDataAttrGet_func_t)dlsym(RTLD_NEXT, "OCIAnyDataAttrGet");
    OCIAnyDataAttrSet_func = (OCIAnyDataAttrSet_func_t)dlsym(RTLD_NEXT, "OCIAnyDataAttrSet");
    OCIAnyDataBeginCreate_func = (OCIAnyDataBeginCreate_func_t)dlsym(RTLD_NEXT, "OCIAnyDataBeginCreate");
    OCIAnyDataCollAddElem_func = (OCIAnyDataCollAddElem_func_t)dlsym(RTLD_NEXT, "OCIAnyDataCollAddElem");
    OCIAnyDataCollGetElem_func = (OCIAnyDataCollGetElem_func_t)dlsym(RTLD_NEXT, "OCIAnyDataCollGetElem");
    OCIAnyDataConvert_func = (OCIAnyDataConvert_func_t)dlsym(RTLD_NEXT, "OCIAnyDataConvert");
    OCIAnyDataDestroy_func = (OCIAnyDataDestroy_func_t)dlsym(RTLD_NEXT, "OCIAnyDataDestroy");
    OCIAnyDataEndCreate_func = (OCIAnyDataEndCreate_func_t)dlsym(RTLD_NEXT, "OCIAnyDataEndCreate");
    OCIAnyDataGetCurrAttrNum_func = (OCIAnyDataGetCurrAttrNum_func_t)dlsym(RTLD_NEXT, "OCIAnyDataGetCurrAttrNum");
    OCIAnyDataGetType_func = (OCIAnyDataGetType_func_t)dlsym(RTLD_NEXT, "OCIAnyDataGetType");
    OCIAnyDataIsNull_func = (OCIAnyDataIsNull_func_t)dlsym(RTLD_NEXT, "OCIAnyDataIsNull");
    OCIAnyDataSetAddInstance_func = (OCIAnyDataSetAddInstance_func_t)dlsym(RTLD_NEXT, "OCIAnyDataSetAddInstance");
    OCIAnyDataSetBeginCreate_func = (OCIAnyDataSetBeginCreate_func_t)dlsym(RTLD_NEXT, "OCIAnyDataSetBeginCreate");
    OCIAnyDataSetDestroy_func = (OCIAnyDataSetDestroy_func_t)dlsym(RTLD_NEXT, "OCIAnyDataSetDestroy");
    OCIAnyDataSetEndCreate_func = (OCIAnyDataSetEndCreate_func_t)dlsym(RTLD_NEXT, "OCIAnyDataSetEndCreate");
    OCIAnyDataSetGetCount_func = (OCIAnyDataSetGetCount_func_t)dlsym(RTLD_NEXT, "OCIAnyDataSetGetCount");
    OCIAnyDataSetGetInstance_func = (OCIAnyDataSetGetInstance_func_t)dlsym(RTLD_NEXT, "OCIAnyDataSetGetInstance");
    OCIAnyDataSetGetType_func = (OCIAnyDataSetGetType_func_t)dlsym(RTLD_NEXT, "OCIAnyDataSetGetType");
    OCIAppCtxClearAll_func = (OCIAppCtxClearAll_func_t)dlsym(RTLD_NEXT, "OCIAppCtxClearAll");
    OCIAppCtxSet_func = (OCIAppCtxSet_func_t)dlsym(RTLD_NEXT, "OCIAppCtxSet");
    OCIArrayDescriptorAlloc_func = (OCIArrayDescriptorAlloc_func_t)dlsym(RTLD_NEXT, "OCIArrayDescriptorAlloc");
    OCIArrayDescriptorFree_func = (OCIArrayDescriptorFree_func_t)dlsym(RTLD_NEXT, "OCIArrayDescriptorFree");
    OCIAttrGet_func = (OCIAttrGet_func_t)dlsym(RTLD_NEXT, "OCIAttrGet");
    OCIAttrSet_func = (OCIAttrSet_func_t)dlsym(RTLD_NEXT, "OCIAttrSet");
    OCIBindArrayOfStruct_func = (OCIBindArrayOfStruct_func_t)dlsym(RTLD_NEXT, "OCIBindArrayOfStruct");
    OCIBindByName_func = (OCIBindByName_func_t)dlsym(RTLD_NEXT, "OCIBindByName");
    OCIBindByPos_func = (OCIBindByPos_func_t)dlsym(RTLD_NEXT, "OCIBindByPos");
    OCIBindDynamic_func = (OCIBindDynamic_func_t)dlsym(RTLD_NEXT, "OCIBindDynamic");
    OCIBindObject_func = (OCIBindObject_func_t)dlsym(RTLD_NEXT, "OCIBindObject");
    OCIBreak_func = (OCIBreak_func_t)dlsym(RTLD_NEXT, "OCIBreak");
    OCICacheFlush_func = (OCICacheFlush_func_t)dlsym(RTLD_NEXT, "OCICacheFlush");
    OCICacheFlushRefresh_func = (OCICacheFlushRefresh_func_t)dlsym(RTLD_NEXT, "OCICacheFlushRefresh");
    OCICacheFree_func = (OCICacheFree_func_t)dlsym(RTLD_NEXT, "OCICacheFree");
    OCICacheGetObjects_func = (OCICacheGetObjects_func_t)dlsym(RTLD_NEXT, "OCICacheGetObjects");
    OCICacheRefresh_func = (OCICacheRefresh_func_t)dlsym(RTLD_NEXT, "OCICacheRefresh");
    OCICacheRegister_func = (OCICacheRegister_func_t)dlsym(RTLD_NEXT, "OCICacheRegister");
    OCICacheUnmark_func = (OCICacheUnmark_func_t)dlsym(RTLD_NEXT, "OCICacheUnmark");
    OCICacheUnpin_func = (OCICacheUnpin_func_t)dlsym(RTLD_NEXT, "OCICacheUnpin");
    OCICharSetConversionIsReplacementUsed_func = (OCICharSetConversionIsReplacementUsed_func_t)dlsym(RTLD_NEXT, "OCICharSetConversionIsReplacementUsed");
    OCIClientVersion_func = (OCIClientVersion_func_t)dlsym(RTLD_NEXT, "OCIClientVersion");
    OCICollAppend_func = (OCICollAppend_func_t)dlsym(RTLD_NEXT, "OCICollAppend");
    OCICollAssign_func = (OCICollAssign_func_t)dlsym(RTLD_NEXT, "OCICollAssign");
    OCICollAssignElem_func = (OCICollAssignElem_func_t)dlsym(RTLD_NEXT, "OCICollAssignElem");
    OCICollGetElem_func = (OCICollGetElem_func_t)dlsym(RTLD_NEXT, "OCICollGetElem");
    OCICollGetElemArray_func = (OCICollGetElemArray_func_t)dlsym(RTLD_NEXT, "OCICollGetElemArray");
    OCICollIsLocator_func = (OCICollIsLocator_func_t)dlsym(RTLD_NEXT, "OCICollIsLocator");
    OCICollMax_func = (OCICollMax_func_t)dlsym(RTLD_NEXT, "OCICollMax");
    OCICollSize_func = (OCICollSize_func_t)dlsym(RTLD_NEXT, "OCICollSize");
    OCICollTrim_func = (OCICollTrim_func_t)dlsym(RTLD_NEXT, "OCICollTrim");
    OCIConnectionPoolCreate_func = (OCIConnectionPoolCreate_func_t)dlsym(RTLD_NEXT, "OCIConnectionPoolCreate");
    OCIConnectionPoolDestroy_func = (OCIConnectionPoolDestroy_func_t)dlsym(RTLD_NEXT, "OCIConnectionPoolDestroy");
    OCIDBShutdown_func = (OCIDBShutdown_func_t)dlsym(RTLD_NEXT, "OCIDBShutdown");
    OCIDBStartup_func = (OCIDBStartup_func_t)dlsym(RTLD_NEXT, "OCIDBStartup");
    OCIDateAddDays_func = (OCIDateAddDays_func_t)dlsym(RTLD_NEXT, "OCIDateAddDays");
    OCIDateAddMonths_func = (OCIDateAddMonths_func_t)dlsym(RTLD_NEXT, "OCIDateAddMonths");
    OCIDateAssign_func = (OCIDateAssign_func_t)dlsym(RTLD_NEXT, "OCIDateAssign");
    OCIDateCheck_func = (OCIDateCheck_func_t)dlsym(RTLD_NEXT, "OCIDateCheck");
    OCIDateCompare_func = (OCIDateCompare_func_t)dlsym(RTLD_NEXT, "OCIDateCompare");
    OCIDateDaysBetween_func = (OCIDateDaysBetween_func_t)dlsym(RTLD_NEXT, "OCIDateDaysBetween");
    OCIDateFromText_func = (OCIDateFromText_func_t)dlsym(RTLD_NEXT, "OCIDateFromText");
    OCIDateLastDay_func = (OCIDateLastDay_func_t)dlsym(RTLD_NEXT, "OCIDateLastDay");
    OCIDateNextDay_func = (OCIDateNextDay_func_t)dlsym(RTLD_NEXT, "OCIDateNextDay");
    OCIDateSysDate_func = (OCIDateSysDate_func_t)dlsym(RTLD_NEXT, "OCIDateSysDate");
    OCIDateTimeAssign_func = (OCIDateTimeAssign_func_t)dlsym(RTLD_NEXT, "OCIDateTimeAssign");
    OCIDateTimeCheck_func = (OCIDateTimeCheck_func_t)dlsym(RTLD_NEXT, "OCIDateTimeCheck");
    OCIDateTimeCompare_func = (OCIDateTimeCompare_func_t)dlsym(RTLD_NEXT, "OCIDateTimeCompare");
    OCIDateTimeConstruct_func = (OCIDateTimeConstruct_func_t)dlsym(RTLD_NEXT, "OCIDateTimeConstruct");
    OCIDateTimeConvert_func = (OCIDateTimeConvert_func_t)dlsym(RTLD_NEXT, "OCIDateTimeConvert");
    OCIDateTimeFromArray_func = (OCIDateTimeFromArray_func_t)dlsym(RTLD_NEXT, "OCIDateTimeFromArray");
    OCIDateTimeFromText_func = (OCIDateTimeFromText_func_t)dlsym(RTLD_NEXT, "OCIDateTimeFromText");
    OCIDateTimeGetDate_func = (OCIDateTimeGetDate_func_t)dlsym(RTLD_NEXT, "OCIDateTimeGetDate");
    OCIDateTimeGetTime_func = (OCIDateTimeGetTime_func_t)dlsym(RTLD_NEXT, "OCIDateTimeGetTime");
    OCIDateTimeGetTimeZoneName_func = (OCIDateTimeGetTimeZoneName_func_t)dlsym(RTLD_NEXT, "OCIDateTimeGetTimeZoneName");
    OCIDateTimeGetTimeZoneOffset_func = (OCIDateTimeGetTimeZoneOffset_func_t)dlsym(RTLD_NEXT, "OCIDateTimeGetTimeZoneOffset");
    OCIDateTimeIntervalAdd_func = (OCIDateTimeIntervalAdd_func_t)dlsym(RTLD_NEXT, "OCIDateTimeIntervalAdd");
    OCIDateTimeIntervalSub_func = (OCIDateTimeIntervalSub_func_t)dlsym(RTLD_NEXT, "OCIDateTimeIntervalSub");
    OCIDateTimeSubtract_func = (OCIDateTimeSubtract_func_t)dlsym(RTLD_NEXT, "OCIDateTimeSubtract");
    OCIDateTimeSysTimeStamp_func = (OCIDateTimeSysTimeStamp_func_t)dlsym(RTLD_NEXT, "OCIDateTimeSysTimeStamp");
    OCIDateTimeToArray_func = (OCIDateTimeToArray_func_t)dlsym(RTLD_NEXT, "OCIDateTimeToArray");
    OCIDateTimeToText_func = (OCIDateTimeToText_func_t)dlsym(RTLD_NEXT, "OCIDateTimeToText");
    OCIDateToText_func = (OCIDateToText_func_t)dlsym(RTLD_NEXT, "OCIDateToText");
    OCIDateZoneToZone_func = (OCIDateZoneToZone_func_t)dlsym(RTLD_NEXT, "OCIDateZoneToZone");
    OCIDefineArrayOfStruct_func = (OCIDefineArrayOfStruct_func_t)dlsym(RTLD_NEXT, "OCIDefineArrayOfStruct");
    OCIDefineByPos_func = (OCIDefineByPos_func_t)dlsym(RTLD_NEXT, "OCIDefineByPos");
    OCIDefineDynamic_func = (OCIDefineDynamic_func_t)dlsym(RTLD_NEXT, "OCIDefineDynamic");
    OCIDefineObject_func = (OCIDefineObject_func_t)dlsym(RTLD_NEXT, "OCIDefineObject");
    OCIDescribeAny_func = (OCIDescribeAny_func_t)dlsym(RTLD_NEXT, "OCIDescribeAny");
    OCIDescriptorAlloc_func = (OCIDescriptorAlloc_func_t)dlsym(RTLD_NEXT, "OCIDescriptorAlloc");
    OCIDescriptorFree_func = (OCIDescriptorFree_func_t)dlsym(RTLD_NEXT, "OCIDescriptorFree");
    OCIDurationBegin_func = (OCIDurationBegin_func_t)dlsym(RTLD_NEXT, "OCIDurationBegin");
    OCIDurationEnd_func = (OCIDurationEnd_func_t)dlsym(RTLD_NEXT, "OCIDurationEnd");
    OCIDurationGetParent_func = (OCIDurationGetParent_func_t)dlsym(RTLD_NEXT, "OCIDurationGetParent");
    OCIEnvCreate_func = (OCIEnvCreate_func_t)dlsym(RTLD_NEXT, "OCIEnvCreate");
    OCIEnvInit_func = (OCIEnvInit_func_t)dlsym(RTLD_NEXT, "OCIEnvInit");
    OCIEnvNlsCreate_func = (OCIEnvNlsCreate_func_t)dlsym(RTLD_NEXT, "OCIEnvNlsCreate");
    OCIErrorGet_func = (OCIErrorGet_func_t)dlsym(RTLD_NEXT, "OCIErrorGet");
    OCIFEnvCreate_func = (OCIFEnvCreate_func_t)dlsym(RTLD_NEXT, "OCIFEnvCreate");
    OCIHandleAlloc_func = (OCIHandleAlloc_func_t)dlsym(RTLD_NEXT, "OCIHandleAlloc");
    OCIHandleFree_func = (OCIHandleFree_func_t)dlsym(RTLD_NEXT, "OCIHandleFree");
    OCIInitialize_func = (OCIInitialize_func_t)dlsym(RTLD_NEXT, "OCIInitialize");
    OCIIntervalAdd_func = (OCIIntervalAdd_func_t)dlsym(RTLD_NEXT, "OCIIntervalAdd");
    OCIIntervalAssign_func = (OCIIntervalAssign_func_t)dlsym(RTLD_NEXT, "OCIIntervalAssign");
    OCIIntervalCheck_func = (OCIIntervalCheck_func_t)dlsym(RTLD_NEXT, "OCIIntervalCheck");
    OCIIntervalCompare_func = (OCIIntervalCompare_func_t)dlsym(RTLD_NEXT, "OCIIntervalCompare");
    OCIIntervalDivide_func = (OCIIntervalDivide_func_t)dlsym(RTLD_NEXT, "OCIIntervalDivide");
    OCIIntervalFromNumber_func = (OCIIntervalFromNumber_func_t)dlsym(RTLD_NEXT, "OCIIntervalFromNumber");
    OCIIntervalFromTZ_func = (OCIIntervalFromTZ_func_t)dlsym(RTLD_NEXT, "OCIIntervalFromTZ");
    OCIIntervalFromText_func = (OCIIntervalFromText_func_t)dlsym(RTLD_NEXT, "OCIIntervalFromText");
    OCIIntervalGetDaySecond_func = (OCIIntervalGetDaySecond_func_t)dlsym(RTLD_NEXT, "OCIIntervalGetDaySecond");
    OCIIntervalGetYearMonth_func = (OCIIntervalGetYearMonth_func_t)dlsym(RTLD_NEXT, "OCIIntervalGetYearMonth");
    OCIIntervalMultiply_func = (OCIIntervalMultiply_func_t)dlsym(RTLD_NEXT, "OCIIntervalMultiply");
    OCIIntervalSetDaySecond_func = (OCIIntervalSetDaySecond_func_t)dlsym(RTLD_NEXT, "OCIIntervalSetDaySecond");
    OCIIntervalSetYearMonth_func = (OCIIntervalSetYearMonth_func_t)dlsym(RTLD_NEXT, "OCIIntervalSetYearMonth");
    OCIIntervalSubtract_func = (OCIIntervalSubtract_func_t)dlsym(RTLD_NEXT, "OCIIntervalSubtract");
    OCIIntervalToNumber_func = (OCIIntervalToNumber_func_t)dlsym(RTLD_NEXT, "OCIIntervalToNumber");
    OCIIntervalToText_func = (OCIIntervalToText_func_t)dlsym(RTLD_NEXT, "OCIIntervalToText");
    OCIIterCreate_func = (OCIIterCreate_func_t)dlsym(RTLD_NEXT, "OCIIterCreate");
    OCIIterDelete_func = (OCIIterDelete_func_t)dlsym(RTLD_NEXT, "OCIIterDelete");
    OCIIterGetCurrent_func = (OCIIterGetCurrent_func_t)dlsym(RTLD_NEXT, "OCIIterGetCurrent");
    OCIIterInit_func = (OCIIterInit_func_t)dlsym(RTLD_NEXT, "OCIIterInit");
    OCIIterNext_func = (OCIIterNext_func_t)dlsym(RTLD_NEXT, "OCIIterNext");
    OCIIterPrev_func = (OCIIterPrev_func_t)dlsym(RTLD_NEXT, "OCIIterPrev");
    OCILobAppend_func = (OCILobAppend_func_t)dlsym(RTLD_NEXT, "OCILobAppend");
    OCILobArrayRead_func = (OCILobArrayRead_func_t)dlsym(RTLD_NEXT, "OCILobArrayRead");
    OCILobArrayWrite_func = (OCILobArrayWrite_func_t)dlsym(RTLD_NEXT, "OCILobArrayWrite");
    OCILobAssign_func = (OCILobAssign_func_t)dlsym(RTLD_NEXT, "OCILobAssign");
    OCILobCharSetForm_func = (OCILobCharSetForm_func_t)dlsym(RTLD_NEXT, "OCILobCharSetForm");
    OCILobCharSetId_func = (OCILobCharSetId_func_t)dlsym(RTLD_NEXT, "OCILobCharSetId");
    OCILobClose_func = (OCILobClose_func_t)dlsym(RTLD_NEXT, "OCILobClose");
    OCILobCopy_func = (OCILobCopy_func_t)dlsym(RTLD_NEXT, "OCILobCopy");
    OCILobCopy2_func = (OCILobCopy2_func_t)dlsym(RTLD_NEXT, "OCILobCopy2");
    OCILobCreateTemporary_func = (OCILobCreateTemporary_func_t)dlsym(RTLD_NEXT, "OCILobCreateTemporary");
    OCILobDisableBuffering_func = (OCILobDisableBuffering_func_t)dlsym(RTLD_NEXT, "OCILobDisableBuffering");
    OCILobEnableBuffering_func = (OCILobEnableBuffering_func_t)dlsym(RTLD_NEXT, "OCILobEnableBuffering");
    OCILobErase_func = (OCILobErase_func_t)dlsym(RTLD_NEXT, "OCILobErase");
    OCILobErase2_func = (OCILobErase2_func_t)dlsym(RTLD_NEXT, "OCILobErase2");
    OCILobFileClose_func = (OCILobFileClose_func_t)dlsym(RTLD_NEXT, "OCILobFileClose");
    OCILobFileCloseAll_func = (OCILobFileCloseAll_func_t)dlsym(RTLD_NEXT, "OCILobFileCloseAll");
    OCILobFileExists_func = (OCILobFileExists_func_t)dlsym(RTLD_NEXT, "OCILobFileExists");
    OCILobFileGetName_func = (OCILobFileGetName_func_t)dlsym(RTLD_NEXT, "OCILobFileGetName");
    OCILobFileIsOpen_func = (OCILobFileIsOpen_func_t)dlsym(RTLD_NEXT, "OCILobFileIsOpen");
    OCILobFileOpen_func = (OCILobFileOpen_func_t)dlsym(RTLD_NEXT, "OCILobFileOpen");
    OCILobFileSetName_func = (OCILobFileSetName_func_t)dlsym(RTLD_NEXT, "OCILobFileSetName");
    OCILobFlushBuffer_func = (OCILobFlushBuffer_func_t)dlsym(RTLD_NEXT, "OCILobFlushBuffer");
    OCILobFreeTemporary_func = (OCILobFreeTemporary_func_t)dlsym(RTLD_NEXT, "OCILobFreeTemporary");
    OCILobGetChunkSize_func = (OCILobGetChunkSize_func_t)dlsym(RTLD_NEXT, "OCILobGetChunkSize");
    OCILobGetContentType_func = (OCILobGetContentType_func_t)dlsym(RTLD_NEXT, "OCILobGetContentType");
    OCILobGetDeduplicateRegions_func = (OCILobGetDeduplicateRegions_func_t)dlsym(RTLD_NEXT, "OCILobGetDeduplicateRegions");
    OCILobGetLength_func = (OCILobGetLength_func_t)dlsym(RTLD_NEXT, "OCILobGetLength");
    OCILobGetLength2_func = (OCILobGetLength2_func_t)dlsym(RTLD_NEXT, "OCILobGetLength2");
    OCILobGetOptions_func = (OCILobGetOptions_func_t)dlsym(RTLD_NEXT, "OCILobGetOptions");
    OCILobGetStorageLimit_func = (OCILobGetStorageLimit_func_t)dlsym(RTLD_NEXT, "OCILobGetStorageLimit");
    OCILobIsEqual_func = (OCILobIsEqual_func_t)dlsym(RTLD_NEXT, "OCILobIsEqual");
    OCILobIsOpen_func = (OCILobIsOpen_func_t)dlsym(RTLD_NEXT, "OCILobIsOpen");
    OCILobIsTemporary_func = (OCILobIsTemporary_func_t)dlsym(RTLD_NEXT, "OCILobIsTemporary");
    OCILobLoadFromFile_func = (OCILobLoadFromFile_func_t)dlsym(RTLD_NEXT, "OCILobLoadFromFile");
    OCILobLoadFromFile2_func = (OCILobLoadFromFile2_func_t)dlsym(RTLD_NEXT, "OCILobLoadFromFile2");
    OCILobLocatorAssign_func = (OCILobLocatorAssign_func_t)dlsym(RTLD_NEXT, "OCILobLocatorAssign");
    OCILobLocatorIsInit_func = (OCILobLocatorIsInit_func_t)dlsym(RTLD_NEXT, "OCILobLocatorIsInit");
    OCILobOpen_func = (OCILobOpen_func_t)dlsym(RTLD_NEXT, "OCILobOpen");
    OCILobRead_func = (OCILobRead_func_t)dlsym(RTLD_NEXT, "OCILobRead");
    OCILobRead2_func = (OCILobRead2_func_t)dlsym(RTLD_NEXT, "OCILobRead2");
    OCILobSetContentType_func = (OCILobSetContentType_func_t)dlsym(RTLD_NEXT, "OCILobSetContentType");
    OCILobSetOptions_func = (OCILobSetOptions_func_t)dlsym(RTLD_NEXT, "OCILobSetOptions");
    OCILobTrim_func = (OCILobTrim_func_t)dlsym(RTLD_NEXT, "OCILobTrim");
    OCILobTrim2_func = (OCILobTrim2_func_t)dlsym(RTLD_NEXT, "OCILobTrim2");
    OCILobWrite_func = (OCILobWrite_func_t)dlsym(RTLD_NEXT, "OCILobWrite");
    OCILobWrite2_func = (OCILobWrite2_func_t)dlsym(RTLD_NEXT, "OCILobWrite2");
    OCILobWriteAppend_func = (OCILobWriteAppend_func_t)dlsym(RTLD_NEXT, "OCILobWriteAppend");
    OCILobWriteAppend2_func = (OCILobWriteAppend2_func_t)dlsym(RTLD_NEXT, "OCILobWriteAppend2");
    OCILogoff_func = (OCILogoff_func_t)dlsym(RTLD_NEXT, "OCILogoff");
    OCILogon_func = (OCILogon_func_t)dlsym(RTLD_NEXT, "OCILogon");
    OCILogon2_func = (OCILogon2_func_t)dlsym(RTLD_NEXT, "OCILogon2");
    OCIMessageClose_func = (OCIMessageClose_func_t)dlsym(RTLD_NEXT, "OCIMessageClose");
    OCIMessageGet_func = (OCIMessageGet_func_t)dlsym(RTLD_NEXT, "OCIMessageGet");
    OCIMessageOpen_func = (OCIMessageOpen_func_t)dlsym(RTLD_NEXT, "OCIMessageOpen");
    OCINlsCharSetIdToName_func = (OCINlsCharSetIdToName_func_t)dlsym(RTLD_NEXT, "OCINlsCharSetIdToName");
    OCINlsCharSetNameToId_func = (OCINlsCharSetNameToId_func_t)dlsym(RTLD_NEXT, "OCINlsCharSetNameToId");
    OCINumberAbs_func = (OCINumberAbs_func_t)dlsym(RTLD_NEXT, "OCINumberAbs");
    OCINumberAdd_func = (OCINumberAdd_func_t)dlsym(RTLD_NEXT, "OCINumberAdd");
    OCINumberArcCos_func = (OCINumberArcCos_func_t)dlsym(RTLD_NEXT, "OCINumberArcCos");
    OCINumberArcSin_func = (OCINumberArcSin_func_t)dlsym(RTLD_NEXT, "OCINumberArcSin");
    OCINumberArcTan_func = (OCINumberArcTan_func_t)dlsym(RTLD_NEXT, "OCINumberArcTan");
    OCINumberArcTan2_func = (OCINumberArcTan2_func_t)dlsym(RTLD_NEXT, "OCINumberArcTan2");
    OCINumberAssign_func = (OCINumberAssign_func_t)dlsym(RTLD_NEXT, "OCINumberAssign");
    OCINumberCeil_func = (OCINumberCeil_func_t)dlsym(RTLD_NEXT, "OCINumberCeil");
    OCINumberCmp_func = (OCINumberCmp_func_t)dlsym(RTLD_NEXT, "OCINumberCmp");
    OCINumberCos_func = (OCINumberCos_func_t)dlsym(RTLD_NEXT, "OCINumberCos");
    OCINumberDec_func = (OCINumberDec_func_t)dlsym(RTLD_NEXT, "OCINumberDec");
    OCINumberDiv_func = (OCINumberDiv_func_t)dlsym(RTLD_NEXT, "OCINumberDiv");
    OCINumberExp_func = (OCINumberExp_func_t)dlsym(RTLD_NEXT, "OCINumberExp");
    OCINumberFloor_func = (OCINumberFloor_func_t)dlsym(RTLD_NEXT, "OCINumberFloor");
    OCINumberFromInt_func = (OCINumberFromInt_func_t)dlsym(RTLD_NEXT, "OCINumberFromInt");
    OCINumberFromReal_func = (OCINumberFromReal_func_t)dlsym(RTLD_NEXT, "OCINumberFromReal");
    OCINumberFromText_func = (OCINumberFromText_func_t)dlsym(RTLD_NEXT, "OCINumberFromText");
    OCINumberHypCos_func = (OCINumberHypCos_func_t)dlsym(RTLD_NEXT, "OCINumberHypCos");
    OCINumberHypSin_func = (OCINumberHypSin_func_t)dlsym(RTLD_NEXT, "OCINumberHypSin");
    OCINumberHypTan_func = (OCINumberHypTan_func_t)dlsym(RTLD_NEXT, "OCINumberHypTan");
    OCINumberInc_func = (OCINumberInc_func_t)dlsym(RTLD_NEXT, "OCINumberInc");
    OCINumberIntPower_func = (OCINumberIntPower_func_t)dlsym(RTLD_NEXT, "OCINumberIntPower");
    OCINumberIsInt_func = (OCINumberIsInt_func_t)dlsym(RTLD_NEXT, "OCINumberIsInt");
    OCINumberIsZero_func = (OCINumberIsZero_func_t)dlsym(RTLD_NEXT, "OCINumberIsZero");
    OCINumberLn_func = (OCINumberLn_func_t)dlsym(RTLD_NEXT, "OCINumberLn");
    OCINumberLog_func = (OCINumberLog_func_t)dlsym(RTLD_NEXT, "OCINumberLog");
    OCINumberMod_func = (OCINumberMod_func_t)dlsym(RTLD_NEXT, "OCINumberMod");
    OCINumberMul_func = (OCINumberMul_func_t)dlsym(RTLD_NEXT, "OCINumberMul");
    OCINumberNeg_func = (OCINumberNeg_func_t)dlsym(RTLD_NEXT, "OCINumberNeg");
    OCINumberPower_func = (OCINumberPower_func_t)dlsym(RTLD_NEXT, "OCINumberPower");
    OCINumberPrec_func = (OCINumberPrec_func_t)dlsym(RTLD_NEXT, "OCINumberPrec");
    OCINumberRound_func = (OCINumberRound_func_t)dlsym(RTLD_NEXT, "OCINumberRound");
    OCINumberSetPi_func = (OCINumberSetPi_func_t)dlsym(RTLD_NEXT, "OCINumberSetPi");
    OCINumberSetZero_func = (OCINumberSetZero_func_t)dlsym(RTLD_NEXT, "OCINumberSetZero");
    OCINumberShift_func = (OCINumberShift_func_t)dlsym(RTLD_NEXT, "OCINumberShift");
    OCINumberSign_func = (OCINumberSign_func_t)dlsym(RTLD_NEXT, "OCINumberSign");
    OCINumberSin_func = (OCINumberSin_func_t)dlsym(RTLD_NEXT, "OCINumberSin");
    OCINumberSqrt_func = (OCINumberSqrt_func_t)dlsym(RTLD_NEXT, "OCINumberSqrt");
    OCINumberSub_func = (OCINumberSub_func_t)dlsym(RTLD_NEXT, "OCINumberSub");
    OCINumberTan_func = (OCINumberTan_func_t)dlsym(RTLD_NEXT, "OCINumberTan");
    OCINumberToInt_func = (OCINumberToInt_func_t)dlsym(RTLD_NEXT, "OCINumberToInt");
    OCINumberToReal_func = (OCINumberToReal_func_t)dlsym(RTLD_NEXT, "OCINumberToReal");
    OCINumberToRealArray_func = (OCINumberToRealArray_func_t)dlsym(RTLD_NEXT, "OCINumberToRealArray");
    OCINumberToText_func = (OCINumberToText_func_t)dlsym(RTLD_NEXT, "OCINumberToText");
    OCINumberTrunc_func = (OCINumberTrunc_func_t)dlsym(RTLD_NEXT, "OCINumberTrunc");
    OCIObjectAlwaysLatest_func = (OCIObjectAlwaysLatest_func_t)dlsym(RTLD_NEXT, "OCIObjectAlwaysLatest");
    OCIObjectArrayPin_func = (OCIObjectArrayPin_func_t)dlsym(RTLD_NEXT, "OCIObjectArrayPin");
    OCIObjectCopy_func = (OCIObjectCopy_func_t)dlsym(RTLD_NEXT, "OCIObjectCopy");
    OCIObjectExists_func = (OCIObjectExists_func_t)dlsym(RTLD_NEXT, "OCIObjectExists");
    OCIObjectFlush_func = (OCIObjectFlush_func_t)dlsym(RTLD_NEXT, "OCIObjectFlush");
    OCIObjectFlushRefresh_func = (OCIObjectFlushRefresh_func_t)dlsym(RTLD_NEXT, "OCIObjectFlushRefresh");
    OCIObjectFree_func = (OCIObjectFree_func_t)dlsym(RTLD_NEXT, "OCIObjectFree");
    OCIObjectGetAttr_func = (OCIObjectGetAttr_func_t)dlsym(RTLD_NEXT, "OCIObjectGetAttr");
    OCIObjectGetInd_func = (OCIObjectGetInd_func_t)dlsym(RTLD_NEXT, "OCIObjectGetInd");
    OCIObjectGetNewOID_func = (OCIObjectGetNewOID_func_t)dlsym(RTLD_NEXT, "OCIObjectGetNewOID");
    OCIObjectGetObjectRef_func = (OCIObjectGetObjectRef_func_t)dlsym(RTLD_NEXT, "OCIObjectGetObjectRef");
    OCIObjectGetPrimaryKeyTypeRef_func = (OCIObjectGetPrimaryKeyTypeRef_func_t)dlsym(RTLD_NEXT, "OCIObjectGetPrimaryKeyTypeRef");
    OCIObjectGetProperty_func = (OCIObjectGetProperty_func_t)dlsym(RTLD_NEXT, "OCIObjectGetProperty");
    OCIObjectGetTypeRef_func = (OCIObjectGetTypeRef_func_t)dlsym(RTLD_NEXT, "OCIObjectGetTypeRef");
    OCIObjectIsDirtied_func = (OCIObjectIsDirtied_func_t)dlsym(RTLD_NEXT, "OCIObjectIsDirtied");
    OCIObjectIsDirty_func = (OCIObjectIsDirty_func_t)dlsym(RTLD_NEXT, "OCIObjectIsDirty");
    OCIObjectIsLoaded_func = (OCIObjectIsLoaded_func_t)dlsym(RTLD_NEXT, "OCIObjectIsLoaded");
    OCIObjectIsLocked_func = (OCIObjectIsLocked_func_t)dlsym(RTLD_NEXT, "OCIObjectIsLocked");
    OCIObjectLock_func = (OCIObjectLock_func_t)dlsym(RTLD_NEXT, "OCIObjectLock");
    OCIObjectLockNoWait_func = (OCIObjectLockNoWait_func_t)dlsym(RTLD_NEXT, "OCIObjectLockNoWait");
    OCIObjectMakeObjectRef_func = (OCIObjectMakeObjectRef_func_t)dlsym(RTLD_NEXT, "OCIObjectMakeObjectRef");
    OCIObjectMarkDelete_func = (OCIObjectMarkDelete_func_t)dlsym(RTLD_NEXT, "OCIObjectMarkDelete");
    OCIObjectMarkDeleteByRef_func = (OCIObjectMarkDeleteByRef_func_t)dlsym(RTLD_NEXT, "OCIObjectMarkDeleteByRef");
    OCIObjectMarkUpdate_func = (OCIObjectMarkUpdate_func_t)dlsym(RTLD_NEXT, "OCIObjectMarkUpdate");
    OCIObjectNew_func = (OCIObjectNew_func_t)dlsym(RTLD_NEXT, "OCIObjectNew");
    OCIObjectNotAlwaysLatest_func = (OCIObjectNotAlwaysLatest_func_t)dlsym(RTLD_NEXT, "OCIObjectNotAlwaysLatest");
    OCIObjectPin_func = (OCIObjectPin_func_t)dlsym(RTLD_NEXT, "OCIObjectPin");
    OCIObjectPinCountReset_func = (OCIObjectPinCountReset_func_t)dlsym(RTLD_NEXT, "OCIObjectPinCountReset");
    OCIObjectPinTable_func = (OCIObjectPinTable_func_t)dlsym(RTLD_NEXT, "OCIObjectPinTable");
    OCIObjectRefresh_func = (OCIObjectRefresh_func_t)dlsym(RTLD_NEXT, "OCIObjectRefresh");
    OCIObjectSetAttr_func = (OCIObjectSetAttr_func_t)dlsym(RTLD_NEXT, "OCIObjectSetAttr");
    OCIObjectSetData_func = (OCIObjectSetData_func_t)dlsym(RTLD_NEXT, "OCIObjectSetData");
    OCIObjectUnmark_func = (OCIObjectUnmark_func_t)dlsym(RTLD_NEXT, "OCIObjectUnmark");
    OCIObjectUnmarkByRef_func = (OCIObjectUnmarkByRef_func_t)dlsym(RTLD_NEXT, "OCIObjectUnmarkByRef");
    OCIObjectUnpin_func = (OCIObjectUnpin_func_t)dlsym(RTLD_NEXT, "OCIObjectUnpin");
    OCIParamGet_func = (OCIParamGet_func_t)dlsym(RTLD_NEXT, "OCIParamGet");
    OCIPasswordChange_func = (OCIPasswordChange_func_t)dlsym(RTLD_NEXT, "OCIPasswordChange");
    OCIPing_func = (OCIPing_func_t)dlsym(RTLD_NEXT, "OCIPing");
    OCIRawAllocSize_func = (OCIRawAllocSize_func_t)dlsym(RTLD_NEXT, "OCIRawAllocSize");
    OCIRawAssignBytes_func = (OCIRawAssignBytes_func_t)dlsym(RTLD_NEXT, "OCIRawAssignBytes");
    OCIRawAssignRaw_func = (OCIRawAssignRaw_func_t)dlsym(RTLD_NEXT, "OCIRawAssignRaw");
    OCIRawPtr_func = (OCIRawPtr_func_t)dlsym(RTLD_NEXT, "OCIRawPtr");
    OCIRawResize_func = (OCIRawResize_func_t)dlsym(RTLD_NEXT, "OCIRawResize");
    OCIRawSize_func = (OCIRawSize_func_t)dlsym(RTLD_NEXT, "OCIRawSize");
    OCIRefAssign_func = (OCIRefAssign_func_t)dlsym(RTLD_NEXT, "OCIRefAssign");
    OCIRefClear_func = (OCIRefClear_func_t)dlsym(RTLD_NEXT, "OCIRefClear");
    OCIRefFromHex_func = (OCIRefFromHex_func_t)dlsym(RTLD_NEXT, "OCIRefFromHex");
    OCIRefHexSize_func = (OCIRefHexSize_func_t)dlsym(RTLD_NEXT, "OCIRefHexSize");
    OCIRefIsEqual_func = (OCIRefIsEqual_func_t)dlsym(RTLD_NEXT, "OCIRefIsEqual");
    OCIRefIsNull_func = (OCIRefIsNull_func_t)dlsym(RTLD_NEXT, "OCIRefIsNull");
    OCIRefToHex_func = (OCIRefToHex_func_t)dlsym(RTLD_NEXT, "OCIRefToHex");
    OCIReset_func = (OCIReset_func_t)dlsym(RTLD_NEXT, "OCIReset");
    OCIResultSetToStmt_func = (OCIResultSetToStmt_func_t)dlsym(RTLD_NEXT, "OCIResultSetToStmt");
    OCIRowidToChar_func = (OCIRowidToChar_func_t)dlsym(RTLD_NEXT, "OCIRowidToChar");
    OCIServerAttach_func = (OCIServerAttach_func_t)dlsym(RTLD_NEXT, "OCIServerAttach");
    OCIServerDetach_func = (OCIServerDetach_func_t)dlsym(RTLD_NEXT, "OCIServerDetach");
    OCIServerRelease_func = (OCIServerRelease_func_t)dlsym(RTLD_NEXT, "OCIServerRelease");
    OCIServerVersion_func = (OCIServerVersion_func_t)dlsym(RTLD_NEXT, "OCIServerVersion");
    OCISessionBegin_func = (OCISessionBegin_func_t)dlsym(RTLD_NEXT, "OCISessionBegin");
    OCISessionEnd_func = (OCISessionEnd_func_t)dlsym(RTLD_NEXT, "OCISessionEnd");
    OCISessionGet_func = (OCISessionGet_func_t)dlsym(RTLD_NEXT, "OCISessionGet");
    OCISessionPoolCreate_func = (OCISessionPoolCreate_func_t)dlsym(RTLD_NEXT, "OCISessionPoolCreate");
    OCISessionPoolDestroy_func = (OCISessionPoolDestroy_func_t)dlsym(RTLD_NEXT, "OCISessionPoolDestroy");
    OCISessionRelease_func = (OCISessionRelease_func_t)dlsym(RTLD_NEXT, "OCISessionRelease");
    OCISharedLibInit_func = (OCISharedLibInit_func_t)dlsym(RTLD_NEXT, "OCISharedLibInit");
    OCIStmtExecute_func = (OCIStmtExecute_func_t)dlsym(RTLD_NEXT, "OCIStmtExecute");
    OCIStmtFetch_func = (OCIStmtFetch_func_t)dlsym(RTLD_NEXT, "OCIStmtFetch");
    OCIStmtFetch2_func = (OCIStmtFetch2_func_t)dlsym(RTLD_NEXT, "OCIStmtFetch2");
    OCIStmtGetBindInfo_func = (OCIStmtGetBindInfo_func_t)dlsym(RTLD_NEXT, "OCIStmtGetBindInfo");
    OCIStmtGetPieceInfo_func = (OCIStmtGetPieceInfo_func_t)dlsym(RTLD_NEXT, "OCIStmtGetPieceInfo");
    OCIStmtPrepare_func = (OCIStmtPrepare_func_t)dlsym(RTLD_NEXT, "OCIStmtPrepare");
    OCIStmtPrepare2_func = (OCIStmtPrepare2_func_t)dlsym(RTLD_NEXT, "OCIStmtPrepare2");
    OCIStmtRelease_func = (OCIStmtRelease_func_t)dlsym(RTLD_NEXT, "OCIStmtRelease");
    OCIStmtSetPieceInfo_func = (OCIStmtSetPieceInfo_func_t)dlsym(RTLD_NEXT, "OCIStmtSetPieceInfo");
    OCIStringAllocSize_func = (OCIStringAllocSize_func_t)dlsym(RTLD_NEXT, "OCIStringAllocSize");
    OCIStringAssign_func = (OCIStringAssign_func_t)dlsym(RTLD_NEXT, "OCIStringAssign");
    OCIStringAssignText_func = (OCIStringAssignText_func_t)dlsym(RTLD_NEXT, "OCIStringAssignText");
    OCIStringPtr_func = (OCIStringPtr_func_t)dlsym(RTLD_NEXT, "OCIStringPtr");
    OCIStringResize_func = (OCIStringResize_func_t)dlsym(RTLD_NEXT, "OCIStringResize");
    OCIStringSize_func = (OCIStringSize_func_t)dlsym(RTLD_NEXT, "OCIStringSize");
    OCITableDelete_func = (OCITableDelete_func_t)dlsym(RTLD_NEXT, "OCITableDelete");
    OCITableExists_func = (OCITableExists_func_t)dlsym(RTLD_NEXT, "OCITableExists");
    OCITableFirst_func = (OCITableFirst_func_t)dlsym(RTLD_NEXT, "OCITableFirst");
    OCITableLast_func = (OCITableLast_func_t)dlsym(RTLD_NEXT, "OCITableLast");
    OCITableNext_func = (OCITableNext_func_t)dlsym(RTLD_NEXT, "OCITableNext");
    OCITablePrev_func = (OCITablePrev_func_t)dlsym(RTLD_NEXT, "OCITablePrev");
    OCITableSize_func = (OCITableSize_func_t)dlsym(RTLD_NEXT, "OCITableSize");
    OCITransCommit_func = (OCITransCommit_func_t)dlsym(RTLD_NEXT, "OCITransCommit");
    OCITransRollback_func = (OCITransRollback_func_t)dlsym(RTLD_NEXT, "OCITransRollback");
    OCITypeAddAttr_func = (OCITypeAddAttr_func_t)dlsym(RTLD_NEXT, "OCITypeAddAttr");
    OCITypeArrayByName_func = (OCITypeArrayByName_func_t)dlsym(RTLD_NEXT, "OCITypeArrayByName");
    OCITypeArrayByRef_func = (OCITypeArrayByRef_func_t)dlsym(RTLD_NEXT, "OCITypeArrayByRef");
    OCITypeAttrByName_func = (OCITypeAttrByName_func_t)dlsym(RTLD_NEXT, "OCITypeAttrByName");
    OCITypeAttrNext_func = (OCITypeAttrNext_func_t)dlsym(RTLD_NEXT, "OCITypeAttrNext");
    OCITypeAttrs_func = (OCITypeAttrs_func_t)dlsym(RTLD_NEXT, "OCITypeAttrs");
    OCITypeBeginCreate_func = (OCITypeBeginCreate_func_t)dlsym(RTLD_NEXT, "OCITypeBeginCreate");
    OCITypeByName_func = (OCITypeByName_func_t)dlsym(RTLD_NEXT, "OCITypeByName");
    OCITypeByRef_func = (OCITypeByRef_func_t)dlsym(RTLD_NEXT, "OCITypeByRef");
    OCITypeCollElem_func = (OCITypeCollElem_func_t)dlsym(RTLD_NEXT, "OCITypeCollElem");
    OCITypeCollExtTypeCode_func = (OCITypeCollExtTypeCode_func_t)dlsym(RTLD_NEXT, "OCITypeCollExtTypeCode");
    OCITypeCollSize_func = (OCITypeCollSize_func_t)dlsym(RTLD_NEXT, "OCITypeCollSize");
    OCITypeCollTypeCode_func = (OCITypeCollTypeCode_func_t)dlsym(RTLD_NEXT, "OCITypeCollTypeCode");
    OCITypeElemCharSetForm_func = (OCITypeElemCharSetForm_func_t)dlsym(RTLD_NEXT, "OCITypeElemCharSetForm");
    OCITypeElemCharSetID_func = (OCITypeElemCharSetID_func_t)dlsym(RTLD_NEXT, "OCITypeElemCharSetID");
    OCITypeElemDefaultValue_func = (OCITypeElemDefaultValue_func_t)dlsym(RTLD_NEXT, "OCITypeElemDefaultValue");
    OCITypeElemExtTypeCode_func = (OCITypeElemExtTypeCode_func_t)dlsym(RTLD_NEXT, "OCITypeElemExtTypeCode");
    OCITypeElemFlags_func = (OCITypeElemFlags_func_t)dlsym(RTLD_NEXT, "OCITypeElemFlags");
    OCITypeElemLength_func = (OCITypeElemLength_func_t)dlsym(RTLD_NEXT, "OCITypeElemLength");
    OCITypeElemName_func = (OCITypeElemName_func_t)dlsym(RTLD_NEXT, "OCITypeElemName");
    OCITypeElemNumPrec_func = (OCITypeElemNumPrec_func_t)dlsym(RTLD_NEXT, "OCITypeElemNumPrec");
    OCITypeElemNumScale_func = (OCITypeElemNumScale_func_t)dlsym(RTLD_NEXT, "OCITypeElemNumScale");
    OCITypeElemParamMode_func = (OCITypeElemParamMode_func_t)dlsym(RTLD_NEXT, "OCITypeElemParamMode");
    OCITypeElemParameterizedType_func = (OCITypeElemParameterizedType_func_t)dlsym(RTLD_NEXT, "OCITypeElemParameterizedType");
    OCITypeElemType_func = (OCITypeElemType_func_t)dlsym(RTLD_NEXT, "OCITypeElemType");
    OCITypeElemTypeCode_func = (OCITypeElemTypeCode_func_t)dlsym(RTLD_NEXT, "OCITypeElemTypeCode");
    OCITypeEndCreate_func = (OCITypeEndCreate_func_t)dlsym(RTLD_NEXT, "OCITypeEndCreate");
    OCITypeIterFree_func = (OCITypeIterFree_func_t)dlsym(RTLD_NEXT, "OCITypeIterFree");
    OCITypeIterNew_func = (OCITypeIterNew_func_t)dlsym(RTLD_NEXT, "OCITypeIterNew");
    OCITypeIterSet_func = (OCITypeIterSet_func_t)dlsym(RTLD_NEXT, "OCITypeIterSet");
    OCITypeMethodByName_func = (OCITypeMethodByName_func_t)dlsym(RTLD_NEXT, "OCITypeMethodByName");
    OCITypeMethodEncap_func = (OCITypeMethodEncap_func_t)dlsym(RTLD_NEXT, "OCITypeMethodEncap");
    OCITypeMethodFlags_func = (OCITypeMethodFlags_func_t)dlsym(RTLD_NEXT, "OCITypeMethodFlags");
    OCITypeMethodMap_func = (OCITypeMethodMap_func_t)dlsym(RTLD_NEXT, "OCITypeMethodMap");
    OCITypeMethodName_func = (OCITypeMethodName_func_t)dlsym(RTLD_NEXT, "OCITypeMethodName");
    OCITypeMethodNext_func = (OCITypeMethodNext_func_t)dlsym(RTLD_NEXT, "OCITypeMethodNext");
    OCITypeMethodOrder_func = (OCITypeMethodOrder_func_t)dlsym(RTLD_NEXT, "OCITypeMethodOrder");
    OCITypeMethodOverload_func = (OCITypeMethodOverload_func_t)dlsym(RTLD_NEXT, "OCITypeMethodOverload");
    OCITypeMethodParams_func = (OCITypeMethodParams_func_t)dlsym(RTLD_NEXT, "OCITypeMethodParams");
    OCITypeMethods_func = (OCITypeMethods_func_t)dlsym(RTLD_NEXT, "OCITypeMethods");
    OCITypeName_func = (OCITypeName_func_t)dlsym(RTLD_NEXT, "OCITypeName");
    OCITypeParamByName_func = (OCITypeParamByName_func_t)dlsym(RTLD_NEXT, "OCITypeParamByName");
    OCITypeParamByPos_func = (OCITypeParamByPos_func_t)dlsym(RTLD_NEXT, "OCITypeParamByPos");
    OCITypeParamPos_func = (OCITypeParamPos_func_t)dlsym(RTLD_NEXT, "OCITypeParamPos");
    OCITypeResult_func = (OCITypeResult_func_t)dlsym(RTLD_NEXT, "OCITypeResult");
    OCITypeSchema_func = (OCITypeSchema_func_t)dlsym(RTLD_NEXT, "OCITypeSchema");
    OCITypeSetBuiltin_func = (OCITypeSetBuiltin_func_t)dlsym(RTLD_NEXT, "OCITypeSetBuiltin");
    OCITypeSetCollection_func = (OCITypeSetCollection_func_t)dlsym(RTLD_NEXT, "OCITypeSetCollection");
    OCITypeTypeCode_func = (OCITypeTypeCode_func_t)dlsym(RTLD_NEXT, "OCITypeTypeCode");
    OCITypeVTInit_func = (OCITypeVTInit_func_t)dlsym(RTLD_NEXT, "OCITypeVTInit");
    OCITypeVTInsert_func = (OCITypeVTInsert_func_t)dlsym(RTLD_NEXT, "OCITypeVTInsert");
    OCITypeVTSelect_func = (OCITypeVTSelect_func_t)dlsym(RTLD_NEXT, "OCITypeVTSelect");
    OCITypeVersion_func = (OCITypeVersion_func_t)dlsym(RTLD_NEXT, "OCITypeVersion");
    is_initialized = 1;
    ocidump_init();
}
