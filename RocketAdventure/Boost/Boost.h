#ifndef BOOST_H
#define BOOST_H

#include "../Entity/Entity.h"


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
	void handleCollision() override;		 // How the Boost should update after it collided with other objects
	const BoostTex& getTextureName() const { return textureName; }

  private:
	  void generateSpawnProperties();  // Assign a random x coordinate and appropriate texture and direction of movement
	  void applyTexture(BoostTex tex);

	SDL_Texture* speed_boost_tex;		 // Texture of a speed boost
	SDL_Texture* force_field_boost_tex;  // Texture of a force field boost
	BoostTex textureName = BoostTex::none;
	bool hidden = true;	 // Is the Boost below or above the game window
};

#endif // BOOST_H
