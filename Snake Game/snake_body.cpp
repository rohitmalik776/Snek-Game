#pragma once

#include<iostream>
#include<SFML/Graphics.hpp>
#include<queue>
#include<list>
#include<vector>


class SnakeBody
{
public:
	static sf::Texture texture;
	static sf::Image image;
	static std::vector<SnakeBody> bodyArray;
	sf::Sprite sprite;
	std::queue<sf::Vector2<int>> bodyQue;
	/*
	SnakeBody(sf::Image bodyImage)
	{
		body = tempBody;
		for (int i = 0; i < 11; i++)
		{
			bodyQue.push(sf::Vector2<int>(0, 0));
		}
	}
	*/
	static void increaseSize() {
		bodyArray.push_back(SnakeBody());
	}

	SnakeBody() {
		auto lastElem = &bodyArray[bodyArray.size() - 1];
		//lastElem--;
		sf::Vector2f lastElemPos = lastElem->sprite.getPosition();
		double x = lastElemPos.x;
		double y = lastElemPos.y;
		sprite.setTexture(texture);
		sprite.setPosition(x, y);
		sprite.setScale(sf::Vector2f(0.0856, 0.0856));
		bodyQue.push(sf::Vector2<int>(x, y));

		for (int i = 0; i < 11; i++)
		{
			bodyQue.push(sf::Vector2<int>(x, y));
			x += 0.0856;
			y += 0.0856;
		}
		std::cout << "set the position of body to: " << x << std::endl;
	}

	void updatePos() {
		sprite.setPosition(bodyQue.front().x, bodyQue.front().y);
	}

	SnakeBody(int x, int y) {
		sprite.setTexture(texture);
		sprite.setPosition(x, y);
		sprite.setScale(sf::Vector2f(0.0856, 0.0856));

		for (int i = 0; i < 11; i++)
		{
			bodyQue.push(sf::Vector2<int>(x, y));
			x += 0.0856;
			y += 0.0856;
		}
		std::cout << "set the position of body to: " << x << std::endl;
	}
};

