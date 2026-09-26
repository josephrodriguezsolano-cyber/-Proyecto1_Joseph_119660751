#include "PilaHold.h"
#include "GameConstants.h"

PilaHold::PilaHold() {
    tamano = 0;
    capacidad = 1;
    cima = NULL;
}

PilaHold::~PilaHold() {
    clear();
}

bool PilaHold::isEmpty() {
    return cima == NULL;
}

void PilaHold::push(Pieza pieza) {
    if (tamano >= capacidad) {
        return;
    }
    NodoHold* nuevo = new NodoHold();
    nuevo->pieza = pieza;
    nuevo->sig = cima;
    cima = nuevo;
    tamano++;
}

NodoHold* PilaHold::pop() {
    if (isEmpty()) {
        return NULL;
    }
    NodoHold* actual = cima;
    cima = cima->sig;
    actual->sig = NULL;
    tamano--;
    return actual;
}

Pieza PilaHold::top() {
    if (isEmpty()) {
        return Pieza(PIEZA_I);
    }
    return cima->pieza;
}

void PilaHold::clear() {
    while (cima != NULL) {
        NodoHold* aux = cima;
        cima = cima->sig;
        delete aux;
    }
    tamano = 0;
}

void PilaHold::setTop(Pieza pieza) {
    if (isEmpty()) {
        push(pieza);
    }
    else {
        cima->pieza = pieza;
    }
}

int PilaHold::getTamano() {
    return tamano;
}
