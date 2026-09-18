#pragma once

#include <SFML/Graphics.hpp>
#include "TexturasBloques.h"
#include "Tablero.h"
#include "Pieza.h"

class Ventana {
public:
    Ventana();
    void ejecutar();
private:
    TexturasBloques texturas;
    Tablero tablero;
    Pieza piezaActual;
    bool juegoTerminado;
    float intervaloCaida;
    void bajarPieza();
    void fijarPieza();
    void generarPieza();
    void caidaRapida();
    void moverPieza(int df, int dc);
    void rotarPieza();
    void dibujarTablero(sf::RenderWindow& w);
    void dibujarFondo(sf::RenderWindow& w);
    void dibujarPieza(sf::RenderWindow& w);
    void dibujarCelda(sf::RenderWindow& w, int fila, int col, int tipo);
    void dibujarFin(sf::RenderWindow& w);
};