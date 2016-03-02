#!/bin/bash

sudo apt-get install libxml2-dev
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-image-dev
sudo apt-get install libsdl2-ttf-dev
sudo apt-get install libsdl2-gfx-dev

make

export PATH="$PATH:$PWD"

#export DYLD_LIBRARY_PATH="$DYLD_LIBRARY_PATH:$PWD/lib"
#export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$PWD/lib"

