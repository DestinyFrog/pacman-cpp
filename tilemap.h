#ifndef TILEMAP_H_
#define TILEMAP_H_

#include <iostream>
#include <fstream>
#include <cstdlib>

#include <SDL2/SDL.h>

typedef enum {
    WALL,
    EMPTY
} Tile;

class Tilemap {
    public:
    int unit;
    int rows;
    int cols;
    Tile** matrix;

    Tile char_to_tile(char c);

    public:
    Tilemap( int unit );
    ~Tilemap();

    int get_width();
    int get_height();
    bool start( const char* filename );
    void close();
};

#endif // TILEMAP_H_