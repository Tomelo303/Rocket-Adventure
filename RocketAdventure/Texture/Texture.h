#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL_image.h"


class Texture
{
  public:
	Texture() {};
	~Texture() {};

	static SDL_Texture* createTexture(const char* texturePath);
};

#endif // TEXTURE_H