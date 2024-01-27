#ifndef PLAYER_H
#define PLAYER_H

#include "../Entity/Entity.h"


enum class PlayerTex
{
	none,
	Rocket  // PLACEHOLDER
};

class Player : public Entity
{
  public:
	Player(int x, int y);
	~Player();

	void handleEvents();  // Handle user input
	void update(const int& frame) override;  // How the Player should update with every game frame
	void handleCollision() override;		 // How the Player should update after it collided with other objects
	int getAltitude() const { return altitude; }
	void addSpeed(int increment) { speed += increment; }

  private:
	void stayInsideWindow();  // Contain player within the game window
	void applyTexture(PlayerTex tex);
	//void applyTexture(EngineTex tex);
	//void applyTexture(BoostersTex tex);

	SDL_Texture* rocket_tex;  // Texture of a rocket
	PlayerTex textureName = PlayerTex::none;
	int altitude = 0;		  // Points describing how well the player has performed (calculated based on the Game::frame)
	SDL_Keycode key = 0;	  // Keycode of the key that is being pressed (as it is implemented in SDL)
	SDL_Keycode currKey = 0;  // Keycode of the key that is being pressed (with custom behaviour)
	SDL_Keycode prevKey = 0;  // Stores the keycode of the most recent key pressed
	bool W = false, S = false, A = false, D = false;  // Flags keeping track of which keys are pressed
};

#endif // PLAYER_H