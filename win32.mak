ORACLE_HOME = c:\oraclexe\app\oracle\product\10.2.0\server

CC = cl /nologo
CFLAGS = /MT /Zi
LD_SHARED = $(CC) /LD
LDFLAGS = /MT /Zi
RM = del

OBJS = ocidump.obj ocifunc.obj ocidefs.obj oranumber_util.obj win32.obj win32_trampoline.obj win32_trampoline_vc.obj
MKOCIFUNC_FILES = ocifunc.c ocidefs.c ocidefs.h
WIN32_TRAMPOLINE_FILES = win32_trampoline.c win32_trampoline_vc.asm

all: oci.dll ocidump.dll

oci.dll: ocidump.dll
	copy ocidump.dll oci.dll

ocidump.dll: $(OBJS) ocidump.def
	$(LD_SHARED) $(LDFLAGS) /Feocidump.dll $(OBJS) dbghelp.lib /link /def:ocidump.def

ocidump.obj: ocidump.c ocidump.h ocidefs.h oranumber_util.h
ocifunc.obj: ocifunc.c ocidump.h ocidefs.h
ocidefs.obj: ocidefs.c ocidump.h ocidefs.h
oranumber_util.obj: oranumber_util.c oranumber_util.h

win32_trampoline_vc.obj: win32_trampoline_vc.asm
	ml /nologo /c /coff /Cp win32_trampoline_vc.asm

$(MKOCIFUNC_FILES): mkocifunc.rb ocifunc.c.tmpl ocifunc.yml ocidefs.yml
	ruby mkocifunc.rb

$(WIN32_TRAMPOLINE_FILES): win32_trampoline.rb ocidump.def
	ruby win32_trampoline.rb

clean:
	$(RM) $(OBJS) $(MKOCIFUNC_FILES) $(WIN32_TRAMPOLINE_FILES) ocidump.ilk ocidump.lib ocidump.exp *.pdb *.dll

install: ocidump.dll
	copy ocidump.dll $(ORACLE_HOME)\bin
