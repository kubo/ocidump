Oracle OCI Dumper
=================

What is this.
---------------

Tracing utility to monitor Oracle OCI function calls.
This is useful for OCI developers to debug your programs.

What is different from others.
------------------------------

There are similar utilities such as [ocitrace][1] and
[ocispy][2]. They use [User-Defined Callback Functions in OCI][3] to
monitor OCI function calls. But it is not perfect. Some OCI functions
call other OCI functions internally. Such internal calls, which are
not executed by an application, also fire user-defined callback
functions. So these utilities cannot monitor function calls exactly
issued by Oracle client applications.

Ocidump uses another methods to monitor OCI functions. It uses LD_PRELOAD
on Unix and IAT hooking or DLL substitution on Windows. It can monitor
function calls exactly as they are issued. Note that there is an exception
that the first call of OCIEnvCreate() or similar functions is not monitored
by IAT hooking on Windows. It is due to the timing of loading ocidump.dll
into process memory.

Supported platforms
-------------------

Linux, Solaris, OS X and Windows

How to compile
----------

### Unix

Install ruby if it isn't installed.

Run `make` to compile ocidump on Linux or OS X. Run `gmake` on Solaris.

Ocidump hooks `dlsym` on linux and solaris for programs which bind OCI
functions at runtime via `dlsym`. However I received a mail saying that
it caused SEGV. If you have trouble, add `-DDISABLE_DYSYM_HOOK` to `CFLAGS`
in `Makefile`.

### Windows

Install ruby if it isn't installed.

Ocidump supports the following two hooking methods on Windows.

