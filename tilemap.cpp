#include "tilemap.h"

Tile Tilemap::char_to_tile(char c) {
    switch (c) {
        case '#': return WALL;
        case 'A': return PACMAN;
        default: return EMPTY;
    }
}

int Tilemap::get_width() {
    return UNIT * rows;
}

int Tilemap::get_height() {
    return UNIT * cols;
}

bool Tilemap::start(const char* filename) {
    std::ifstream f(filename);
    if (!f.is_open()) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        return true;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(f, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        lines.push_back(line);
    }

    if (lines.empty()) {
        std::cerr << "Arquivo vazio!" << std::endl;
        return true;
    }

    rows = lines.size();
    cols = lines[0].size();

    matrix = (Tile**) malloc(sizeof(Tile*) * rows);
    if (!matrix) {
        std::cerr << "Erro ao alocar matriz!" << std::endl;
        return true;
    }

    for (int i = 0; i < rows; i++) {
        matrix[i] = (Tile*) malloc(sizeof(Tile) * cols);
        if (!matrix[i]) {
            for (int j = 0; j < i; j++) free(matrix[j]);
            free(matrix);
            return true;
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = char_to_tile(lines[i][j]);
        }
    }

    f.close();
    return false;
}

void Tilemap::close() {
    for (int i = 0; i < rows; i++)
        free(matrix[i]);

    free(matrix);
}

bool Tilemap::paint(SDL_Texture_Graphics* texture) {
    (*texture).lock();
    (*texture).color( 0x0000FFFF );
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == WALL)
                continue;

            int x = UNIT * j;
            int y = UNIT * i;

            if (i > 0 && matrix[i - 1][j] == WALL)
                (*texture).line( x, y, x + UNIT, y );

            if (i < rows - 1  && matrix[i + 1][j] == WALL)
                (*texture).line( x, y + UNIT, x + UNIT, y + UNIT);

            if (j > 0 && matrix[i][j - 1] == WALL)
                (*texture).line( x, y, x, y + UNIT );

            if (j < cols - 1 && matrix[i][j + 1] == WALL)
                (*texture).line( x + UNIT, y, x + UNIT, y + UNIT);
        }
    }
    (*texture).unlock();

    return false;
}