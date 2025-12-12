#ifndef SDL_TEXTURE_GRAPHICS_H_
#define SDL_TEXTURE_GRAPHICS_H_

#include <SDL2/SDL.h>

#include "graphics.cpp"

class SDL_Texture_Graphics : public Graphics {
    private:
    SDL_Renderer* render;
    SDL_Texture* texture;
    Uint32* pixel_data;
    int pitch = 0;

    public:
    SDL_Texture_Graphics( SDL_Renderer* render, int width, int height )
        : Graphics(width, height) {
        this->render = render;
    }

    bool start() {
        texture = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
        return texture == NULL;
    }

    void lock() {
        void* void_pixel_data;
        SDL_LockTexture(texture, NULL, &void_pixel_data, &pitch);
    }

    void unlock() {
        SDL_UnlockTexture(texture);
    }

    void paint() {
        SDL_RenderCopy(render, texture, NULL, NULL);
    }

    void pixel( int x, int y ) {
        if (x > 0 && x < width && y > 0 && y < height) {
            int pixel_index = (y * (pitch / 4)) + x;
            pixel_data[pixel_index] = 0x0000FF00;
        }
    }

    void close() {
        SDL_DestroyTexture(texture);
    }
};

#endif // SDL_TEXTURE_GRAPHICS_H_