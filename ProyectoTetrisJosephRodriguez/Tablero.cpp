#include "Tablero.h"
#include "Pieza.h"

Tablero::Tablero() {
    cabeza = NULL;
    lineasEliminadas = 0;
    limpiarTablero();
}

Tablero::~Tablero() {
    liberarMemoria();
}

void Tablero::liberarMemoria() {
    NodoFila* actual = cabeza;
    while (actual != NULL) {
        NodoFila* aux = actual->sig;
        delete actual;
        actual = aux;
    }
    cabeza = NULL;
}

void Tablero::limpiarTablero() {
    liberarMemoria();
    NodoFila* ultimo = NULL;
    for (int f = 0; f < ROWS; f++) {
        NodoFila* nuevo = new NodoFila();
        if (cabeza == NULL) {
            cabeza = nuevo;
            ultimo = nuevo;
        }
        else {
            ultimo->sig = nuevo;
            ultimo = nuevo;
        }
    }
}

NodoFila* Tablero::obtenerNodoFila(int fila) {
    if (fila < 0 || fila >= ROWS) {
        return NULL;
    }
    NodoFila* actual = cabeza;
    for (int i = 0; i < fila && actual != NULL; i++) {
        actual = actual->sig;
    }
    return actual;
}

int Tablero::getCelda(int fila, int col) {
    if (!estaDentro(fila, col)) {
        return EMPTY_CELL;
    }
    NodoFila* nodo = obtenerNodoFila(fila);
    if (nodo != NULL) {
        return nodo->celdas[col];
    }
    return EMPTY_CELL;
}

void Tablero::setCelda(int fila, int col, int tipo) {
    if (!estaDentro(fila, col)) {
        return;
    }
    NodoFila* nodo = obtenerNodoFila(fila);
    if (nodo != NULL) {
        nodo->celdas[col] = tipo;
    }
}

bool Tablero::estaDentro(int fila, int col) {
    bool filaValida = (fila >= 0 && fila < ROWS);
    bool colValida = (col >= 0 && col < COLS);
    return filaValida && colValida;
}

bool Tablero::puedeColocar(Pieza pieza) {
    const Coord* celdasPieza = pieza.getCeldas();
    
    for (int i = 0; i < 4; i++) {
        int fila = celdasPieza[i].row;
        int col = celdasPieza[i].col;
        
        if (!estaDentro(fila, col)) {
            return false;
        }
        
        if (getCelda(fila, col) != EMPTY_CELL) {
            return false;
        }
    }
    
    return true;
}

int Tablero::fijar(Pieza pieza) {
    const Coord* celdasPieza = pieza.getCeldas();
    
    for (int i = 0; i < 4; i++) {
        int fila = celdasPieza[i].row;
        int col = celdasPieza[i].col;
        if (estaDentro(fila, col)) {
            setCelda(fila, col, pieza.getTipo());
        }
    }
    
    int eliminadas = eliminarLineas();
    lineasEliminadas += eliminadas;
    return eliminadas;
}

int Tablero::getLineasEliminadas() {
    return lineasEliminadas;
}

bool Tablero::esFilaCompleta(NodoFila* nodo) {
    if (nodo == NULL) {
        return false;
    }
    for (int c = 0; c < COLS; c++) {
        if (nodo->celdas[c] == EMPTY_CELL) {
            return false;
        }
    }
    return true;
}

int Tablero::eliminarLineas() {
    int contador = 0;
    NodoFila* anterior = NULL;
    NodoFila* actual = cabeza;

    while (actual != NULL) {
        if (esFilaCompleta(actual)) {
            NodoFila* aEliminar = actual;
            if (anterior == NULL) {
                cabeza = actual->sig;
                actual = cabeza;
            }
            else {
                anterior->sig = actual->sig;
                actual = anterior->sig;
            }
            delete aEliminar;

            // Inserción en tiempo O(1) de una nueva fila vacía en la cabeza
            NodoFila* nuevaFila = new NodoFila();
            nuevaFila->sig = cabeza;
            cabeza = nuevaFila;

            if (anterior == NULL) {
                anterior = nuevaFila;
            }

            contador++;
        }
        else {
            anterior = actual;
            actual = actual->sig;
        }
    }

    return contador;
}
