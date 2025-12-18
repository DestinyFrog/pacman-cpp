#ifndef PACMAN_H_
#define PACMAN_H_

#include "data.h"
#include "tilemap.h"
#include "sdl_graphics.h"

class Pacman {
    private:
    int x;
    int y;
    int direction_x;
    int direction_y;

    int mouth_angle = 0;
    int mouth_angle_direction = 1;
    const int mouth_max_angle = 45;

    public:
    void set_position(Tilemap tilemap);
    void draw(SDL_Graphics g);
};

#endif // PACMAN_H_