#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "../Entity/Entity.h"


enum class ObstacleTex
{
	none,
	Plane_R,
	Plane_L,
	UFO
};

class Obstacle : public Entity
{
  public:
	Obstacle(int y);
	~Obstacle();

	void update(const unsigned int& frame) override;  // How the Obstacle should update with every game frame
	void handleCollision() override;  // How the Obstacle should update after it collided with other objects
	void addSpeed(int increment) override { speed.y += increment; }
	ObstacleTex getTextureName() const { return textureName; }

  private:
	void bounceFromWalls();  // Change the direction in x axis if Obstacle hits the vertical boundry of the game window
	void generateSpawnProperties();  // Assign a random x coordinate and appropriate texture and direction of movement
	void applyTexture(ObstacleTex tex);

	SDL_Texture* plane_r_tex;  // Texture of a plane facing the right side
	SDL_Texture* plane_l_tex;  // Texture of a plane facing the left side
	SDL_Texture* ufo_tex;	   // Texture of a UFO
	ObstacleTex textureName = ObstacleTex::none;
	bool hidden = true;		   // Obstacle is below or above the game window
	bool turnIntoUFO = false;  // Change into a UFO needed
	bool stopped = false;	   // Obstacle's movement stopped
	Vector2 increaseSpeed = Vector2(false, false);  // Increase of speed in x or y axis needed
};

#endif // OBSTACLE_H