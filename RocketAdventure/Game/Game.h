#ifndef GAME_H
#define GAME_H

#include <SDL.h>

class Game
{
public:
	Game(const char* title, int Xpos, int Ypos, int width, int height, bool fullscreen, bool resizable);
	~Game();

	//void init(const char* title, int Xpos, int Ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() const { return isRunning; }

private:
	int counter = 0;
	bool isRunning = false;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
};

#endif // GAME_H