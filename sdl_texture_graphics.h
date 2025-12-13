#ifndef SDL_TEXTURE_GRAPHICS_H_
#define SDL_TEXTURE_GRAPHICS_H_

#include <SDL2/SDL.h>

#include "graphics.h"

class SDL_Texture_Graphics : public Graphics {
    private:
    SDL_Renderer* render;
    SDL_Texture* texture;
    Uint32* pixel_data;
    int pitch = 0;

    public:
    SDL_Texture_Graphics( SDL_Renderer* render, int w, int h );
    bool start();
    void lock();
    void unlock();
    void paint();
    void pixel( int x, int y );
    void close();
};

#endif // SDL_TEXTURE_GRAPHICS_H_