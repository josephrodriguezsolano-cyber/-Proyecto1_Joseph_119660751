#pragma once

#include "Coord.h"
#include "GameConstants.h"

class Pieza {
public:
    Pieza();
    Pieza(int tipo);
    int getTipo() const;
    const Coord* getCeldas() const;
    Coord getPosicion() const;
    void setPosicion(int fila, int col);
private:
    int tipo;
    Coord celdas[4];
    Coord posicion;
};
