#include "Tablero.h"
#include "Pieza.h"

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

bool Tablero::cabe(const Pieza& pieza) const {
    const Coord* cs = pieza.getCeldas();
    for (int i = 0; i < 4; ++i) {
        if (!dentro(cs[i].row, cs[i].col))
            return false;
        if (celdas[cs[i].row][cs[i].col] != EMPTY_CELL)
            return false;
    }
    return true;
}

void Tablero::fijar(const Pieza& pieza) {
    const Coord* cs = pieza.getCeldas();
    for (int i = 0; i < 4; ++i) {
        celdas[cs[i].row][cs[i].col] = pieza.getTipo();
    }
}