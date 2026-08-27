#include "Ventana.h"
#include <SFML/Graphics.hpp>

Ventana::Ventana() {}

void Ventana::ejecutar() {
	sf::RenderWindow w(sf::VideoMode(640, 480), "Ejemplo de SFML");
	sf::Texture t;
	sf::Sprite s;

	t.loadFromFile("sfml.png");
	s.setTexture(t);
	s.setPosition(175, 130);

	while (w.isOpen()) {
		sf::Event e;
		while (w.pollEvent(e)) {
			if (e.type == sf::Event::Closed)
				w.close();
		}

		w.clear(sf::Color(255, 255, 255, 255));
		w.draw(s);
		w.display();
	}
}