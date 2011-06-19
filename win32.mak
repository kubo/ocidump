ORACLE_HOME = c:\oraclexe\app\oracle\product\10.2.0\server

CC = cl /nologo
CFLAGS = /MT
LD_SHARED = $(CC) /LD
LDFLAGS = /MT
RM = del

OBJS = ocidump.obj ocifunc.obj ocidefs.obj oranumber_util.obj win32.obj

ocidump.dll: $(OBJS)
	$(LD_SHARED) $(LDFLAGS) /Feocidump.dll $(OBJS) dbghelp.lib

ocidump.obj: ocidump.c ocidump.h ocidefs.h oranumber_util.h
ocifunc.obj: ocifunc.c ocidump.h ocidefs.h
ocidefs.obj: ocidefs.c ocidump.h ocidefs.h
oranumber_util.obj: oranumber_util.c oranumber_util.h

ocifunc.c ocidefs.c ocidefs.h: mkocifunc.rb ocifunc.c.tmpl ocifunc.yml ocidefs.yml
	ruby mkocifunc.rb

clean:
	$(RM) ocidump.dll $(OBJS)

install: ocidump.dll
	copy ocidump.dll $(ORACLE_HOME)\bin
