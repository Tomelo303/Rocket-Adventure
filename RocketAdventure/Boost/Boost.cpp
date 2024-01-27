#include "Boost.h"
#include "../Game/Game.h"

Boost::Boost(int y)
{
	// Set values regarding size and movement
	width = 66;
	height = 66;
	velocity.y = 1;
	speed.y = 7;

	// Load all textures
	speed_boost_tex = TextureHandler::createTexture("../Assets/speed_boost.png");
	// !!! Need to widen the borders of this texture


	// Set values regarding position and texture
	position.y = y;
	sourceRect = { 0, 0, 660, 660 };
	destinationRect = { position.x, position.y, width, height };

	std::cout << "Boost initialized.\n";
}

Boost::~Boost()
{
	// Destroy saved textures
	SDL_DestroyTexture(speed_boost_tex);
	std::cout << "Boost destroyed. ";
}

void Boost::update(const int& frame)
{
	move();

	// Move the Boost back on top when it passes the bottom of the game window
	if (position.y > Game::height)
	{
		placeAboveWindow(3 * Game::height, 10 * Game::height);
		hidden = true;
	}

	// Change the Boost's properties and behaviour
	if (position.y > -height && hidden) // when at the top of the game window
	{
		generateSpawnProperties();	  // position.x, velocity.x and texture
		setPos(position.x, -height);  // Place the Boost on the new x position
		hidden = false;
		std::cout << "X = " << position.x << "\n";
	}
}

void Boost::handleCollision()
{
	placeAboveWindow(5 * Game::height, 10 * Game::height);
	std::cout << "Boost collided\n";
}

void Boost::generateSpawnProperties()
{
	position.x = (std::rand() % ((Game::width - 100 - width) - 100)) + 100;  // Get a random number from range [100; Game::width - width - 100]
	
	// Here will be another random number generator that will choose which boost to use
	// A proper texture will be used
	// Currently there's only one boost variant
	applyTexture(BoostTex::Speed);
}

void Boost::applyTexture(BoostTex tex)
{
	if (textureName != tex)
	{
		// Apply proper texture and its corresponding name
		switch (tex)
		{
		case (BoostTex::Speed):
			texture = speed_boost_tex;
			textureName = BoostTex::Speed;
			break;

		case (BoostTex::none):
			texture = nullptr;
			textureName = BoostTex::none;
			break;

		default:
			break;
		}
	}
}
