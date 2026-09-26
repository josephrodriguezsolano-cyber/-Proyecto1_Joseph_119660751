#include "ColaPiezas.h"
#include <cstdlib>

ColaPiezas::ColaPiezas() {
    frente = NULL;
    fin = NULL;
    cantidad = 0;
    reiniciar();
}

ColaPiezas::~ColaPiezas() {
    vaciar();
}

void ColaPiezas::encolar(Pieza p) {
    NodoPieza* nuevo = new NodoPieza(p);
    if (fin == NULL) {
        frente = nuevo;
        fin = nuevo;
    }
    else {
        fin->sig = nuevo;
        fin = nuevo;
    }
    cantidad++;
}

Pieza ColaPiezas::desencolar() {
    if (estaVacia()) {
        rellenarBolsa();
    }

    NodoPieza* aux = frente;
    Pieza resultado = aux->pieza;
    frente = frente->sig;
    if (frente == NULL) {
        fin = NULL;
    }
    delete aux;
    cantidad--;

    if (cantidad < 4) {
        rellenarBolsa();
    }

    return resultado;
}

Pieza ColaPiezas::consultarFrente() const {
    if (estaVacia()) {
        return Pieza(PIEZA_I);
    }
    return frente->pieza;
}

Pieza ColaPiezas::consultarPorIndice(int indice) const {
    if (indice < 0 || estaVacia()) {
        return Pieza(PIEZA_I);
    }
    NodoPieza* actual = frente;
    for (int i = 0; i < indice && actual != NULL; ++i) {
        actual = actual->sig;
    }
    if (actual != NULL) {
        return actual->pieza;
    }
    return Pieza(PIEZA_I);
}

int ColaPiezas::getCantidad() const {
    return cantidad;
}

bool ColaPiezas::estaVacia() const {
    return frente == NULL;
}

void ColaPiezas::vaciar() {
    while (frente != NULL) {
        NodoPieza* aux = frente;
        frente = frente->sig;
        delete aux;
    }
    fin = NULL;
    cantidad = 0;
}

void ColaPiezas::rellenarBolsa() {
    int bolsa[PIECE_TYPES] = {
        PIEZA_I, PIEZA_O, PIEZA_T, PIEZA_S, PIEZA_Z, PIEZA_J, PIEZA_L
    };

    for (int i = PIECE_TYPES - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        int aux = bolsa[i];
        bolsa[i] = bolsa[j];
        bolsa[j] = aux;
    }

    for (int i = 0; i < PIECE_TYPES; ++i) {
        encolar(Pieza(bolsa[i]));
    }
}

void ColaPiezas::reiniciar() {
    vaciar();
    rellenarBolsa();
    rellenarBolsa();
}
