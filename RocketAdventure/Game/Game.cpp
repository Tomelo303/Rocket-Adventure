#include "Game.h"
#include "../CollisionHandler/CollisionHandler.h"

#include <iostream>


Player* player;
Obstacle* obstacle;
Boost* boost;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Game::Game(const char* title, int x, int y)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0 && IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG)
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
	SDL_Quit();
	IMG_Quit();
	std::cout << "Game closed.\n";
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
	obstacle->update(frame);
	boost->update(frame);
	
	// Check for collisions
	checkPlayerCollisionWith(obstacle);
	bool assignBonus = checkPlayerCollisionWith(boost);

	// Assign a proper bonus for collecting a boost
	if (assignBonus)
	{
		switch (boost->getTextureName())
		{
		case (BoostTex::Speed):
			player->addSpeed(1);
			break;

		default:
			break;
		}
	}

	frame++;

	//std::cout << "Frame #" << playerPoints << "\n";
}

void Game::render()
{
	SDL_RenderClear(renderer);
	// Render updated entities onto the game window
	player->render();
	obstacle->render();
	boost->render();
	SDL_RenderPresent(renderer);
}

bool Game::checkPlayerCollisionWith(Entity* entity)
{
	if (CollisionHandler::AABB(player->getRect(), entity->getRect()))
	{
		player->handleCollision();
		entity->handleCollision();
		return true;
	}
	else
	{
		return false;
	}
}
