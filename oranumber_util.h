/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/*
 * oranumber_util.h - copied from ruby-oci8
 *
 * Copyright (C) 2010-2011 Kubo Takehiro <kubo@jiubao.org>
 */
#ifndef ORANUMBER_UTIL_H
#define ORANUMBER_UTIL_H 1

#define ORANUMBER_INVALID_INTERNAL_FORMAT -1
#define ORANUMBER_TOO_SHORT_BUFFER -2

#define ORANUMBER_SUCCESS 0
#define ORANUMBER_INVALID_NUMBER 1722
#define ORANUMBER_NUMERIC_OVERFLOW 1426

int ocidump_oranumber_to_str(const OCINumber *on, char *buf, int buflen);

#define ORANUMBER_DUMP_BUF_SIZ 99
int ocidump_oranumber_dump(const OCINumber *on, char *buf);

#endif
