#include "ListaReplay.h"

ListaReplay::ListaReplay() {
    cabeza = NULL;
    cola = NULL;
    actual = NULL;
    tamano = 0;
}

ListaReplay::~ListaReplay() {
    reiniciar();
}

void ListaReplay::registrar(EstadoReplay estado) {
    if (actual != NULL && actual->sig != NULL) {
        NodoReplay* rama = actual->sig;
        while (rama != NULL) {
            NodoReplay* aux = rama->sig;
            delete rama;
            rama = aux;
            tamano--;
        }
        cola = actual;
        actual->sig = NULL;
    }

    NodoReplay* nuevo = new NodoReplay();
    nuevo->dato = estado;
    nuevo->ant = actual;
    nuevo->sig = NULL;

    if (actual == NULL) {
        cabeza = nuevo;
    }
    else {
        actual->sig = nuevo;
    }

    cola = nuevo;
    actual = nuevo;
    tamano++;
}

bool ListaReplay::deshacer(EstadoReplay& salida) {
    if (actual == NULL || actual->ant == NULL) {
        return false;
    }
    actual = actual->ant;
    salida = actual->dato;
    return true;
}

bool ListaReplay::rehacer(EstadoReplay& salida) {
    if (actual == NULL || actual->sig == NULL) {
        return false;
    }
    actual = actual->sig;
    salida = actual->dato;
    return true;
}

void ListaReplay::irAlInicio() {
    actual = cabeza;
}

void ListaReplay::irAlFinal() {
    actual = cola;
}

bool ListaReplay::avanzar(EstadoReplay& salida) {
    return rehacer(salida);
}

bool ListaReplay::retroceder(EstadoReplay& salida) {
    return deshacer(salida);
}

bool ListaReplay::obtenerActual(EstadoReplay& salida) const {
    if (actual == NULL) {
        return false;
    }
    salida = actual->dato;
    return true;
}

int ListaReplay::getIndiceActual() const {
    int idx = 0;
    NodoReplay* n = cabeza;
    while (n != NULL) {
        idx++;
        if (n == actual) {
            return idx;
        }
        n = n->sig;
    }
    return idx;
}

void ListaReplay::reiniciar() {
    NodoReplay* nodo = cabeza;
    while (nodo != NULL) {
        NodoReplay* aux = nodo->sig;
        delete nodo;
        nodo = aux;
    }
    cabeza = NULL;
    cola = NULL;
    actual = NULL;
    tamano = 0;
}

int ListaReplay::getTamano() {
    return tamano;
}