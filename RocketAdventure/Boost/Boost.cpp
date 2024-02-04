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
	speed_boost_tex = Texture::createTexture("../Assets/speed_boost.png");
	speed_boost_white_tex = Texture::createTexture("../Assets/speed_boost_white.png");
	force_field_boost_tex = Texture::createTexture("../Assets/force_field_boost.png");
	force_field_boost_white_tex = Texture::createTexture("../Assets/force_field_boost_white.png");

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
	SDL_DestroyTexture(speed_boost_white_tex);
	SDL_DestroyTexture(force_field_boost_tex);
	SDL_DestroyTexture(force_field_boost_white_tex);
	std::cout << "Boost destroyed. ";
}

void Boost::update(const unsigned int& frame)
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
		//std::cout << "X = " << position.x << "\n";
	}
}

void Boost::handleCollision()
{
	generateSpawnProperties();
	placeAboveWindow(5 * Game::height, 10 * Game::height);
	hidden = true;
}

void Boost::applySpaceTexture()
{
	spaceTexture = true;
	applyTexture(textureName);
}

void Boost::disableSpaceTexture()
{
	spaceTexture = false;
	applyTexture(textureName);
}

void Boost::generateSpawnProperties()
{
	position.x = (std::rand() % ((Game::width - width - 100) - 100)) + 100;  // Get a random number from range [100; Game::width - width - 100]
	
	// Get a random variant
	int variant = (rand() % 100) + 1;  // Get a random number from range [1; 100]

	if (variant <= 60)
		applyTexture(BoostTex::SpeedBoost);
	else
		applyTexture(BoostTex::ForceFieldBoost);
}

void Boost::applyTexture(BoostTex tex)
{
	// Apply proper texture and its corresponding name
	switch (tex)
	{
	case (BoostTex::SpeedBoost):
		if (!spaceTexture)
			texture = speed_boost_tex;
		else
			texture = speed_boost_white_tex;
		textureName = BoostTex::SpeedBoost;
		break;

	case (BoostTex::ForceFieldBoost):
		if (!spaceTexture)
			texture = force_field_boost_tex;
		else
			texture = force_field_boost_white_tex;
		textureName = BoostTex::ForceFieldBoost;
		break;

	case (BoostTex::none):
		texture = nullptr;
		textureName = BoostTex::none;
		break;

	default:
		break;
	}
}
