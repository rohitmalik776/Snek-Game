#include <SFML/Graphics.hpp>
#include <iostream>
#include "board.cpp"

int blockside = 41;


int main() {

	int snakeX = -1, snakeY = 1;
	int snakePosX = 0, snakePosY = 0;

	//Scale of sprites
	double spr_scale = 0.0214;
	spr_scale *= 4;



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

	sf::Image snakeHeadImg, snakeBodyImg;
	if (!snakeHeadImg.loadFromFile("Resources/snake_head.png")) 
	{
		std::cout << "Error loading 'Resources/snake_head.bmp'\n";
		return 0;
	}
	if (!snakeBodyImg.loadFromFile("Resources/snake_body.png"))
	{
		std::cout << "Error loading 'Resources/snake_body.bmp'\n";
		return 0;
	}


	//Making snake texture
	sf::Texture snakeHeadTex, snakeBodyTex;
	snakeHeadTex.loadFromImage(snakeHeadImg);
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


		//Drawing snake
		snakePosX += 4 * snakeX;
		snakePosY += 4 * snakeY;

		if (snakePosX > 571)
			snakePosX = 0;
		if (snakePosY > 571)
			snakePosY = 0;
		if (snakePosX < 0)
			snakePosX = 571;
		if (snakePosY < 0)
			snakePosY = 571;


		snakeHeadSpr.setPosition(snakePosX, snakePosY);

		mainWin.draw(snakeHeadSpr);



		mainWin.display();

		while (mainWin.pollEvent(mainEvent)) {


			if (mainEvent.type == sf::Event::Closed) {
			
				mainWin.close();
			
			}

			if (mainEvent.type == sf::Event::KeyPressed) {
			
				std::cout << mainEvent.key.code << std::endl;
				switch (mainEvent.key.code) {
				
				case 71:
					snakeX = -1;
					snakeY = 0;
					break;

				case 73:
					snakeY = -1;
					snakeX = 0;
					break;

				case 72:
					snakeX = 1;
					snakeY = 0;
					break;

				case 74:
					snakeY = 1;
					snakeX = 0;
					break;
				
				}
			
			}

		
		
		}
		
		
		}
	
	}