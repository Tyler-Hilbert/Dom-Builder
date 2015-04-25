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

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(displayText);
		window.display();
	}
}