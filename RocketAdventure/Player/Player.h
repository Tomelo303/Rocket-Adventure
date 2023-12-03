#ifndef PLAYER_H
#define PLAYER_H

#include "../TextureHandler/TextureHandler.h"

class Player
{
  public:
	Player(const char* textureFile, SDL_Renderer* renderer);
	~Player();

	void move(int x, int y);  // Method for moving player by x in horizontal direction and by y in vertical direction
	void setPos(int x, int y) { _posX = x; _posY = y; }  // Method for placing a Player in x, y coordinates
	int x() const { return _posX; }
	int y() const { return _posY; }
	void speed(int v) { _speed = v; }  // Method for changing the speed of a Player
	int speed() const { return _speed; }
	void eventNum(int e) { _event = e; }
	int eventNum() const { return _event; }

	SDL_Rect sourceRect() const { return _sourceRect; }
	SDL_Rect destinationRect() const { return _destinationRect; }
	void applyTexture(SDL_Texture* texture) { _playerTexture = texture; }
	SDL_Texture* texture() const { return _playerTexture; }

  private:
	int _width = 66;
	int _height = 99;
	int _posX = 400 - _width / 2;
	int _posY = 850 - _height;
	int _speed = 3;
	int _event = 0;
	SDL_Rect _sourceRect = { 0, 0, 650, 1000 };  // Sets which part of the texture to load
	SDL_Rect _destinationRect = { _posX, _posY, _width, _height };  // Sets where and in what scale the loaded texture will be
	SDL_Texture* _playerTexture = nullptr;
	SDL_Renderer* G_renderer = nullptr;  // Renderer passed down by the Game object
};

#endif // PLAYER_H