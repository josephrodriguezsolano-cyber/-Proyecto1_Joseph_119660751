#pragma once

#include "Coord.h"
#include "GameConstants.h"

class Pieza {
public:
    Pieza();
    Pieza(int tipo);
    static Pieza crearAleatoria();
    int getTipo() const;
    const Coord* getCeldas() const;
    Coord getPosicion() const;
    void setPosicion(int fila, int col);
    void mover(int df, int dc);
    void rotar();
private:
    int tipo;
    int forma[4][4];
    Coord celdas[4];
    Coord posicion;
    void actualizarCeldas();
};