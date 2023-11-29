#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

class Game
{
  public:
	Game(const char* title, int posX, int posY, bool fullscreen, bool resizable, bool borderless);
	~Game();

	void handleEvents();  // Handling user input
	void update();  // Method for updating the state of the game, e.g. player position
	void render();  // Method for displaying the changes on the screen

	bool isRunning() const { return _running; }

  private:
	// !! Might move to the Player class !!
	SDL_Texture* createTexture(const char* fileName);  // Method for creating a texture which is only used by other methods
	
	const int _width = 800;
	const int _height = 1000;
	bool _running = false;
	SDL_Window* _window = nullptr;
	SDL_Renderer* _renderer = nullptr;
	// !! Might move to the Player class !!
	SDL_Texture* _playerTexture = nullptr;
};

#endif // GAME_H