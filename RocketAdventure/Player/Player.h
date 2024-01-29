#ifndef PLAYER_H
#define PLAYER_H

#include "../Entity/Entity.h"


enum class PlayerTex
{
	none,
	Rocket,
	ForceField
};

class Player : public Entity
{
  public:
	Player(int x, int y, bool secondPlayer);
	~Player();

	void handleEvents();  // Handle user input
	void update(const unsigned int& frame) override;  // How the Player should update with every game frame
	void handleCollision() override;    // How the Player should update after it collided with other objects
	void applySpaceTexture() override;  // Apply textures used in space
	void disableSpaceTexture() override;
	void forceFieldOn() { applyTexture(PlayerTex::ForceField); }
	void forceFieldOff() { applyTexture(PlayerTex::Rocket); }

  private:
	void stayInsideWindow();  // Contain player within the game window
	void applyTexture(PlayerTex tex);

	SDL_Texture* rocket_tex;			 // Texture of a rocket
	SDL_Texture* rocket_white_tex;		 // Texture of a white rocket
	SDL_Texture* force_field_tex;		 // Texture of a rocket in a force field
	SDL_Texture* force_field_white_tex;  // Texture of a white rocket in a force field
	PlayerTex textureName = PlayerTex::none;
	SDL_Keycode key = 0;	  // Keycode of the key that is being pressed (as it is implemented in SDL)
	SDL_Keycode currKey = 0;  // Keycode of the key that is being pressed (with custom behaviour)
	SDL_Keycode prevKey = 0;  // Stores the keycode of the most recent key pressed
	bool W = false, S = false, A = false, D = false;  // Flags keeping track of which keys are pressed
	bool secondPlayer = false;  // Is this instance of Player a second Player
};

#endif // PLAYER_H