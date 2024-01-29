#include "Background.h"
#include "../Game/Game.h"


Background::Background()
{
	// Set values regarding size and movement
	width = 700;
	height = 2000;
	velocity.y = 1;
	speed.y = 5;

	// Load all textures
	clouds_tex = Texture::createTexture("../Assets/clouds.png");
	stars_tex = Texture::createTexture("../Assets/stars.png");

	// Set values regarding position and texture
	texture = clouds_tex;
	position.x = startPos.x = 0;
	position.y = startPos.y = -height / 2;
	sourceRect = { 0, 0, 700, 2000 };
	destinationRect = { position.x, position.y, width, height };

	std::cout << "Background initialized.\n";
}

Background::~Background()
{
	SDL_DestroyTexture(clouds_tex);
	SDL_DestroyTexture(stars_tex);
	std::cout << "Background destroyed. ";
}

void Background::update(const unsigned int& frame)
{
	move();

	if (!transition)
	{
		if (position.y > 0)
			setPos(startPos.x, startPos.y + position.y);  // Placing the Background at the starts position minding the possible offset in y axis
	}

	if (position.y > Game::height)
		velocity.y = 0;

	if (frame == Game::spaceStart)
		transition = true;

	if (frame == Game::spaceStart + Game::transitionDuration)
	{
		setPos(position.x, -height);
		applyTexture(BackgroundTex::Stars);
		velocity.y = 1;
		transition = false;
	}
}

void Background::handleCollision()
{
	if (textureName == BackgroundTex::Stars)
		applyTexture(BackgroundTex::Clouds);
	setPos(startPos);
	transition = false;
}

void Background::applyTexture(BackgroundTex tex)
{
	if (textureName != tex)
	{
		switch (tex)
		{
		case (BackgroundTex::Clouds):
			texture = clouds_tex;
			textureName = BackgroundTex::Clouds;
			break;

		case (BackgroundTex::Stars):
			texture = stars_tex;
			textureName = BackgroundTex::Stars;
			break;

		case (BackgroundTex::none):
			texture = nullptr;
			textureName = BackgroundTex::none;
			break;

		default:
			break;
		}
	}
}
