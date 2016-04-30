ORACLE_HOME = c:\oraclexe\app\oracle\product\10.2.0\server

CC = cl /nologo
CFLAGS = /MT /Zi
LD_SHARED = $(CC) /LD
LDFLAGS = /MT /Zi
RM = del

!ifdef WIN64
MACHINE = x64
!else
MACHINE = x86
!endif

OBJS = ocidump.obj ocifunc.obj ocidefs.obj ociattr.obj oranumber_util.obj ocihandle.obj win32.obj
MKOCIFUNC_FILES = ocifunc.c ocidefs.c ocidefs.h ociattr.c ocidump.map

all: ocidump.dll

ocidump.dll: $(OBJS) oci-orig.lib ocidump.def
	$(LD_SHARED) $(LDFLAGS) /Feocidump.dll $(OBJS) dbghelp.lib oci-orig.lib /link /def:ocidump.def

ocidump.obj: ocidump.c ocidump.h ocidefs.h oranumber_util.h ocihandle.h
ocifunc.obj: ocifunc.c ocidump.h ocidefs.h
ocidefs.obj: ocidefs.c ocidump.h ocidefs.h
ociattr.obj: ociattr.c ocidump.h
oranumber_util.obj: oranumber_util.c oranumber_util.h
ocihandle.obj: ocihandle.c ocidump.h ocihandle.h

$(MKOCIFUNC_FILES): mkocifunc.rb ocifunc.c.tmpl ocifunc.yml ocidefs.yml ociattr.yml
	ruby mkocifunc.rb

ocidump.def:
	echo EXPORTS > ocidump.def

oci-orig.def:
	echo EXPORTS > oci-orig.def

oci-orig.lib: oci-orig.def
	lib /nologo /def:oci-orig.def /out:oci-orig.lib /machine:$(MACHINE)

clean:
	$(RM) $(OBJS) $(MKOCIFUNC_FILES) ocidump.ilk ocidump.lib oci.lib ocidump.exp *.pdb *.dll

install: ocidump.dll
	copy ocidump.dll $(ORACLE_HOME)\bin
