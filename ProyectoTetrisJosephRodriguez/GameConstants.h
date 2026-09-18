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
