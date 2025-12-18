#ifndef SDL_GRAPHICS_H_
#define SDL_GRAPHICS_H_

#include <SDL2/SDL.h>

#include "graphics.h"

class SDL_Graphics : public Graphics {
    private:
    SDL_Renderer* render;

    public:
    SDL_Graphics( SDL_Renderer* render, int width, int height );
    void color( int r, int g, int b, int a );
    void pixel( int x, int y );
};

#endif // SDL_GRAPHICS_H_