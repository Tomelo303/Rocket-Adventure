#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "SDL.h"

class CollisionHandler
{
  public:
	CollisionHandler();
	~CollisionHandler();

	static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);  // Axis-Aligned Bounding Box collision detection method
};

#endif // COLLISIONHANDLER_H