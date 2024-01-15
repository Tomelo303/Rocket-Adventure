#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>



class Game
{
  public:
	Game(const char* title, int x, int y);
	~Game();

	void handleEvents();  // Handle user input
	void update();        // Update the state of the game
	void render();        // Display the changes on the screen
	bool isRunning() const { return running; }

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static const int width = 800;	 // Width of the game window
	static const int height = 1000;  // Height of the game window

  private:	
	SDL_Window* window = nullptr;
	bool running = false;
	int frame = 0;  // Number of frames that passed since the start of the game
};

#endif // GAME_H