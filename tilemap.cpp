#ifndef TILEMAP_H_
#define TILEMAP_H_

#include <cstdlib>

#include <SDL2/SDL.h>

typedef enum {
    WALL,
    EMPTY
} Tile;

class Tilemap {
    public:
    int unit;
    int rows;
    int cols;
    Tile** matrix;

    Tile char_to_tile(char c) {
        switch (c) {
            case '#': return WALL;
            default: return EMPTY;
        }
    }

    public:
    Tilemap( int unit ) {
        this->unit = unit;
    }

    int get_width() {
        return unit * rows;
    }

    int get_height() {
        return unit * cols;
    }

    bool start( const char* filename ) {
        FILE* f = fopen(filename, "r");
        if (f == NULL) {
            printf("Error opening file: %s\n", filename);
            return true;
        }

        char c;
        do {
            c = (char) fgetc(f);

            if (c == '\n')
                rows++;

            if (rows == 0)
                cols++;
        } while(c != EOF);
        rows++;

        fseek(f, 0, SEEK_SET);

        Tilemap* tilemap = (Tilemap*) malloc( sizeof(Tilemap) );

        matrix = (Tile**) malloc( sizeof(Tile*) * rows );
        if (matrix == NULL) {
            printf("Error allocation matrix\n");
            return true;
        }

        for (int i = 0; i < rows; i++) {
            matrix[i] = (Tile*) malloc( sizeof(Tile) * cols );
            if (tilemap->matrix[i] == NULL) {
                printf("Error allocation matrix row\n");
                for (int j = 0; j < i; j++) {
                    free(matrix[j]);
                }
                free(matrix);
                fclose(f);
                return true;
            }
        }

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                c = (char) fgetc(f);
                matrix[i][j] = char_to_tile(c);
            }
            fgetc(f);
        }

        fclose(f);
    }

    void close() {
        for (int i = 0; i < rows; i++)
            free(matrix[i]);
        free(matrix);
    }

    ~Tilemap() {
        close();
    }
};

#endif // TILEMAP_H_