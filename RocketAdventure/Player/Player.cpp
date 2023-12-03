#include "Player.h"
#include <iostream>


Player::Player(const char* textureFile, SDL_Renderer* renderer)
{
	G_renderer = renderer;
	_playerTexture = TextureHandler::createTexture(textureFile, renderer);
	std::cout << "Player initialized.\n";
}

Player::~Player()
{
	SDL_DestroyTexture(_playerTexture);
	std::cout << "Player destroyed.\n";
}

void Player::move(int x, int y)
{
	_posX += x * _speed;
	_posY += y * _speed;
	_destinationRect.x = _posX;
	_destinationRect.y = _posY;
}
