#pragma once

#include "GameConstants.h"
#include "ExceptionManager.h"
#include <SFML/Graphics.hpp>

class TexturasBloques {
public:
    sf::Texture texturasPiezas[PIECE_TYPES];
    sf::Texture texturaFondo;
    void cargar();
    const sf::Texture& getTextura(int tipo) const;
    const sf::Texture& getFondo() const;
};
