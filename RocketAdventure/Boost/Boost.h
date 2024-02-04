#ifndef BOOST_H
#define BOOST_H

#include "../Entity/Entity.h"

// Idea for a new boost type: A boost that gives lives that player spends by hitting obstacles


enum class BoostTex
{
	none,
	SpeedBoost,
	ForceFieldBoost
};

class Boost : public Entity
{
  public:
	Boost(int y);
	~Boost();

	void update(const unsigned int& frame) override;  // How the Boost should update with every game frame
	void handleCollision() override;      // How the Boost should update after it collided with other objects
	void applySpaceTexture() override;    // Apply textures used in space
	void disableSpaceTexture() override;  // Disable textures used in space
	BoostTex getTextureName() const { return textureName; }

	static const int forceFieldDuration = 500;  // How many frames the force field lasts

  private:
	void generateSpawnProperties();  // Assign a random x coordinate and appropriate texture and direction of movement
	void applyTexture(BoostTex tex);

	SDL_Texture* speed_boost_tex;			   // Texture of a speed boost
	SDL_Texture* speed_boost_white_tex;		   // Texture of a white speed boost
	SDL_Texture* force_field_boost_tex;		   // Texture of a force field boost
	SDL_Texture* force_field_boost_white_tex;  // Texture of a white force field boost
	BoostTex textureName = BoostTex::none;
	bool spaceTexture = false;  // Change to texture used in space
	bool hidden = true;			// Boost is below or above the game window
};

#endif // BOOST_H
