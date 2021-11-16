#include<iostream>
#include<SFML/Graphics.hpp>

class Food {
public:
	sf::Sprite foodSprite;
	double x;
	double y;
	Food(sf::Sprite foodSprite) {
		this->foodSprite = foodSprite;
		std::pair<int, int> newPos = changePosition();
		std::cout << newPos.first << " " << newPos.second << std::endl;
		this->foodSprite.setPosition(x, y);
	}
	std::pair<int, int> changePosition() {
		this->x = 35.0 + abs(rand() % 435);
		this->y = 35.0 + abs(rand() % 435);
		foodSprite.setPosition(x, y);
		return std::make_pair(x, y);
	}
};