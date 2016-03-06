CC 	= gcc
CFLAGS 	= -Wall --pedantic -O2 -std=c11
HFLAGS  = -Iparse -Irender
LIB 	= librender.so libparse.so
LIBLINK	= -L$(PWD)/src $(LIB:lib%.so=-l%)
SOURCES	= $(wildcard *.c)
OBJS	= $(SOURCES:%.c=%.o)

EXEC 	= ../osmaps

all 	:
	make -C parse
	make -C render
	make $(EXEC)

$(EXEC)	: $(OBJS)
	$(CC) -o $@ $^ $(LIBLINK)

%.o 	: %.c
	$(CC) $(CFLAGS) $(HFLAGS) -c -o $@ $<

clean 	:
	make -C parse clean
	make -C render clean
	rm -f $(EXEC) $(OBJS)
