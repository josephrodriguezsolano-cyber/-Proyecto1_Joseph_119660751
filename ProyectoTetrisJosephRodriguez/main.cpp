#include "Ventana.h"
#include "ExceptionManager.h"
#include <iostream>
#include <ctime>

int main() {
	try {
		srand(static_cast<unsigned int>(time(nullptr)));
		
		Ventana ventana;
		ventana.ejecutar();
	}
	catch (const std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
		return -1;
	}
	
	return 0;
}
