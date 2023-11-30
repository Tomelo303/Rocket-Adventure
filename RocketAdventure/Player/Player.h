#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

class Player
{
  public:
	Player(int posX, int posY);
	~Player();

	void move(int x, int y);  // Method for moving player by x in horizontal direction and by y in vertical direction
	void setPos(int x, int y) { _posX = x; _posY = y; }  // Method for placing a Player in x, y coordinates
	int x() const { return _posX; }
	int y() const { return _posY; }
	void speed(int v) { _speed = v; }  // Method for changing the speed of a Player
	int speed() const { return _speed; }

	SDL_Rect rect() const { return _playerRect; }
	void applyTexture(SDL_Texture* texture) { _playerTexture = texture; }
	SDL_Texture* texture() const { return _playerTexture; }

  private:
	int _posX = 0;
	int _posY = 0;
	int _width = 66;
	int _height = 100;
	int _speed = 10;
	SDL_Rect _playerRect = { _posX, _posY, _width, _height };
	SDL_Texture* _playerTexture = nullptr;
};

#endif // PLAYER_H