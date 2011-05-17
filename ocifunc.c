/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/*
 * This file was created by mkocifunc.rb
 * Don't edit this file manually.
 */
#include <dlfcn.h>
#include <pthread.h>
#include "ocidump.h"

static int is_initialized;
static void initialize(void);


typedef sword (*OCIAttrGet_func_t)(const dvoid *trgthndlp, ub4 trghndltyp, dvoid *attributep, ub4 *sizep, ub4 attrtype, OCIError *errhp);
static OCIAttrGet_func_t OCIAttrGet_func;
static int trace_OCIAttrGet = 1;

sword OCIAttrGet(const dvoid *trgthndlp, ub4 trghndltyp, dvoid *attributep, ub4 *sizep, ub4 attrtype, OCIError *errhp)
{
    sword ret;
    char buf1[OCIDUMP_NAME_BUF_SIZE];
    char buf2[OCIDUMP_NAME_BUF_SIZE];
    char buf3[OCIDUMP_NAME_BUF_SIZE];
    char buf4[OCIDUMP_NAME_BUF_SIZE];
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
    char buf1[OCIDUMP_NAME_BUF_SIZE];
    char buf2[OCIDUMP_NAME_BUF_SIZE];
    char buf3[OCIDUMP_NAME_BUF_SIZE];
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

typedef sword (*OCIBindByName_func_t)(OCIStmt *stmtp, OCIBind **bindp, OCIError *errhp, const text *placeholder, sb4 placeh_len, dvoid *valuep, sb4 value_sz, ub2 dty, dvoid *indp, ub2 *alenp, ub2 *rcodep, ub4 maxarr_len, ub4 *curelep, ub4 mode);
static OCIBindByName_func_t OCIBindByName_func;
static int trace_OCIBindByName = 1;

sword OCIBindByName(OCIStmt *stmtp, OCIBind **bindp, OCIError *errhp, const text *placeholder, sb4 placeh_len, dvoid *valuep, sb4 value_sz, ub2 dty, dvoid *indp, ub2 *alenp, ub2 *rcodep, ub4 maxarr_len, ub4 *curelep, ub4 mode)
{
    sword ret;
    char buf1[OCIDUMP_NAME_BUF_SIZE];
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
    char buf1[OCIDUMP_NAME_BUF_SIZE];
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

typedef sword (*OCIBindObject_func_t)(OCIBind *bindp, OCIError *errhp, const OCIType *type, dvoid **pgvpp, ub4 *pvszsp, dvoid **indpp, ub4 *indszp);
static OCIBindObject_func_t OCIBindObject_func;
static int trace_OCIBindObject = 1;

sword OCIBindObject(OCIBind *bindp, OCIError *errhp, const OCIType *type, dvoid **pgvpp, ub4 *pvszsp, dvoid **indpp, ub4 *indszp)
{
    sword ret;
    char buf1[OCIDUMP_NAME_BUF_SIZE];
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
    char buf1[OCIDUMP_NAME_BUF_SIZE];
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

typedef sword (*OCIDefineArrayOfStruct_func_t)(OCIDefine *defnp, OCIError *errhp, ub4 pvskip, ub4 indskip, ub4 rlskip, ub4 rcskip);
static OCIDefineArrayOfStruct_func_t OCIDefineArrayOfStruct_func;
static int trace_OCIDefineArrayOfStruct = 1;

sword OCIDefineArrayOfStruct(OCIDefine *defnp, OCIError *errhp, ub4 pvskip, ub4 indskip, ub4 rlskip, ub4 rcskip)
{
    sword ret;
    char buf1[OCIDUMP_NAME_BUF_SIZE];
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
    char buf1[OCIDUMP_NAME_BUF_SIZE];
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

typedef sword (*OCIDefineObject_func_t)(OCIDefine *defnp, OCIError *errhp, const OCIType *type, dvoid **pgvpp, ub4 *pvszsp, dvoid **indpp, ub4 *indszp);
static OCIDefineObject_func_t OCIDefineObject_func;
static int trace_OCIDefineObject = 1;

sword OCIDefineObject(OCIDefine *defnp, OCIError *errhp, const OCIType *type, dvoid **pgvpp, ub4 *pvszsp, dvoid **indpp, ub4 *indszp)
{
    sword ret;
    char buf1[OCIDUMP_NAME_BUF_SIZE];
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
    char buf1[OCIDUMP_NAME_BUF_SIZE];
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
    char buf1[OCIDUMP_NAME_BUF_SIZE];
    char buf2[OCIDUMP_NAME_BUF_SIZE];
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
    char buf1[OCIDUMP_NAME_BUF_SIZE];
    char buf2[OCIDUMP_NAME_BUF_SIZE];
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

typedef sword (*OCIEnvCreate_func_t)(OCIEnv **envp, ub4 mode, dvoid *ctxp, dvoid *(*malocfp)(dvoid *ctxp, size_t size), dvoid *(*ralocfp)(dvoid *ctxp, dvoid *memptr, size_t newsize), void   (*mfreefp)(dvoid *ctxp, dvoid *memptr), size_t xtramem_sz, dvoid **usrmempp);
static OCIEnvCreate_func_t OCIEnvCreate_func;
static int trace_OCIEnvCreate = 1;

sword OCIEnvCreate(OCIEnv **envp, ub4 mode, dvoid *ctxp, dvoid *(*malocfp)(dvoid *ctxp, size_t size), dvoid *(*ralocfp)(dvoid *ctxp, dvoid *memptr, size_t newsize), void   (*mfreefp)(dvoid *ctxp, dvoid *memptr), size_t xtramem_sz, dvoid **usrmempp)
{
    sword ret;
    char buf1[OCIDUMP_NAME_BUF_SIZE];
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
    char buf1[OCIDUMP_NAME_BUF_SIZE];
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
    char buf1[OCIDUMP_NAME_BUF_SIZE];
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
    char buf1[OCIDUMP_NAME_BUF_SIZE];
    char buf2[OCIDUMP_NAME_BUF_SIZE];
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

typedef sword (*OCIHandleAlloc_func_t)(const dvoid *parenth, dvoid **hndlpp, ub4 type, size_t xtramem_sz, dvoid **usrmempp);
static OCIHandleAlloc_func_t OCIHandleAlloc_func;
static int trace_OCIHandleAlloc = 1;

sword OCIHandleAlloc(const dvoid *parenth, dvoid **hndlpp, ub4 type, size_t xtramem_sz, dvoid **usrmempp)
{
    sword ret;
    char buf1[OCIDUMP_NAME_BUF_SIZE];
    char buf2[OCIDUMP_NAME_BUF_SIZE];
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
    char buf1[OCIDUMP_NAME_BUF_SIZE];
    char buf2[OCIDUMP_NAME_BUF_SIZE];
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
    char buf1[OCIDUMP_NAME_BUF_SIZE];
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

typedef sword (*OCILogoff_func_t)(OCISvcCtx *svchp, OCIError *errhp);
static OCILogoff_func_t OCILogoff_func;
static int trace_OCILogoff = 1;

sword OCILogoff(OCISvcCtx *svchp, OCIError *errhp)
{
    sword ret;
    char buf1[OCIDUMP_NAME_BUF_SIZE];
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
    char buf1[OCIDUMP_NAME_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCILogon_func(envhp, errhp, svchp, username, uname_len, password, passwd_len, dbname, dbname_len);
    if (trace_OCILogon) {
        if (ocidump_hide_string) {
            uname_len = 6;
            username = (OraText*)"hidden";
            passwd_len = 6;
            password = (OraText*)"hidden";
            dbname_len = 6;
            dbname = (OraText*)"hidden";
        }
        ocidump_log("%0*lX: OCILogon(%p, %p, [%p], \"%.*s\", %u, \"%.*s\", %u, \"%.*s\", %u) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     envhp,
                     errhp,
                     *svchp,
                     uname_len, username,
                     uname_len,
                     passwd_len, password,
                     passwd_len,
                     dbname_len, dbname,
                     dbname_len,
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
    char buf1[OCIDUMP_NAME_BUF_SIZE];
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

typedef sword (*OCIObjectGetInd_func_t)(OCIEnv *env, OCIError *err, dvoid *instance, dvoid **null_struct);
static OCIObjectGetInd_func_t OCIObjectGetInd_func;
static int trace_OCIObjectGetInd = 1;

sword OCIObjectGetInd(OCIEnv *env, OCIError *err, dvoid *instance, dvoid **null_struct)
{
    sword ret;
    char buf1[OCIDUMP_NAME_BUF_SIZE];
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

typedef sword (*OCIObjectNew_func_t)(OCIEnv *env, OCIError *err, const OCISvcCtx *svc, OCITypeCode typecode, OCIType *tdo, dvoid *table, OCIDuration duration, boolean value, dvoid **instance);
static OCIObjectNew_func_t OCIObjectNew_func;
static int trace_OCIObjectNew = 1;

sword OCIObjectNew(OCIEnv *env, OCIError *err, const OCISvcCtx *svc, OCITypeCode typecode, OCIType *tdo, dvoid *table, OCIDuration duration, boolean value, dvoid **instance)
{
    sword ret;
    char buf1[OCIDUMP_NAME_BUF_SIZE];
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

typedef sword (*OCIObjectPin_func_t)(OCIEnv *env, OCIError *err, OCIRef *object_ref, OCIComplexObject *corhdl, OCIPinOpt pin_option, OCIDuration pin_duration, OCILockOpt lock_option, dvoid **object);
static OCIObjectPin_func_t OCIObjectPin_func;
static int trace_OCIObjectPin = 1;

sword OCIObjectPin(OCIEnv *env, OCIError *err, OCIRef *object_ref, OCIComplexObject *corhdl, OCIPinOpt pin_option, OCIDuration pin_duration, OCILockOpt lock_option, dvoid **object)
{
    sword ret;
    char buf1[OCIDUMP_NAME_BUF_SIZE];
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

typedef sword (*OCIObjectUnpin_func_t)(OCIEnv *env, OCIError *err, dvoid *object);
static OCIObjectUnpin_func_t OCIObjectUnpin_func;
static int trace_OCIObjectUnpin = 1;

sword OCIObjectUnpin(OCIEnv *env, OCIError *err, dvoid *object)
{
    sword ret;
    char buf1[OCIDUMP_NAME_BUF_SIZE];
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
    char buf1[OCIDUMP_NAME_BUF_SIZE];
    char buf2[OCIDUMP_NAME_BUF_SIZE];
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

typedef sword (*OCIPing_func_t)(OCISvcCtx *svchp, OCIError *errhp, ub4 mode);
static OCIPing_func_t OCIPing_func;
static int trace_OCIPing = 1;

sword OCIPing(OCISvcCtx *svchp, OCIError *errhp, ub4 mode)
{
    sword ret;
    char buf1[OCIDUMP_NAME_BUF_SIZE];
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

typedef sword (*OCIReset_func_t)(dvoid *hndlp, OCIError *errhp);
static OCIReset_func_t OCIReset_func;
static int trace_OCIReset = 1;

sword OCIReset(dvoid *hndlp, OCIError *errhp)
{
    sword ret;
    char buf1[OCIDUMP_NAME_BUF_SIZE];
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

typedef sword (*OCIServerAttach_func_t)(OCIServer *srvhp, OCIError *errhp, CONST text *dblink, sb4 dblink_len, ub4 mode);
static OCIServerAttach_func_t OCIServerAttach_func;
static int trace_OCIServerAttach = 1;

sword OCIServerAttach(OCIServer *srvhp, OCIError *errhp, CONST text *dblink, sb4 dblink_len, ub4 mode)
{
    sword ret;
    char buf1[OCIDUMP_NAME_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIServerAttach_func(srvhp, errhp, dblink, dblink_len, mode);
    if (trace_OCIServerAttach) {
        if (ocidump_hide_string) {
            dblink_len = 6;
            dblink = (OraText*)"hidden";
        }
        ocidump_log("%0*lX: OCIServerAttach(%p, %p, \"%.*s\", %d, 0x%x) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     srvhp,
                     errhp,
                     dblink_len, dblink,
                     dblink_len,
                     mode,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIServerDetach_func_t)(OCIServer *srvhp, OCIError *errhp, ub4 mode);
static OCIServerDetach_func_t OCIServerDetach_func;
static int trace_OCIServerDetach = 1;

sword OCIServerDetach(OCIServer *srvhp, OCIError *errhp, ub4 mode)
{
    sword ret;
    char buf1[OCIDUMP_NAME_BUF_SIZE];
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
    char buf1[OCIDUMP_NAME_BUF_SIZE];
    char buf2[OCIDUMP_NAME_BUF_SIZE];
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
    char buf1[OCIDUMP_NAME_BUF_SIZE];
    char buf2[OCIDUMP_NAME_BUF_SIZE];
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
    char buf1[OCIDUMP_NAME_BUF_SIZE];
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
    char buf1[OCIDUMP_NAME_BUF_SIZE];
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

typedef sword (*OCIStmtExecute_func_t)(OCISvcCtx *svchp, OCIStmt *stmtp, OCIError *errhp, ub4 iters, ub4 rowoff, const OCISnapshot *snap_in, OCISnapshot *snap_out, ub4 mode);
static OCIStmtExecute_func_t OCIStmtExecute_func;
static int trace_OCIStmtExecute = 1;

sword OCIStmtExecute(OCISvcCtx *svchp, OCIStmt *stmtp, OCIError *errhp, ub4 iters, ub4 rowoff, const OCISnapshot *snap_in, OCISnapshot *snap_out, ub4 mode)
{
    sword ret;
    char buf1[OCIDUMP_NAME_BUF_SIZE];
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
    char buf1[OCIDUMP_NAME_BUF_SIZE];
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

typedef sword (*OCIStmtGetPieceInfo_func_t)(OCIStmt *stmtp, OCIError *errhp, dvoid **hndlpp, ub4 *typep, ub1 *in_outp, ub4 *iterp, ub4 *idxp, ub1 *piecep);
static OCIStmtGetPieceInfo_func_t OCIStmtGetPieceInfo_func;
static int trace_OCIStmtGetPieceInfo = 1;

sword OCIStmtGetPieceInfo(OCIStmt *stmtp, OCIError *errhp, dvoid **hndlpp, ub4 *typep, ub1 *in_outp, ub4 *iterp, ub4 *idxp, ub1 *piecep)
{
    sword ret;
    char buf1[OCIDUMP_NAME_BUF_SIZE];
    char buf2[OCIDUMP_NAME_BUF_SIZE];
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
    char buf1[OCIDUMP_NAME_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIStmtPrepare_func(stmtp, errhp, stmt, stmt_len, language, mode);
    if (trace_OCIStmtPrepare) {
        if (ocidump_hide_string) {
            stmt_len = 6;
            stmt = (OraText*)"hidden";
        }
        ocidump_log("%0*lX: OCIStmtPrepare(%p, %p, \"%.*s\", %u, %u, 0x%x) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     stmtp,
                     errhp,
                     stmt_len, stmt,
                     stmt_len,
                     language,
                     mode,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIStmtPrepare2_func_t)(OCISvcCtx *svchp, OCIStmt **stmtp, OCIError *errhp, const OraText *stmt, ub4 stmt_len, const OraText *key, ub4 key_len, ub4 language, ub4 mode);
static OCIStmtPrepare2_func_t OCIStmtPrepare2_func;
static int trace_OCIStmtPrepare2 = 1;

sword OCIStmtPrepare2(OCISvcCtx *svchp, OCIStmt **stmtp, OCIError *errhp, const OraText *stmt, ub4 stmt_len, const OraText *key, ub4 key_len, ub4 language, ub4 mode)
{
    sword ret;
    char buf1[OCIDUMP_NAME_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIStmtPrepare2_func(svchp, stmtp, errhp, stmt, stmt_len, key, key_len, language, mode);
    if (trace_OCIStmtPrepare2) {
        if (ocidump_hide_string) {
            stmt_len = 6;
            stmt = (OraText*)"hidden";
            key_len = 6;
            key = (OraText*)"hidden";
        }
        ocidump_log("%0*lX: OCIStmtPrepare2(%p, [%p], %p, \"%.*s\", %u, \"%.*s\", %u, %u, 0x%x) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     svchp,
                     *stmtp,
                     errhp,
                     stmt_len, stmt,
                     stmt_len,
                     key_len, key,
                     key_len,
                     language,
                     mode,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIStmtRelease_func_t)(OCIStmt *stmtp, OCIError *errhp, const OraText *key, ub4 key_len, ub4 mode);
static OCIStmtRelease_func_t OCIStmtRelease_func;
static int trace_OCIStmtRelease = 1;

sword OCIStmtRelease(OCIStmt *stmtp, OCIError *errhp, const OraText *key, ub4 key_len, ub4 mode)
{
    sword ret;
    char buf1[OCIDUMP_NAME_BUF_SIZE];
    if (!is_initialized) {
        initialize();
    }
    ret = OCIStmtRelease_func(stmtp, errhp, key, key_len, mode);
    if (trace_OCIStmtRelease) {
        if (ocidump_hide_string) {
            key_len = 6;
            key = (OraText*)"hidden";
        }
        ocidump_log("%0*lX: OCIStmtRelease(%p, %p, \"%.*s\", %u, 0x%x) => %s\n",
                     (int)sizeof(pthread_t), pthread_self(),
                     stmtp,
                     errhp,
                     key_len, key,
                     key_len,
                     mode,
                     ocidump_status2name(ret, buf1));
    }
    return ret;
}

typedef sword (*OCIStmtSetPieceInfo_func_t)(dvoid *hndlp, ub4 type, OCIError *errhp, CONST dvoid *bufp, ub4 *alenp, ub1 piece, CONST dvoid *indp, ub2 *rcodep);
static OCIStmtSetPieceInfo_func_t OCIStmtSetPieceInfo_func;
static int trace_OCIStmtSetPieceInfo = 1;

sword OCIStmtSetPieceInfo(dvoid *hndlp, ub4 type, OCIError *errhp, CONST dvoid *bufp, ub4 *alenp, ub1 piece, CONST dvoid *indp, ub2 *rcodep)
{
    sword ret;
    char buf1[OCIDUMP_NAME_BUF_SIZE];
    char buf2[OCIDUMP_NAME_BUF_SIZE];
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

typedef sword (*OCITransCommit_func_t)(OCISvcCtx *svchp, OCIError *errhp, ub4 flags);
static OCITransCommit_func_t OCITransCommit_func;
static int trace_OCITransCommit = 1;

sword OCITransCommit(OCISvcCtx *svchp, OCIError *errhp, ub4 flags)
{
    sword ret;
    char buf1[OCIDUMP_NAME_BUF_SIZE];
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
    char buf1[OCIDUMP_NAME_BUF_SIZE];
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

ocidump_target_t ocidump_targets[] = {
    {"OCIAttrGet", &trace_OCIAttrGet},
    {"OCIAttrSet", &trace_OCIAttrSet},
    {"OCIBindByName", &trace_OCIBindByName},
    {"OCIBindByPos", &trace_OCIBindByPos},
    {"OCIBindObject", &trace_OCIBindObject},
    {"OCIBreak", &trace_OCIBreak},
    {"OCIClientVersion", &trace_OCIClientVersion},
    {"OCIDefineArrayOfStruct", &trace_OCIDefineArrayOfStruct},
    {"OCIDefineByPos", &trace_OCIDefineByPos},
    {"OCIDefineObject", &trace_OCIDefineObject},
    {"OCIDescribeAny", &trace_OCIDescribeAny},
    {"OCIDescriptorAlloc", &trace_OCIDescriptorAlloc},
    {"OCIDescriptorFree", &trace_OCIDescriptorFree},
    {"OCIEnvCreate", &trace_OCIEnvCreate},
    {"OCIEnvInit", &trace_OCIEnvInit},
    {"OCIEnvNlsCreate", &trace_OCIEnvNlsCreate},
    {"OCIErrorGet", &trace_OCIErrorGet},
    {"OCIHandleAlloc", &trace_OCIHandleAlloc},
    {"OCIHandleFree", &trace_OCIHandleFree},
    {"OCIInitialize", &trace_OCIInitialize},
    {"OCILogoff", &trace_OCILogoff},
    {"OCILogon", &trace_OCILogon},
    {"OCIObjectFree", &trace_OCIObjectFree},
    {"OCIObjectGetInd", &trace_OCIObjectGetInd},
    {"OCIObjectNew", &trace_OCIObjectNew},
    {"OCIObjectPin", &trace_OCIObjectPin},
    {"OCIObjectUnpin", &trace_OCIObjectUnpin},
    {"OCIParamGet", &trace_OCIParamGet},
    {"OCIPing", &trace_OCIPing},
    {"OCIReset", &trace_OCIReset},
    {"OCIServerAttach", &trace_OCIServerAttach},
    {"OCIServerDetach", &trace_OCIServerDetach},
    {"OCIServerRelease", &trace_OCIServerRelease},
    {"OCIServerVersion", &trace_OCIServerVersion},
    {"OCISessionBegin", &trace_OCISessionBegin},
    {"OCISessionEnd", &trace_OCISessionEnd},
    {"OCIStmtExecute", &trace_OCIStmtExecute},
    {"OCIStmtFetch", &trace_OCIStmtFetch},
    {"OCIStmtGetPieceInfo", &trace_OCIStmtGetPieceInfo},
    {"OCIStmtPrepare", &trace_OCIStmtPrepare},
    {"OCIStmtPrepare2", &trace_OCIStmtPrepare2},
    {"OCIStmtRelease", &trace_OCIStmtRelease},
    {"OCIStmtSetPieceInfo", &trace_OCIStmtSetPieceInfo},
    {"OCITransCommit", &trace_OCITransCommit},
    {"OCITransRollback", &trace_OCITransRollback},
    {NULL, NULL},
};

static void initialize(void)
{
    OCIAttrGet_func = (OCIAttrGet_func_t)dlsym(RTLD_NEXT, "OCIAttrGet");
    OCIAttrSet_func = (OCIAttrSet_func_t)dlsym(RTLD_NEXT, "OCIAttrSet");
    OCIBindByName_func = (OCIBindByName_func_t)dlsym(RTLD_NEXT, "OCIBindByName");
    OCIBindByPos_func = (OCIBindByPos_func_t)dlsym(RTLD_NEXT, "OCIBindByPos");
    OCIBindObject_func = (OCIBindObject_func_t)dlsym(RTLD_NEXT, "OCIBindObject");
    OCIBreak_func = (OCIBreak_func_t)dlsym(RTLD_NEXT, "OCIBreak");
    OCIClientVersion_func = (OCIClientVersion_func_t)dlsym(RTLD_NEXT, "OCIClientVersion");
    OCIDefineArrayOfStruct_func = (OCIDefineArrayOfStruct_func_t)dlsym(RTLD_NEXT, "OCIDefineArrayOfStruct");
    OCIDefineByPos_func = (OCIDefineByPos_func_t)dlsym(RTLD_NEXT, "OCIDefineByPos");
    OCIDefineObject_func = (OCIDefineObject_func_t)dlsym(RTLD_NEXT, "OCIDefineObject");
    OCIDescribeAny_func = (OCIDescribeAny_func_t)dlsym(RTLD_NEXT, "OCIDescribeAny");
    OCIDescriptorAlloc_func = (OCIDescriptorAlloc_func_t)dlsym(RTLD_NEXT, "OCIDescriptorAlloc");
    OCIDescriptorFree_func = (OCIDescriptorFree_func_t)dlsym(RTLD_NEXT, "OCIDescriptorFree");
    OCIEnvCreate_func = (OCIEnvCreate_func_t)dlsym(RTLD_NEXT, "OCIEnvCreate");
    OCIEnvInit_func = (OCIEnvInit_func_t)dlsym(RTLD_NEXT, "OCIEnvInit");
    OCIEnvNlsCreate_func = (OCIEnvNlsCreate_func_t)dlsym(RTLD_NEXT, "OCIEnvNlsCreate");
    OCIErrorGet_func = (OCIErrorGet_func_t)dlsym(RTLD_NEXT, "OCIErrorGet");
    OCIHandleAlloc_func = (OCIHandleAlloc_func_t)dlsym(RTLD_NEXT, "OCIHandleAlloc");
    OCIHandleFree_func = (OCIHandleFree_func_t)dlsym(RTLD_NEXT, "OCIHandleFree");
    OCIInitialize_func = (OCIInitialize_func_t)dlsym(RTLD_NEXT, "OCIInitialize");
    OCILogoff_func = (OCILogoff_func_t)dlsym(RTLD_NEXT, "OCILogoff");
    OCILogon_func = (OCILogon_func_t)dlsym(RTLD_NEXT, "OCILogon");
    OCIObjectFree_func = (OCIObjectFree_func_t)dlsym(RTLD_NEXT, "OCIObjectFree");
    OCIObjectGetInd_func = (OCIObjectGetInd_func_t)dlsym(RTLD_NEXT, "OCIObjectGetInd");
    OCIObjectNew_func = (OCIObjectNew_func_t)dlsym(RTLD_NEXT, "OCIObjectNew");
    OCIObjectPin_func = (OCIObjectPin_func_t)dlsym(RTLD_NEXT, "OCIObjectPin");
    OCIObjectUnpin_func = (OCIObjectUnpin_func_t)dlsym(RTLD_NEXT, "OCIObjectUnpin");
    OCIParamGet_func = (OCIParamGet_func_t)dlsym(RTLD_NEXT, "OCIParamGet");
    OCIPing_func = (OCIPing_func_t)dlsym(RTLD_NEXT, "OCIPing");
    OCIReset_func = (OCIReset_func_t)dlsym(RTLD_NEXT, "OCIReset");
    OCIServerAttach_func = (OCIServerAttach_func_t)dlsym(RTLD_NEXT, "OCIServerAttach");
    OCIServerDetach_func = (OCIServerDetach_func_t)dlsym(RTLD_NEXT, "OCIServerDetach");
    OCIServerRelease_func = (OCIServerRelease_func_t)dlsym(RTLD_NEXT, "OCIServerRelease");
    OCIServerVersion_func = (OCIServerVersion_func_t)dlsym(RTLD_NEXT, "OCIServerVersion");
    OCISessionBegin_func = (OCISessionBegin_func_t)dlsym(RTLD_NEXT, "OCISessionBegin");
    OCISessionEnd_func = (OCISessionEnd_func_t)dlsym(RTLD_NEXT, "OCISessionEnd");
    OCIStmtExecute_func = (OCIStmtExecute_func_t)dlsym(RTLD_NEXT, "OCIStmtExecute");
    OCIStmtFetch_func = (OCIStmtFetch_func_t)dlsym(RTLD_NEXT, "OCIStmtFetch");
    OCIStmtGetPieceInfo_func = (OCIStmtGetPieceInfo_func_t)dlsym(RTLD_NEXT, "OCIStmtGetPieceInfo");
    OCIStmtPrepare_func = (OCIStmtPrepare_func_t)dlsym(RTLD_NEXT, "OCIStmtPrepare");
    OCIStmtPrepare2_func = (OCIStmtPrepare2_func_t)dlsym(RTLD_NEXT, "OCIStmtPrepare2");
    OCIStmtRelease_func = (OCIStmtRelease_func_t)dlsym(RTLD_NEXT, "OCIStmtRelease");
    OCIStmtSetPieceInfo_func = (OCIStmtSetPieceInfo_func_t)dlsym(RTLD_NEXT, "OCIStmtSetPieceInfo");
    OCITransCommit_func = (OCITransCommit_func_t)dlsym(RTLD_NEXT, "OCITransCommit");
    OCITransRollback_func = (OCITransRollback_func_t)dlsym(RTLD_NEXT, "OCITransRollback");
    is_initialized = 1;
    ocidump_init();
}
