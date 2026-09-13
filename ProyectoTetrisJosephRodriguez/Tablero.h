#pragma once

#include "GameConstants.h"

class Pieza;

class Tablero {
public:
    Tablero();
    void limpiar();
    int getCelda(int fila, int col) const;
    void setCelda(int fila, int col, int tipo);
    bool dentro(int fila, int col) const;
    bool cabe(const Pieza& pieza) const;
    void fijar(const Pieza& pieza);
private:
    int celdas[ROWS][COLS];
};