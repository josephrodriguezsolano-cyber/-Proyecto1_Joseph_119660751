#pragma once

#include "GameConstants.h"
#include <string>

class GestorPuntajes {
public:
    GestorPuntajes();
    ~GestorPuntajes();
    GestorPuntajes(const GestorPuntajes&) = delete;
    GestorPuntajes& operator=(const GestorPuntajes&) = delete;
    void cargar();
    void guardar();
    void establecerJugador(const std::string& nombre);
    std::string getJugador() const;
    int existeJugador(const std::string& nombre) const;
    int getIndiceUltimoJugador() const;
    void agendarLineas(int lineasCompletadas);
    void alternarMetodo();
    int getMetodo() const;
    int getCantidad() const;
    int getLineasJugador(int indice) const;
    const std::string& getNombreJugador(int indice) const;
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