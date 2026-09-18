#include "Pieza.h"
#include <cstdlib>

const int FORMAS[7][4][4] = {
    {
        { 0, 0, 0, 0 },
        { 1, 1, 1, 1 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    },
    {
        { 1, 1, 0, 0 },
        { 1, 1, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    },
    {
        { 0, 1, 0, 0 },
        { 1, 1, 1, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    },
    {
        { 0, 1, 1, 0 },
        { 1, 1, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    },
    {
        { 1, 1, 0, 0 },
        { 0, 1, 1, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    },
    {
        { 1, 0, 0, 0 },
        { 1, 1, 1, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    },
    {
        { 0, 0, 1, 0 },
        { 1, 1, 1, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    }
};

Pieza::Pieza() : tipo(PIEZA_I) {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            forma[i][j] = FORMAS[tipo][i][j];
    setPosicion(0, COLS / 2 - 2);
}

Pieza::Pieza(int t) : tipo(t) {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            forma[i][j] = FORMAS[tipo][i][j];
    setPosicion(0, COLS / 2 - 2);
}

Pieza Pieza::crearAleatoria() {
    return Pieza(rand() % PIECE_TYPES);
}

int Pieza::getTipo() const {
    return tipo;
}

const Coord* Pieza::getCeldas() const {
    return celdas;
}

Coord Pieza::getPosicion() const {
    return posicion;
}

void Pieza::setPosicion(int fila, int col) {
    posicion = Coord(fila, col);
    actualizarCeldas();
}

void Pieza::mover(int df, int dc) {
    setPosicion(posicion.row + df, posicion.col + dc);
}

void Pieza::rotar() {
    int rotada[4][4];
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            rotada[i][j] = forma[3 - j][i];
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            forma[i][j] = rotada[i][j];
    actualizarCeldas();
}

void Pieza::actualizarCeldas() {
	int indice = 0;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (forma[i][j] == 1) {
				celdas[indice].row = i + posicion.row;
				celdas[indice].col = j + posicion.col;
				++indice;
			}
		}
	}
}
