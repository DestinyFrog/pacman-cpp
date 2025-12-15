#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <iostream>
#include <cmath>

#include "util.h"

using namespace std;

class Graphics {    
    protected:
    int width;
    int height;
    
    void hline( int y, int ax, int bx );
    void vline( int x, int ay, int by );

    public:
    Graphics( int w, int h );

    virtual void pixel( int x, int y );
    void line( int ax, int ay, int bx, int by );
    void square( int x, int y, int l );
    void rect( int x, int y, int lx, int ly );
    void circle( int x, int y, int radius );
    void circle( int x, int y, int radius, int from, int to );
};

#endif // GRAPHICS_H_