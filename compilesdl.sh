#!/bin/bash
echo "If compilation is not success try install sdl2: sudo apt-get install libsdl2-2.0 libsdl2-dev;";
echo "Or sudo apt-get libsdl2-2.0 libsdl2-dev libsdl-mixer-2.0-0 libsdl-mixer-dev libsdl-image-2.0-0 libsdl-image-dev libsdl-ttf-2.0-0 libsdl-ttf-dev";
#if not working install full sdl:
#libsdl2-2.0-0 - Simple DirectMedia Layer
#libsdl2-dev - Simple DirectMedia Layer development files
#libsdl2-doc - Reference manual for libsdl2
#libsdl2-gfx-1.0-0 - drawing and graphical effects extension for SDL2
#libsdl2-gfx-dev - development files for SDL2_gfx
#libsdl2-gfx-doc - documentation files for SDL2_gfx
#libsdl2-image-2.0-0 - Image loading library for Simple DirectMedia Layer 2, libraries
#libsdl2-image-dev - Image loading library for Simple DirectMedia Layer 2, development files
#libsdl2-mixer-2.0-0 - Mixer library for Simple DirectMedia Layer 2, libraries
#libsdl2-mixer-dev - Mixer library for Simple DirectMedia Layer 2, development files
#libsdl2-net-2.0-0 - Network library for Simple DirectMedia Layer 2, libraries
#libsdl2-net-dev - Network library for Simple DirectMedia Layer 2, development files
#libsdl2-ttf-2.0-0 - TrueType Font library for Simple DirectMedia Layer 2, libraries
#libsdl2-ttf-dev
echo "Your file (without cpp):";
read n;
b="$(basename -- $n)"
g++ "$n.cpp" -c `sdl2-config --cflags --libs` -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lpthread
g++ -o "$b" "$b.o" `sdl2-config --cflags --libs` -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lpthread
echo "Press any key to launch";
read n;
rm "$b.o"
"./$b"

