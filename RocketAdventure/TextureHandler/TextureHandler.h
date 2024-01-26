#ifndef TEXTUREHANDLER_H
#define TEXTUREHANDLER_H

#include "SDL_image.h"


class TextureHandler
{
  public:
	TextureHandler() {};
	~TextureHandler() {};

	static SDL_Texture* createTexture(const char* texturePath);
};

#endif // TEXTUREHANDLER_H