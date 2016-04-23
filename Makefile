#Open Street Map Renderer Osmaps Makefile

.PHONY	: all clean clean-all

all 		:
	make -C src

clean 		:
	make -C src clean

clean-all 	:
	make -C src cleanx
