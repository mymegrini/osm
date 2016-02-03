CC = gcc
CFLAGS = -Wall --pedantic -O2
VPATH = src:lib

EXEC = osmaps

HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst src/%.c, src/%.o, $(wildcard src/*.c)) \
$(patsubst lib/%.c, lib/lib%.o, $(wildcard lib/*.c))

LIBLINK = -lrender -lparse

all : lib exe clean

exe : $(EXEC)

lib : $(LIB)

clean :
	rm -f $(OBJECTS)

mrproper: clean
	rm -f $(EXEC) $(LIB)
