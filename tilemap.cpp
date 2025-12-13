#include "tilemap.h"

Tile Tilemap::char_to_tile(char c) {
    switch (c) {
        case '#': return WALL;
        default: return EMPTY;
    }
}

Tilemap::Tilemap( int unit ) {
    this->unit = unit;
}

int Tilemap::get_width() {
    return unit * rows;
}

int Tilemap::get_height() {
    return unit * cols;
}

bool Tilemap::start( const char* filename ) {
    std::ifstream f(filename);

    if (!f.is_open()) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        return true;
    }

    char c;
    do {
        c = f.get();

        if (c == '\n')
            rows++;

        if (rows == 0)
            cols++;
    } while(c);
    rows++;

    f.seekg(0);

    Tilemap* tilemap = (Tilemap*) malloc( sizeof(Tilemap) );

    matrix = (Tile**) malloc( sizeof(Tile*) * rows );
    if (matrix == NULL) {
        std::cerr << "Error allocation matrix\n" << std::endl;
        return true;
    }

    for (int i = 0; i < rows; i++) {
        matrix[i] = (Tile*) malloc( sizeof(Tile) * cols );
        if (tilemap->matrix[i] == NULL) {
            std::cerr << "Error allocation matrix row" << std::endl;
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            f.close();
            return true;
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            c = f.get();
            matrix[i][j] = char_to_tile(c);
        }
        f.get();
    }

    f.close();
    return false;
}

void Tilemap::close() {
    for (int i = 0; i < rows; i++)
        free(matrix[i]);

    free(matrix);
}

Tilemap::~Tilemap() {
    close();
}