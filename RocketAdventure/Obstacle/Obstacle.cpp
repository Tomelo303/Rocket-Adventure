#include "Obstacle.h"


Obstacle::Obstacle(int y)
{
	width = 66;
	height = 42;
	velocity.y = 1;
	speed.x = 1;
	speed.y = 5;

	plane_r_tex = TextureHandler::createTexture("../Assets/plane_r.png");
	plane_l_tex = TextureHandler::createTexture("../Assets/plane_l.png");

	generateSpawnProperties();  // position.x and texture
	position.y = y - height;
	sourceRect = { 0, 0, 650, 420 };
	destinationRect = { position.x, position.y, width, height };

	std::cout << "Obstacle initialized.\n";
}

Obstacle::~Obstacle()
{
	// Destroy saved textures
	SDL_DestroyTexture(plane_r_tex);
	SDL_DestroyTexture(plane_l_tex);

	std::cout << "Obstacle destroyed. ";
}

void Obstacle::update(const int& frame)
{
	move();

	// Move the Obstacle back on top when it passes the bottom of the game window
	if (position.y > Game::height)
	{
		hidden = true;
		setPos(position.x, -(Game::height / 2));
		velocity.x = 0;  // Start moving straight down when above the game window
	}

	// Set a random x coordinate and start moving diagonally when at the top of the game window
	if (position.y > -height && hidden)
	{
		generateSpawnProperties();
		setPos(position.x, -height);
		//std::cout << "X = " << position.x << "\n";
		hidden = false;
	}

	// Increase the speed of the Obstacle in y axis every 1000 game frames
	if (frame % 1000 == 0 && frame != 0)
		increaseSpeed.y = true;

	// Increase the speed of the Obstacle in x axis every 2000 game frames
	if (frame % 2000 == 0 && frame != 0)
		increaseSpeed.x = true;

	//bounceFromWalls();

	//std::cout << "Obstacle is now on " << position << " coordinates\n";
	//std::cout << increaseSpeed << "\n";
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
	position.x = (std::rand() % ( (Game::width + 100 - width) + 100 )) - 100;  // Get a random number from range [-100; Game::width - width + 100]

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
		int random = std::rand() % 2;  // Get either 0 or 1

		if (random) // Move to the right
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

		case (ObstacleTex::none):
			texture = nullptr;
			textureName = ObstacleTex::none;
			break;

		default:
			break;
		}
	}
}
