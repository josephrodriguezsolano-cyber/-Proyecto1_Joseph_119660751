#include "Pieza.h"
#include <cstdlib>

namespace {
    const Coord FORMAS[PIECE_TYPES][4] = {
        { Coord(1, 0), Coord(1, 1), Coord(1, 2), Coord(1, 3) },
        { Coord(0, 0), Coord(0, 1), Coord(1, 0), Coord(1, 1) },
        { Coord(0, 1), Coord(1, 0), Coord(1, 1), Coord(1, 2) },
        { Coord(0, 1), Coord(0, 2), Coord(1, 0), Coord(1, 1) },
        { Coord(0, 0), Coord(0, 1), Coord(1, 1), Coord(1, 2) },
        { Coord(0, 0), Coord(1, 0), Coord(1, 1), Coord(1, 2) },
        { Coord(0, 2), Coord(1, 0), Coord(1, 1), Coord(1, 2) }
    };
    constexpr int FORMA_ANCHO = 4;
}

Pieza::Pieza() : tipo(PIEZA_I) {
    for (int i = 0; i < 4; ++i)
        forma[i] = FORMAS[tipo][i];
    setPosicion(0, COLS / 2 - 2);
}

Pieza::Pieza(int t) : tipo(t) {
    for (int i = 0; i < 4; ++i)
        forma[i] = FORMAS[tipo][i];
    setPosicion(0, COLS / 2 - 2);
}

Pieza Pieza::crearAleatoria() {
    return Pieza(rand() % PIECE_TYPES);
}

int Pieza::getTipo() const {
    return tipo;
}

const Coord* Pieza::getCeldas() const {
    return celdas;
}

Coord Pieza::getPosicion() const {
    return posicion;
}

void Pieza::setPosicion(int fila, int col) {
    posicion = Coord(fila, col);
    actualizarCeldas();
}

void Pieza::mover(int df, int dc) {
    setPosicion(posicion.row + df, posicion.col + dc);
}

void Pieza::rotar() {
    for (int i = 0; i < 4; ++i) {
        int nr = forma[i].col;
        int nc = FORMA_ANCHO - 1 - forma[i].row;
        forma[i] = Coord(nr, nc);
    }
    actualizarCeldas();
}

void Pieza::actualizarCeldas() {
    for (int i = 0; i < 4; ++i) {
        celdas[i].row = forma[i].row + posicion.row;
        celdas[i].col = forma[i].col + posicion.col;
    }
}