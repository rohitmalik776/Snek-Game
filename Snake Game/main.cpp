#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>
#include <vector>
#include "board.cpp"
#include "food.cpp"
#include "snake_head.cpp"
#include "snake_body.cpp"

int blockside = 41;
double spr_scale = 0.0856;
std::vector<SnakeBody> SnakeBody::bodyArray = {};
sf::Texture SnakeBody::texture = sf::Texture();
sf::Image SnakeBody::image = sf::Image();

int main() {
	srand(time(0));
	//Scale of sprites
	//Setting up Window
	sf::RenderWindow mainWin(sf::VideoMode(574, 574), "snek", sf::Style::Close);
	mainWin.setFramerateLimit(60);
	//Importing Images
	//Importing background images
	sf::Image grassLightImg;
	if (!grassLightImg.loadFromFile("Resources/grass_light.bmp"))
	{
		std::cout << "Error loading 'Resources/grass_light.bmp'\n";
		system("break");
		return 0;
	}

	sf::Image grassDarkImg;
	if (!grassDarkImg.loadFromFile("Resources/grass_dark.bmp"))
	{
		std::cout << "Error loading 'Resources/grass_dark.bmp'\n";
		system("break");
		return 0;
	}


	//Importing snake images

	sf::Image snakeBodyImg, snakeHeadRight, snakeHeadDown, snakeHeadLeft, snakeHeadUp;
	if (!snakeHeadLeft.loadFromFile("Resources/snake_head_left.png"))
	{
		std::cout << "Error loading 'Resources/snake_left.bmp'\n";
		return 0;
	}

	if (!snakeHeadRight.loadFromFile("Resources/snake_head_right.png"))
	{
		std::cout << "Error loading 'Resources/snake_right.bmp'\n";
		return 0;
	}

	if (!snakeHeadUp.loadFromFile("Resources/snake_head_up.png"))
	{
		std::cout << "Error loading 'Resources/snake_up.bmp'\n";
		return 0;
	}

	if (!snakeHeadDown.loadFromFile("Resources/snake_head_down.png"))
	{
		std::cout << "Error loading 'Resources/snake_down.bmp'\n";
		return 0;
	}

	if (!SnakeBody::image.loadFromFile("Resources/snake_body.png"))
	{
		std::cout << "Error loading 'Resources/snake_body.bmp'\n";
		return 0;
	}
	SnakeBody::texture.loadFromImage(SnakeBody::image);
	//Snake head
	SnakeHead snakeHead(snakeHeadRight);
	//Snake body, 1 block
	SnakeBody::bodyArray.push_back(SnakeBody(0, 0));

	//Making snake body vertical sprite
	sf::Image snakeBodyVert;
	if (!(snakeBodyVert.loadFromFile("Resources/snake_body_vert.png")))
	{
		std::cout << "Couldn't load Snake body vertical << endl";
		return 0;
	}
	//Making snake texture
	sf::Texture snakeHeadTex, snakeBodyTex;
	snakeHeadTex.loadFromImage(snakeHeadRight);
	snakeBodyTex.loadFromImage(snakeBodyImg);
	//Making snake head sprite
	sf::Sprite snakeHeadSpr, snakeBodySpr;
	snakeHeadSpr.setTexture(snakeHeadTex);
	snakeHeadSpr.setPosition(0, 0);
	snakeHeadSpr.setScale(sf::Vector2f(spr_scale, spr_scale));
	//Making textures
	sf::Texture grassLightTex;
	grassLightTex.loadFromImage(grassLightImg);
	sf::Texture grassDarkTex;
	grassDarkTex.loadFromImage(grassDarkImg);
	//Making sprites
	sf::Sprite grassLightSpr;
	grassLightSpr.setTexture(grassLightTex);
	grassLightSpr.setScale(spr_scale, spr_scale);
	grassLightSpr.setPosition(0, 0);

	sf::Sprite grassDarkSpr;
	grassDarkSpr.setTexture(grassDarkTex);
	grassDarkSpr.setScale(spr_scale, spr_scale);
	grassDarkSpr.setPosition(0, 0);

	//Making food
	sf::Image foodImage;
	if (!foodImage.loadFromFile("Resources/food.png"))
	{
		std::cout << "Error loading 'Resources/food.png'\n";
		system("break");
		return 0;
	}
	// Making food texture
	sf::Texture foodTex;
	foodTex.loadFromImage(foodImage);
	// Making food sprite
	sf::Sprite foodSpr;
	foodSpr.setTexture(foodTex);
	foodSpr.setScale(spr_scale*0.6, spr_scale*0.6);
	Food food(foodSpr);

	//Initialising board
	board mainBoard;
	//Events
	sf::Event mainEvent;


	while (mainWin.isOpen()) {

		mainWin.clear(sf::Color(255, 255, 255));

		//Drawing grass sprites
		mainWin.draw(grassLightSpr);
		mainWin.draw(grassDarkSpr);


		//Drawing grid lines
		mainBoard.drawGrid(&mainWin);

		//Drawing grass
		mainBoard.drawGrass(&mainWin, &grassLightSpr, &grassDarkSpr);


		//Storing snake's last seen position
		int headLastSeenX = snakeHead.posX, headLastSeenY = snakeHead.posY;


		//Drawing snake
		snakeHead.posX += 4 * snakeHead.dirX;			//snakeHead.dirX = -1 or 1
		snakeHead.posY += 4 * snakeHead.dirY;
		// std:: cout << snakeHead.posX << std::endl;
		
		
		
		if ((food.x > snakeHead.posX - 20) && (food.x < snakeHead.posX + 20) && (food.y > snakeHead.posY - 20) && (food.y < snakeHead.posY + 20)) {
			std::cout << "Snake and food's coordinates clashed!\n";
			// std::cout << "food.x: " << food.x << std::endl;
			SnakeBody::increaseSize();
			food.changePosition();
			std::cout << "snakeHead.posX: " << snakeHead.posX << std::endl;
		}

		if (snakeHead.posX > 571)
			snakeHead.posX = 0;
		if (snakeHead.posY > 571)
			snakeHead.posY = 0;
		if (snakeHead.posX < 0)
			snakeHead.posX = 571;
		if (snakeHead.posY < 0)
			snakeHead.posY = 571;


		snakeHeadSpr.setPosition(snakeHead.posX, snakeHead.posY);


		// Body follow head function
		SnakeBody::bodyArray[0].sprite.setPosition(snakeHead.headPos.front().x, snakeHead.headPos.front().y);
		SnakeBody::bodyArray[0].bodyQue.push(snakeHead.headPos.front());

		//Updating snake body position
		snakeHead.headPos.push(sf::Vector2<int>(snakeHead.posX, snakeHead.posY));
		sf::Vector2<int> headLast = snakeHead.headPos.front();
		snakeHead.headPos.pop();

		// Updating snake body position
		for (int i = 1; i < SnakeBody::bodyArray.size(); i++) {
			//TODO:
			//1. Push new position to current (previous.back)
			//2. Move sprite to current.front
			//3. Pop front
			SnakeBody::bodyArray[i].bodyQue.push(SnakeBody::bodyArray[i-1].bodyQue.back());
			SnakeBody::bodyArray[i].updatePos();
			SnakeBody::bodyArray[i].bodyQue.pop();
		}

		/*
		//Updating snake body texture on direction change
		//Vertical set
		for (int i = 0; i < snakeBodyArr.size(); i++)
		{
			int a = (snakeBodyArr[i].bodyQue.front()).y - (snakeBodyArr[i].bodyQue.back()).y;
			if (a)
			{
				snakeBodyArr[i].body.setTexture(snakeBodyVertTex);
			}
		}
		//Horizontal set
		for (int i = 0; i < snakeBodyArr.size(); i++)
		{
			int a = (snakeBodyArr[i].bodyQue.front()).x - (snakeBodyArr[i].bodyQue.back()).x;
			if (a)
			{
				snakeBodyArr[i].body.setTexture(snakeBodyTex);
			}
		}

		// error
		for (int i = 1; i < snakeBodyArr.size(); i++)
		{
			sf::Vector2<int> currPos = snakeBodyArr[i - 1].bodyQue.front();
			snakeBodyArr[i].body.setPosition(currPos.x, currPos.y);
			snakeBodyArr[i - 1].bodyQue.pop();
			snakeBodyArr[i].bodyQue.push(sf::Vector2i(currPos.x, currPos.y));
		}
		*/
		//Drawing food
		mainWin.draw(food.foodSprite);

		//Drawing snake head
		mainWin.draw(snakeHeadSpr);

		//Drawing snake body
		for (int i = 0; i < SnakeBody::bodyArray.size(); i++)
		{
			mainWin.draw((SnakeBody::bodyArray[i].sprite));
		}

		mainWin.display();

		while (mainWin.pollEvent(mainEvent)) {


			if (mainEvent.type == sf::Event::Closed) {
				mainWin.close();
			}

			if (mainEvent.type == sf::Event::KeyPressed) {

				switch (mainEvent.key.code) {

				case 71: //Left
					snakeHead.dirX = -1;
					snakeHead.dirY = 0;
					snakeHeadTex.loadFromImage(snakeHeadLeft);
					break;

				case 73: //Up
					snakeHead.dirY = -1;
					snakeHead.dirX = 0;
					snakeHeadTex.loadFromImage(snakeHeadUp);
					break;

				case 72: //Right
					snakeHead.dirX = 1;
					snakeHead.dirY = 0;
					snakeHeadTex.loadFromImage(snakeHeadRight);
					break;

				case 74: //Down
					snakeHead.dirY = 1;
					snakeHead.dirX = 0;
					snakeHeadTex.loadFromImage(snakeHeadDown);
					break;
				}
			}
		}
	}
}