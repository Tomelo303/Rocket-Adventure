#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "../Entity/Entity.h"


enum class ObstacleTex
{
	none,
	Plane_R,
	Plane_L
	///UFO
};

class Obstacle : public Entity
{
  public:
	Obstacle(int y);
	~Obstacle();

	void update(const int& frame);  // How the Obstacle should update with every game frame
	void handleCollision();  // How the Obstacle should update after it collided with other objects

  private:
	void bounceFromWalls();  // Change the direction in x axis if Obstacle hits the vertical wall of the game window
	void generateSpawnProperties();  // Assign a random x coordinate and appropriate texture and direction of movement
	void applyTexture(ObstacleTex tex);

	SDL_Texture* plane_r_tex;  // Texture of a plane facing the right side
	SDL_Texture* plane_l_tex;  // Texture of a plane facing the left side
	ObstacleTex textureName = ObstacleTex::none;
	bool hidden = false;  // Is the Obstacle below or above the game window
	Vector2 increaseSpeed = Vector2(false, false);  // Is the increase of speed in x or y axis needed
};

#endif // OBSTACLE_H