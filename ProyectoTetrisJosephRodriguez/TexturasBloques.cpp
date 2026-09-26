#include "TexturasBloques.h"
#include <string>

using namespace std;

void TexturasBloques::cargar() {
    for (int i = 0; i < PIECE_TYPES; ++i) {
        string ruta = "recursos/gemas/gem" + to_string(i) + ".png";
        if (!texturasPiezas[i].loadFromFile(ruta)) {
            throw ExceptionManager(ExceptionManager::TextureLoad, ruta);
        }
        texturasPiezas[i].setSmooth(true);
    }
    if (!texturaFondo.loadFromFile("recursos/gemas/BackGround.png")) {
        throw ExceptionManager(ExceptionManager::TextureLoad, "recursos/gemas/BackGround.png");
    }
    texturaFondo.setSmooth(true);
}

const sf::Texture& TexturasBloques::getTextura(int tipo) const {
    if (tipo < 0 || tipo >= PIECE_TYPES) {
        throw ExceptionManager(ExceptionManager::TextureLoad, "tipo de pieza invalido");
    }
    return texturasPiezas[tipo];
}

const sf::Texture& TexturasBloques::getFondo() const {
    return texturaFondo;
}
