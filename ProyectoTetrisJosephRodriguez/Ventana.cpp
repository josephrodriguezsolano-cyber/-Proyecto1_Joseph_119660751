#include "Ventana.h"
#include "GameConstants.h"

Ventana::Ventana()
    : piezaActual(Pieza::crearAleatoria()),
      juegoTerminado(false),
      intervaloCaida(DROP_INTERVAL_BASE) {
    texturas.cargar();
}

void Ventana::ejecutar() {
    sf::RenderWindow ventana(sf::VideoMode(830, 900), "Tetris");
    sf::Clock reloj;
    float acumulado = 0.f;

    while (ventana.isOpen()) {
        float delta = reloj.restart().asSeconds();
        if (delta > MAX_DT) {
            delta = MAX_DT;
        }

        sf::Event e;
        while (ventana.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                ventana.close();
            }
            else if (e.type == sf::Event::KeyPressed) {
                if (!juegoTerminado) {
                    if (e.key.code == sf::Keyboard::Left) {
                        moverPieza(0, -1);
                    }
                    else if (e.key.code == sf::Keyboard::Right) {
                        moverPieza(0, 1);
                    }
                    else if (e.key.code == sf::Keyboard::Down) {
                        bajarPieza();
                    }
                    else if (e.key.code == sf::Keyboard::Up) {
                        rotarPieza();
                    }
                    else if (e.key.code == sf::Keyboard::Space) {
                        caidaRapida();
                    }
                }
            }
        }

        if (!juegoTerminado) {
            acumulado += delta;
            if (acumulado >= intervaloCaida) {
                acumulado = 0.f;
                bajarPieza();
            }
        }

        ventana.clear(sf::Color(15, 15, 22));
        dibujarFondo(ventana);
        dibujarTablero(ventana);
        if (!juegoTerminado) {
            dibujarPieza(ventana);
        }
        if (juegoTerminado) {
            dibujarFin(ventana);
        }
        ventana.display();
    }
}

void Ventana::moverPieza(int df, int dc) {
    piezaActual.mover(df, dc);
    if (!tablero.cabe(piezaActual)) {
        piezaActual.mover(-df, -dc);
    }
}

void Ventana::rotarPieza() {
    Pieza p = piezaActual;
    p.rotar();
    if (tablero.cabe(p)) {
        piezaActual.rotar();
    }
}

void Ventana::bajarPieza() {
    piezaActual.mover(1, 0);
    if (!tablero.cabe(piezaActual)) {
        piezaActual.mover(-1, 0);
        fijarPieza();
    }
}

void Ventana::caidaRapida() {
    while (tablero.cabe(piezaActual)) {
        piezaActual.mover(1, 0);
    }
    piezaActual.mover(-1, 0);
    fijarPieza();
}

void Ventana::fijarPieza() {
    tablero.fijar(piezaActual);
    generarPieza();
}

void Ventana::generarPieza() {
    piezaActual = Pieza::crearAleatoria();
    if (!tablero.cabe(piezaActual)) {
        juegoTerminado = true;
    }
}

void Ventana::dibujarFondo(sf::RenderWindow& ventana) {
    const sf::Texture& textura = texturas.getFondo();
    sf::Sprite s(textura);
    float escalaX = static_cast<float>(ventana.getSize().x) / static_cast<float>(textura.getSize().x);
    float escalaY = static_cast<float>(ventana.getSize().y) / static_cast<float>(textura.getSize().y);
    float escala = (escalaX > escalaY) ? escalaX : escalaY;
    s.setScale(escala, escala);
    float ancho = static_cast<float>(textura.getSize().x) * escala;
    float alto = static_cast<float>(textura.getSize().y) * escala;
    s.setPosition((static_cast<float>(ventana.getSize().x) - ancho) / 2.f,
                  (static_cast<float>(ventana.getSize().y) - alto) / 2.f);
    ventana.draw(s);
}

void Ventana::dibujarTablero(sf::RenderWindow& ventana) {
    sf::RectangleShape fondo(sf::Vector2f(COLS * CELL_SIZE, ROWS * CELL_SIZE));
    fondo.setFillColor(sf::Color(0, 0, 0, 0));
    fondo.setOutlineThickness(1.5f);
    fondo.setOutlineColor(sf::Color(255, 255, 255, 60));
    fondo.setPosition(BOARD_OFFSET_X, BOARD_OFFSET_Y);
    ventana.draw(fondo);

    for (int f = 0; f < ROWS; ++f) {
        for (int c = 0; c < COLS; ++c) {
            int tipo = tablero.getCelda(f, c);
            if (tipo != EMPTY_CELL) {
                dibujarCelda(ventana, f, c, tipo);
            }
            else {
                sf::RectangleShape celda(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                celda.setFillColor(sf::Color(0, 0, 0, 0));
                celda.setOutlineThickness(1.f);
                celda.setOutlineColor(sf::Color(255, 255, 255, 30));
                celda.setPosition(BOARD_OFFSET_X + c * CELL_SIZE, BOARD_OFFSET_Y + f * CELL_SIZE);
                ventana.draw(celda);
            }
        }
    }
}

void Ventana::dibujarPieza(sf::RenderWindow& ventana) {
    const Coord* cs = piezaActual.getCeldas();
    for (int i = 0; i < 4; ++i) {
        dibujarCelda(ventana, cs[i].row, cs[i].col, piezaActual.getTipo());
    }
}

void Ventana::dibujarCelda(sf::RenderWindow& ventana, int fila, int col, int tipo) {
    const sf::Texture& textura = texturas.getTextura(tipo);
    sf::Sprite s(textura);
    s.setScale(CELL_SIZE / textura.getSize().x, CELL_SIZE / textura.getSize().y);
    s.setPosition(BOARD_OFFSET_X + col * CELL_SIZE, BOARD_OFFSET_Y + fila * CELL_SIZE);
    ventana.draw(s);
}

void Ventana::dibujarFin(sf::RenderWindow& ventana) {
    sf::RectangleShape cubre(sf::Vector2f(COLS * CELL_SIZE, ROWS * CELL_SIZE));
    cubre.setFillColor(sf::Color(0, 0, 0, 160));
    cubre.setPosition(BOARD_OFFSET_X, BOARD_OFFSET_Y);
    ventana.draw(cubre);
}
