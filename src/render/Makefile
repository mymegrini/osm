CC 		= gcc
OPATH		= ../../bin
LPATH		= ../../lib
VPATH 		= $(OPATH)

CFLAGS 		= -Wall --pedantic -O2 -std=c11
HSDL		= -I../parse `pkg-config --cflags sdl2`
LIBSDL		= `pkg-config --libs sdl2 SDL2_gfx` -lm
SOURCES 	= render.c format.c
OBJS		= $(SOURCES:%.c=$(OPATH)/%.o)

NAME		= ../../lib/librender.so

all 	: $(NAME)

$(LPATH)/%.so	: $(OBJS)
		$(CC) -shared -o $@ $^ $(LIBSDL)

$(OPATH)/%.o	: %.c
		$(CC) $(CFLAGS) $(HSDL) -fPIC -c -o $@ $<

$(OPATH)/render.o: render.h format.h ../gui/gui.h
$(OPATH)/render.o: ../parse/free.h ../parse/print.h ../parse/parse.h
$(OPATH)/format.o: format.h ../parse/parse.h

clean	:
		rm -f $(OBJS)
