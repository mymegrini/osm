CC 	= gcc
CFLAGS 	= -Wall --pedantic -O2 -std=c11
HSDL	= -I../parse `pkg-config --cflags sdl2`
LIBSDL	= `pkg-config --libs sdl2 SDL2_gfx` -lm
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
