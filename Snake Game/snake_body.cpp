#pragma once

#include<iostream>
#include"SFML/Graphics.hpp"
#include<queue>

class snakeBody
{
public:
	bool isVisible = false;
	sf::Sprite specialBody;
	sf::Sprite body;
	std::queue<sf::Vector2<int>> bodyQue;

	sf::Sprite getBody() {
		if (isVisible)
			return body;
		else return specialBody;
	}

	snakeBody(sf::Sprite tempBody)
	{
		body = tempBody;
		for (int i = 0; i < 11; i++)
		{
			bodyQue.push(sf::Vector2<int>(0, 0));
		}
	}
	snakeBody(sf::Sprite tempBody, sf::Texture* tempSpecialBody, int x, int y) {
		body = tempBody;
		specialBody.setTexture(*tempSpecialBody);
		for (int i = 0; i < 11; i++)
		{
			bodyQue.push(sf::Vector2<int>(x, y));
			body.setPosition(x, y);
		}
	}
};