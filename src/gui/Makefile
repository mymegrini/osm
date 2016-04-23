CC 		= gcc
OPATH		= ../../bin
LPATH		= ../../lib
VPATH 		= $(OPATH)

CFLAGS 		= -Wall --pedantic -O2 -std=c11
HSDL		= -I../render -I../parse `pkg-config --cflags sdl2`
LIBSDL		= `pkg-config --libs sdl2 SDL2_gfx` -lm
SOURCES		= gui.c
OBJS		= $(SOURCES:%.c=$(OPATH)/%.o)

NAME		= ../../lib/libgui.so

all 		: $(NAME)

$(LPATH)/%.so	: $(OBJS)
	$(CC) -shared -o $@ $^ $(LIBSDL)

$(OPATH)/%.o	: %.c
	$(CC) $(CFLAGS) $(HSDL) -fPIC -c -o $@ $<

gui.o		: gui.h parse.h render.h

clean		:
	rm -f $(OBJS)
