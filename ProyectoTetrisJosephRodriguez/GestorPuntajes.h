#pragma once

#include "GameConstants.h"
#include <string>

using namespace std;

class GestorPuntajes {
public:
    GestorPuntajes();
    ~GestorPuntajes();
    void cargar();
    void guardar();
    void establecerJugador(string nombre);
    string getJugador();
    int existeJugador(string nombre);
    int getIndiceUltimoJugador();
    void registrarLineas(int lineasCompletadas);
    void alternarOrdenamiento();
    int getMetodo();
    int getCantidad();
    int getLineasJugador(int indice);
    string getNombreJugador(int indice);
private:
    int lineas[MAX_TABLA];
    string nombres[MAX_TABLA];
    string jugadorActual;
    string ultimoJugador;
    int cantidad;
    int metodo;
    void ordenarPorInsercion();
    void ordenarQuickSort(int inicio, int fin);
    void particion(int inicio, int fin, int& pivote);
    void intercambiar(int a, int b);
};