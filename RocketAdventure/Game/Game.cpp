#include "Game.h"


Game::Game(const char* title, int posX, int posY, bool fullscreen, bool resizable, bool borderless)
{
	int flags[3] = { 0, 0, 0 };

	if (fullscreen)
	{
		flags[0] = SDL_WindowFlags::SDL_WINDOW_FULLSCREEN;
	}

	if (resizable)
	{
		flags[1] = SDL_WindowFlags::SDL_WINDOW_RESIZABLE;
	}

	if (borderless)
	{
		flags[2] = SDL_WindowFlags::SDL_WINDOW_BORDERLESS;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0 && IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG)
	{
		std::cout << "Subsystems initialised.\n";

		_window = SDL_CreateWindow(title, posX, posY, _width, _height, flags[0] | flags[1] | flags[2]);
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

		_running = true;
	}
	else
	{
		_running = false;
	}
	
	// Creating all textures
	_playerTexture = Game::createTexture("../Assets/rocket0.png");
}

Game::~Game()
{
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyTexture(_playerTexture);
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

}
void Game::render()
{
	SDL_RenderClear(_renderer);
	SDL_Rect playerRect = { (_width - 65)/2 , _height - 100, 65, 100 };
	SDL_RenderCopy(_renderer, _playerTexture, NULL, &playerRect);
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
			return texture;
		}
		else
		{
			std::cout << "Problem loading texture: " << SDL_GetError() << "\n";
		}
		SDL_FreeSurface(surface);
	}
	else
	{
		std::cout << "Problem loading surface: " << SDL_GetError() << "\n";
	}
}