1. [IAT hooking](#windows-iat-hooking)
2. [DLL substitution](#windows-dll-substitution)

Run `nmake -f win32.mak` if you use the former only.

If you use both or the latter, run the following command to create
.def files prior to `nmake -f win32.mak`.

If oci.dll is in `c:\oracle\instantclient_12_1`,

    ruby mkdef.rb c:\oracle\instantclient_12_1\oci.dll

How to use
----------

### Unix

Set the environment variable `LD_PRELOAD` to point to `libocidump.so` and
run a Oracle client application.

    export LD_PRELOAD=/foo/bar/libocidump.so
    sqlplus scott/tiger

### Windows (IAT hooking)

1. Copy ocidump.dll to the directory containing oci.dll.
2. Set the environment variable `ORA_OCI_UCBPKG=ocidump`.

If oci.dll is in `c:\oracle\instantclient_12_1`,

    copy ocidump.dll c:\oracle\instantclient_12_1\ocidump.dll
    set ORA_OCI_UCBPKG=ocidump
    sqlplus scott/tiger

This method hooks function calls invoked via IAT(Import Address Table).
It doesn't work for applications which dynamically resolve OCI
functions by `GetProcAddress` such as Toad. Use the next method for
such applications.

### Windows (DLL substitution)

1. Rename oci.dll to oci-orig.dll.
2. Copy ocidump.dll as oci.dll.
2. Set the environment variable `OCIDUMP_ENABLE=1`.

If oci.dll is in `c:\oracle\instantclient_12_1`,

    move c:\oracle\instantclient_12_1\oci.dll c:\oracle\instantclient_12_1\oci-orig.dll 
    copy ocidump.dll c:\oracle\instantclient_12_1\oci.dll
    set OCIDUMP_ENABLE=1
    sqlplus scott/tiger

Be careful when you move or copy DLLs. Don't delete or overwrite the original oci.dll.

When an application calls OCI functions, functions in ocidump.dll copied
as oci.dll are invoked and ocidump.dll logs function calls and forwards
them to oci-orig.dll.

If `OCIDUMP_ENABLE=1` isn't set, ocidump.dll just forwards function calls to
oci-orig.dll and do nothing else.

Note that the ocidump.dll needs to be compiled for the original oci.dll.
If you use other Oracle client versions, you need to recreate .def files by
`mkdef.rb` and recompile ocidump.dll.

Configuration Environment Variables
-----------------------------------

### OCIDUMP_LOGFILE

OCI function calls are dumped to the standard error by default.
Set `OCIDUMP_LOGFILE` to log them to a file.

    # UNIX
    export OCIDUMP_LOGFILE=/tmp/ocidump.log
    
    # Windows
    set OCIDUMP_LOGFILE=%TEMP%\ocidump.log

### OCIDUMP_CONFIG

All supported OCI functions are dumped by default. The output may be
verbose because it needs several function calls to issue a single SQL
statement. Set `OCIDUMP_CONFIG` to point to a file which contains
functions to be monitored.

    $ cat ocidump.cfg
    # monitor only the following two functions.
    OCIStmtPrepare
    OCIStmtPrepare2
    
    $ export OCIDUMP_CONFIG=ocidump.cfg

### OCIDUMP_TRACE_HANDLE

OCI handles are printed as pointer addresses by default as follows.

```
 8211: OCIStmtPrepare2(0x1d1c188, [0x1d46b88], 0x1d1b128, "SELECT DECODE(USER, 'XS$NULL',  XS_SYS_CONTEXT('XS$SESSION','USERNAME'), USER) FROM DUAL\0", 89, (nil), 0, OCI_NTV_SYNTAX, 32) => OCI_SUCCESS
 8211: OCIStmtExecute(0x1d1c188, 0x1d46b88, 0x1d1b128, 0, 0, (nil), (nil), 0x0) => OCI_SUCCESS
 8211: OCIDefineByPos2(0x1d46b88, [0x1d46900], 0x1d1b128, 1, 0x1c88dd8, 31, SQLT_STR, (nil), 0x7fff9eeb5750, (nil), 0x0) => OCI_SUCCESS
 8211: OCIStmtFetch(0x1d46b88, 0x1d1b128, 1, OCI_FETCH_NEXT, 0) => OCI_SUCCESS
  ...
 8211: OCIStmtRelease(0x1d46b88, 0x1d1b128, (nil), 0, 0) => OCI_SUCCESS

```

If `OCIDUMP_TRACE_HANDLE=1` is set, handles are printed with type and
serial number. For example `SVCCTX_1(0x1d1c188)` and `STMT_3(0x1d46b88)`
are the first service context handle and the third statement handle
respectively.

```
 8211: OCIStmtPrepare2(SVCCTX_1(0x1d1c188), [STMT_3(0x1d46b88)], ERROR_1(0x1d1b128), "SELECT DECODE(USER, 'XS$NULL',  XS_SYS_CONTEXT('XS$SESSION','USERNAME'), USER) FROM DUAL\0", 89, (nil), 0, OCI_NTV_SYNTAX, 32) => OCI_SUCCESS
 8211: OCIStmtExecute(SVCCTX_1(0x1d1c188), STMT_3(0x1d46b88), ERROR_1(0x1d1b128), 0, 0, (nil), (nil), 0x0) => OCI_SUCCESS
 8211: OCIDefineByPos2(STMT_3(0x1d46b88), [0x1d46900], ERROR_1(0x1d1b128), 1, 0x1c88dd8, 31, SQLT_STR, (nil), 0x7fff9eeb5750, (nil), 0x0) => OCI_SUCCESS
 8211: OCIStmtFetch(STMT_3(0x1d46b88), ERROR_1(0x1d1b128), 1, OCI_FETCH_NEXT, 0) => OCI_SUCCESS
  ...
 8211: OCIStmtRelease(STMT_3(0x1d46b88), ERROR_1(0x1d1b128), (nil), 0, 0) => OCI_SUCCESS
```

Note that this may cause memory leaks. ocidump tries to trace all
handle allocations and deletions. However some handle deletions
cannot be caught and the information about it remains in ocidump
memory until the process termination.

### OCIDUMP_HIDE_STRING

If you are an application user who is requested to send a trace log by
application developers, set `OCIDUMP_HIDE_STRING` to hide sensitive
data. It hides all string data such as user name, password, SQL
statements and so on.

    export OCIDUMP_HIDE_STRING=1

[1]: http://sourceforge.net/projects/ocitrace/
[2]: http://www.reocities.com/ocispy/
[3]: http://download.oracle.com/docs/cd/B28359_01/appdev.111/b28395/oci09adv.htm#i466264
