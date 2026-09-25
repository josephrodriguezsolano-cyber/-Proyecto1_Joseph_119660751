#pragma once

#include "GameConstants.h"
#include <string>

class GestorPuntajes {
public:
    GestorPuntajes();
    ~GestorPuntajes();
    void cargar();
    void guardar();
    void establecerJugador(std::string nombre);
    std::string getJugador();
    int existeJugador(std::string nombre);
    int getIndiceUltimoJugador();
    void registrarLineas(int lineasCompletadas);
    void alternarOrdenamiento();
    int getMetodo();
    int getCantidad();
    int getLineasJugador(int indice);
    std::string getNombreJugador(int indice);
private:
    int lineas[MAX_TABLA];
    std::string nombres[MAX_TABLA];
    std::string jugadorActual;
    std::string ultimoJugador;
    int cantidad;
    int metodo;
    void ordenarPorInsercion();
    void ordenarQuickSort(int inicio, int fin);
    void particion(int inicio, int fin, int& pivote);
    void intercambiar(int a, int b);
};