#include "Game.h"
#include "../Collision/Collision.h"
#include "../Text/Text.h"

#include <iostream>


Player* player;
Obstacle* obstacle;
Boost* boost;
Text* text;
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

		// Initialising text objects
		//text = new Text("../Assets/Minecraftia.ttf", 30, "Test text", { 255, 0, 0, 255 });
		text = new Text("../Assets/Minecraftia.ttf");

		// Setting properties of text objects
		text->setFontSize(30);
		text->setFontColor(FontColor::Black);

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
	delete text;
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
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
	if (playerCollision)
	checkPlayerCollisionWith(obstacle);
	checkPlayerCollisionWith(boost);

	// Turn the force field off after 500 frames and activate the collision back
	if (frame - forceFieldStart == 500 && playerCollision == false)
	{
		player->forceFieldOff();
		playerCollision = true;
	}

	frame++;

	//std::cout << "Frame #" << playerPoints << "\n";
}

void Game::render()
{
	SDL_RenderClear(renderer);  // Clear previous render
	// Render updated entities onto the game window
	// (order of rendering determines which objects are further in the background from the furthest to the nearest)
	obstacle->render();
	player->render();
	boost->render();
	text->display(20, height - 20 - text->height(), "Frame: ", frame);
	SDL_RenderPresent(renderer);
}

void Game::checkPlayerCollisionWith(Obstacle* obs)
{
	if (Collision::AABB(player->getRect(), obs->getRect()))
	{
		player->handleCollision();
		boost->handleCollision();
		obs->handleCollision();
		
		frame = 0;
	}
}

void Game::checkPlayerCollisionWith(Boost* boo)
{
	if (Collision::AABB(player->getRect(), boo->getRect()))
	{
		// Assign a proper bonus for collecting a boost
		switch (boo->getTextureName())
		{
		case (BoostTex::SpeedBoost):
			player->addSpeed(1);
			obstacle->addSpeed(1);
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
