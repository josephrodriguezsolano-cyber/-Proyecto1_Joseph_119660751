#pragma once
#include <SFML/Graphics.hpp>

constexpr int ROWS = 20;
constexpr int COLS = 10;
constexpr int PIECE_TYPES = 7;
constexpr int PIEZA_I = 0;
constexpr int PIEZA_O = 1;
constexpr int PIEZA_T = 2;
constexpr int PIEZA_S = 3;
constexpr int PIEZA_Z = 4;
constexpr int PIEZA_J = 5;
constexpr int PIEZA_L = 6;

constexpr float CELL_SIZE = 36.f;
constexpr float BOARD_OFFSET_X = 232.f;
constexpr float BOARD_OFFSET_Y = 72.f;
constexpr float DROP_INTERVAL_BASE = 0.85f;
constexpr float MAX_DT = 1.f / 60.f;
constexpr int EMPTY_CELL = -1;

constexpr int PUNTOS_LINEA[4] = { 100, 300, 500, 800 };
constexpr int BONUS_DROP_SUAVE = 1;
constexpr int BONUS_DROP_DURO = 2;
constexpr int MAX_TABLA = 10;

constexpr int LINEAS_POR_NIVEL = 10;
constexpr float DROP_INTERVAL_MIN = 0.2f;
constexpr float DROP_REDUCCION_NIVEL = 0.05f;

constexpr const char* FONT_PATH = "recursos/fuente.ttf";

constexpr float PREVIEW_CENTER_X = 116.f;
constexpr float PREVIEW_CENTER_Y = 200.f;
constexpr float PREVIEW_CELL_SIZE = 22.f;

constexpr float TEXTO_PUNTUACION_X = 710.f;
constexpr float TEXTO_PUNTUACION_Y = 200.f;
constexpr float TEXTO_NIVEL_X = 710.f;
constexpr float TEXTO_NIVEL_Y = 440.f;
constexpr float TEXTO_LINEAS_X = 710.f;
constexpr float TEXTO_LINEAS_Y = 680.f;
constexpr float TEXTO_TAMANO = 26.f;
constexpr float TEXTO_ETIQUETA_TAMANO = 16.f;
constexpr float TEXTO_ETIQUETA_OFFSET_Y = 54.f;
constexpr float TEXTO_CONTROLES_X = 710.f;
constexpr float TEXTO_CONTROLES_Y = 846.f;
constexpr float TEXTO_CONTROLES_TAMANO = 15.f;

constexpr float HOLD_PIECE_CENTER_X = 116.f;
constexpr float HOLD_PIECE_CENTER_Y = 100.f;
constexpr int PUNTOS_BONUS_EVENTO = 500;

constexpr int EVENTO_VELOCIDAD = 0;
constexpr int EVENTO_BONUS = 1;
constexpr int EVENTO_NIVEL = 2;
constexpr float INTERVALO_VELOCIDAD = 45.f;
constexpr float INTERVALO_BONUS = 60.f;
constexpr float INTERVALO_NIVEL = 120.f;

constexpr int MOV_INICIO = 0;
constexpr int MOV_IZQUIERDA = 1;
constexpr int MOV_DERECHA = 2;
constexpr int MOV_ROTAR = 3;
constexpr int MOV_BAJAR = 4;
constexpr int MOV_FIJAR = 5;
constexpr int MOV_HOLD = 6;

constexpr int ESTADO_MENU_JUGADOR = 0;
constexpr int ESTADO_JUGANDO = 1;

constexpr float MENU_CENTRO_X = BOARD_OFFSET_X + COLS * CELL_SIZE / 2.f;
constexpr float MENU_INICIO_Y = BOARD_OFFSET_Y + 60.f;
constexpr float MENU_TITULO_TAMANO = 42.f;
constexpr float MENU_OPCION_TAMANO = 22.f;
constexpr float MENU_NOMBRE_TAMANO = 26.f;
constexpr float MENU_DETALLE_TAMANO = 16.f;
constexpr int MENU_NOMBRE_MAX = 12;
