#include "TextureHandler.h"
#include "../Game/Game.h"

#include <iostream>


SDL_Texture* TextureHandler::createTexture(const char* texturePath)
{
	SDL_Surface* surface = IMG_Load(texturePath);
	if (surface)
	{
		SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
		if (texture)
		{
			SDL_FreeSurface(surface);
			return texture;
		}
		else
		{
			SDL_FreeSurface(surface);
			std::cout << "Problem loading texture: " << SDL_GetError() << "\n";
			return nullptr;
		}
	}
	else
	{
		std::cout << "Problem loading surface: " << SDL_GetError() << "\n";
		return nullptr;
	}
}
