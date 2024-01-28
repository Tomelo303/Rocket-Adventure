#ifndef COLLISION_H
#define COLLISION_H

#include "SDL.h"

class Collision
{
  public:
	Collision();
	~Collision();

	static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);  // Axis-Aligned Bounding Box collision detection method
};

#endif // COLLISION_H