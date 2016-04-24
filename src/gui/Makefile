CC 		= gcc
OPATH		= ../../bin
LPATH		= ../../lib
VPATH 		= $(OPATH)

CFLAGS 		= -Wall --pedantic -O2 -std=c11
HSDL		= -I../render `pkg-config --cflags sdl2`
LIBSDL		= `pkg-config --libs sdl2 SDL2_gfx`
LIB 		= librender.so libparse.so
LIBLINK		= -L../../lib $(LIBSDL) $(LIB:lib%.so=-l%)
SOURCES		= gui.c
OBJS		= $(SOURCES:%.c=$(OPATH)/%.o)

NAME		= ../../lib/libgui.so

all 		: $(NAME)

$(LPATH)/%.so	: $(OBJS)
		$(CC) -shared -o $@ $^ $(LIBLINK)

$(OPATH)/%.o	: %.c
		$(CC) $(CFLAGS) $(HSDL) -fPIC -c -o $@ $<

$(OPATH)/gui.o	: ../render/render.h

clean		:
		rm -f $(OBJS)
