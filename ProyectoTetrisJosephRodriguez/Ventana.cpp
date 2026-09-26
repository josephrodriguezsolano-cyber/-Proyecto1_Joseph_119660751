#include "Ventana.h"
#include "GameConstants.h"
#include "ExceptionManager.h"
#include <string>

Ventana::Ventana() {
    texturas.cargar();
    if (!fuente.loadFromFile(FONT_PATH)) {
        throw ExceptionManager(ExceptionManager::FontLoad, FONT_PATH);
    }
    estado = ESTADO_MENU_JUGADOR;
    opcionMenu = 0;
    modoMenu = 0;
    indiceJugadorMenu = 0;
    nombreEntrada = "";
    juegoTerminado = false;
    reiniciarPartida();
}

void Ventana::ejecutar() {
    sf::RenderWindow ventana(sf::VideoMode(830, 900), "Tetris");
    sf::Clock reloj;
    float acumulado = 0.0f;

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
            else if (e.type == sf::Event::TextEntered && estado == ESTADO_MENU_JUGADOR && modoMenu == 1) {
                if (e.text.unicode == 8) {
                    if (!nombreEntrada.empty()) {
                        nombreEntrada.erase(nombreEntrada.size() - 1, 1);
                    }
                }
                else if (e.text.unicode == 13) {
                    if (!nombreEntrada.empty()) {
                        iniciarJuego(nombreEntrada);
                    }
                }
                else if (e.text.unicode >= 32 && e.text.unicode < 128 && e.text.unicode != ' '
                         && nombreEntrada.size() < MENU_NOMBRE_MAX) {
                    nombreEntrada += static_cast<char>(e.text.unicode);
                }
            }
            else if (e.type == sf::Event::KeyPressed) {
                if (estado == ESTADO_MENU_JUGADOR) {
                    if (e.key.code == sf::Keyboard::Up || e.key.code == sf::Keyboard::Left) {
                        if (modoMenu == 0) {
                            if (opcionMenu == 0) {
                                opcionMenu = 1;
                            }
                            else {
                                opcionMenu = 0;
                            }
                        }
                        else if (modoMenu == 2) {
                            if (indiceJugadorMenu > 0) {
                                indiceJugadorMenu--;
                            }
                        }
                    }
                    else if (e.key.code == sf::Keyboard::Down || e.key.code == sf::Keyboard::Right) {
                        if (modoMenu == 0) {
                            if (opcionMenu == 0) {
                                opcionMenu = 1;
                            }
                            else {
                                opcionMenu = 0;
                            }
                        }
                        else if (modoMenu == 2) {
                            if (indiceJugadorMenu < gestorPuntajes.getCantidad() - 1) {
                                indiceJugadorMenu++;
                            }
                        }
                    }
                    else if (e.key.code == sf::Keyboard::Return) {
                        if (modoMenu == 0) {
                            if (opcionMenu == 0) {
                                modoMenu = 1;
                            }
                            else if (gestorPuntajes.getCantidad() > 0) {
                                modoMenu = 2;
                                indiceJugadorMenu = gestorPuntajes.getIndiceUltimoJugador();
                            }
                        }
                        else if (modoMenu == 1) {
                            if (!nombreEntrada.empty()) {
                                iniciarJuego(nombreEntrada);
                            }
                        }
                        else if (modoMenu == 2) {
                            iniciarJuego(gestorPuntajes.getNombreJugador(indiceJugadorMenu));
                        }
                    }
                    else if (e.key.code == sf::Keyboard::Escape) {
                        modoMenu = 0;
                    }
                }
                else if (juegoTerminado) {
                    if (e.key.code == sf::Keyboard::Left) {
                        EstadoReplay est;
                        if (listaReplay.retroceder(est)) {
                            actualReplay = est;
                        }
                    }
                    else if (e.key.code == sf::Keyboard::Right) {
                        EstadoReplay est;
                        if (listaReplay.avanzar(est)) {
                            actualReplay = est;
                        }
                    }
                    else if (e.key.code == sf::Keyboard::R) {
                        reiniciarPartida();
                    }
                }
                else if (pausado) {
                    if (e.key.code == sf::Keyboard::P) {
                        pausado = false;
                    }
                    else if (e.key.code == sf::Keyboard::R) {
                        reiniciarPartida();
                    }
                }
                else {
                    if (e.key.code == sf::Keyboard::Left) {
                        moverPieza(0, -1);
                        registrarMovimiento(MOV_IZQUIERDA);
                    }
                    else if (e.key.code == sf::Keyboard::Right) {
                        moverPieza(0, 1);
                        registrarMovimiento(MOV_DERECHA);
                    }
                    else if (e.key.code == sf::Keyboard::Down) {
                        bajarPieza();
                        registrarMovimiento(MOV_BAJAR);
                    }
                    else if (e.key.code == sf::Keyboard::Up) {
                        rotarPieza();
                        registrarMovimiento(MOV_ROTAR);
                    }
                    else if (e.key.code == sf::Keyboard::Space) {
                        caidaRapida();
                        registrarMovimiento(MOV_FIJAR);
                    }
                    else if (e.key.code == sf::Keyboard::C) {
                        usarHold();
                        registrarMovimiento(MOV_HOLD);
                    }
                    else if (e.key.code == sf::Keyboard::Z) {
                        deshacer();
                    }
                    else if (e.key.code == sf::Keyboard::X) {
                        rehacer();
                    }
                    else if (e.key.code == sf::Keyboard::P) {
                        pausado = true;
                    }
                    else if (e.key.code == sf::Keyboard::T) {
                        gestorPuntajes.alternarOrdenamiento();
                    }
                    else if (e.key.code == sf::Keyboard::R) {
                        reiniciarPartida();
                    }
                }
            }
        }

        if (estado == ESTADO_JUGANDO && !juegoTerminado && !pausado) {
            acumulado += delta;
            tiempoPartida += delta;
            int tipoEvento = 0;
            while (colaEventos.despachar(tiempoPartida, tipoEvento)) {
                procesarEvento(tipoEvento);
            }
            if (acumulado >= intervaloCaida) {
                acumulado = 0.0f;
                bajarPieza();
                registrarMovimiento(MOV_BAJAR);
            }
        }

        ventana.clear(sf::Color(15, 15, 22));
        dibujarFondo(ventana);
        dibujarTablero(ventana);
        if (estado == ESTADO_MENU_JUGADOR) {
            dibujarMenu(ventana);
        }
        else {
            dibujarHud(ventana);
            dibujarPieza(ventana);
            if (juegoTerminado) {
                dibujarFin(ventana);
            }
        }
        ventana.display();
    }
}

