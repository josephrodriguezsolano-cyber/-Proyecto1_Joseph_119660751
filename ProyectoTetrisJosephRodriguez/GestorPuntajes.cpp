#include "GestorPuntajes.h"
#include "ExceptionManager.h"
#include <fstream>

GestorPuntajes::GestorPuntajes()
    : jugadorActual(""),
      ultimoJugador(""),
      cantidad(0),
      metodo(0) {
    for (int i = 0; i < MAX_TABLA; ++i) {
        lineas[i] = 0;
        nombres[i] = "";
    }
    cargar();
}

GestorPuntajes::~GestorPuntajes() {
}

void GestorPuntajes::cargar() {
    std::ifstream archivo("recursos/puntajes.txt");
    if (!archivo.is_open()) {
        return;
    }
    std::string etiqueta;
    archivo >> etiqueta;
    if (etiqueta == "ultimo") {
        archivo >> ultimoJugador;
    }
    cantidad = 0;
    while (cantidad < MAX_TABLA && archivo >> lineas[cantidad] >> nombres[cantidad]) {
        ++cantidad;
    }
    archivo.close();
}

void GestorPuntajes::guardar() {
    std::ofstream archivo("recursos/puntajes.txt");
    if (!archivo.is_open()) {
        throw ExceptionManager(ExceptionManager::FileLoad, "recursos/puntajes.txt");
    }
    archivo << "ultimo " << ultimoJugador << std::endl;
    for (int i = 0; i < cantidad; ++i) {
        archivo << lineas[i] << " " << nombres[i] << std::endl;
    }
    archivo.close();
}

void GestorPuntajes::establecerJugador(const std::string& nombre) {
    jugadorActual = nombre;
}

std::string GestorPuntajes::getJugador() const {
    return jugadorActual;
}

int GestorPuntajes::existeJugador(const std::string& nombre) const {
    for (int i = 0; i < cantidad; ++i) {
        if (nombres[i] == nombre) {
            return i;
        }
    }
    return -1;
}

int GestorPuntajes::getIndiceUltimoJugador() const {
    for (int i = 0; i < cantidad; ++i) {
        if (nombres[i] == ultimoJugador) {
            return i;
        }
    }
    return 0;
}

void GestorPuntajes::agendarLineas(int lineasCompletadas) {
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
        ++cantidad;
    }
    else {
        int minimo = 0;
        for (int i = 1; i < cantidad; ++i) {
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

void GestorPuntajes::alternarMetodo() {
    if (metodo == 0) {
        metodo = 1;
        ordenarQuickSort(0, cantidad - 1);
    }
    else {
        metodo = 0;
        ordenarPorInsercion();
    }
}

int GestorPuntajes::getMetodo() const {
    return metodo;
}

int GestorPuntajes::getCantidad() const {
    return cantidad;
}

int GestorPuntajes::getLineasJugador(int indice) const {
    if (indice < 0 || indice >= cantidad) {
        return 0;
    }
    return lineas[indice];
}

const std::string& GestorPuntajes::getNombreJugador(int indice) const {
    if (indice < 0 || indice >= cantidad) {
        return nombres[0];
    }
    return nombres[indice];
}

void GestorPuntajes::ordenarPorInsercion() {
    for (int i = 1; i < cantidad; ++i) {
        int valor = lineas[i];
        std::string nombre = nombres[i];
        int j = i - 1;
        while (j >= 0 && lineas[j] < valor) {
            lineas[j + 1] = lineas[j];
            nombres[j + 1] = nombres[j];
            --j;
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
    for (int j = inicio; j < fin; ++j) {
        if (lineas[j] >= valorPivote) {
            intercambiar(i, j);
            ++i;
        }
    }
    intercambiar(i, fin);
    pivote = i;
}

void GestorPuntajes::intercambiar(int a, int b) {
    int auxLineas = lineas[a];
    lineas[a] = lineas[b];
    lineas[b] = auxLineas;
    std::string auxNombre = nombres[a];
    nombres[a] = nombres[b];
    nombres[b] = auxNombre;
}