#pragma once

#include <cstddef>
#include "Pieza.h"

struct NodoHold {
    Pieza pieza;
    NodoHold* sig;
    NodoHold() : sig(NULL) {}
};

class PilaHold {
public:
    PilaHold();
    ~PilaHold();
    PilaHold(const PilaHold&) = delete;
    PilaHold& operator=(const PilaHold&) = delete;
    bool isEmpty() const;
    void push(const Pieza& pieza);
    NodoHold* pop();
    Pieza top() const;
    void clear();
    void setTop(const Pieza& pieza);
    int getTamano() const;
private:
    int tamano;
    int capacidad;
    NodoHold* head;
};