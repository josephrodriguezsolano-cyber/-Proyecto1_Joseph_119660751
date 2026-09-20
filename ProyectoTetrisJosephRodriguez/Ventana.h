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
    Pieza piezaSiguiente;
    sf::Font fuente;
    bool juegoTerminado;
    float intervaloCaida;
    int puntaje;
    int nivel;
    int lineasTotales;
    void bajarPieza();
    void fijarPieza();
    void generarPieza();
    void caidaRapida();
    void moverPieza(int df, int dc);
    void rotarPieza();
    void actualizarNivel();
    void dibujarTablero(sf::RenderWindow& w);
    void dibujarFondo(sf::RenderWindow& w);
    void dibujarPieza(sf::RenderWindow& w);
    void dibujarCelda(sf::RenderWindow& w, int fila, int col, int tipo);
    void dibujarGema(sf::RenderWindow& w, float x, float y, float tamano, int tipo);
    void dibujarTexto(sf::RenderWindow& w, const std::string& cadena, float x, float y, float tamano, sf::Color color);
    void dibujarSiguiente(sf::RenderWindow& w);
    void dibujarHud(sf::RenderWindow& w);
    void dibujarFin(sf::RenderWindow& w);
};