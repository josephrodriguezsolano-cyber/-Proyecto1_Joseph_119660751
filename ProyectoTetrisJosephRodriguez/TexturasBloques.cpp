#include "TexturasBloques.h"
#include <string>
#include <iostream>
using namespace std;

void TexturasBloques::cargar() {
    for (int i = 0; i < PIECE_TYPES; ++i) {
        std::string ruta = "recursos/gemas/gem" + std::to_string(i) + ".png";
        if (!texturasPiezas[i].loadFromFile(ruta)) {
            throw ExceptionManager(ExceptionManager::TextureLoad, ruta);
			cout<<"Imagenes cargadas correctamente";
        }
        texturasPiezas[i].setSmooth(true);
    }
}

const sf::Texture& TexturasBloques::getTextura(int tipo) const {
    if (tipo < 0 || tipo >= PIECE_TYPES) {
        throw ExceptionManager(ExceptionManager::TextureLoad, "tipo de pieza invalido");
    }
    return texturasPiezas[tipo];
}
