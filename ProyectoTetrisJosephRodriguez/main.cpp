#include "Ventana.h"
#include "ExceptionManager.h"
#include <iostream>
#include <ctime>

using namespace std;

int main() {
	try {
		srand(static_cast<unsigned int>(time(0)));
		
		Ventana ventana;
		ventana.ejecutar();
	}
	catch (const exception& e) {
		cout << "Error: " << e.what() << endl;
		return -1;
	}
	
	return 0;
}
