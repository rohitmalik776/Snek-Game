#pragma once
#include <iostream>
#include <assert.h>
#include <SFML/Graphics.hpp>
#include <queue>

class board
{

public:
	sf::RectangleShape line;
	sf::Texture horizontalBrick;
	sf::Sprite horizontalBrickSprite;
	sf::Texture verticalBrick;
	sf::Sprite verticalBrickSprite;

	sf::Vector2f vSpriteSize;
	sf::Vector2f hSpriteSize;

	board()
	{
		if (!horizontalBrick.loadFromFile("Resources/brick_horizontal.png"))
		{
			assert(false && "Failed to load Resources/brick_horizontal.png");
		}
		horizontalBrickSprite.setTexture(horizontalBrick);
		horizontalBrickSprite.setScale(0.15, 0.15);
		horizontalBrickSprite.setPosition(0, 0);

		if (!verticalBrick.loadFromFile("Resources/brick_vertical.png"))
		{
			assert(false && "Faild to load Resources/brick_vertical.png");
		}

		verticalBrickSprite.setTexture(verticalBrick);
		verticalBrickSprite.setScale(0.15, 0.15);
		verticalBrickSprite.setPosition(0, 0);

		const sf::Vector2f spriteSize(
			horizontalBrickSprite.getTexture()->getSize().x * horizontalBrickSprite.getScale().x,
			horizontalBrickSprite.getTexture()->getSize().y * horizontalBrickSprite.getScale().y);
		hSpriteSize.x = spriteSize.x;
		hSpriteSize.y = spriteSize.y;

		const sf::Vector2f verticalSpriteSize(
			verticalBrickSprite.getTexture()->getSize().x * verticalBrickSprite.getScale().x,
			verticalBrickSprite.getTexture()->getSize().y * verticalBrickSprite.getScale().y);
		vSpriteSize.x = verticalSpriteSize.x;
		vSpriteSize.y = verticalSpriteSize.y;
	}

	void drawGrass(sf::RenderWindow *mainWin, sf::Sprite *grassLight, sf::Sprite *grassDark)
	{
		for (int x = 0, j = 0; x < 574; x += 41, j++)
		{
			for (int y = 0, i = 0; y < 574; y += 41, i++)
			{
				grassLight->setPosition(x, y);
				grassDark->setPosition(x, y);

				// i&1 implies i is odd or not
				if (i & 1 && j & 1)
				{
					mainWin->draw(*grassLight);
				}
				else
					mainWin->draw(*grassDark);
			}
		}
	}

	void drawGrid(sf::RenderWindow *mainWin)
	{

		// Drawing Grid
		line.setFillColor(sf::Color(0, 0, 0, 50));
		line.setSize(sf::Vector2f(551, 01));

		int x = 0, y = 0;

		line.setPosition(0, y);
		line.setPosition(x, 0);

		// Drawing Vertical Lines
		for (; y <= 550; y += 11)
		{
			line.setPosition(0, y);
			mainWin->draw(line);
		}
		// Drawing Horizontal Lines
		line.setSize(sf::Vector2f(1, 551));
		for (; x <= 550; x += 11)
		{
			line.setPosition(x, 0);
			mainWin->draw(line);
		}
	}

	void drawBorder(sf::RenderWindow *mainWin)
	{

		// Drawing horizontal wall
		for (double i = 0; i < mainWin->getSize().x; i += hSpriteSize.x - 0.5)
		{
			horizontalBrickSprite.setPosition(i, 0);
			mainWin->draw(horizontalBrickSprite);
			horizontalBrickSprite.setPosition(i, mainWin->getSize().y - hSpriteSize.y);
			mainWin->draw(horizontalBrickSprite);
		}

		// Drawing vertical wall
		for (double i = 0; i < mainWin->getSize().y; i += vSpriteSize.y - 0.5)
		{
			verticalBrickSprite.setPosition(0, i);
			mainWin->draw(verticalBrickSprite);
			verticalBrickSprite.setPosition(mainWin->getSize().x - vSpriteSize.x, i);
			mainWin->draw(verticalBrickSprite);
		}
	}
};
