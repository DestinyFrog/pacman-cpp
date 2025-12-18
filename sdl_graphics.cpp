#include "sdl_graphics.h"

SDL_Graphics::SDL_Graphics( SDL_Renderer* render, int w, int h ):
    Graphics( w, h ),
    render( render )
{}

void SDL_Graphics::color( int r, int g, int b, int a ) {
    SDL_SetRenderDrawColor( render, r, g, b, a );
}

void SDL_Graphics::pixel( int x, int y ) {
    if (x > 0 && x < width && y > 0 && y < height)
        SDL_RenderDrawPoint(render, x, y);
}