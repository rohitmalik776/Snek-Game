#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>
#include <vector>
#include <list>

#include "snake_body.cpp"
#include "board.cpp"
#include "food.cpp"
#include "pause_prompt.cpp"
int blockside = 41;
int score = 0;

enum class GameState {
	Running,
	Paused,
	GameOver
};

int main() {
	srand(time(0));
	GameState currentGameState = GameState::Running;

	//Importing fonts
	sf::Font font;
	if(!(font.loadFromFile("Resources/Raleway-Bold.ttf"))){
		std::cout << "Error loading font file!" << std::endl;
	}
	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setFillColor(sf::Color::Black);
	scoreText.setPosition(530, 0);
	scoreText.setCharacterSize(30);
	//A queue to make the body follow the head
	std::queue<sf::Vector2<int>> headPos;
	for (int i = 0; i < 11; i++) 
	{
		sf::Vector2<int> origin(0, 0);
		headPos.push(origin);
	}
	int snakeX = 0, snakeY = 0;
	int snakePosX = 100, snakePosY = 100;
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
	if (!snakeBodyImg.loadFromFile("Resources/snake_body.png"))
	{
		std::cout << "Error loading 'Resources/snake_body.bmp'\n";
		return 0;
	}
	//Making snake body vertical sprite
	sf::Image snakeBodyVert;
	if (!(snakeBodyVert.loadFromFile("Resources/snake_body_vert.png")))
	{
		std::cout << "Couldn't load Snake body vertical << endl";
		return 0;
	}
	sf::Image specialImg;
	if (!(specialImg.loadFromFile("Resources/special.png"))) {
		std::cout << "Couldn't load special image << endl";
		return 0;
	}
	sf::Texture specialTex;
	specialTex.loadFromImage(specialImg);
	//Making snake texture
	sf::Texture snakeHeadTex, snakeBodyTex;
	snakeHeadTex.loadFromImage(snakeHeadRight);
	snakeBodyTex.loadFromImage(snakeBodyImg);
	//Making snake head sprite
	sf::Sprite snakeHeadSpr, snakeBodySpr;
	snakeHeadSpr.setTexture(snakeHeadTex);
	snakeHeadSpr.setPosition(100, 100);
	snakeHeadSpr.setScale(sf::Vector2f(spr_scale, spr_scale));
	//Making snake body sprite
	snakeBodySpr.setTexture(snakeBodyTex);
	snakeBodySpr.setPosition(0, 0);
	snakeBodySpr.setScale(sf::Vector2f(spr_scale, spr_scale));
	sf::Texture snakeBodyVertTex;
	snakeBodyVertTex.loadFromImage(snakeBodyVert);
	sf::Sprite snakeBodyVertSpr;
	snakeBodyVertSpr.setTexture(snakeBodyVertTex);
	snakeBodyVertSpr.setPosition(0, 0);
	snakeBodyVertSpr.setScale(sf::Vector2f(spr_scale, spr_scale));
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
	
MAINEVENT:
	//Making snake body
	std::vector <snakeBody> snakeBodyArr;
	snakeBody temp(snakeBodySpr);
	snakePosX = 100;
	snakePosY = 100;
	for (int i = 0; i < 20; i++)
		snakeBodyArr.push_back(temp);
	currentGameState = GameState::Running;


	while (mainWin.isOpen()) {
	
		while (currentGameState == GameState::GameOver) {
			// Resetting snake body
			for (int i = 0; i < score; i++) {
				snakeBodyArr[i].isVisible = false;
			}
			// Resetting score
			score = 0;
			// Resetting snake's position multipliers
			snakeX = 0;
			snakeY = 0;
			while (mainWin.pollEvent(mainEvent)) {
				if (mainEvent.type == sf::Event::Closed) {
					return 0;
				}
				if (mainEvent.key.code == sf::Keyboard::R) {
					currentGameState = GameState::Running;
					break;
				}
			}
			if(currentGameState != GameState::GameOver)
				goto MAINEVENT;
		}
		

		while (currentGameState == GameState::Paused) {
			PausePrompt pausePrompt(&font);
			pausePrompt.draw(&mainWin);
			mainWin.display();
			while (mainWin.pollEvent(mainEvent)) {
				pausePrompt.draw(&mainWin);
				mainWin.display();
				if (mainEvent.type == sf::Event::Closed) {
					return 0;
				}
				if (mainEvent.key.code == sf::Keyboard::Return) {
					currentGameState = GameState::Running;
					break;
				}
			}
		}

		mainWin.clear(sf::Color(255, 255, 255));

		//Drawing grass sprites
		mainWin.draw(grassLightSpr);
		mainWin.draw(grassDarkSpr);


		//Drawing grid lines
		mainBoard.drawGrid(&mainWin);

		//Drawing grass
		mainBoard.drawGrass(&mainWin, &grassLightSpr, &grassDarkSpr);

		//Drawing border
		mainBoard.drawBorder(&mainWin);

		//Storing snake's last seen position
		int headLastSeenX = snakePosX, headLastSeenY = snakePosY;


		//Drawing snake
		snakePosX += 4 * snakeX;			//snakeX = -1 or 1
		snakePosY += 4 * snakeY;
		// std:: cout << snakePosX << std::endl;
		if ((food.x > snakePosX - 20.0) && (food.x < snakePosX + 20.0) && (food.y > snakePosY - 20.0) && (food.y < snakePosY + 20.0)) {
			std::cout << "Snake and food's coordinates clashed!\n";
			// std::cout << "food.x: " << food.x << std::endl;
			food.changePosition();
			std::cout << "snakePosX: " << snakePosX << std::endl;
			if (score < snakeBodyArr.size()) {
				snakeBodyArr[score].isVisible = true;
				score++;
			}
		}

		if (snakePosX > 510 ) {
			currentGameState = GameState::GameOver;
			//snakePosX = 0;
		}
		if (snakePosY > 510 )
		{
			currentGameState = GameState::GameOver;
			//snakePosY = 0;
		}
		if (snakePosX < 25) {
			currentGameState = GameState::GameOver;
			//snakePosX = 571;
		}
		if (snakePosY < 25)
		{
			currentGameState = GameState::GameOver;
			//snakePosY = 571;
		}

		snakeHeadSpr.setPosition(snakePosX, snakePosY);


		//Updating snake body position
		headPos.push(sf::Vector2<int>(snakePosX, snakePosY));
		sf::Vector2<int> headLast = headPos.front();
		headPos.pop();
		snakeBodyArr[0].body.setPosition(headLast.x, headLast.y);
		snakeBodyArr[0].bodyQue.push(headLast);

		//Updating score
		scoreText.setString(std::to_string(score));

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
		for (int i = 1; i < snakeBodyArr.size(); i++)
		{
			sf::Vector2<int> currPos = snakeBodyArr[i - 1].bodyQue.front();
			snakeBodyArr[i].body.setPosition(currPos.x, currPos.y);
			snakeBodyArr[i - 1].bodyQue.pop();
			snakeBodyArr[i].bodyQue.push(sf::Vector2i(currPos.x, currPos.y));
		}

		//Drawing food
		mainWin.draw(food.foodSprite);

		//Drawing snake head
		mainWin.draw(snakeHeadSpr);
		//Drawing snake body
		for (int i = 0; i < snakeBodyArr.size() - 1; i++)
		{
			mainWin.draw((snakeBodyArr[i].getBody()));
		}
		//Drawing score
		mainWin.draw(scoreText);

		mainWin.display();

		while (mainWin.pollEvent(mainEvent)) {


			if (mainEvent.type == sf::Event::Closed) {
				mainWin.close();
			}

			if (mainEvent.type == sf::Event::KeyPressed) {

				switch (mainEvent.key.code) {

				case 36: {
					std::cout << "Pressed!" << std::endl;
					currentGameState = GameState::Paused;
				}
				break;
				case 71: //Left
					if (snakeX != 1) {
						snakeX = -1;
						snakeY = 0;
						snakeHeadTex.loadFromImage(snakeHeadLeft);
					}
					break;

				case 73: //Up
					if (snakeY != 1) {
						snakeY = -1;
						snakeX = 0;
						snakeHeadTex.loadFromImage(snakeHeadUp);
					}break;

				case 72: //Right
					if (snakeX != -1)
					{
						snakeX = 1;
						snakeY = 0;
						snakeHeadTex.loadFromImage(snakeHeadRight);
					}break;

				case 74: //Down
					if (snakeY != -1)
					{
						snakeY = 1;
						snakeX = 0;
						snakeHeadTex.loadFromImage(snakeHeadDown);
					}break;
				}
			}
		}
	}
}