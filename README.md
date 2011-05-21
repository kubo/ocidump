Oracle OCI Dumper
=================

What's is this.
---------------

Tracing utility to monitor Oracle OCI function calls.
This is useful for OCI developers to debug your programs.

What is different from others.
------------------------------

There have been similar utilities such as [ocitrace][1] and
[ocispy][2]. They use [User-Defined Callback Functions in OCI][3] to
monitor OCI function calls. But it is not perfect. Some OCI functions
call other OCI functions internally. Such internal calls, which are
not executed by an application, also fire user-defined callback
functions. So these utilities cannot monitor function calls exactly
issued by Oracle client applications.

Ocidump uses another way to monitor OCI functions. It uses LD_PRELOAD
on Unix and IAT hooking on Windows. It can monitor function calls
exactly as they are issued. Note that there is an exception that the
first call of OCIEnvCreate() or similar functions is not monitored on
Windows. It is due to the timing of loading ocidump.dll into process
memory.

The downside of ocidump way is that it cannot monitor explicitly
linked functions. Some applications try to get the entry point of a
function and use it if it is found, otherwise do another job.
As far as I know, the ruby-oci8 Windows binary package does it to
use OCI functions newly added in recent Oracle versions.

Supported platforms
-------------------

Officially it supports Linux only. It may work on other Unix-like operating systems.
Windows is supported experimentally.

How to compile
--------------

If ruby is not in the system, install it. Then run `make`.

Run `nmake -f win32.mak` instead for Windows.

How to use
----------

Set the environment variable `LD_PRELOAD` to point to libocidump.so and
run a Oracle client application.

    LD_PRELOAD=/foo/bar/libocidump.so
    export LD_PRELOAD
    sqlplus scott/tiger

On Windows, copy ocidump.dll to %ORACLE_HOME\bin and set the environment
variable ORA_OCI_UCBPKG=ocidump in order to inject the dll into application
memory space.

    set ORA_OCI_UCBPKG=ocidump
    sqlplus scott/tiger

OCI function calls are dumped to the standard error by default.
Set `OCIDUMP_LOGFILE` to log them to a file.

    OCIDUMP_LOGFILE=/tmp/ocidump.log
    export OCIDUMP_LOGFILE

All supported OCI functions are dumped by default. The output may be
verbose because it needs several function calls to issue a single SQL
statement. Set `OCIDUMP_CONFIG` to point to a file which contains
functions to be monitored.

    $ cat ocidump.cfg
    # monitor only the following two functions.
    OCIStmtPrepare
    OCIStmtPrepare2
    
    $ OCIDUMP_CONFIG=ocidump.cfg
    $ export OCIDUMP_CONFIG

If you are an application user who is requested to send a trace log by
application developers, set `OCIDUMP_HIDE_STRING` to hide sensitive
data. It hides all string data such as username, password, SQL
statements and so on.

    OCIDUMP_HIDE_STRING=1
    export OCIDUMP_HIDE_STRING

[1]: http://sourceforge.net/projects/ocitrace/
[2]: http://www.reocities.com/ocispy/
[3]: http://download.oracle.com/docs/cd/B28359_01/appdev.111/b28395/oci09adv.htm#i466264
