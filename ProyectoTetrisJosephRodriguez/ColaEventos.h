#pragma once

#include <cstddef>

struct DatoEvento {
    int tipo;
    float tiempo;
    float periodo;

    DatoEvento() : tipo(0), tiempo(0.0f), periodo(0.0f) {}
};

struct NodoEvento {
    DatoEvento dato;
    NodoEvento* sig;

    NodoEvento() : sig(NULL) {}
};

class ColaEventos {
public:
    ColaEventos();
    ~ColaEventos();
    void programar(int tipo, float periodo, float tiempoActual);
    bool despachar(float tiempoActual, int& tipo);
    void vaciarCola();
    int getCantidad();
private:
    NodoEvento* frente;
    int cantidad;
    void insertarOrdenado(DatoEvento dato);
};
