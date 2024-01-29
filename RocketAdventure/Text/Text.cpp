#include "Text.h"
#include "../Game/Game.h"

#include <iostream>


Text::Text(const std::string& fontPath)
{
	this->fontPath = fontPath;
	std::cout << "Text initialized.\n";
}

Text::~Text()
{
	std::cout << "Text destroyed.\n";
}

void Text::setFontColor(FontColor fontColor)
{
	switch (fontColor)
	{
	case (FontColor::White):
		this->fontColor = { 255, 255, 255, 255 };
		break;

	case (FontColor::Black):
		this->fontColor = { 0, 0, 0, 255 };
		break;

	case (FontColor::Red):
		this->fontColor = { 255, 0, 0, 255 };
		break;

	case (FontColor::Green):
		this->fontColor = { 0, 255, 0, 255 };
		break;

	case (FontColor::Blue):
		this->fontColor = { 0, 0, 255, 255 };
		break;

	default:
		break;
	}
}

void Text::display(int x, int y, std::string& text)
{
	texture = loadFont(text);  // Convert the text to texture
	SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);  // Get width and height of the texture

	// Place the text in the right coordinates
	rect.x = x;
	rect.y = y;

	SDL_RenderCopy(Game::renderer, texture, nullptr, &rect);  // Render the text
}

void Text::display(int x, int y, const char* text)
{
	std::string str = text;  // Convert const char* to std::string
	display(x, y, str);
}

void Text::display(int x, int y, std::string& text, int number)
{
	display(x, y, concatenate(text, number));
}

void Text::display(int x, int y, const char* text, int number)
{
	std::string str = text;  // Convert const char* to std::string
	display(x, y, concatenate(str, number));
}

void Text::display(int x, int y, std::string& text1, int number, std::string& text2)
{
	display(x, y, concatenate(text1, number) += text2);
}

void Text::display(int x, int y, const char* text1, int number, const char* text2)
{
	// Convert const char* to std::string
	std::string str1 = text1;
	std::string str2 = text2;

	display(x, y, concatenate(str1, number) += str2);
}

std::string& Text::concatenate(std::string& text, int number)
{
	return text += std::to_string(number);
}

SDL_Texture* Text::loadFont(std::string& text)
{
	TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
	if (font)
	{
		SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), fontColor);
		if (surface)
		{
			SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
			if (texture)
			{
				SDL_FreeSurface(surface);
				return texture;
			}
			else
			{
				SDL_FreeSurface(surface);
				std::cout << "Problem loading text texture: " << SDL_GetError() << "\n";
				return nullptr;
			}
		}
		else
		{
			std::cout << "Problem loading text surface: " << SDL_GetError() << "\n";
			return nullptr;
		}
	}
	else
	{
		std::cout << "Problem loading font: " << SDL_GetError() << "\n";
		return nullptr;
	}
}
