#pragma once

#include <cstddef>

struct DatoEvento {
    int tipo;
    float tiempo;
    float periodo;
    DatoEvento() : tipo(0), tiempo(0.f), periodo(0.f) {}
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
    ColaEventos(const ColaEventos&) = delete;
    ColaEventos& operator=(const ColaEventos&) = delete;
    void programar(int tipo, float periodo, float tiempoActual);
    bool despachar(float tiempoActual, int& tipo);
    void vaciar();
    int getCantidad() const;
private:
    NodoEvento* frente;
    int cantidad;
    void insertarOrdenado(const DatoEvento& dato);
};