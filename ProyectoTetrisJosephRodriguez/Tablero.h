#pragma once

#include "GameConstants.h"
#include "Pieza.h"

struct NodoFila {
    int celdas[COLS];
    NodoFila* sig;

    NodoFila() {
        sig = NULL;
        for (int c = 0; c < COLS; c++) {
            celdas[c] = EMPTY_CELL;
        }
    }
};

class Tablero {
public:
    Tablero();
    ~Tablero();
    void limpiarTablero();
    int getCelda(int fila, int col);
    void setCelda(int fila, int col, int tipo);
    bool estaDentro(int fila, int col);
    bool puedeColocar(Pieza pieza);
    int fijar(Pieza pieza);
    int getLineasEliminadas();
private:
    NodoFila* cabeza;
    int lineasEliminadas;
    NodoFila* obtenerNodoFila(int fila);
    bool esFilaCompleta(NodoFila* nodo);
    int eliminarLineas();
    void liberarMemoria();
};