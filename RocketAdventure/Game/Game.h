#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "../Player/Player.h"
#include "../Obstacle/Obstacle.h"
#include "../Boost/Boost.h"


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
	static const int width = 700;	 // Width of the game window
	static const int height = 1000;  // Height of the game window

  private:
	void checkPlayerCollisionWith(Obstacle* obs);  // Check for a Player collision with an Obstacle
	void checkPlayerCollisionWith(Boost* boo);  // Check for a Player collision with an Obstacle
	inline void quitGame() { running = false; }

	SDL_Window* window = nullptr;
	bool running = false;
	bool playerCollision = true;  // Turns the collision of a Player and an Obstacle on and off
	unsigned int frame = 0;  // Number of frames that passed since the start of the game
	unsigned int forceFieldStart = 0;  // The frame at which the force field was activated
};

#endif // GAME_H