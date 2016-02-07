makeCC 	= gcc
CFLAGS 	= -Wall --pedantic -O2 -std=c11
HFLAGS  = -Ilib
HXML	= `xml2-config --cflags`
LIBXML	= `xml2-config --libs`
HSDL	= `sdl2-config --cflags`
LIBSDL	= `sdl2-config --libs`

VPATH 	= src:lib

EXEC 	= osmaps
LIB 	= $(patsubst lib/%.c, lib/%.o, $(wildcard lib/*.c))

HEADERS	= $(wildcard lib/*.h)
OBJECTS	= $(patsubst src/%.c, src/%.o, $(wildcard src/*.c)) $(LIB)

all : lib exe

exe : $(EXEC)

lib : $(LIB)

osmaps : $(OBJECTS) $(LIB)
	$(CC) -o $@ $^ $(LIBXML)

%.o : %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS) $(HXML) $(HFLAGS)

clean :
	rm -f $(OBJECTS)

mrproper: clean
	rm -f $(EXEC) $(LIB)
