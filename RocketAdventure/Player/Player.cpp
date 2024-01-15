#include "Player.h"


Player::Player(int x, int y)
{
	// Set values regarding size, position and movement
	width = 66;
	height = 99;
	position.x = x - width / 2;
	position.y = y - height;
	speed = 5;
	
	// Load all textures
	rocket_tex = TextureHandler::createTexture("../Assets/rocket0.png");

	// Set values regarding texture
	applyTexture(PlayerTex::Rocket);
	sourceRect = { 0, 0, 650, 1000 };
	destinationRect = { position.x, position.y, width, height };

	std::cout << "Player initialized.\n";
}

Player::~Player()
{
	// Destroy saved textures
	SDL_DestroyTexture(rocket_tex);

	std::cout << "Player destroyed. ";
}

void Player::handleEvents()
{
	key = Game::event.key.keysym.sym;  // Get the keycode of the key that is being pressed

	if (key != 0 && (key == SDLK_w || key == SDLK_s || key == SDLK_a || key == SDLK_d))
	{
		// Prevent setting the previous key keycode to 0
		if (currKey != 0)
		{
			prevKey = currKey;
		}
		currKey = key;
	}

	// Register which keys are being pressed
	if (Game::event.type == SDL_KEYDOWN)
	{
		switch (currKey)
		{
		case SDLK_w:
			W = true;
			break;

		case SDLK_s:
			S = true;
			break;

		case SDLK_a:
			A = true;
			break;

		case SDLK_d:
			D = true;
			break;

		default:
			break;
		}
	}

	// Register which keys are being released
	if (Game::event.type == SDL_KEYUP)
	{
		switch (currKey)
		{
		case SDLK_w:
			W = false;
			break;

		case SDLK_s:
			S = false;
			break;

		case SDLK_a:
			A = false;
			break;

		case SDLK_d:
			D = false;
			break;

		default:
			break;
		}

		// Set the current key keycode to 0 only when every key is released
		// If next key was pressed before releasing the previous one, assign the value stored in prevKey variable
		if (!W && !S && !A && !D)
			currKey = 0;
		else
			currKey = prevKey;
	}
	//std::cout << "Previous key: " << prevKey << "  Current Key: " << currKey << "  Key: " << key << "\n";

	// Assign proper directions of movement based on keys that are being pressed
	if (W && S == false)
		velocity.y = -1;
	else if (S && W == false)
		velocity.y = 1;
	else
		velocity.y = 0;

	if (A && D == false)
		velocity.x = -1;
	else if (D && A == false)
		velocity.x = 1;
	else
		velocity.x = 0;
}

void Player::update(const int& frame)
{
	move();
	//std::cout << "Player is on " << position << " coordinates.\n";
	stayInsideWindow();
}

void Player::stayInsideWindow()
{
	if (position.y < 0)
		setPos(position.x, 0);

	if (position.y > Game::height - height)
		setPos(position.x, Game::height - height);

	if (position.x < 0)
		setPos(0, position.y);

	if (position.x > Game::width - width)
		setPos(Game::width - width, position.y);
}

void Player::applyTexture(PlayerTex tex)
{
	if (textureName != tex)
	{
		// Apply proper texture and its corresponding name
		switch (tex)
		{
		case (PlayerTex::Rocket):
			texture = rocket_tex;
			textureName = PlayerTex::Rocket;
			break;

		case (PlayerTex::none):
			texture = nullptr;
			textureName = PlayerTex::none;
			break;

		default:
			break;
		}
	}
}
