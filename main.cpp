#include <iostream>
#include <cstdlib>

#include <SDL2/SDL.h>

#include "pacman.h"
#include "tilemap.h"
#include "sdl_graphics.h"
#include "sdl_texture_graphics.h"

int main() {
    SDL_Window* window;
    SDL_Renderer* render;
    SDL_Event window_event;
    bool running = true;

    Tilemap tilemap = Tilemap();
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
        texture.close();
        tilemap.close();
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    if (tilemap.paint(&texture)) {
        std::cerr << "Failed to paint texture graphics" << std::endl;
        texture.close();
        tilemap.close();
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Graphics g(render, width, height);
    Pacman pacman = Pacman();
    pacman.set_position(tilemap);

    while (running) {
        while (SDL_PollEvent(&window_event)) {
            if (window_event.type == SDL_QUIT)
                running = false;
        }

        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
        SDL_RenderClear(render);

        texture.paint();
        pacman.draw(g);

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