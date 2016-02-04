CC 	= gcc
CFLAGS 	= -Wall --pedantic -O2 -std=c11
HFLAGS  = -Ilib -Isrc
HXML	= `xml2-config --cflags`
LIBXML	= `xml2-config --libs`
LIBSDL	= 
VPATH 	= src:lib

EXEC 	= osmaps
LIB 	= $(patsubst lib/%.c, lib/%.o, $(wildcard lib/*.c))

HEADERS	= $(wildcard *.h)
OBJECTS	= $(patsubst src/%.c, src/%.o, $(wildcard src/*.c)) $(LIB)

all : lib exe clean

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