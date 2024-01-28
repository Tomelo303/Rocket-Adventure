#include "Obstacle.h"
#include "../Game/Game.h"


Obstacle::Obstacle(int y)
{
	// Set values regarding size and movement
	width = 66;
	height = 42;
	velocity.y = 1;
	speed.x = startSpeed.x = 1;
	speed.y = startSpeed.y = 5;

	// Load all textures
	plane_r_tex = Texture::createTexture("../Assets/plane_r.png");
	plane_l_tex = Texture::createTexture("../Assets/plane_l.png");
	ufo_tex = Texture::createTexture("../Assets/ufo.png");

	// Set values regarding position and texture
	position.y = y;
	sourceRect = { 0, 0, 650, 420 };
	destinationRect = { position.x, position.y, width, height };

	std::cout << "Obstacle initialized.\n";
}

Obstacle::~Obstacle()
{
	// Destroy saved textures
	SDL_DestroyTexture(plane_r_tex);
	SDL_DestroyTexture(plane_l_tex);
	SDL_DestroyTexture(ufo_tex);

	std::cout << "Obstacle destroyed. ";
}

void Obstacle::update(const unsigned int& frame)
{
	move();

	// Move the Obstacle back on top when it passes the bottom of the game window
	if (position.y > Game::height)
	{
		placeAboveWindow(Game::height / 4, 1.5 * Game::height);
		velocity.x = 0;  // Move straight down when above the game window
		hidden = true;
	}

	// Change the Obstacle's properties and behaviour
	if (position.y > -height && hidden && !stopped) // when at the top of the game window
	{
		// Change the Obstacle into a UFO
		if (turnIntoUFO)
		{
			applyTexture(ObstacleTex::UFO);
			turnIntoUFO = false;  // Turn this flag off so this part of the code never repeates
			
			velocity = 0;  // Stop the Obstacle's movement
			std::cout << "Obstacle's movement stopped\n";
			stopped = true;
		}

		generateSpawnProperties();	  // position.x, velocity.x and texture
		setPos(position.x, -height);  // Place the Obstacle on the new x position

		if (turnIntoUFO)
			hidden = true;  // Turn this flag on, because the Obstacle will not leave its current position for a while
		else
			hidden = false;
		
		//std::cout << "X = " << position.x << "\n";
	}
	if (textureName != ObstacleTex::UFO) // when it's a plane
	{
		// Set the speed to change next time the Obstacle will be outside the game window
		if (frame % 1000 == 0 && frame != 0)
			increaseSpeed.y = true;

		if (frame % 2000 == 0 && frame != 0)
			increaseSpeed.x = true;
	}
	else // when it's a UFO
	{
		// Set the speed to change next time the Obstacle will be outside the game window
		if (frame % 300 == 0)
			increaseSpeed.x = true;

		if (frame % 1500 == 0)
			increaseSpeed.y = true;

		bounceFromWalls();
	}

	// Set the turn into an UFO flag on when the game frame hits a desired value
	if (frame == 10000)
	{
		turnIntoUFO = true;
		increaseSpeed = false;  // Turn this flag off to make sure the Obstacle starts with default speed as a UFO
	}

	// Resume the Obstacle's movement when the game frame hits a desired value
	if (frame == 11000)
	{
		speed.x = 10;	  // Set a default in x axis speed for a UFO
		speed.y = 4;	  // Set a default in y axis speed for a UFO
		velocity.y = 1;	  // Resume the Obtacle's downwards movement
		stopped = false;  // Turn this flag off to let the Obstacle generate new starting position and move
		std::cout << "Obstacle's movement resumed\n";
	}

	//std::cout << "Obstacle is now on " << position << " coordinates\n";
	//std::cout << increaseSpeed << "\n";
}

void Obstacle::handleCollision()
{
	// Reset Obstacle's texture if it is a UFO
	if (textureName == ObstacleTex::UFO)
		textureName = ObstacleTex::none;
	generateSpawnProperties();  // position.x, velocity.x and texture

	placeAboveWindow(Game::height / 4, 1.5 * Game::height);
	speed = startSpeed;

	hidden = true;
	turnIntoUFO = false;
}

void Obstacle::bounceFromWalls()
{
	if (position.x < 0)
	{
		setPos(0, position.y);
		velocity.x *= -1;
	}
	if (position.x > Game::width - width)
	{
		setPos(Game::width - width, position.y);
		velocity.x *= -1;
	}
}

void Obstacle::generateSpawnProperties()
{
	if (textureName != ObstacleTex::UFO)
	{
		position.x = (std::rand() % ((Game::width - width + 100) + 100)) - 100;  // Get a random number from range [-100; Game::width - width + 100]

		if (position.x <= 100) // Move to the right
		{
			applyTexture(ObstacleTex::Plane_R);
			velocity.x = 1;
		}
		else if (position.x >= Game::width - 100) // Move to the left
		{
			applyTexture(ObstacleTex::Plane_L);
			velocity.x = -1;
		}
		else
		{
			int direction = std::rand() % 2;  // Get either 0 or 1

			if (direction) // Move to the right
			{
				applyTexture(ObstacleTex::Plane_R);
				velocity.x = 1;
			}
			else // Move to the left
			{
				applyTexture(ObstacleTex::Plane_L);
				velocity.x = -1;
			}
		}
	}
	else // Obstacle is an UFO
	{
		position.x = (std::rand() % (Game::width - width));  // Get a random number from range [0; Game::width - width]
		int direction = std::rand() % 2;  // Get either 0 or 1

		if (direction) // Move to the right
			velocity.x = 1;
		else // Move to the left
			velocity.x = -1;
	}

	// Increase the speed if needed
	if (increaseSpeed.x)
		speed.x += 1;
	if (increaseSpeed.y)
		speed.y += 1;

	increaseSpeed = false;
}

void Obstacle::applyTexture(ObstacleTex tex)
{
	if (textureName != tex)
	{
		// Apply proper texture and its corresponding name
		switch (tex)
		{
		case (ObstacleTex::Plane_R):
			texture = plane_r_tex;
			textureName = ObstacleTex::Plane_R;
			break;

		case (ObstacleTex::Plane_L):
			texture = plane_l_tex;
			textureName = ObstacleTex::Plane_L;
			break;

		case (ObstacleTex::UFO):
			texture = ufo_tex;
			textureName = ObstacleTex::UFO;
			break;

		case (ObstacleTex::none):
			texture = nullptr;
			textureName = ObstacleTex::none;
			break;

		default:
			break;
		}
	}
}
