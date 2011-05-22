#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#include <dlfcn.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "ocidump.h"

#ifdef __linux
#define HAVE_ASPRINTF
#endif

#ifndef _WIN32
static pthread_once_t init_once = PTHREAD_ONCE_INIT;
#endif

#define OUT_OF_MEMORY_MSG "... out of memory ..."

int ocidump_hide_string = 0;
int ocidump_is_initialized;

static FILE *logfp;

static void ocidump_do_init(void)
{
    char *val;

    if (ocidump_is_initialized) {
        return;
    }
    val = getenv("OCIDUMP_HIDE_STRING");
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

            /* clear all hooks */
            for (i = 0; ocidump_hooks[i].name != NULL; i++) {
                *ocidump_hooks[i].flags = 0;
            }

            while (fgets(buf, sizeof(buf), fp) != NULL) {
                size_t len = strlen(buf);
                while (len > 0 && (buf[len - 1] == '\n' || buf[len - 1] == '\r')) {
                    buf[len - 1] = '\0';
                }
                for (i = 0; ocidump_hooks[i].name != NULL; i++) {
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
    ocidump_setup_win32_api_hook();
#else
    {
        int i;
        for (i = 0; ocidump_hooks[i].name != NULL; i++) {
            *ocidump_hooks[i].orig_func = dlsym(RTLD_NEXT, ocidump_hooks[i].name);
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

const char *ocidump_attrtype2name(ub4 htype, ub4 attrtype, char *buf)
{
    if (htype >= OCI_DTYPE_FIRST) {
        const char *rval = ocidump_dtypeattr2name(attrtype);
        if (rval != NULL) {
            return rval;
        }
    }
    return ocidump_htypeattr2name(attrtype, buf);
}

const char *ocidump_ocinumber(char *buf, const OCINumber *on)
{
    int idx;
    int len = on->OCINumberPart[0];
    int offset;

    offset = sprintf(buf, "Len=%u: ", len);
    if (len > 21) {
        len = 21;
    }
    for (idx = 1; idx <= len; idx++) {
        offset += sprintf(buf + offset, "%u,", (ub4)on->OCINumberPart[idx]);
    }
    buf[--offset] = '\0';
    return buf;
}

const char *ocidump_quotestring(char **buf, const OraText *str, ub4 len)
{
    ub4 idx;
    ub4 cnt;

    if (ocidump_hide_string) {
        return "--hidden--";
    }

    if (str == NULL) {
        return "(nil)";
    }
    for (idx = cnt = 0; idx < len; idx++) {
        if (str[idx] == '"') {
            cnt++;
        }
    }
    *buf = malloc(len + cnt + 3);
    if (*buf == NULL) {
        return OUT_OF_MEMORY_MSG;
    }
    (*buf)[0] = '"';
    for (idx = cnt = 0; idx < len; idx++) {
        (*buf)[idx + cnt + 1] = str[idx];
        if (str[idx] == '"') {
            cnt++;
            (*buf)[idx + cnt + 1] = str[idx];
        }
    }
    (*buf)[idx + cnt + 1] = '"';
    (*buf)[idx + cnt + 2] = '\0';
    return *buf;
}

const char *ocidump_quotestring2(char **buf, OraText **str, ub4 *len)
{
    ub4 idx;
    ub4 cnt;

    if (ocidump_hide_string) {
        return "--hidden--";
    }

    if (str == NULL) {
        return "(nil)";
    }
    if (*str == NULL) {
        return "[(nil)]";
    }
    for (idx = cnt = 0; idx < *len; idx++) {
        if ((*str)[idx] == '"') {
            cnt++;
        }
    }
    *buf = malloc(*len + cnt + 5);
    if (*buf == NULL) {
        return OUT_OF_MEMORY_MSG;
    }
    (*buf)[0] = '"';
    (*buf)[1] = '[';
    for (idx = cnt = 0; idx < *len; idx++) {
        (*buf)[idx + cnt + 2] = (*str)[idx];
        if ((*str)[idx] == '"') {
            cnt++;
            (*buf)[idx + cnt + 2] = (*str)[idx];
        }
    }
    (*buf)[idx + cnt + 2] = ']';
    (*buf)[idx + cnt + 3] = '"';
    (*buf)[idx + cnt + 4] = '\0';
    return *buf;
}

const char *ocidump_sprintf(char *buf, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vsprintf(buf, fmt, ap);
    va_end(ap);
    return buf;
}

const char *ocidump_asprintf(char **buf, const char *fmt, ...)
{
#ifdef HAVE_VASPRINTF
    va_list ap;
    va_start(ap, fmt);
    vasprintf(buf, fmt, ap);
    va_end(ap);
    return *buf ? *buf : OUT_OF_MEMORY_MSG;
#else
    int size = strlen(fmt) + 32;
    char *ptr;

    if ((ptr = malloc(size)) == NULL) {
        return OUT_OF_MEMORY_MSG;
    }

    while (1) {
        va_list ap;
        int n;
        char *new_ptr;

        va_start(ap, fmt);
        n = vsnprintf(ptr, size, fmt, ap);
        va_end(ap);
        if (n > -1 && n < size) {
            *buf = ptr;
            return ptr;
        }
        if (n > -1) {
            size = n + 1;
        } else {
            size *= 2;
        }
        if ((new_ptr = realloc(ptr, size)) == NULL) {
            free(ptr);
            return OUT_OF_MEMORY_MSG;
        } else {
            ptr = new_ptr;
        }
    }
#endif
}

void ocidump_log(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(logfp, fmt, ap);
    va_end(ap);
}
