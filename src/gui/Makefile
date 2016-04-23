CC 	= gcc
CFLAGS 	= -Wall --pedantic -O2 -std=c11
HSDL	= -I../render -I../parse `pkg-config --cflags sdl2`
LIBSDL	= `pkg-config --libs sdl2 SDL2_gfx` -lm
SOURCES = gui.c
OBJS	= $(SOURCES:%.c=%.o)

NAME	= ../../lib/libgui.so

.PHONY	: all clean

all 	: $(NAME) clean

%.so	: $(OBJS)
	$(CC) -shared -o $@ $^ $(LIBSDL)

%.o	: %.c
	$(CC) $(CFLAGS) $(HSDL) -fPIC -c $<

gui.o	: gui.h

clean	:
	rm -f $(OBJS)
