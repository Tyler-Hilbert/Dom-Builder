#include "View.h"
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

View::View(std::string text) {
	sf::RenderWindow window(sf::VideoMode(800, 800), "Parsed HTML");

	sf::Font font;
	font.loadFromFile("arial.ttf");
	sf::Text displayText;
	displayText.setFont(font);
	displayText.setString(text);
	displayText.setCharacterSize(24);
	displayText.setColor(sf::Color::White);

	window.draw(displayText);
	window.display();

	int y = 0;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				y -= 100;
				int textSize = displayText.getLocalBounds().height * -1 + 800;
				if (y < textSize)
					y = textSize;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				y += 100;
				if (y > 0)
					y = 0;
			}

			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		displayText.setPosition(0, y);
		window.draw(displayText);
		window.display();
	}
}