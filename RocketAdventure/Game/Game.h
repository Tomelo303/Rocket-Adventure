#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "../Player/Player.h"

class Game
{
  public:
	Game(const char* title, int posX, int posY);
	~Game();

	void handleEvents();  // Handling user input
	void update();        // Method for updating the state of the game, e.g. player position
	void render();        // Method for displaying the changes on the screen
	bool isRunning() const { return _running; }

  private:
	SDL_Texture* createTexture(const char* fileName);  // Method for creating a texture which is only used by other methods
	
	const int _width = 800;
	const int _height = 1000;
	bool _running = false;
	SDL_Window* _window = nullptr;
	SDL_Renderer* _renderer = nullptr;
	Player player = Player(_width/2, _height);
};

#endif // GAME_H