#include "GestorPuntajes.h"
#include "ExceptionManager.h"
#include <fstream>

using namespace std;

GestorPuntajes::GestorPuntajes() {
    jugadorActual = "";
    ultimoJugador = "";
    cantidad = 0;
    metodo = 0;
    for (int i = 0; i < MAX_TABLA; i++) {
        lineas[i] = 0;
        nombres[i] = "";
    }
    cargar();
}

GestorPuntajes::~GestorPuntajes() {
}

void GestorPuntajes::cargar() {
    ifstream archivo("recursos/puntajes.txt");
    if (!archivo.is_open()) {
        return;
    }
    string etiqueta;
    archivo >> etiqueta;
    if (etiqueta == "ultimo") {
        archivo >> ultimoJugador;
    }
    cantidad = 0;
    while (cantidad < MAX_TABLA && archivo >> lineas[cantidad] >> nombres[cantidad]) {
        cantidad++;
    }
    archivo.close();
}

void GestorPuntajes::guardar() {
    ofstream archivo("recursos/puntajes.txt");
    if (!archivo.is_open()) {
        throw ExceptionManager(ExceptionManager::FileLoad, "recursos/puntajes.txt");
    }
    archivo << "ultimo " << ultimoJugador << endl;
    for (int i = 0; i < cantidad; i++) {
        archivo << lineas[i] << " " << nombres[i] << endl;
    }
    archivo.close();
}

void GestorPuntajes::establecerJugador(string nombre) {
    jugadorActual = nombre;
}

string GestorPuntajes::getJugador() {
    return jugadorActual;
}

int GestorPuntajes::existeJugador(string nombre) {
    for (int i = 0; i < cantidad; i++) {
        if (nombres[i] == nombre) {
            return i;
        }
    }
    return -1;
}

int GestorPuntajes::getIndiceUltimoJugador() {
    for (int i = 0; i < cantidad; i++) {
        if (nombres[i] == ultimoJugador) {
            return i;
        }
    }
    return 0;
}

void GestorPuntajes::registrarLineas(int lineasCompletadas) {
    if (jugadorActual.empty()) {
        return;
    }
    int indice = existeJugador(jugadorActual);
    if (indice >= 0) {
        if (lineasCompletadas > lineas[indice]) {
            lineas[indice] = lineasCompletadas;
        }
    }
    else if (cantidad < MAX_TABLA) {
        lineas[cantidad] = lineasCompletadas;
        nombres[cantidad] = jugadorActual;
        cantidad++;
    }
    else {
        int minimo = 0;
        for (int i = 1; i < cantidad; i++) {
            if (lineas[i] < lineas[minimo]) {
                minimo = i;
            }
        }
        if (lineasCompletadas > lineas[minimo]) {
            lineas[minimo] = lineasCompletadas;
            nombres[minimo] = jugadorActual;
        }
    }
    ultimoJugador = jugadorActual;

    if (metodo == 0) {
        ordenarPorInsercion();
    }
    else {
        ordenarQuickSort(0, cantidad - 1);
    }
    guardar();
}

void GestorPuntajes::alternarOrdenamiento() {
    if (metodo == 0) {
        metodo = 1;
        ordenarQuickSort(0, cantidad - 1);
    }
    else {
        metodo = 0;
        ordenarPorInsercion();
    }
}

int GestorPuntajes::getMetodo() {
    return metodo;
}

int GestorPuntajes::getCantidad() {
    return cantidad;
}

int GestorPuntajes::getLineasJugador(int indice) {
    if (indice < 0 || indice >= cantidad) {
        return 0;
    }
    return lineas[indice];
}

string GestorPuntajes::getNombreJugador(int indice) {
    if (indice < 0 || indice >= cantidad) {
        return nombres[0];
    }
    return nombres[indice];
}

void GestorPuntajes::ordenarPorInsercion() {
    for (int i = 1; i < cantidad; i++) {
        int valor = lineas[i];
        string nombre = nombres[i];
        int j = i - 1;
        while (j >= 0 && lineas[j] < valor) {
            lineas[j + 1] = lineas[j];
            nombres[j + 1] = nombres[j];
            j--;
        }
        lineas[j + 1] = valor;
        nombres[j + 1] = nombre;
    }
}

void GestorPuntajes::ordenarQuickSort(int inicio, int fin) {
    if (inicio >= fin) {
        return;
    }
    int pivote = 0;
    particion(inicio, fin, pivote);
    ordenarQuickSort(inicio, pivote - 1);
    ordenarQuickSort(pivote + 1, fin);
}

void GestorPuntajes::particion(int inicio, int fin, int& pivote) {
    int valorPivote = lineas[fin];
    int i = inicio;
    for (int j = inicio; j < fin; j++) {
        if (lineas[j] >= valorPivote) {
            intercambiar(i, j);
            i++;
        }
    }
    intercambiar(i, fin);
    pivote = i;
}

void GestorPuntajes::intercambiar(int a, int b) {
    int auxLineas = lineas[a];
    lineas[a] = lineas[b];
    lineas[b] = auxLineas;
    string auxNombre = nombres[a];
    nombres[a] = nombres[b];
    nombres[b] = auxNombre;
}
