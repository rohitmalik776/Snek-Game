#include <iostream>
#include <assert.h>
#include "SFML/Graphics.hpp"

class PausePrompt
{
	sf::RectangleShape box;
	sf::Text pauseText;
	sf::Text pauseSubText;

	sf::Font lightFont;
	sf::Font boldFont;

public:
	PausePrompt()
	{
		if (!lightFont.loadFromFile("Resources/Raleway-ExtraLight.ttf"))
		{
			std::cout << "Unable to load raleway light fonts\n";
		}
		if (!boldFont.loadFromFile("Resources/Raleway-Black.ttf"))
		{
			assert(false && "Can't load Raleway-Black.ttf");
		}
		box.setSize(sf::Vector2f(200, 200));
		box.setOutlineColor(sf::Color::Black);
		box.setOutlineThickness(10);
		box.setFillColor(sf::Color(0xFFE77AFF));
		box.setPosition(185.5, 185.5);

		pauseText.setFont(boldFont);
		pauseText.setFillColor(sf::Color::Black);
		pauseText.setPosition(185.5 + 40, 185.5 + 30);
		pauseText.setString("Paused");
		// pauseText.setScale(0.5, 0.5);

		pauseSubText.setFont(lightFont);
		pauseSubText.setFillColor(sf::Color::Black);
		pauseSubText.setPosition(190, 185.5 + 100);
		pauseSubText.setString("Press Enter key to continue...");
		pauseSubText.setScale(0.5, 0.5);
	}
	sf::RectangleShape getSprite()
	{
		return box;
	}
	void draw(sf::RenderWindow *mainWin)
	{
		mainWin->draw(box);
		mainWin->draw(pauseText);
		mainWin->draw(pauseSubText);
	}
};
