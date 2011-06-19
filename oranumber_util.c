/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*-
 * oranumber_util.h - copied from ruby-oci8
 *
 * Copyright (C) 2010-2011 Kubo Takehiro <kubo@jiubao.org>
 */
#include <stdio.h>
#include <string.h>
#include "ocidump.h"
#include "oranumber_util.h"

int ocidump_oranumber_to_str(const OCINumber *on, char *buf, int buflen)
{
    signed char exponent;
    signed char mantissa[21]; /* terminated by a negative number */
    int datalen = on->OCINumberPart[0];
    int len = 0;
    int idx;
    int n;
#define PUTC(chr) do { \
    if (len < buflen) { \
        buf[len++] = (chr); \
    } else { \
        return ORANUMBER_TOO_SHORT_BUFFER; \
    } \
} while(0)
#define PUTEND() do { \
    if (len < buflen) { \
        buf[len] = '\0'; \
    } else { \
        return ORANUMBER_TOO_SHORT_BUFFER; \
    } \
} while(0)

    if (datalen == 0) {
        /* too short */
        return -1;
    }
    if (datalen == 1) {
        if (on->OCINumberPart[1] == 0x80) {
            /* zero */
            PUTC('0');
            PUTEND();
            return 1;
        }
        if (on->OCINumberPart[1] == 0) {
            /* negative infinity */
            PUTC('-');
            PUTC('~');
            PUTEND();
            return 2;
        }
        /* unexpected format */
        return -1;
    }
    if (datalen == 2) {
        if (on->OCINumberPart[1] == 255 && on->OCINumberPart[2] == 101) {
            /* positive infinity */
            PUTC('~');
            PUTEND();
            return 1;
        }
    }
    if (datalen > 21) {
        /* too long */
        return -1;
    }
    /* normalize exponent and mantissa */
    if (on->OCINumberPart[1] >= 128) {
        /* positive number */
        exponent = on->OCINumberPart[1] - 193;
        for (idx = 0; idx < on->OCINumberPart[0] - 1; idx++) {
            mantissa[idx] = on->OCINumberPart[idx + 2] - 1;
        }
        mantissa[idx] = -1;
    } else {
        /* negative number */
        exponent = 62 - on->OCINumberPart[1];
        for (idx = 0; idx < on->OCINumberPart[0] - 1; idx++) {
            mantissa[idx] = 101 - on->OCINumberPart[idx + 2];
        }
        mantissa[idx] = -1;
        PUTC('-');
    }
    /* convert exponent and mantissa to human readable number */
    idx = 0;
    if (exponent-- >= 0) {
        /* integer part */
        n = mantissa[idx++];
        if (n / 10 != 0) {
            PUTC(n / 10 + '0');
        }
        PUTC(n % 10 + '0');
        while (exponent-- >= 0) {
            n = mantissa[idx++];
            if (n < 0) {
                do {
                    PUTC('0');
                    PUTC('0');
                } while (exponent-- >= 0);
                PUTEND();
                return len;
            }
            PUTC(n / 10 + '0');
            PUTC(n % 10 + '0');
        }
        if (mantissa[idx] < 0) {
            PUTEND();
            return len;
        }
    } else {
        PUTC('0');
    }
    PUTC('.');
    /* fractional number part */
    while (++exponent < -1) {
        PUTC('0');
        PUTC('0');
    }
    while ((n = mantissa[idx++]) >= 0) {
        PUTC(n / 10 + '0');
        PUTC(n % 10 + '0');
    }
    if (buf[len - 1] == '0') {
        len--;
    }
    PUTEND();
    return len;
}

int ocidump_oranumber_dump(const OCINumber *on, char *buf)
{
    int idx;
    int len = on->OCINumberPart[0];
    int offset;

    offset = sprintf(buf, "Typ=2 Len=%u: ", len);
    if (len > 21) {
        len = 21;
    }
    for (idx = 1; idx <= len; idx++) {
        offset += sprintf(buf + offset, "%u,", (ub4)on->OCINumberPart[idx]);
    }
    buf[--offset] = '\0';
    return offset;
}
