#include "Pieza.h"

Pieza::Pieza() : tipo(PIEZA_I) {
    setPosicion(0, COLS / 2 - 1);
}

Pieza::Pieza(int t) : tipo(t) {
    setPosicion(0, COLS / 2 - 1);
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
}
