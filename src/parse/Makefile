CC 		= gcc
OPATH		= ../../bin
LPATH		= ../../lib
VPATH 		= $(OPATH)

CFLAGS 		= -Wall --pedantic -O2 -std=c11
HXML		= `pkg-config --cflags libxml-2.0`
LIBXML		= `pkg-config --libs libxml-2.0`
SOURCES 	= parse.c sort.c print.c free.c
OBJS		= $(SOURCES:%.c=$(OPATH)/%.o)

NAME		= ../../lib/libparse.so

all 		: $(NAME)

$(LPATH)/%.so	: $(OBJS)
		$(CC) -shared -o $@ $^ $(LIBXML)

$(OPATH)/%.o	: %.c
		$(CC) $(CFLAGS) $(HXML) -fPIC -c -o $@ $<

$(OPATH)/parse.o: parse.h sort.h
$(OPATH)/print.o: print.h parse.h
$(OPATH)/sort.o : sort.h parse.h
$(OPATH)/free.o	: parse.h

clean		:
		rm -f $(OBJS)
