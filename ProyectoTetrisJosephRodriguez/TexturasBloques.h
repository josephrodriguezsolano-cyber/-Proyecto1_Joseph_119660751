#pragma once

#include "GameConstants.h"
#include "ExceptionManager.h"
#include <SFML/Graphics.hpp>

class TexturasBloques {
public:
    sf::Texture texturasPiezas[PIECE_TYPES];
    void cargar();
    const sf::Texture& getTextura(int tipo) const;
};
