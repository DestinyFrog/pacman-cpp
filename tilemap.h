#ifndef TILEMAP_H_
#define TILEMAP_H_

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

#include <SDL2/SDL.h>

#include "data.h"
#include "sdl_texture_graphics.h"

typedef enum {
    WALL,
    PACMAN,
    EMPTY
} Tile;

class Tilemap {
    public:
    int rows;
    int cols;
    Tile** matrix;

    Tile char_to_tile(char c);

    public:
    int get_width();
    int get_height();
    bool start( const char* filename );
    bool paint(SDL_Texture_Graphics* texture);
    void close();
};

#endif // TILEMAP_H_