#pragma once

#include "Pieza.h"

struct NodoPieza {
    Pieza pieza;
    NodoPieza* sig;

    NodoPieza(Pieza p) : pieza(p), sig(NULL) {}
};

class ColaPiezas {
public:
    ColaPiezas();
    ~ColaPiezas();

    void encolar(Pieza p);
    Pieza desencolar();
    Pieza consultarFrente() const;
    Pieza consultarPorIndice(int indice) const;
    int getCantidad() const;
    bool estaVacia() const;
    void vaciar();
    void rellenarBolsa();
    void reiniciar();

private:
    NodoPieza* frente;
    NodoPieza* fin;
    int cantidad;
};