void Ventana::moverPieza(int df, int dc) {
    piezaActual.mover(df, dc);
    if (!tablero.puedeColocar(piezaActual)) {
        piezaActual.mover(-df, -dc);
    }
}

void Ventana::rotarPieza() {
    Pieza p = piezaActual;
    p.rotar();
    if (tablero.puedeColocar(p)) {
        piezaActual.rotar();
        rotaciones++;
    }
}

void Ventana::bajarPieza() {
    piezaActual.mover(1, 0);
    if (!tablero.puedeColocar(piezaActual)) {
        piezaActual.mover(-1, 0);
        fijarPieza();
    }
}

void Ventana::caidaRapida() {
    int distancia = 0;
    while (tablero.puedeColocar(piezaActual)) {
        piezaActual.mover(1, 0);
        distancia++;
    }
    piezaActual.mover(-1, 0);
    if (distancia > 0) {
        distancia--;
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
    piezaActual = colaPiezas.desencolar();
    rotaciones = 0;
    swapUsado = false;
    if (!tablero.puedeColocar(piezaActual)) {
        juegoTerminado = true;
    }
}

void Ventana::usarHold() {
    if (swapUsado) {
        return;
    }
    if (pilaHold.isEmpty()) {
        pilaHold.push(piezaActual);
        rotacionesHold = rotaciones;
        rotaciones = 0;
        generarPieza();
        swapUsado = true;
    }
    else {
        NodoHold* reten = pilaHold.pop();
        Pieza retenida = reten->pieza;
        delete reten;
        pilaHold.push(piezaActual);
        piezaActual = retenida;
        piezaActual.setPosicion(0, COLS / 2 - 2);
        int aux = rotacionesHold;
        rotacionesHold = rotaciones;
        rotaciones = aux;
        swapUsado = true;
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

void Ventana::registrarMovimiento(int mov) {
    EstadoReplay nuevo = capturarEstado(mov);
    listaReplay.registrar(nuevo);
    actualReplay = nuevo;
    if (nuevo.juegoTerminado && !partidaGuardada) {
        partidaGuardada = true;
        gestorPuntajes.registrarLineas(nuevo.lineas);
        enReplay = true;
    }
}

EstadoReplay Ventana::capturarEstado(int mov) {
    EstadoReplay est;
    est.movimiento = mov;
    est.tipoPieza = piezaActual.getTipo();
    est.posicionPieza = piezaActual.getPosicion();
    est.rotaciones = rotaciones;
    est.rotacionesHold = rotacionesHold;
    est.piezaSiguienteTipo = colaPiezas.consultarFrente().getTipo();
    for (int f = 0; f < ROWS; f++) {
        for (int c = 0; c < COLS; c++) {
            est.celdas[f][c] = tablero.getCelda(f, c);
        }
    }
    est.puntaje = puntaje;
    est.nivel = nivel;
    est.lineas = lineasTotales;
    if (pilaHold.isEmpty()) {
        est.piezaHoldTipo = EMPTY_CELL;
    }
    else {
        est.piezaHoldTipo = pilaHold.top().getTipo();
    }
    est.swapUsado = swapUsado;
    est.juegoTerminado = juegoTerminado;
    return est;
}

void Ventana::restaurarEstado(EstadoReplay est) {
    tablero.limpiarTablero();
    for (int f = 0; f < ROWS; f++) {
        for (int c = 0; c < COLS; c++) {
            tablero.setCelda(f, c, est.celdas[f][c]);
        }
    }

    piezaActual = Pieza(est.tipoPieza);
    piezaActual.setPosicion(est.posicionPieza.row, est.posicionPieza.col);
    for (int i = 0; i < est.rotaciones; i++) {
        piezaActual.rotar();
    }

    if (est.piezaHoldTipo == EMPTY_CELL) {
        pilaHold.clear();
    }
    else {
        Pieza retenida(est.piezaHoldTipo);
        for (int i = 0; i < est.rotacionesHold; i++) {
            retenida.rotar();
        }
        pilaHold.setTop(retenida);
    }

    puntaje = est.puntaje;
    nivel = est.nivel;
    lineasTotales = est.lineas;
    rotaciones = est.rotaciones;
    rotacionesHold = est.rotacionesHold;
    swapUsado = est.swapUsado;
    juegoTerminado = est.juegoTerminado;
    enReplay = false;
}

void Ventana::deshacer() {
    EstadoReplay est;
    if (listaReplay.deshacer(est)) {
        restaurarEstado(est);
        actualReplay = est;
    }
}

void Ventana::rehacer() {
    EstadoReplay est;
    if (listaReplay.rehacer(est)) {
        restaurarEstado(est);
        actualReplay = est;
    }
}

void Ventana::reiniciarPartida() {
    tablero.limpiarTablero();
    pilaHold.clear();
    listaReplay.reiniciar();
    colaEventos.vaciarCola();
    colaPiezas.reiniciar();

    piezaActual = colaPiezas.desencolar();

    puntaje = 0;
    nivel = 1;
    lineasTotales = 0;
    intervaloCaida = DROP_INTERVAL_BASE;
    tiempoPartida = 0.0f;
    rotaciones = 0;
    rotacionesHold = 0;
    juegoTerminado = false;
    enReplay = false;
    pausado = false;
    swapUsado = false;
    partidaGuardada = false;

    colaEventos.programar(EVENTO_VELOCIDAD, INTERVALO_VELOCIDAD, 0.0f);
    colaEventos.programar(EVENTO_BONUS, INTERVALO_BONUS, 0.0f);
    colaEventos.programar(EVENTO_NIVEL, INTERVALO_NIVEL, 0.0f);

    registrarMovimiento(MOV_INICIO);
}

void Ventana::iniciarJuego(std::string nombre) {
    gestorPuntajes.establecerJugador(nombre);
    reiniciarPartida();
    estado = ESTADO_JUGANDO;
    modoMenu = 0;
}

void Ventana::procesarEvento(int tipo) {
    if (tipo == EVENTO_VELOCIDAD) {
        float nuevo = intervaloCaida - DROP_REDUCCION_NIVEL;
        if (nuevo < DROP_INTERVAL_MIN) {
            nuevo = DROP_INTERVAL_MIN;
        }
        intervaloCaida = nuevo;
        puntaje += PUNTOS_BONUS_EVENTO;
    }
    else if (tipo == EVENTO_BONUS) {
        puntaje += PUNTOS_BONUS_EVENTO;
    }
    else if (tipo == EVENTO_NIVEL) {
        nivel++;
        puntaje += PUNTOS_BONUS_EVENTO;
    }
}

std::string Ventana::nombreMovimiento(int mov) {
    if (mov == MOV_INICIO) {
        return "INICIO";
    }
    if (mov == MOV_IZQUIERDA) {
        return "IZQUIERDA";
    }
    if (mov == MOV_DERECHA) {
        return "DERECHA";
    }
    if (mov == MOV_ROTAR) {
        return "ROTAR";
    }
    if (mov == MOV_BAJAR) {
        return "BAJAR";
    }
    if (mov == MOV_FIJAR) {
        return "FIJAR";
    }
    if (mov == MOV_HOLD) {
        return "HOLD";
    }
    return "?";
}

void Ventana::dibujarFondo(sf::RenderWindow& ventana) {
    const sf::Texture& textura = texturas.getFondo();
    sf::Sprite s(textura);
    float escalaX = static_cast<float>(ventana.getSize().x) / static_cast<float>(textura.getSize().x);
    float escalaY = static_cast<float>(ventana.getSize().y) / static_cast<float>(textura.getSize().y);
    float escala = escalaX;
    if (escalaY > escalaX) {
        escala = escalaY;
    }
    s.setScale(escala, escala);
    float ancho = static_cast<float>(textura.getSize().x) * escala;
    float alto = static_cast<float>(textura.getSize().y) * escala;
    s.setPosition((static_cast<float>(ventana.getSize().x) - ancho) / 2.0f,
                  (static_cast<float>(ventana.getSize().y) - alto) / 2.0f);
    ventana.draw(s);
}

void Ventana::dibujarTablero(sf::RenderWindow& ventana) {
    sf::RectangleShape fondo(sf::Vector2f(COLS * CELL_SIZE, ROWS * CELL_SIZE));
    fondo.setFillColor(sf::Color(0, 0, 0, 0));
    fondo.setOutlineThickness(1.5f);
    fondo.setOutlineColor(sf::Color(255, 255, 255, 60));
    fondo.setPosition(BOARD_OFFSET_X, BOARD_OFFSET_Y);
    ventana.draw(fondo);

    for (int f = 0; f < ROWS; f++) {
        for (int c = 0; c < COLS; c++) {
            int tipo;
            if (enReplay) {
                tipo = actualReplay.celdas[f][c];
            }
            else {
                tipo = tablero.getCelda(f, c);
            }
            if (tipo != EMPTY_CELL) {
                dibujarCelda(ventana, f, c, tipo);
            }
            else {
                sf::RectangleShape celda(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                celda.setFillColor(sf::Color(0, 0, 0, 0));
                celda.setOutlineThickness(1.0f);
                celda.setOutlineColor(sf::Color(255, 255, 255, 30));
                celda.setPosition(BOARD_OFFSET_X + c * CELL_SIZE, BOARD_OFFSET_Y + f * CELL_SIZE);
                ventana.draw(celda);
            }
        }
    }
}

void Ventana::dibujarPieza(sf::RenderWindow& ventana) {
    if (enReplay) {
        Pieza p(actualReplay.tipoPieza);
        p.setPosicion(actualReplay.posicionPieza.row, actualReplay.posicionPieza.col);
        for (int i = 0; i < actualReplay.rotaciones; i++) {
            p.rotar();
        }
        const Coord* cs = p.getCeldas();
        for (int i = 0; i < 4; i++) {
            dibujarCelda(ventana, cs[i].row, cs[i].col, p.getTipo());
        }
    }
    else if (!juegoTerminado) {
        const Coord* cs = piezaActual.getCeldas();
        for (int i = 0; i < 4; i++) {
            dibujarCelda(ventana, cs[i].row, cs[i].col, piezaActual.getTipo());
        }
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

void Ventana::dibujarTexto(sf::RenderWindow& ventana, std::string cadena,
                           float x, float y, float tamano, sf::Color color) {
    sf::Text texto(cadena, fuente, static_cast<unsigned int>(tamano));
    texto.setFillColor(color);
    sf::FloatRect rect = texto.getLocalBounds();
    texto.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
    texto.setPosition(x, y);
    ventana.draw(texto);
}

void Ventana::dibujarPiezaPreview(sf::RenderWindow& ventana, int tipo, int rotaciones,
                                  float cx, float cy, float tamano) {
    Pieza p(tipo);
    p.setPosicion(0, 0);
    for (int i = 0; i < rotaciones; i++) {
        p.rotar();
    }
    const Coord* cs = p.getCeldas();
    for (int i = 0; i < 4; i++) {
        float x = cx + (cs[i].col - 1.5f) * tamano;
        float y = cy + (cs[i].row - 1.5f) * tamano;
        dibujarGema(ventana, x, y, tamano, tipo);
    }
}

void Ventana::dibujarSiguiente(sf::RenderWindow& ventana) {
    if (enReplay) {
        dibujarPiezaPreview(ventana, actualReplay.piezaSiguienteTipo, 0,
                            PREVIEW_CENTER_X, PREVIEW_CENTER_Y, PREVIEW_CELL_SIZE);
    }
    else {
        constexpr float ESPACIADO_PREVIEW = 80.f;
        for (int i = 0; i < 3; i++) {
            Pieza p = colaPiezas.consultarPorIndice(i);
            float y = PREVIEW_CENTER_Y + i * ESPACIADO_PREVIEW;
            dibujarPiezaPreview(ventana, p.getTipo(), 0,
                                PREVIEW_CENTER_X, y, PREVIEW_CELL_SIZE);
        }
    }
}

void Ventana::dibujarHold(sf::RenderWindow& ventana) {
    if (enReplay) {
        if (actualReplay.piezaHoldTipo != EMPTY_CELL) {
            dibujarPiezaPreview(ventana, actualReplay.piezaHoldTipo, actualReplay.rotacionesHold,
                                HOLD_PIECE_CENTER_X, HOLD_PIECE_CENTER_Y, PREVIEW_CELL_SIZE);
        }
    }
    else if (!pilaHold.isEmpty()) {
        dibujarPiezaPreview(ventana, pilaHold.top().getTipo(), rotacionesHold,
                            HOLD_PIECE_CENTER_X, HOLD_PIECE_CENTER_Y, PREVIEW_CELL_SIZE);
    }
}

void Ventana::dibujarHud(sf::RenderWindow& ventana) {
    dibujarTexto(ventana, "JUGADOR: " + gestorPuntajes.getJugador(),
                 TEXTO_PUNTUACION_X, TEXTO_CONTROLES_Y - 88.0f, TEXTO_ETIQUETA_TAMANO, sf::Color(180, 200, 220));

    int puntajeVista;
    int nivelVista;
    int lineasVista;
    if (enReplay) {
        puntajeVista = actualReplay.puntaje;
        nivelVista = actualReplay.nivel;
        lineasVista = actualReplay.lineas;
    }
    else {
        puntajeVista = puntaje;
        nivelVista = nivel;
        lineasVista = lineasTotales;
    }

    dibujarTexto(ventana, "HOLD", HOLD_PIECE_CENTER_X, HOLD_PIECE_CENTER_Y - TEXTO_ETIQUETA_OFFSET_Y,
                 TEXTO_ETIQUETA_TAMANO, sf::Color(200, 200, 200));
    dibujarHold(ventana);
    dibujarTexto(ventana, "SIGUIENTE", PREVIEW_CENTER_X, PREVIEW_CENTER_Y - TEXTO_ETIQUETA_OFFSET_Y,
                 TEXTO_ETIQUETA_TAMANO, sf::Color(200, 200, 200));
    dibujarSiguiente(ventana);

    dibujarTexto(ventana, "PUNTAJE", TEXTO_PUNTUACION_X, TEXTO_PUNTUACION_Y - TEXTO_ETIQUETA_OFFSET_Y,
                 TEXTO_ETIQUETA_TAMANO, sf::Color(200, 200, 200));
    dibujarTexto(ventana, std::to_string(puntajeVista),
                 TEXTO_PUNTUACION_X, TEXTO_PUNTUACION_Y, TEXTO_TAMANO, sf::Color::White);
    dibujarTexto(ventana, "NIVEL", TEXTO_NIVEL_X, TEXTO_NIVEL_Y - TEXTO_ETIQUETA_OFFSET_Y,
                 TEXTO_ETIQUETA_TAMANO, sf::Color(200, 200, 200));
    dibujarTexto(ventana, std::to_string(nivelVista),
                 TEXTO_NIVEL_X, TEXTO_NIVEL_Y, TEXTO_TAMANO, sf::Color::White);
    dibujarTexto(ventana, "LINEAS", TEXTO_LINEAS_X, TEXTO_LINEAS_Y - TEXTO_ETIQUETA_OFFSET_Y,
                 TEXTO_ETIQUETA_TAMANO, sf::Color(200, 200, 200));
    dibujarTexto(ventana, std::to_string(lineasVista),
                 TEXTO_LINEAS_X, TEXTO_LINEAS_Y, TEXTO_TAMANO, sf::Color::White);

    if (!enReplay) {
        dibujarTexto(ventana, "METODO ORDEN: " + std::to_string(gestorPuntajes.getMetodo() + 1),
                     TEXTO_CONTROLES_X, TEXTO_CONTROLES_Y - 26.0f, TEXTO_CONTROLES_TAMANO, sf::Color(180, 200, 220));
        dibujarTexto(ventana, "C HOLD   Z DESHACER   X REHACER   P PAUSA",
                     TEXTO_CONTROLES_X, TEXTO_CONTROLES_Y, TEXTO_CONTROLES_TAMANO, sf::Color(160, 160, 160));
        dibujarTexto(ventana, "T ORDEN   R REINICIAR",
                     TEXTO_CONTROLES_X, TEXTO_CONTROLES_Y + 24.0f, TEXTO_CONTROLES_TAMANO, sf::Color(160, 160, 160));
    }

    if (pausado && !juegoTerminado) {
        dibujarTexto(ventana, "PAUSA", BOARD_OFFSET_X + COLS * CELL_SIZE / 2.0f,
                     BOARD_OFFSET_Y + ROWS * CELL_SIZE / 2.0f, TEXTO_TAMANO + 8.0f, sf::Color::White);
    }
}

void Ventana::dibujarMenu(sf::RenderWindow& ventana) {
    sf::RectangleShape fondo(sf::Vector2f(static_cast<float>(ventana.getSize().x),
                                          static_cast<float>(ventana.getSize().y)));
    fondo.setFillColor(sf::Color(0, 0, 0, 170));
    ventana.draw(fondo);

    float cx = MENU_CENTRO_X;
    dibujarTexto(ventana, "TETRIS", cx, MENU_INICIO_Y, MENU_TITULO_TAMANO, sf::Color(255, 220, 100));
    dibujarTexto(ventana, "MENU DE JUGADOR", cx, MENU_INICIO_Y + 60.0f,
                 MENU_OPCION_TAMANO, sf::Color(200, 220, 255));

    if (modoMenu == 1) {
        dibujarTexto(ventana, "NUEVO JUGADOR", cx, MENU_INICIO_Y + 150.0f,
                     MENU_OPCION_TAMANO, sf::Color::White);
        dibujarTexto(ventana, "NOMBRE: " + nombreEntrada + "|", cx, MENU_INICIO_Y + 205.0f,
                     MENU_NOMBRE_TAMANO, sf::Color::White);
        dibujarTexto(ventana, "ESCRIBE TU NOMBRE   ENTER: CONFIRMAR   ESC: VOLVER",
                     cx, MENU_INICIO_Y + 260.0f, MENU_DETALLE_TAMANO, sf::Color(180, 180, 180));
    }
    else if (modoMenu == 2) {
        dibujarTexto(ventana, "JUGADORES REGISTRADOS", cx, MENU_INICIO_Y + 150.0f,
                     MENU_OPCION_TAMANO, sf::Color::White);
        int inicioLista = static_cast<int>(MENU_INICIO_Y) + 210;
        for (int i = 0; i < gestorPuntajes.getCantidad() && i < MAX_TABLA; i++) {
            std::string fila = "   ";
            if (i == indiceJugadorMenu) {
                fila = ">> ";
            }
            fila += std::to_string(i + 1) + ". " + gestorPuntajes.getNombreJugador(i)
                    + "   LINEAS " + std::to_string(gestorPuntajes.getLineasJugador(i));
            sf::Color color = sf::Color::White;
            if (i == indiceJugadorMenu) {
                color = sf::Color(255, 220, 100);
            }
            dibujarTexto(ventana, fila, cx, inicioLista + i * 34.0f, 18.0f, color);
        }
        float ayudaY = inicioLista + gestorPuntajes.getCantidad() * 34.0f + 4.0f;
        dibujarTexto(ventana, "FLECHAS: ELEGIR   ENTER: JUGAR   ESC: VOLVER",
                     cx, ayudaY, MENU_DETALLE_TAMANO, sf::Color(180, 180, 180));
    }
    else {
        float y = MENU_INICIO_Y + 150.0f;
        sf::Color opcion1 = sf::Color::White;
        if (opcionMenu == 0) {
            opcion1 = sf::Color(255, 220, 100);
        }
        sf::Color opcion2 = sf::Color::White;
        if (opcionMenu == 1) {
            opcion2 = sf::Color(255, 220, 100);
        }
        dibujarTexto(ventana, "1. NUEVO JUGADOR", cx, y, MENU_OPCION_TAMANO, opcion1);
        dibujarTexto(ventana, "2. JUGADOR EXISTENTE", cx, y + 55.0f, MENU_OPCION_TAMANO, opcion2);
        if (opcionMenu == 1 && gestorPuntajes.getCantidad() == 0) {
            dibujarTexto(ventana, "NO HAY JUGADORES REGISTRADOS",
                         cx, y + 115.0f, MENU_DETALLE_TAMANO, sf::Color(200, 100, 100));
        }
        else {
            dibujarTexto(ventana, "FLECHAS: CAMBIAR   ENTER: CONFIRMAR   ESC: VOLVER",
                         cx, y + 115.0f, MENU_DETALLE_TAMANO, sf::Color(180, 180, 180));
        }
    }
}

void Ventana::dibujarFin(sf::RenderWindow& ventana) {
    float cx = BOARD_OFFSET_X + COLS * CELL_SIZE / 2.0f;
    sf::RectangleShape cubre(sf::Vector2f(COLS * CELL_SIZE, ROWS * CELL_SIZE));
    cubre.setFillColor(sf::Color(0, 0, 0, 170));
    cubre.setPosition(BOARD_OFFSET_X, BOARD_OFFSET_Y);
    ventana.draw(cubre);

    dibujarTexto(ventana, "JUEGO TERMINADO", cx, BOARD_OFFSET_Y + 60.0f,
                 TEXTO_TAMANO + 8.0f, sf::Color::White);
    dibujarTexto(ventana, "REPLAY PASO A PASO", cx, BOARD_OFFSET_Y + 110.0f,
                 TEXTO_TAMANO, sf::Color(255, 220, 100));
    dibujarTexto(ventana, "MOVIMIENTO: " + nombreMovimiento(actualReplay.movimiento),
                 cx, BOARD_OFFSET_Y + 155.0f, TEXTO_ETIQUETA_TAMANO + 2.0f, sf::Color(200, 220, 255));

    std::string lineaEstado = "PUNTAJE " + std::to_string(actualReplay.puntaje)
                              + "   NIVEL " + std::to_string(actualReplay.nivel)
                              + "   LINEAS " + std::to_string(actualReplay.lineas);
    dibujarTexto(ventana, lineaEstado, cx, BOARD_OFFSET_Y + 190.0f,
                 TEXTO_ETIQUETA_TAMANO + 2.0f, sf::Color::White);

    dibujarTexto(ventana, "IZQ/DER: PASO      R: REINICIAR",
                 cx, BOARD_OFFSET_Y + 235.0f, TEXTO_ETIQUETA_TAMANO, sf::Color(180, 180, 180));

    dibujarTexto(ventana, "TOP 10   (METODO " + std::to_string(gestorPuntajes.getMetodo() + 1) + ")",
                 cx, BOARD_OFFSET_Y + 290.0f, TEXTO_TAMANO, sf::Color(255, 220, 100));

    int inicio = static_cast<int>(BOARD_OFFSET_Y) + 330;
    for (int i = 0; i < gestorPuntajes.getCantidad() && i < MAX_TABLA; i++) {
        std::string fila = std::to_string(i + 1) + ".  " + gestorPuntajes.getNombreJugador(i)
                           + "   LINEAS " + std::to_string(gestorPuntajes.getLineasJugador(i));
        dibujarTexto(ventana, fila, cx, inicio + i * 30.0f,
                     TEXTO_ETIQUETA_TAMANO + 2.0f, sf::Color::White);
    }
}