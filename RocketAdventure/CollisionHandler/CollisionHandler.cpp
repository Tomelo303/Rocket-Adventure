#include "CollisionHandler.h"

CollisionHandler::CollisionHandler()
{}

CollisionHandler::~CollisionHandler()
{}

bool CollisionHandler::AABB(const SDL_Rect& rectA, const SDL_Rect& rectB)
{
	// Check if the rectangles intersect with each other
	if (rectA.x + rectA.w >= rectB.x &&
		rectB.x + rectB.w >= rectA.x &&
		rectA.y + rectA.h >= rectB.y &&
		rectB.y + rectB.h >= rectA.y)
		return true;
	else
		return false;
}
