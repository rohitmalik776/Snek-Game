#include <iostream>
#include <assert.h>
#include "SFML/Graphics.hpp"

class GameOver
{
	sf::RectangleShape box;
	sf::Text gameOverText;
	sf::Text gameOverSubText;

	sf::Font lightFont;
	sf::Font boldFont;

public:
	GameOver() {
		if (!lightFont.loadFromFile("Resources/Raleway-ExtraLight.ttf")) {
			std::cout << "Unable to load raleway light fonts\n";
		}
		if (!boldFont.loadFromFile("Resources/Raleway-Black.ttf")) {
			assert(false && "Can't load Raleway-Black.ttf");
		}
		box.setSize(sf::Vector2f(200, 200));
		box.setOutlineColor(sf::Color::Black);
		box.setOutlineThickness(10);
		box.setFillColor(sf::Color(0xFFE77AFF));
		box.setPosition(185.5, 185.5);

		gameOverText.setFont(boldFont);
		gameOverText.setFillColor(sf::Color::Black);
		gameOverText.setPosition(185.5 + 10, 185.5 + 30);
		gameOverText.setString("Game Over!");
		// gameOverText.setScale(0.5, 0.5);

		gameOverSubText.setFont(lightFont);
		gameOverSubText.setFillColor(sf::Color::Black);
		gameOverSubText.setPosition(190 + 10, 185.5 + 100);
		gameOverSubText.setString("Press R key to restart");
		gameOverSubText.setScale(0.6, 0.6);
	}
	sf::RectangleShape getSprite() {
		return box;
	}
	void draw(sf::RenderWindow* mainWin) {
		mainWin->draw(box);
		mainWin->draw(gameOverText);
		mainWin->draw(gameOverSubText);
	}
};
