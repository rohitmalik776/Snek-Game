#pragma once;
#include <iostream>
#include <SFML/Graphics.hpp>



class board {

public:

	sf::RectangleShape line;

	
	void drawGrass(sf::RenderWindow* mainWin , sf::Sprite* grassLight, sf::Sprite* grassDark)
	{
		for (int x = 0, j = 0; x < 574; x += 41, j++)
		{
			for (int y = 0, i = 0; y < 574; y += 41, i++)
			{
				grassLight->setPosition(x, y);
				grassDark->setPosition(x, y);

				if (i & 1 && j & 1)
				{
					mainWin->draw(*grassLight);
				}
				else
					mainWin->draw(*grassDark);
			}
		}
	}


	void drawGrid(sf::RenderWindow* mainWin)
	{


		//Drawing Grid
		line.setFillColor(sf::Color(0,0,0, 50));
		line.setSize(sf::Vector2f(551, 01));

		int x = 0, y = 0;

		line.setPosition(0, y);
		line.setPosition(x, 0);

		//Drawing Vertical Lines
		for ( ; y <= 550 ; y += 11 ) 
		{
			line.setPosition(0, y);
			mainWin->draw(line);
		}
		//Drawing Horizontal Lines
		line.setSize(sf::Vector2f(1, 551));
		for (; x <= 550; x += 11) 
		{
			line.setPosition(x, 0);
			mainWin->draw(line);
		}
	
	}

};




class snake {

public:

	sf::Sprite *snakeHead, *snakeBody;

	void moveRight() {
	
		
	
	}





};