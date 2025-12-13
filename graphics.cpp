#include "graphics.h"

Graphics::Graphics( int w, int h ):
    width(w),
    height(h)
{}

void Graphics::hline( int y, int ax, int bx ) {
    const int direction_x = ax < bx ? 1 : -1;
    for (int x = ax; x != bx; x += direction_x)
        pixel( x, y );
}

void Graphics::vline( int x, int ay, int by ) {
    const int direction_y = ay < by ? 1 : -1;
    for (int y = ay; y != by; y += direction_y)
        pixel( x, y );
}

void Graphics::pixel( int x, int y ) {
    std::cerr << "metodo [pixel] nao implementado" << std::endl;
}

void Graphics::line( int ax, int ay, int bx, int by ) {
    if (ax == bx)
        return vline( ax, ay, by );
    
    if (ay == by)
        return hline( ay, ax, bx );

    const int delta_x = abs(bx - ax);
    const int delta_y = abs(by - ay);

    const double direction_x = bx < ax ? -1 : 1;
    const double direction_y = by < ay ? -1 : 1;
    const double uy = (double) delta_y / delta_x;

    const int delta = delta_x > delta_y
        ? delta_x
        : delta_y;

    float x = ax;
    float y = ay;
    for (int i = 0; i < delta; i++) {
        x += (double) delta_x / delta * direction_x;
        y += (double) delta_y / delta * direction_y;
        pixel( floor(x), floor(y) );
    }
}

void Graphics::square( int x, int y, int l ) {
    hline( x, y, y + l );
    hline( x + l, y, y + l );
    vline( y, x, x + l );
    vline( y + l, x, x + l );
}

void Graphics::rect( int x, int y, int lx, int ly ) {
    hline( x, y, y + ly );
    hline( x + lx, y, y + ly );
    vline( y, x, x + lx );
    vline( y + ly, x, x + lx );
}