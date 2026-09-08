#pragma once

#include "GameConstants.h"

class Tablero {
public:
    Tablero();
    void limpiar();
    int getCelda(int fila, int col) const;
    void setCelda(int fila, int col, int tipo);
    bool dentro(int fila, int col) const;
private:
    int celdas[ROWS][COLS];
};
