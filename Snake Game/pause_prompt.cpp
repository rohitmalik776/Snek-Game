#include <iostream>
#include "SFML/Graphics.hpp"

class PausePrompt
{
	sf::RectangleShape box;
	sf::Text pauseText;
	sf::Text pauseSubText;

public:
	PausePrompt(sf::Font* font) {
		/*
		sf::Font lightFont;
		if (!lightFont.loadFromFile("Resources/Raleway-ExtraLight.ttf")) {
			std::cout << "Unable to load raleway light fonts\n";
		}
		*/
		box.setSize(sf::Vector2f(200, 200));
		box.setOutlineColor(sf::Color::Black);
		box.setOutlineThickness(10);
		box.setFillColor(sf::Color::White);
		box.setPosition(185.5, 185.5);

		pauseText.setFont(*font);
		pauseText.setFillColor(sf::Color::Black);
		pauseSubText.setFont(*font);
		pauseSubText.setFillColor(sf::Color::Black);
		pauseSubText.setPosition(185.5, 185.5);
		pauseSubText.setString("Press Enter key to continue...");
		pauseSubText.setCharacterSize(10);
	}
	sf::RectangleShape getSprite() {
		return box;
	}
	void draw(sf::RenderWindow* mainWin) {
		mainWin->draw(box);
		//mainWin->draw(pauseText);
		mainWin->draw(pauseSubText);
	}
};
