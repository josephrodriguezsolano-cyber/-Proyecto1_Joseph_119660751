#include "Ventana.h"
#include "GameConstants.h"

namespace {
    constexpr int VENTANA_ANCHO = BOARD_OFFSET_X * 2 + COLS * CELL_SIZE;
    constexpr int VENTANA_ALTO = BOARD_OFFSET_Y * 2 + ROWS * CELL_SIZE;
}

Ventana::Ventana() : piezaActual(Pieza::crearAleatoria()) {
    texturas.cargar();
}

void Ventana::ejecutar() {
    sf::RenderWindow w(sf::VideoMode(VENTANA_ANCHO, VENTANA_ALTO), "Tetris");

    while (w.isOpen()) {
        sf::Event e;
        while (w.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                w.close();
        }

        w.clear(sf::Color(15, 15, 22));
        dibujarTablero(w);
        dibujarPieza(w);
        w.display();
    }
}

void Ventana::dibujarTablero(sf::RenderWindow& w) {
    sf::RectangleShape fondo(sf::Vector2f(COLS * CELL_SIZE, ROWS * CELL_SIZE));
    fondo.setFillColor(sf::Color(25, 25, 35));
    fondo.setOutlineThickness(2.f);
    fondo.setOutlineColor(sf::Color(120, 120, 140));
    fondo.setPosition(BOARD_OFFSET_X, BOARD_OFFSET_Y);
    w.draw(fondo);

    for (int f = 0; f < ROWS; ++f) {
        for (int c = 0; c < COLS; ++c) {
            int tipo = tablero.getCelda(f, c);
            if (tipo != EMPTY_CELL) {
                dibujarCelda(w, f, c, tipo);
            }
            else {
                sf::RectangleShape celda(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                celda.setFillColor(sf::Color(35, 35, 48));
                celda.setOutlineThickness(1.f);
                celda.setOutlineColor(sf::Color(20, 20, 30));
                celda.setPosition(BOARD_OFFSET_X + c * CELL_SIZE, BOARD_OFFSET_Y + f * CELL_SIZE);
                w.draw(celda);
            }
        }
    }
}

void Ventana::dibujarPieza(sf::RenderWindow& w) {
    const Coord* cs = piezaActual.getCeldas();
    for (int i = 0; i < 4; ++i) {
        dibujarCelda(w, cs[i].row, cs[i].col, piezaActual.getTipo());
    }
}

void Ventana::dibujarCelda(sf::RenderWindow& w, int fila, int col, int tipo) {
    sf::Sprite s(texturas.getTextura(tipo));
    s.setPosition(BOARD_OFFSET_X + col * CELL_SIZE, BOARD_OFFSET_Y + fila * CELL_SIZE);
    w.draw(s);
}