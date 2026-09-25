#include "Tablero.h"
#include "Pieza.h"

Tablero::Tablero() {
	lineasEliminadas = 0;
	limpiarTablero();
}

void Tablero::limpiarTablero() {
	for (int f = 0; f < ROWS; f++) {
		for (int c = 0; c < COLS; c++) {
			celdas[f][c] = EMPTY_CELL;
		}
	}
}

int Tablero::getCelda(int fila, int col) {
	return celdas[fila][col];
}

void Tablero::setCelda(int fila, int col, int tipo) {
	celdas[fila][col] = tipo;
}

bool Tablero::estaDentro(int fila, int col) {
	bool filaValida = (fila >= 0 && fila < ROWS);
	bool colValida = (col >= 0 && col < COLS);
	return filaValida && colValida;
}

bool Tablero::puedeColocar(Pieza pieza) {
	const Coord* celdasPieza = pieza.getCeldas();
	
	for (int i = 0; i < 4; i++) {
		int fila = celdasPieza[i].row;
		int col = celdasPieza[i].col;
		
		if (!estaDentro(fila, col)) {
			return false;
		}
		
		if (celdas[fila][col] != EMPTY_CELL) {
			return false;
		}
	}
	
	return true;
}

int Tablero::fijar(Pieza pieza) {
	const Coord* celdasPieza = pieza.getCeldas();
	
	for (int i = 0; i < 4; i++) {
		int fila = celdasPieza[i].row;
		int col = celdasPieza[i].col;
		celdas[fila][col] = pieza.getTipo();
	}
	
	int eliminadas = eliminarLineas();
	lineasEliminadas += eliminadas;
	return eliminadas;
}

int Tablero::getLineasEliminadas() {
	return lineasEliminadas;
}

bool Tablero::esFilaCompleta(int fila) {
	for (int c = 0; c < COLS; c++) {
		if (celdas[fila][c] == EMPTY_CELL) {
			return false;
		}
	}
	return true;
}

void Tablero::bajarFilas(int filaDesde) {
	for (int f = filaDesde; f > 0; f--) {
		for (int c = 0; c < COLS; c++) {
			celdas[f][c] = celdas[f - 1][c];
		}
	}
	
	for (int c = 0; c < COLS; c++) {
		celdas[0][c] = EMPTY_CELL;
	}
}

int Tablero::eliminarLineas() {
	int contador = 0;
	
	for (int f = ROWS - 1; f >= 0; f--) {
		if (esFilaCompleta(f)) {
			bajarFilas(f);
			f++;
			contador++;
		}
	}
	
	return contador;
}
