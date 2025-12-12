#ifndef SDL_GRAPHICS_H_
#define SDL_GRAPHICS_H_

#include <SDL2/SDL.h>

#include "graphics.cpp"

class SDL_Graphics : public Graphics {
    private:
    SDL_Renderer* render;

    public:
    SDL_Graphics( SDL_Renderer* render, int width, int height )
        : Graphics(width, height) {
        this->render = render;
    }

    void pixel( int x, int y ) {
        if (x > 0 && x < width && y > 0 && y < height)
            SDL_RenderDrawPoint(render, x, y);
    }
};

#endif // SDL_GRAPHICS_H_