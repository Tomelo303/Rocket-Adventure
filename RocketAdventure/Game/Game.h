#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "../Player/Player.h"
#include "../Obstacle/Obstacle.h"
#include "../Boost/Boost.h"
#include "../Background/Background.h"


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
	static const int spaceStart = 8000;			 // Frame at which the transition from clouds to stars accurs
	static const int transitionDuration = 1000;  // Number of frames it takes to finish the transition

  private:
	void handlePlayerCollisionWith(Obstacle* obs);  // Check for a Player collision with an Obstacle
	void handlePlayerCollisionWith(Boost* boo);  // Check for a Player collision with an Obstacle
	inline void quitGame() { running = false; }

	SDL_Window* window = nullptr;
	bool running = false;
	bool playerCollision = true;		 // Turns the collision of a Player and an Obstacle on and off
	unsigned int frame = 0;				 // Number of frames that passed since the start of the game
	unsigned int forceFieldStart = 0;	 // The frame at which the force field was activated
	unsigned int score = 0;				 // Points describing how well player performed
	unsigned int highScore = 0;			 // The highest number of points player got while playing
	const int forceFieldDuration = 500;  // How many frames the force field lasts
	bool darkening = false;				 // Is the darkening of the screen happening
	int darkeningFactor = 500;			 // Multiplier used to gradually darken the screen
};

#endif // GAME_H