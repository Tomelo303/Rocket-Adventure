#include "Text.h"
#include "../Game/Game.h"

#include <iostream>


Text::Text(const std::string& fontPath, int fontSize)
{
	font = loadFont(fontPath, fontSize);
	std::cout << "Text initialized.\n";
}

Text::Text(const std::string& fontPath, int fontSize, SDL_Color fontColor)
{
	font = loadFont(fontPath, fontSize);
	this->fontColor = fontColor;
	std::cout << "Text initialized.\n";
}

Text::Text(const std::string& fontPath, int fontSize, FontColor fontColor)
{
	font = loadFont(fontPath, fontSize);
	setColor(fontColor);
	std::cout << "Text initialized.\n";
}

Text::~Text()
{
	SDL_DestroyTexture(texture);
	std::cout << "Text destroyed.\n";
}

void Text::setColor(FontColor fontColor)
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

void Text::setText(std::string& text)
{
	this->text = text;
}

void Text::setText(const char* text)
{
	std::string str = text;
	this->text = str;
}

void Text::setText(std::string& text, int number)
{
	this->text = concatenate(text, number);
}

void Text::setText(const char* text, int number)
{
	std::string str = text;
	this->text = concatenate(str, number);
}

void Text::setText(std::string& text1, int number, std::string& text2)
{
	this->text = concatenate(text1, number) += text2;
}

void Text::setText(const char* text1, int number, const char* text2)
{
	std::string str1 = text1;
	std::string str2 = text2;
	this->text = concatenate(str1, number) += str2;
}

void Text::display(int x, int y)
{
	display(x, y, text);
}

void Text::display(int x, int y, std::string& text)
{
	if (texture != nullptr)
		SDL_DestroyTexture(texture);

	this->text = text;
	texture = createTexture();  // Convert the text to texture
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

TTF_Font* Text::loadFont(const std::string& fontPath, int fontSize)
{
	TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
	if (font)
	{
		return font;
	}
	else
	{
		std::cout << "Problem loading font: " << SDL_GetError() << "\n";
		return nullptr;
	}
}

SDL_Texture* Text::createTexture()
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
