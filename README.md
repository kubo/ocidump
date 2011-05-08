Oracle OCI Tracer
=================

What's is this.
---------------

Tracing utility to monitor Oracle OCI function calls.
This is useful for OCI developers to debug your programs.

What is this different with other utilities?
--------------------------------------------

There have been similar utilities such as [ocitrace][1] and
[ocispy][2]. They use [User-Defined Callback Functions in OCI][3] to
monitor OCI function calls. But it is not perfect. Some OCI functions
call other OCI functions internally. Such internal calls, which are
not executed by an application, also fire user-defined callback
functions. So this utility was made to monitor function calls exactly
issued by Oracle client applications.

Supported platforms
-------------------

Officially it supports Linux only. It may work on other Unix-like operating systems.

How to compile
--------------

Edit Makefile and run `make`.

How to uee
----------

Set the environment variable `LD_PRELOAD` to point to libocitrace.so and
run a Oracle client application.

    LD_PRELOAD=/foo/bar/libocitrace.so
    export LD_PRELOAD
    sqlplus scott/tiger

OCI function calls are dumped to the standard error by default.
Set `OCITRACE_LOGFILE` to log them to a file.

    OCITRACER_LOGFILE=/tmp/ocitracer.log
    export OCITRACER_LOGFILE

All supported OCI functions are dumped by default. The output may be
verbose because it needs several function calls to issue a single SQL
statement. Set `OCITRACRER_CONFIG` to point to a file which contains
functions to be monitored.

    $ cat ocitrace.cfg
    # monitor only the following two functions.
    OCIStmtPrepare
    OCIStmtPrepare2
    
    $ OCITRACRER_CONFIG=ocitrace.cfg
    $ export OCITRACRER_CONFIG

If you are an application user who is requested to send a trace log by
application developers, set OCITRACER_HIDE_STRING=1 to hide sensitive
data. It hides all string data such as username, password, SQL
statements and so on.

[1]: http://sourceforge.net/projects/ocitrace/
[2]: http://www.reocities.com/ocispy/
[3]: http://download.oracle.com/docs/cd/B28359_01/appdev.111/b28395/oci09adv.htm#i466264
