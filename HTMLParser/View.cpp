#include "View.h"
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

/**
  * The main view that shows all the parsed html
  */
View::View(DomTree &domTree, std::mutex &mutex) {
	sf::RenderWindow window(sf::VideoMode(800, 800), "Parsed HTML");
	window.setFramerateLimit(30);

	// Set attributes
	sf::Font font;
	font.loadFromFile("arial.ttf");
	sf::Text displayText;
	displayText.setFont(font);
	displayText.setCharacterSize(24);
	displayText.setColor(sf::Color::Black);

	window.draw(displayText);
	window.display();

	int y = 0; // The location on the page that is shown.
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			// Move page down
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				y -= 100;
				int textSize = displayText.getLocalBounds().height * -1 + 800;
				if (y < textSize)
					y = textSize;
			}

			// Move page up
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				y += 100;
				if (y > 0)
					y = 0;
			}

			// Close the program
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Refresh the view
		window.clear(sf::Color::White);
		displayText.setPosition(0, y);
		mutex.lock();
		string text;
		for (Node child : domTree.getRoot().getChildren()) {
			text += child.getContent() + "\n";
		}
		displayText.setString(text);
		mutex.unlock();
		window.draw(displayText);
		window.display();
	}
}