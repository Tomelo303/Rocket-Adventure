#include "Game.h"


Game::Game(const char* title, int posX, int posY)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0 && IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG)
	{
		std::cout << "Subsystems initialised.\n";

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

		// Creating all textures
		player.applyTexture(Game::createTexture("../Assets/rocket0.png"));

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
	}
}

void Game::update()
{
	if (player.y() > 0)
	{
		player.move(0, -1);
		std::cout << "Player is on y = " << player.y() << "\n";
	}
	
	if (player.y() < 0)
	{
		player.setPos(player.x(), 0);
		std::cout << "Player moved to (" << player.x() << ", " << player.y() << ") coordinates.\n";
	}
}

void Game::render()
{
	SDL_RenderClear(_renderer);
	SDL_Rect pRect = player.rect();
	SDL_RenderCopy(_renderer, player.texture(), NULL, &pRect);
	SDL_RenderPresent(_renderer);
}

SDL_Texture* Game::createTexture(const char* fileName)
{
	SDL_Surface* surface = IMG_Load(fileName);
	if (surface)
	{
		SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);
		if (texture)
		{
			SDL_FreeSurface(surface);
			return texture;
		}
		else
		{
			SDL_FreeSurface(surface);
			std::cout << "Problem loading texture: " << SDL_GetError() << "\n";
		}
	}
	else
	{
		std::cout << "Problem loading surface: " << SDL_GetError() << "\n";
	}
}
