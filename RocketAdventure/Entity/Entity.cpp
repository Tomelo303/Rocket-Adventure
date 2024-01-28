#include "Entity.h"
#include "../Game/Game.h"


Entity::Entity()
{}

Entity::~Entity()
{
	// Destroy Entity's current texture
	SDL_DestroyTexture(texture);

	std::cout << "Last position: " << position << "\n";
}

void Entity::render()
{
	SDL_RenderCopy(Game::renderer, texture, &sourceRect, &destinationRect);
}

void Entity::update(const unsigned int& frame)
{} // Method ment to be overridden

void Entity::handleCollision()
{} // Method ment to be overridden

void Entity::move()
{
	position.x += velocity.x * speed.x;
	position.y += velocity.y * speed.y;
	destinationRect.x = position.x;
	destinationRect.y = position.y;
}

void Entity::setPos(int x, int y)
{
	destinationRect.x = position.x = x;
	destinationRect.y = position.y = y;
}

void Entity::setPos(Vector2 newPos)
{
	destinationRect.x = position.x = newPos.x;
	destinationRect.y = position.y = newPos.y;
}

void Entity::placeAboveWindow(int a, int b)
{
	int distance = (std::rand() & (b - a)) + a;  // Get a random number from range [a, b]
	setPos(position.x, -distance);
}

