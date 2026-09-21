#pragma once

#include <cstddef>
#include "Coord.h"
#include "GameConstants.h"

struct EstadoReplay {
    int movimiento;
    int tipoPieza;
    Coord posicionPieza;
    int rotaciones;
    int rotacionesHold;
    int piezaSiguienteTipo;
    int celdas[ROWS][COLS];
    int puntaje;
    int nivel;
    int lineas;
    int piezaHoldTipo;
    bool swapUsado;
    bool juegoTerminado;
};

struct NodoReplay {
    EstadoReplay dato;
    NodoReplay* ant;
    NodoReplay* sig;
    NodoReplay() : ant(NULL), sig(NULL) {}
};

class ListaReplay {
public:
    ListaReplay();
    ~ListaReplay();
    ListaReplay(const ListaReplay&) = delete;
    ListaReplay& operator=(const ListaReplay&) = delete;
    void registrar(const EstadoReplay& estado);
    bool deshacer(EstadoReplay& salida);
    bool rehacer(EstadoReplay& salida);
    void irAlInicio();
    void irAlFinal();
    bool avanzar(EstadoReplay& salida);
    bool retroceder(EstadoReplay& salida);
    void reiniciar();
    int getTamano() const;
private:
    NodoReplay* cabeza;
    NodoReplay* cola;
    NodoReplay* actual;
    int tamano;
};