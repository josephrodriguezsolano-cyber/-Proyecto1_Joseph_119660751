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
    void dibujarTablero(sf::RenderWindow& w);
    void dibujarPieza(sf::RenderWindow& w);
    void dibujarCelda(sf::RenderWindow& w, int fila, int col, int tipo);
};