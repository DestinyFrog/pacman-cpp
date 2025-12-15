#ifndef SDL_TEXTURE_GRAPHICS_H_
#define SDL_TEXTURE_GRAPHICS_H_

#include <algorithm>

#include <SDL2/SDL.h>

#include "graphics.h"

class SDL_Texture_Graphics : public Graphics {
    private:
    SDL_Renderer* render;
    SDL_Texture* texture;
    void* pixel_data = nullptr;
    int pitch = 0;
    Uint32 paint_color = 0x00000000;

    public:
    SDL_Texture_Graphics( SDL_Renderer* render, int w, int h );
    bool start();
    void lock();
    void unlock();
    void paint();
    void pixel( int x, int y );
    void color( Uint32 c );
    void close();
};

#endif // SDL_TEXTURE_GRAPHICS_H_