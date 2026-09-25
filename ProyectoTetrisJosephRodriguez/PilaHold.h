#ifndef PILAHOLD_H
#define PILAHOLD_H

#include "Pieza.h"

struct NodoHold {
	Pieza pieza;
	NodoHold* sig;
	
	NodoHold() {
		sig = NULL;
	}
};

class PilaHold {
private:
	int tamano;
	int capacidad;
	NodoHold* head;
	
public:
	PilaHold();
	~PilaHold();
	
	bool isEmpty();
	void push(Pieza pieza);
	NodoHold* pop();
	Pieza top();
	void clear();
	void setTop(Pieza pieza);
	int getTamano();
};

#endif
