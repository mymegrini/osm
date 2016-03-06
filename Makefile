CC 	= gcc -g
CFLAGS 	= -Wall --pedantic -O2 -std=c11
HFLAGS  = -Isrc/parse -Isrc/render
LIB 	= librender.so libparse.so
LIBLINK	= -L$(PWD)/src $(LIB:lib%.so=-l%)
SOURCES	= main.c
OBJS	= $(SOURCES:%.c=src/%.o)

VPATH 	= src

EXEC 	= osmaps

all 	:
	make -C src/parse
	make -C src/render
	make $(EXEC)

$(EXEC)	: $(OBJS)
	$(CC) -o $@ $^ $(LIBLINK)

%.o 	: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(HFLAGS) -c -o $@ $<

main.o	: osmaps.h

clean 	:
	make -C src/parse clean
	make -C src/render clean
	rm -f $(EXEC) $(OBJECTS)
