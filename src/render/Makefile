CC 	= gcc
CFLAGS 	= -Wall --pedantic -O2 -std=c11
HSDL	= `sdl2-config --cflags` -I../parse
LIBSDL	= `sdl2-config --libs` -lSDL2_gfx -lm
SOURCES = render.c
OBJS	= $(SOURCES:%.c=%.o)

NAME	= ../librender.so

all 	: $(NAME)

%.so	: $(OBJS)
	$(CC) -shared -o $@ $^ $(LIBSDL)

%.o	: %.c
	$(CC) $(CFLAGS) $(HSDL) -fPIC -c $<

render.o: render.h

clean	:
	rm -f $(NAME) $(OBJS)
