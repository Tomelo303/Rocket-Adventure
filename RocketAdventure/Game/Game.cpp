#include "Game.h"
#include "../Collision/Collision.h"
#include "../Text/Text.h"

#include <iostream>


Player* player;
Obstacle* obstacle;
Boost* boost;
Background* background;
Text* score_text;
Text* high_score_text;
Text* force_field_text;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Game::Game(const char* title, int x, int y)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0 && IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG && TTF_Init() != -1)
	{
		std::cout << "Subsystems initialized.\n";

		window = SDL_CreateWindow(title, x, y, width, height, 0);
		if (window)
		{
			std::cout << "Window created.\n";
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created.\n";
		}

		std::srand(static_cast<unsigned int>(std::time(NULL)));  // Generating a seed for the rand() functions based on the time

		// Initialising game entities
		player = new Player(width / 2, height - 200);
		obstacle = new Obstacle(-height);
		boost = new Boost(-3 * height);
		background = new Background();

		// Initialising text objects
		score_text = new Text("../Assets/Minecraftia.ttf");
		score_text->setFontSize(30);
		score_text->setFontColor(FontColor::Red);
		
		high_score_text = new Text("../Assets/Minecraftia.ttf");
		high_score_text->setFontSize(30);
		high_score_text->setFontColor(FontColor::Black);
		
		force_field_text = new Text("../Assets/Minecraftia.ttf");
		force_field_text->setFontSize(20);
		force_field_text->setFontColor(FontColor::Blue);


		running = true;
	}
	else
	{
		running = false;
	}
}

Game::~Game()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	delete player;
	delete obstacle;
	delete boost;
	delete background;
	delete score_text;
	delete high_score_text;
	delete force_field_text;
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
	std::cout << "Game closed. High score: " << highScore << "\n";
}

void Game::handleEvents()
{
	SDL_PollEvent(&event);

	// Handle events regarding the game window
	switch (event.type)
	{
	case SDL_QUIT:  // Closing of the game window
		quitGame();
		break;

	default:
		break;
	}

	// Handle events regarding game entities
	player->handleEvents();
}

void Game::update()
{
	// Update game entities
	player->update(frame);
	if (obstacle->getTextureName() != ObstacleTex::UFO)  // After obstacle turns into a UFO change speed only when player does
		background->setSpeed(obstacle->getSpeed().y);  // Ensure background has the same speed as Obstacle
	obstacle->update(frame);
	boost->update(frame);
	background->update(frame);
	
	// Handle collisions
	if (playerCollision)
		handlePlayerCollisionWith(obstacle);
	handlePlayerCollisionWith(boost);

	// Turn the force field off and activate the collision back
	if (frame - forceFieldStart == forceFieldDuration && playerCollision == false)
	{
		player->forceFieldOff();
		playerCollision = true;
	}

	frame++;

	// Calculate score
	if (obstacle->getTextureName() != ObstacleTex::UFO)
		score += (player->getSpeed().y * obstacle->getSpeed().y) / 15;
	else
		score += (player->getSpeed().y * obstacle->getSpeed().x) / 15 + 5;

	// Handle darkening of the screen
	if (frame == spaceStart + transitionDuration - darkeningFactor)
		darkening = true;

	if (darkening && darkeningFactor >= 0)
	{
		// Darken the screen during transmition
		if (frame == spaceStart + transitionDuration - darkeningFactor)
		{
			SDL_SetRenderDrawColor(renderer, darkeningFactor / 2, darkeningFactor / 2, darkeningFactor / 2, 255);
			darkeningFactor -= 10;
		}

		if (darkeningFactor == 250)
		{
			player->applySpaceTexture();
			boost->applySpaceTexture();
			high_score_text->setFontColor(FontColor::White);
		}
	}
	else if (darkening && darkeningFactor < 0)
	{
		darkening = false;
	}

	//std::cout << "Frame #" << playerPoints << "\n";
}

void Game::render()
{
	SDL_RenderClear(renderer);  // Clear previous render
	// Render updated entities onto the game window
	// (order of rendering determines which objects are further in the background from the furthest to the nearest)
	background->render();
	obstacle->render();
	player->render();
	boost->render();
	high_score_text->display(20, height - 20 - high_score_text->height(), "High score: ", highScore);
	score_text->display(20, height - 70 - score_text->height(), "Score: ", score);
	if(!playerCollision)
		force_field_text->display(20, height - 120 - force_field_text->height(), "Force field: ", (static_cast<double>(forceFieldStart) - static_cast<double>(frame)) / static_cast<double>(forceFieldDuration) * 100 + 100, "%");
	SDL_RenderPresent(renderer);
}

void Game::handlePlayerCollisionWith(Obstacle* obs)
{
	if (Collision::AABB(player->getRect(), obs->getRect()))
	{
		player->handleCollision();
		boost->handleCollision();
		background->handleCollision();
		obs->handleCollision();
		
		// Disable space textures
		player->disableSpaceTexture();
		boost->disableSpaceTexture();

		// Return previous render and text color
		if (darkeningFactor < 500)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			high_score_text->setFontColor(FontColor::Black);
		}
		frame = 0;
		darkeningFactor = 500;
		if (highScore < score)
			highScore = score;
		score = 0;
		std::cout << "Game restarted.\n\n";
	}
}

void Game::handlePlayerCollisionWith(Boost* boo)
{
	if (Collision::AABB(player->getRect(), boo->getRect()))
	{
		// Assign a proper bonus for collecting a boost
		switch (boo->getTextureName())
		{
		case (BoostTex::SpeedBoost):
			player->addSpeed(1);
			obstacle->addSpeed(1);
			if (obstacle->getTextureName() == ObstacleTex::UFO)
				background->addSpeed(1);
			break;

		case (BoostTex::ForceFieldBoost):
			player->forceFieldOn();
			playerCollision = false;
			forceFieldStart = frame;  // Set current frame as the frame in which the force field was activated
			break;

		default:
			break;
		}

		boo->handleCollision();
	}
}
