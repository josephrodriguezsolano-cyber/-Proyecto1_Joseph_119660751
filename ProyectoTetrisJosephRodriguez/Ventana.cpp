#include "Ventana.h"
#include "GameConstants.h"
#include "ExceptionManager.h"
#include <string>

Ventana::Ventana()
    : piezaActual(Pieza::crearAleatoria()),
      piezaSiguiente(Pieza::crearAleatoria()),
      juegoTerminado(false),
      intervaloCaida(DROP_INTERVAL_BASE),
      puntaje(0),
      nivel(1),
      lineasTotales(0) {
    texturas.cargar();
    if (!fuente.loadFromFile(FONT_PATH)) {
        throw ExceptionManager(ExceptionManager::FontLoad, FONT_PATH);
    }
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
                        puntaje += BONUS_DROP_SUAVE;
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
        dibujarHud(ventana);
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
    int distancia = 0;
    while (tablero.cabe(piezaActual)) {
        piezaActual.mover(1, 0);
        ++distancia;
    }
    piezaActual.mover(-1, 0);
    if (distancia > 0) {
        --distancia;
    }
    puntaje += distancia * BONUS_DROP_DURO;
    fijarPieza();
}

void Ventana::fijarPieza() {
    int lineas = tablero.fijar(piezaActual);
    if (lineas > 0) {
        puntaje += PUNTOS_LINEA[lineas - 1];
        lineasTotales += lineas;
        actualizarNivel();
    }
    generarPieza();
}

void Ventana::generarPieza() {
    piezaActual = piezaSiguiente;
    piezaSiguiente = Pieza::crearAleatoria();
    if (!tablero.cabe(piezaActual)) {
        juegoTerminado = true;
    }
}

void Ventana::actualizarNivel() {
    int nuevoNivel = lineasTotales / LINEAS_POR_NIVEL + 1;
    if (nuevoNivel > nivel) {
        nivel = nuevoNivel;
    }
    float nuevoIntervalo = DROP_INTERVAL_BASE - (nivel - 1) * DROP_REDUCCION_NIVEL;
    if (nuevoIntervalo < DROP_INTERVAL_MIN) {
        nuevoIntervalo = DROP_INTERVAL_MIN;
    }
    intervaloCaida = nuevoIntervalo;
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
    float x = BOARD_OFFSET_X + col * CELL_SIZE;
    float y = BOARD_OFFSET_Y + fila * CELL_SIZE;
    dibujarGema(ventana, x, y, CELL_SIZE, tipo);
}

void Ventana::dibujarGema(sf::RenderWindow& ventana, float x, float y, float tamano, int tipo) {
    const sf::Texture& textura = texturas.getTextura(tipo);
    sf::Sprite s(textura);
    s.setScale(tamano / textura.getSize().x, tamano / textura.getSize().y);
    s.setPosition(x, y);
    ventana.draw(s);
}

void Ventana::dibujarTexto(sf::RenderWindow& ventana, const std::string& cadena,
                           float x, float y, float tamano, sf::Color color) {
    sf::Text texto(cadena, fuente, static_cast<unsigned int>(tamano));
    texto.setFillColor(color);
    sf::FloatRect rect = texto.getLocalBounds();
    texto.setOrigin(rect.left + rect.width / 2.f, rect.top + rect.height / 2.f);
    texto.setPosition(x, y);
    ventana.draw(texto);
}

void Ventana::dibujarSiguiente(sf::RenderWindow& ventana) {
    Coord pos = piezaSiguiente.getPosicion();
    const Coord* cs = piezaSiguiente.getCeldas();
    for (int i = 0; i < 4; ++i) {
        int localF = cs[i].row - pos.row;
        int localC = cs[i].col - pos.col;
        float x = PREVIEW_CENTER_X + (localC - 1.5f) * PREVIEW_CELL_SIZE;
        float y = PREVIEW_CENTER_Y + (localF - 1.5f) * PREVIEW_CELL_SIZE;
        dibujarGema(ventana, x, y, PREVIEW_CELL_SIZE, piezaSiguiente.getTipo());
    }
}

void Ventana::dibujarHud(sf::RenderWindow& ventana) {
    dibujarSiguiente(ventana);
    dibujarTexto(ventana, std::to_string(puntaje),
                 TEXTO_PUNTUACION_X, TEXTO_PUNTUACION_Y, TEXTO_TAMANO, sf::Color::White);
    dibujarTexto(ventana, std::to_string(nivel),
                 TEXTO_NIVEL_X, TEXTO_NIVEL_Y, TEXTO_TAMANO, sf::Color::White);
    dibujarTexto(ventana, std::to_string(lineasTotales),
                 TEXTO_LINEAS_X, TEXTO_LINEAS_Y, TEXTO_TAMANO, sf::Color::White);
}

void Ventana::dibujarFin(sf::RenderWindow& ventana) {
    sf::RectangleShape cubre(sf::Vector2f(COLS * CELL_SIZE, ROWS * CELL_SIZE));
    cubre.setFillColor(sf::Color(0, 0, 0, 160));
    cubre.setPosition(BOARD_OFFSET_X, BOARD_OFFSET_Y);
    ventana.draw(cubre);
    dibujarTexto(ventana, "JUEGO TERMINADO",
                 BOARD_OFFSET_X + COLS * CELL_SIZE / 2.f,
                 BOARD_OFFSET_Y + ROWS * CELL_SIZE / 2.f,
                 TEXTO_TAMANO + 8.f, sf::Color::White);
}