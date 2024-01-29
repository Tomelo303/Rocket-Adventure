#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "../Entity/Entity.h"


enum class BackgroundTex
{
	none,
	Clouds,
	Stars
};

class Background : public Entity
{
  public:
	Background();
	~Background();

	void update(const unsigned int& frame) override;  // How the Background should update with every game frame
	void handleCollision() override;  // How the Background should update after it collided with other objects
	void addSpeed(int increment) override { speed.y += increment; }
	void setSpeed(int speed) override { this->speed.y = speed; }

  private:
	void applyTexture(BackgroundTex tex);

	SDL_Texture* clouds_tex;  // Texture of clouds
	SDL_Texture* stars_tex;	  // Texture of stars
	BackgroundTex textureName = BackgroundTex::none;
	bool transition = false;  // Is the transition from clouds to stars incoming
};

#endif // BACKGROUND_H
