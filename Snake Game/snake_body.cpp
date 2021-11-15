#pragma once

#include<iostream>
#include<SFML/Graphics.hpp>
#include<queue>
#include<list>
#include<vector>

#include"snake_head.cpp"


class SnakeBody
{
public:
	static sf::Texture texture;
	static int arrSize;
	static sf::Image image;
	static std::vector<SnakeBody> bodyArray;
	std::queue<int> prevDirX;
	std::queue<int> prevDirY;
	sf::Sprite sprite;
	std::queue<sf::Vector2<float>> bodyQue;
	static void increaseSize() {
		bodyArray.push_back(SnakeBody());
		arrSize++;
	}

	SnakeBody() {
		//auto lastElem = &bodyArray[bodyArray.size() - 1];
		auto lastElem = bodyArray[arrSize];
		//lastElem--;
		sf::Vector2f lastElemPos = lastElem.bodyQue.back();
		double x = lastElemPos.x;
		double y = lastElemPos.y;
		sprite.setTexture(texture);
		sprite.setPosition(x, y);
		sprite.setScale(sf::Vector2f(0.0856, 0.0856));

		for (int i = 0; i < 11; i++)
		{
			bodyQue.push(sf::Vector2<float>(x + SnakeHead::dirX * 40, y + SnakeHead::dirX*40));
			prevDirX.push(SnakeHead::dirX);
			prevDirX.push(SnakeHead::dirY);
		}
	}

	void updatePos() {
		sprite.setPosition(bodyQue.front().x, bodyQue.front().y);
	}

	SnakeBody(float x, float y) {
		sprite.setTexture(texture);
		sprite.setPosition(x, y);
		sprite.setScale(sf::Vector2f(0.0856, 0.0856));

		for (int i = 0; i < 11; i++)
		{
			bodyQue.push(sf::Vector2<float>(x, y));
			prevDirX.push(SnakeHead::dirX);
			prevDirX.push(SnakeHead::dirY);
		}
		std::cout << "set the position of body to: " << x << std::endl;
	}
};

