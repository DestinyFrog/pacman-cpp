#include "sdl_texture_graphics.h"

SDL_Texture_Graphics::SDL_Texture_Graphics( SDL_Renderer* render, int w, int h ):
    Graphics(width, height),
    render( render )
{}

bool SDL_Texture_Graphics::start() {
    texture = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    return texture == NULL;
}

void SDL_Texture_Graphics::lock() {
    void* void_pixel_data;
    SDL_LockTexture(texture, NULL, &void_pixel_data, &pitch);
}

void SDL_Texture_Graphics::unlock() {
    SDL_UnlockTexture(texture);
}

void SDL_Texture_Graphics::paint() {
    SDL_RenderCopy(render, texture, NULL, NULL);
}

void SDL_Texture_Graphics::pixel( int x, int y ) {
    if (x > 0 && x < width && y > 0 && y < height) {
        int pixel_index = (y * (pitch / 4)) + x;
        pixel_data[pixel_index] = 0x0000FF00;
    }
}

void SDL_Texture_Graphics::close() {
    SDL_DestroyTexture(texture);
}
