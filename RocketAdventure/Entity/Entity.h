#ifndef ENTITY_H
#define ENTITY_H

#include "../Vector2/Vector2.h"
#include "../Texture/Texture.h"


class Entity
{
  public:
	Entity();
	~Entity();

	virtual void update(const unsigned int& frame);  // How the Entity should update with every game frame
	virtual void handleCollision();      // How the Entity should update after it collided with other objects
	
	virtual void applySpaceTexture();    // Apply textures used in space
	virtual void disableSpaceTexture();  // Disable textures used in space
	
	virtual void addSpeed(int increment) { speed += increment; }
	virtual void setSpeed(int speed) { this->speed = speed; }
	virtual void setSpeed(Vector2 speed) { this->speed = speed; }
	virtual Vector2 getSpeed() const { return speed; }
	const SDL_Rect& getRect() const { return destinationRect; }
	
	void render();  // Display the changes after an update

  protected:
	void move();  // Move Entity based on the values in velocity vector and speed variable
	void setPos(int x, int y);	  // Place the Entity in x, y coordinates
	void setPos(Vector2 newPos);  // Place the Entity in x, y coordinates specified by the newPos vector
	void placeAboveWindow(int a, int b);  // Place the Entity in the random distance from the top of the game window in range [a, b]

	Vector2 position = Vector2(0, 0);    // Position relative to the top left corner of the game window
	Vector2 velocity = Vector2(0, 0);    // Direction of movement (e.g.: x = -1 is left, x = 1 is right, x = 0 means no movement in x axis)
	Vector2 speed = Vector2(0, 0);	     // How many pixels Entity travels in one game frame in x and y direction
	Vector2 startPos = Vector2(0, 0);    // Position at which the Entity was placed at the beginning of the game
	Vector2 startSpeed = Vector2(0, 0);  // Speed at which the Entity moves at the beginning
	int width = 0;
	int height = 0;
	SDL_Texture* texture = nullptr;
	SDL_Rect sourceRect = { 0, 0, 0, 0 };  // Sets which part of the texture to load
	SDL_Rect destinationRect = { 0, 0, 0, 0 };  // Sets where and in what scale the loaded texture will be
};

#endif // ENTITY_H