#include "Game.h"
#include "../CollisionHandler/CollisionHandler.h"
#include "../Player/Player.h"
#include "../Obstacle/Obstacle.h"

#include <iostream>


Player* player;
Obstacle* obstacle1;
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
		obstacle1 = new Obstacle(-height);

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
	delete obstacle1;
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
		running = false;
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
	obstacle1->update(frame);
	
	// Check for collisions
	if (CollisionHandler::AABB(player->getRect(), obstacle1->getRect()))
	{
		player->handleCollision();
		obstacle1->handleCollision();
		std::cout << "Collision detected\n";
		//running = false;  // Close the game
	}

	// Update game properties
	if (frame == 1000000)
		frame = 1;  // A simple way to prevent reaching max int value
	else
		frame++;

	//std::cout << "Frame #" << playerPoints << "\n";
}

void Game::render()
{
	SDL_RenderClear(renderer);
	// Render updated entities onto the game window
	player->render();
	obstacle1->render();
	SDL_RenderPresent(renderer);
}
