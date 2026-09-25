#include "PilaHold.h"
#include "GameConstants.h"

PilaHold::PilaHold() {
	tamano = 0;
	capacidad = 1;
	head = NULL;
}

PilaHold::~PilaHold() {
	clear();
}

bool PilaHold::isEmpty() {
	return head == NULL;
}

void PilaHold::push(Pieza pieza) {
	if (tamano >= capacidad) {
		return;
	}
	NodoHold* nuevo = new NodoHold();
	nuevo->pieza = pieza;
	nuevo->sig = head;
	head = nuevo;
	tamano++;
}

NodoHold* PilaHold::pop() {
	if (isEmpty()) {
		return NULL;
	}
	NodoHold* actual = head;
	head = head->sig;
	actual->sig = NULL;
	tamano--;
	return actual;
}

Pieza PilaHold::top() {
	if (isEmpty()) {
		return Pieza(PIEZA_I);
	}
	return head->pieza;
}

void PilaHold::clear() {
	while (head != NULL) {
		NodoHold* aux = head;
		head = head->sig;
		delete aux;
	}
	tamano = 0;
}

void PilaHold::setTop(Pieza pieza) {
	if (isEmpty()) {
		push(pieza);
	}
	else {
		head->pieza = pieza;
	}
}

int PilaHold::getTamano() {
	return tamano;
}
