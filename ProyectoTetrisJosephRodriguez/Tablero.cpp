#include "Tablero.h"
#include "Pieza.h"

Tablero::Tablero() {
	lineasEliminadas = 0;
	limpiar();
}

void Tablero::limpiar() {
	for (int f = 0; f < ROWS; ++f) {
		for (int c = 0; c < COLS; ++c) {
			celdas[f][c] = EMPTY_CELL;
		}
	}
}

int Tablero::getCelda(int fila, int col) const {
	return celdas[fila][col];
}

void Tablero::setCelda(int fila, int col, int tipo) {
	celdas[fila][col] = tipo;
}

bool Tablero::dentro(int fila, int col) const {
	bool filaValida = (fila >= 0 && fila < ROWS);
	bool colValida = (col >= 0 && col < COLS);
	return filaValida && colValida;
}

bool Tablero::cabe(const Pieza& pieza) const {
	const Coord* celdasPieza = pieza.getCeldas();
	
	for (int i = 0; i < 4; ++i) {
		int fila = celdasPieza[i].row;
		int col = celdasPieza[i].col;
		
		if (!dentro(fila, col)) {
			return false;
		}
		
		if (celdas[fila][col] != EMPTY_CELL) {
			return false;
		}
	}
	
	return true;
}

void Tablero::fijar(const Pieza& pieza) {
	const Coord* celdasPieza = pieza.getCeldas();
	
	for (int i = 0; i < 4; ++i) {
		int fila = celdasPieza[i].row;
		int col = celdasPieza[i].col;
		celdas[fila][col] = pieza.getTipo();
	}
	
	eliminarLineas();
}

int Tablero::getLineasEliminadas() const {
	return lineasEliminadas;
}

bool Tablero::filaCompleta(int fila) const {
	for (int c = 0; c < COLS; ++c) {
		if (celdas[fila][c] == EMPTY_CELL) {
			return false;
		}
	}
	return true;
}

void Tablero::bajarFilas(int filaDesde) {
	for (int f = filaDesde; f > 0; --f) {
		for (int c = 0; c < COLS; ++c) {
			celdas[f][c] = celdas[f - 1][c];
		}
	}
	
	for (int c = 0; c < COLS; ++c) {
		celdas[0][c] = EMPTY_CELL;
	}
}

void Tablero::eliminarLineas() {
	lineasEliminadas = 0;
	
	for (int f = ROWS - 1; f >= 0; --f) {
		if (filaCompleta(f)) {
			bajarFilas(f);
			++f;
			++lineasEliminadas;
		}
	}
}
