#!/usr/bin/bash

clear;
g++ *.cpp -o pacman.out `sdl2-config --cflags --libs` -lSDL2 -lSDL2_ttf -lm;
./pacman.out