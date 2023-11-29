#include "Game/Game.h"


int main(int argc, char* argv[])
{
	Game game("Rocket Adventure", SDL_WINDOWPOS_CENTERED, 32, false, false, false);
	
	// Game loop
	while (game.isRunning())
	{
		game.handleEvents();
		game.update();
		game.render();
	}

	return 0;
}
