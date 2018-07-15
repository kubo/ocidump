ORACLE_INC = /opt/instantclient_11_2/sdk/include

UNAME_S := $(shell uname -s)

# Linux
ifeq ($(UNAME_S),Linux)
  CFLAGS = -g -pthread -fPIC -D_GNU_SOURCE -Wall
  LDFLAGS = -shared -pthread -Wl,--version-script,ocidump.map
  LIBS = -ldl
endif

# Solaris
ifeq ($(UNAME_S),SunOS)
  ifeq (gcc,$(findstring gcc,$(shell $(CC) --version 2>/dev/null)))
    CC_IS_GCC = 1
  else ifeq (SunOS,$(findstring SunOS,$(shell $(CC) -V 2>&1)))
  else ifeq (gcc,$(findstring gcc,$(shell gcc --version 2>/dev/null)))
    CC_IS_GCC = 1
    CC = gcc
  endif
  ifdef CC_IS_GCC
    CFLAGS = -fPIC -Wall
    LDFLAGS = -shared
  else
    CFLAGS = -KPIC
    LDFLAGS = -G
  endif
  CFLAGS += -g -D_REENTRANT
  LDFLAGS += -Wl,-M,ocidump.map
  LIBS = -ldl
endif

# OS X
ifeq ($(UNAME_S),Darwin)
  CFLAGS = -pthread -fPIC -Wall -fvisibility=hidden
  LDFLAGS = -shared
  LIBS = -lpthread -ldl
endif

OBJS = ocidump.o ocifunc.o ocidefs.o ociattr.o oranumber_util.o ocihandle.o

.PHONY : clean check_defs

libocidump.so: $(OBJS) ocidump.map
	$(CC) $(LDFLAGS) -o libocidump.so $(OBJS) $(LIBS)

ocidump.o: ocidump.c ocidump.h ocidefs.h oranumber_util.h ocihandle.h
ocifunc.o: ocifunc.c ocidump.h ocidefs.h
ocidefs.o: ocidefs.c ocidump.h ocidefs.h
oranumber_util.o: oranumber_util.c oranumber_util.h
ocihandle.o: ocihandle.c ocidump.h ocihandle.h

ocifunc.c ocidefs.c ocidefs.h ociattr.c ocidump.map: mkocifunc.rb ocifunc.c.tmpl ocifunc.yml ocidefs.yml ociattr.yml oranumber_util.o
	ruby mkocifunc.rb

clean:
	$(RM) libocidump.so $(OBJS)

distclean:
	$(RM) libocidump.so $(OBJS) ocifunc.c ocidefs.c ocidefs.h ociattr.c ocidump.map

check_defs:
	ruby mkocifunc.rb check_defs
	$(CC) $(CFLAGS) -I$(ORACLE_INC) -o check_defs check_defs.c
	./check_defs
