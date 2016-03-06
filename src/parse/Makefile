CC 	= gcc
CFLAGS 	= -Wall --pedantic -O2 -std=c11
HXML	= `xml2-config --cflags`
LIBXML	= `xml2-config --libs`
SOURCES = parse.c sort.c print.c free.c
OBJS	= $(SOURCES:%.c=%.o)

NAME	= ../libparse.so

all 	: $(NAME)

%.so	: $(OBJS)
	$(CC) -shared -o $@ $^ $(LIBXML)

%.o	: %.c
	$(CC) $(CFLAGS) $(HXML) -fPIC -c $<

parse.o : parse.h sort.h
print.o : print.h parse.h
sort.o 	: sort.h parse.h
free.o	: parse.h

clean	:
	rm -f $(NAME) $(OBJS)
