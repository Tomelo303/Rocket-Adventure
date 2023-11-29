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
	//void applyTexture(SDL_Texture* texture);

  private:
	int _posX;
	int _posY;
	int _speed;
};

#endif // PLAYER_H