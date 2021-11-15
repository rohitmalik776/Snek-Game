#pragma once

#include<iostream>
#include<queue>

#include<SFML/graphics.hpp>

class SnakeHead {
public:
	static int dirX;
	static int dirY;
	double posX = 0;
	double posY = 0;
	sf::Sprite sprite;
	//A queue to make the body follow the head
	std::queue<sf::Vector2<float>> headPos;

	SnakeHead(sf::Image image) {
		for (int i = 0; i < 11; i++)
		{
			sf::Vector2<float> origin(0, 0);
			headPos.push(origin);
		}
	}
};