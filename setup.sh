#!/bin/bash

sudo apt-get install libxml2-dev
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-image-dev
sudo apt-get install libsdl2-ttf-dev
sudo apt-get install libsdl2-gfx-dev

make

#referencing executable path
#export PATH="$PATH:$PWD"

#referencing libraries path
#export DYLD_LIBRARY_PATH="$DYLD_LIBRARY_PATH:$PWD/src"
#export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$PWD/src"
