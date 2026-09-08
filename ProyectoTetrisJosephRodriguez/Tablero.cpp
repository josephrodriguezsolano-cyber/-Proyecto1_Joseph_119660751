#include "Tablero.h"

Tablero::Tablero() {
    limpiar();
}

void Tablero::limpiar() {
    for (int f = 0; f < ROWS; ++f)
        for (int c = 0; c < COLS; ++c)
            celdas[f][c] = EMPTY_CELL;
}

int Tablero::getCelda(int fila, int col) const {
    return celdas[fila][col];
}

void Tablero::setCelda(int fila, int col, int tipo) {
    celdas[fila][col] = tipo;
}

bool Tablero::dentro(int fila, int col) const {
    return fila >= 0 && fila < ROWS && col >= 0 && col < COLS;
}
