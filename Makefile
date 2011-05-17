# full client
INC = $$ORACLE_HOME/rdbms/public

# instant client
#INC = /opt/instantclient_11_2/sdk/include

CC = gcc
CFLAGS = -pthread -fPIC -I$(INC) -D_GNU_SOURCE -Wall
LD_SHARED = $(CC) -shared
LDFLAGS = -pthread

.PHONY : clean all

libocidump.so: ocidump.o ocifunc.o
	$(LD_SHARED) $(LDFLAGS) -o libocidump.so ocidump.o ocifunc.o

all: .ocifunc.c.timestamp libocidump.so

ocidump.o: ocidump.c ocidump.h
ocifunc.o: ocifunc.c ocidump.h

.ocifunc.c.timestamp: ocifunc.c.tmpl ocifunc.yml
	ruby mkocifunc.rb
	touch .ocifunc.c.timestamp

clean:
	$(RM) libocidump.so ocidump.o ocifunc.o
