#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "../Player/Player.h"
#include "../Obstacle/Obstacle.h"
#include "../Boost/Boost.h"
#include "../Background/Background.h"
#include "../Text/Text.h"


class Game
{
  public:
	Game(const char* title, int x, int y, bool two_players_mode);
	~Game();

	void handleEvents();  // Handle user input
	void update();        // Update the state of the game
	void render();        // Display the changes on the screen
	bool isRunning() const { return running; }

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static const int width = 700;				 // Width of the game window
	static const int height = 1000;				 // Height of the game window
	static const int spaceStart = 1000;			 // Frame at which the transition from clouds to stars occurs
	static const int transitionDuration = 1000;  // Number of frames it takes to finish the transition

  private:
	void handleCollisionOf(Player* player, Obstacle* obstacle);					   // Handle Player collision with an Obstacle
	void handleCollisionOf(Player* player1, Obstacle* obstacle, Player* player2);  // Handle Player collision with an Obstacle in two player mode
	void handleCollisionOf(Player* player, Boost* boost);						   // Handle Player collision with a Boost
	void handleCollisionOf(Player* player1, Boost* boost, Player* player2);		   // Handle Player collision with a Boost in two player mode
	inline void quitGame() { running = false; }

	SDL_Window* window = nullptr;
	Player* player1 = nullptr;
	Player* player2 = nullptr;
	Obstacle* obstacle = nullptr;
	Boost* boost = nullptr;
	Background* background = nullptr;
	Text* score_text = nullptr;
	Text* high_score_text = nullptr;
	Text* force_field_text = nullptr;  
	bool running = false;
	bool secondPlayer = false;		   // Two players mode active
	bool playerCollision = true;	   // Collision of a Player and an Obstacle active
	bool darkening = false;			   // Darkening of the screen in progress
	int darkeningFactor = 500;		   // Multiplier used to gradually darken the screen
	unsigned int frame = 0;			   // Number of frames that passed since the start of the game
	unsigned int forceFieldStart = 0;  // The frame at which the force field was activated
	unsigned int score = 0;			   // Points describing how well player performed
	unsigned int highScore = 0;		   // The highest number of points player got while playing
};

#endif // GAME_H