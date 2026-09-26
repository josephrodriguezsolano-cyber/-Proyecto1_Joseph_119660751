#include "ColaEventos.h"

ColaEventos::ColaEventos() {
    frente = NULL;
    cantidad = 0;
}

ColaEventos::~ColaEventos() {
    vaciarCola();
}

void ColaEventos::programar(int tipo, float periodo, float tiempoActual) {
    DatoEvento dato;
    dato.tipo = tipo;
    dato.tiempo = tiempoActual + periodo;
    dato.periodo = periodo;
    insertarOrdenado(dato);
}

bool ColaEventos::despachar(float tiempoActual, int& tipo) {
    if (frente == NULL) {
        return false;
    }
    if (frente->dato.tiempo > tiempoActual) {
        return false;
    }

    NodoEvento* aux = frente;
    tipo = aux->dato.tipo;
    float periodo = aux->dato.periodo;
    float nuevoTiempo = aux->dato.tiempo + periodo;
    frente = frente->sig;
    delete aux;
    cantidad--;

    DatoEvento dato;
    dato.tipo = tipo;
    dato.tiempo = nuevoTiempo;
    dato.periodo = periodo;
    insertarOrdenado(dato);
    return true;
}

void ColaEventos::vaciarCola() {
    NodoEvento* nodo = frente;
    while (nodo != NULL) {
        NodoEvento* aux = nodo->sig;
        delete nodo;
        nodo = aux;
    }
    frente = NULL;
    cantidad = 0;
}

int ColaEventos::getCantidad() {
    return cantidad;
}

void ColaEventos::insertarOrdenado(DatoEvento dato) {
    NodoEvento* nuevo = new NodoEvento();
    nuevo->dato = dato;
    nuevo->sig = NULL;

    if (frente == NULL) {
        frente = nuevo;
        cantidad++;
        return;
    }

    NodoEvento* actual = frente;
    NodoEvento* anterior = NULL;
    while (actual != NULL && actual->dato.tiempo <= dato.tiempo) {
        anterior = actual;
        actual = actual->sig;
    }

    if (anterior == NULL) {
        nuevo->sig = frente;
        frente = nuevo;
    }
    else {
        anterior->sig = nuevo;
        nuevo->sig = actual;
    }
    cantidad++;
}