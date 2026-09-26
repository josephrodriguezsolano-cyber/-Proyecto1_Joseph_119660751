#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "TexturasBloques.h"
#include "Tablero.h"
#include "Pieza.h"
#include "PilaHold.h"
#include "ListaReplay.h"
#include "ColaEventos.h"
#include "ColaPiezas.h"
#include "GestorPuntajes.h"

class Ventana {
public:
    Ventana();
    void ejecutar();
private:
    TexturasBloques texturas;
    Tablero tablero;
    Pieza piezaActual;
    ColaPiezas colaPiezas;
    PilaHold pilaHold;
    ListaReplay listaReplay;
    ColaEventos colaEventos;
    GestorPuntajes gestorPuntajes;
    EstadoReplay actualReplay;
    sf::Font fuente;
    bool juegoTerminado;
    bool enReplay;
    bool pausado;
    bool swapUsado;
    bool partidaGuardada;
    bool mostrarModalFin;
    bool autoReplay;
    float tiempoAutoReplay;
    float intervaloCaida;
    float tiempoPartida;
    int estado;
    int opcionMenu;
    int modoMenu;
    int indiceJugadorMenu;
    std::string nombreEntrada;
    int puntaje;
    int nivel;
    int lineasTotales;
    int rotaciones;
    int rotacionesHold;
    void bajarPieza();
    void fijarPieza();
    void generarPieza();
    void caidaRapida();
    void moverPieza(int df, int dc);
    void rotarPieza();
    void usarHold();
    void actualizarNivel();
    void registrarMovimiento(int mov);
    EstadoReplay capturarEstado(int mov);
    void restaurarEstado(EstadoReplay estado);
    void deshacer();
    void rehacer();
    void reiniciarPartida();
    void iniciarJuego(std::string nombre);
    void procesarEvento(int tipo);
    std::string nombreMovimiento(int mov);
    void dibujarTablero(sf::RenderWindow& w);
    void dibujarFondo(sf::RenderWindow& w);
    void dibujarPieza(sf::RenderWindow& w);
    void dibujarCelda(sf::RenderWindow& w, int fila, int col, int tipo);
    void dibujarGema(sf::RenderWindow& w, float x, float y, float tamano, int tipo);
    void dibujarTexto(sf::RenderWindow& w, std::string cadena, float x, float y, float tamano, sf::Color color);
    void dibujarPiezaPreview(sf::RenderWindow& w, int tipo, int rotaciones, float cx, float cy, float tamano);
    void dibujarSiguiente(sf::RenderWindow& w);
    void dibujarHold(sf::RenderWindow& w);
    void dibujarHud(sf::RenderWindow& w);
    void dibujarMenu(sf::RenderWindow& w);
    void dibujarFin(sf::RenderWindow& w);
};