# LIB
V=0.1.0
PREFIX=/opt/projects/github/crate/crate-odbc
LIBDIR=$(PREFIX)/lib/
LIBNAME=libcrateodbc.so
LIB_OPTION= -shared

# ODBC
DRIVER_LIBS= -L/usr/local/lib -lodbc -lcurl -ljansson
DRIVER_INCS= -DUNIXODBC -I/usr/local/include -I$(PREFIX)/include

EXAMPLE_LIBS= -L$(LIBDIR) -lcrateodbc
# COMPILER
WARN= -Wall -Wmissing-prototypes -Wmissing-declarations
CC=gcc
CFLAGS= -O2 $(WARN) -fPIC $(DRIVER_INCS) $(INCS) $(DEFS)

# SOURCE
OBJS=src/crateodbc.o src/crateclient.o
SRCS=src/crateodbc.c src/crateclient.c
AR=ar rcu
RANLIB=ranlib
TESTS=$(patsubst %.c,%.o, $(wildcard tests/odbc/*.c))
EXAMPLES=$(patsubst %.c,%.o, $(wildcard examples/*.c))

# TARGETS
all: clean lib install examples

lib: src/$(LIBNAME)

src/$(LIBNAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(LIB_OPTION) $(OBJS) $(DRIVER_LIBS)

install: lib
	mkdir -p $(LIBDIR)
	cp src/$(LIBNAME) $(LIBDIR)

clean:
	rm -f src/$(LIBNAME) src/*.o
	rm -f lib/* lib64/*
	rm -f tests/odbc/*.o
	rm -f examples/*.o

# tests
tests/odbc/%.o: tests/odbc/%.c
	$(CC) $(CFLAGS) -o $@ $< $(DRIVER_LIBS)
	-$@
tests: $(TESTS)

# examples
examples/%.o: examples/%.c
	$(CC) $(CFLAGS) $(EXAMPLE_LIBS) -o $@ $< $(DRIVER_LIBS)
	-$@
examples: $(EXAMPLES)
