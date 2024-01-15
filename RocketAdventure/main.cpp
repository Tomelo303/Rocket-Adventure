#include "Game/Game.h"


int main(int argc, char* argv[])
{
	Game game("Rocket Adventure", SDL_WINDOWPOS_CENTERED, 32);

	const int FPS = 60;					// Target frame rate
	const int frameDelay = 1000 / FPS;  // The shortest time a frame should last
	Uint32 frameStart = 0;				// The time at which the frame starts
	int frameTime = 0;					// The time it took to finish the frame
	
	// Game loop
	while (game.isRunning())
	{
		// Getting the starting time of the frame
		frameStart = SDL_GetTicks();

		game.handleEvents();  // Handling user input
		game.update();	      // Updating the state of the game
		game.render();        // Displaying the new state on the screen

		// Measuring the time it took to finish the frame
		frameTime = SDL_GetTicks() - frameStart;
		
		// Delaying the frame if it took less time than is set by frameDelay
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	return 0;
}
