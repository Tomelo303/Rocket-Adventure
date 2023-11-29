#include "Player.h"

Player::Player(int posX, int posY)
	:_posX(posX), _posY(posY){}

Player::~Player(){}

void Player::move(int x, int y)
{
	_posX += x * _speed;
	_posY += y * _speed;
}
