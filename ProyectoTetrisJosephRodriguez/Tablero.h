#pragma once

#include "GameConstants.h"
#include "Pieza.h"

class Tablero {
public:
    Tablero();
    void limpiarTablero();
    int getCelda(int fila, int col);
    void setCelda(int fila, int col, int tipo);
    bool estaDentro(int fila, int col);
    bool puedeColocar(Pieza pieza);
    int fijar(Pieza pieza);
    int getLineasEliminadas();
private:
    int celdas[ROWS][COLS];
    int lineasEliminadas;
    bool esFilaCompleta(int fila);
    void bajarFilas(int fila);
    int eliminarLineas();
};