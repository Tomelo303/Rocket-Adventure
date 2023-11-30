#include "Player.h"

Player::Player(int posX, int posY)
{
	_posX = posX - _width / 2;
	_posY = posY - _height;
	std::cout << "Player initialised.\n";
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
	_playerRect.x = _posX;
	_playerRect.y = _posY;
}
