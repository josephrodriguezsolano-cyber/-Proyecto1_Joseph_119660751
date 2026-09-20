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
    int fijar(const Pieza& pieza);
    int getLineasEliminadas() const;
private:
    int celdas[ROWS][COLS];
    int lineasEliminadas;
    bool filaCompleta(int fila) const;
    void bajarFilas(int fila);
    int eliminarLineas();
};