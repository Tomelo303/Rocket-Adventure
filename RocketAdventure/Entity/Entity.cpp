#include "Entity.h"


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
	position = newPos;
	destinationRect.x = position.x;
	destinationRect.y = position.y;
}

