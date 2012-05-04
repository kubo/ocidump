ORACLE_INC = /opt/instantclient_11_2/sdk/include

## Linux
CC = gcc
CFLAGS = -pthread -fPIC -D_GNU_SOURCE -Wall
LD_SHARED = $(CC) -shared
LDFLAGS = -pthread -Wl,--version-script,ocidump.map

## Solaris gcc
#CC = gcc
#CFLAGS = -D_REENTRANT -fPIC -Wall
#LD_SHARED = $(CC) -shared
#LDFLAGS = -Wl,-M,ocidump.map

## Solaris Studio
#CC = cc
#CFLAGS = -D_REENTRANT -KPIC
#LD_SHARED = $(CC) -G
#LDFLAGS = -Wl,-M,ocidump.map

OBJS = ocidump.o ocifunc.o ocidefs.o ociattr.o oranumber_util.o

.PHONY : clean check_defs

libocidump.so: $(OBJS)
	$(LD_SHARED) $(LDFLAGS) -o libocidump.so $(OBJS)

ocidump.o: ocidump.c ocidump.h ocidefs.h oranumber_util.h
ocifunc.o: ocifunc.c ocidump.h ocidefs.h
ocidefs.o: ocidefs.c ocidump.h ocidefs.h
oranumber_util.o: oranumber_util.c oranumber_util.h

ocifunc.c ocidefs.c ocidefs.h ociattr.c: mkocifunc.rb ocifunc.c.tmpl ocifunc.yml ocidefs.yml ociattr.yml
	ruby mkocifunc.rb

clean:
	$(RM) libocidump.so $(OBJS)

check_defs:
	ruby mkocifunc.rb check_defs
	$(CC) $(CFLAGS) -I$(ORACLE_INC) -o check_defs check_defs.c
	./check_defs
