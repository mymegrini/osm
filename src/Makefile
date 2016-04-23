CC 	= gcc
CFLAGS 	= -Wall --pedantic -O2 -std=c11
HFLAGS  = -Iparse -Irender -Igui
LIB 	= librender.so libgui.so libparse.so
LIBLINK	= -L../lib $(LIB:lib%.so=-l%)
SOURCES	= $(wildcard *.c)
OBJS	= $(SOURCES:%.c=%.o)

EXEC 	= ../bin/osmaps

.PHONY	: all clean clean-all

all 	:
	make -C parse
	make -C gui
	make -C render
	make $(EXEC)
	rm -f $(OBJS)

$(EXEC)	: $(OBJS)
	$(CC) -o $@ $^ $(LIBLINK)

%.o 	: %.c
	$(CC) $(CFLAGS) $(HFLAGS) -c -o $@ $<

clean 	:
	rm -f $(EXEC)
	rm -f $(LIB:%.so=lib/%.so)
