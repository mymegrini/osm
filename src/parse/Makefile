CC 	= gcc
CFLAGS 	= -Wall --pedantic -O2 -std=c11
HXML	= `pkg-config --cflags libxml-2.0`
LIBXML	= `pkg-config --libs libxml-2.0`
SOURCES = parse.c sort.c print.c free.c
OBJS	= $(SOURCES:%.c=%.o)

NAME	= ../../lib/libparse.so

.PHONY	: all clean

all 	: $(NAME) clean

%.so	: $(OBJS)
	$(CC) -shared -o $@ $^ $(LIBXML)

%.o	: %.c
	$(CC) $(CFLAGS) $(HXML) -fPIC -c $<

parse.o : parse.h sort.h
print.o : print.h parse.h
sort.o 	: sort.h parse.h
free.o	: parse.h

clean	:
	rm -f $(OBJS)
