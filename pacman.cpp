#include "pacman.h"

void Pacman::set_position(Tilemap tilemap) {
    for (int i = 0; i < tilemap.rows; i++) {
        for (int j = 0; j < tilemap.cols; j++) {
            if (tilemap.matrix[i][j] == PACMAN) {
                x = j;
                y = i;
                return;
            }
        }
    }
}

void Pacman::draw(SDL_Graphics g) {
    if (mouth_angle > mouth_max_angle || mouth_angle < 0)
        mouth_angle_direction *= -1;

    mouth_angle += mouth_angle_direction;

    g.color(255, 255, 0, 255);
    g.circle(
        x * UNIT + UNIT / 2,
        y * UNIT + UNIT / 2,
        UNIT / 2 - 2,
        mouth_angle,
        359 - (mouth_angle*2) );
}