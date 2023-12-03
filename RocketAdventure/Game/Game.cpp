#include "Game.h"
#include "../Player/Player.h"

Player* player;

Game::Game(const char* title, int posX, int posY)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0 && IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG)
	{
		std::cout << "Subsystems initialized.\n";

		_window = SDL_CreateWindow(title, posX, posY, _width, _height, 0);
		if (_window)
		{
			std::cout << "Window created.\n";
		}

		_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
		if (_renderer)
		{
			SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
			std::cout << "Renderer created.\n";
		}

		// Initializing a Player
		player = new Player("../Assets/rocket0.png", _renderer);

		_running = true;
	}
	else
	{
		_running = false;
	}
}

Game::~Game()
{
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	delete player;
	SDL_Quit();
	IMG_Quit();
	std::cout << "Game closed.\n";
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	  case SDL_QUIT:
		_running = false;
		break;

	  case SDL_KEYDOWN:
		  switch (event.key.keysym.sym)
		  {
		    case SDLK_a:
			  player->eventNum(SDLK_a);
			  break;

		    case SDLK_d:
			  player->eventNum(SDLK_d);
			  break;
		  }
	}
}

void Game::update()
{
	switch (player->eventNum())
	{
	  case SDLK_a:
		  player->move(-1, 0);
		  break;

	  case SDLK_d:
		  player->move(1, 0);
		  break;
	}

	if (player->x() < 0)
		player->setPos(0, player->y());
	else if (player->x() > _width - player->destinationRect().w)
		player->setPos(_width - player->destinationRect().w, player->y());
}

void Game::render()
{
	SDL_RenderClear(_renderer);
	SDL_Rect pSrcRect = player->sourceRect();
	SDL_Rect pDstRect = player->destinationRect();
	SDL_RenderCopy(_renderer, player->texture(), &pSrcRect, &pDstRect);
	SDL_RenderPresent(_renderer);
}
