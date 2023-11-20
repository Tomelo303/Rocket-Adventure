#include "Game/Game.h"


int main(int argc, char* argv[])
{
	Game game("My game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false, true);

	// Game loop
	while (game.running())
	{
		game.handleEvents();
		game.update();
		game.render();
	}

	game.clean();

	return 0;
}
