#include "Game.h"

#include <iostream>

Game::Game(const char* title, int Xpos, int Ypos, int width, int height, bool fullscreen, bool resizable)
{
	int flags[2] = { 0, 0 };

	if (fullscreen)
	{
		flags[0] = SDL_WINDOW_FULLSCREEN;
	}

	if (resizable)
	{
		flags[1] = SDL_WINDOW_RESIZABLE;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems initialised.\n";

		window = SDL_CreateWindow(title, Xpos, Ypos, width, height, flags[0] | flags[1]);
		if (window)
		{
			std::cout << "Window created.\n";
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created.\n";
		}

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}
}

Game::~Game()
{
	std::cout << "Game class destroyed.\n";
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	}
}
void Game::update()
{
	std::cout << counter++ << "\n";
}
void Game::render()
{
	SDL_RenderClear(renderer);
	// Stuff that needs to be rendered goes here
	SDL_RenderPresent(renderer);
}
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned.\n";
}
