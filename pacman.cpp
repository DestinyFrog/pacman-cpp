#include <iostream>
#include <cstdlib>

#include <SDL2/SDL.h>

#include "tilemap.h"
#include "sdl_graphics.h"
#include "sdl_texture_graphics.h"

int main() {
    SDL_Window* window;
    SDL_Renderer* render;
    SDL_Event window_event;
    bool running = true;
    
    const int unit = 24;

    Tilemap tilemap = Tilemap(unit);
    tilemap.start("map.txt");

    const int width = tilemap.get_width();
    const int height = tilemap.get_height();

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Error initializing: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow("PACMAN", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return EXIT_FAILURE;
    }

    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (render == NULL) {
        std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Texture_Graphics texture = SDL_Texture_Graphics(render, width, height);
    if (!texture.start()) {
        std::cerr << "Failed to initialize texture graphics" << std::endl;
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    texture.lock();
    texture.color( 0x0000FFFF );
    for (int i = 0; i < tilemap.rows; i++) {
        for (int j = 0; j < tilemap.cols; j++) {
            if (tilemap.matrix[i][j] == WALL)
                continue;

            int x = unit * j;
            int y = unit * i;

            if (i > 0 && tilemap.matrix[i - 1][j] == WALL)
                texture.line( x, y, x + unit, y );

            if (i < tilemap.rows - 1  && tilemap.matrix[i + 1][j] == WALL)
                texture.line( x, y + unit, x + unit, y + unit);

            if (j > 0 && tilemap.matrix[i][j - 1] == WALL)
                texture.line( x, y, x, y + unit );

            if (j < tilemap.cols - 1 && tilemap.matrix[i][j + 1] == WALL)
                texture.line( x + unit, y, x + unit, y + unit);
        }
    }
    texture.unlock();

    SDL_Graphics g(render, width, height);

    while (running) {
        while (SDL_PollEvent(&window_event)) {
            if (window_event.type == SDL_QUIT)
                running = false;
        }

        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
        SDL_RenderClear(render);

        texture.paint();

        SDL_SetRenderDrawColor(render, 255, 255, 0, 255);
        g.circle( 100, 100, unit * 2, 45, 270 );

        SDL_RenderPresent(render);
        SDL_Delay(16);
    }

    texture.close();
    tilemap.close();
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}