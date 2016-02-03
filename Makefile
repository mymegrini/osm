CC = gcc
CFLAGS = -Wall --pedantic -O2
VPATH = src:lib

EXEC = osm.exe

HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst src/%.c, src/%.o, $(wildcard src/*.c)) \
$(patsubst lib/%.c, lib/lib%.o, $(wildcard lib/*.c))

LIBLINK = -lrender -lparse

all : lib exe clean

exe : $(EXEC)

lib : $(LIB)

bin/% : obj/%.o
	$(CC) -o $@ $< -Lbin $(LIBLINK)

obj/lib%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -fpic -c -Ilib -o $@ $<	

obj/%.o : src/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c -Ilib -o $@ $<

clean :
	rm -f $(OBJECTS)

mrproper: clean
	rm -f $(EXEC) $(LIB)
