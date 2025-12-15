#include "sdl_texture_graphics.h"

SDL_Texture_Graphics::SDL_Texture_Graphics( SDL_Renderer* render, int w, int h ):
    Graphics(w, h),
    render( render )
{}

bool SDL_Texture_Graphics::start() {
    texture = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    return !(texture == NULL);
}

void SDL_Texture_Graphics::lock() {
    if (SDL_LockTexture(texture, nullptr, &pixel_data, &pitch) < 0) {
        std::cerr << "SDL_LockTexture error: " << SDL_GetError() << std::endl;
        pixel_data = nullptr;
    }
}

void SDL_Texture_Graphics::unlock() {
    SDL_UnlockTexture(texture);
}

void SDL_Texture_Graphics::paint() {
    SDL_RenderCopy(render, texture, NULL, NULL);
}

void SDL_Texture_Graphics::pixel( int x, int y ) {
    if (pixel_data == nullptr) return;

    if (x >= 0 && x < width && y >= 0 && y < height) {
        Uint32* pixels = static_cast<Uint32*>(pixel_data);
        int pixel_index = y * (pitch / sizeof(Uint32)) + x;
        pixels[pixel_index] = paint_color;
    }
}

void SDL_Texture_Graphics::color( Uint32 c ) {
    paint_color = c;
}

void SDL_Texture_Graphics::close() {
    SDL_DestroyTexture(texture);
}
