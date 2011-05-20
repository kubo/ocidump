#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "ocidump.h"
#include "ocidefs.h"

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
        return "... out of memory ...";
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
        return "... out of memory ...";
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
    va_list ap;
    va_start(ap, fmt);
    vasprintf(buf, fmt, ap);
    va_end(ap);
    return *buf ? *buf : "";
}

void ocidump_log(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(logfp, fmt, ap);
    va_end(ap);
}
