# full client
INC = $$ORACLE_HOME/rdbms/public

# instant client
#INC = /opt/instantclient_11_2/sdk/include

CC = gcc
CFLAGS = -pthread -fPIC -I$(INC) -D_GNU_SOURCE -Wall
LD_SHARED = $(CC) -shared
LDFLAGS = -pthread

.PHONY : clean all

libocitracer.so: ocitracer.o ocifunc.o
	$(LD_SHARED) $(LDFLAGS) -o libocitracer.so ocitracer.o ocifunc.o

all: .ocifunc.c.timestamp libocitracer.so

ocitracer.o: ocitracer.c ocitracer.h
ocifunc.o: ocifunc.c ocitracer.h

.ocifunc.c.timestamp: ocifunc.c.tmpl ocifunc.yml
	ruby mkocifunc.rb
	touch .ocifunc.c.timestamp

clean:
	$(RM) libocitracer.so ocitracer.o ocifunc.o
