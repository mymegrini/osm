CC 		= gcc
OPATH		= ../bin
LPATH		= ../lib
VPATH 		= $(OPATH)

CFLAGS 		= -Wall --pedantic -O2 -std=c11
HFLAGS  	= -Iparse -Irender -Igui
LIB 		= librender.so libgui.so libparse.so
LIBLINK		= -L../lib $(LIB:lib%.so=-l%)
SOURCES		= $(wildcard *.c)
OBJS		= $(SOURCES:%.c=$(OPATH)/%.o)

EXEC 		= $(OPATH)/osmaps

all 		:
	make -C parse
	make -C gui
	make -C render
	make $(EXEC)

$(EXEC)		: $(OBJS)
	$(CC) -o $@ $^ $(LIBLINK)

$(OPATH)/%.o 	: %.c
	$(CC) $(CFLAGS) $(HFLAGS) -c -o $@ $<

clean 		:
	make -C parse clean
	make -C gui clean
	make -C render clean
	rm -f $(OBJS)
	rm -f $(LIB:%.so=$(LPATH)/%.so)
	rm -f $(EXEC)
