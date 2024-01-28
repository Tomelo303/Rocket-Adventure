#ifndef TEXT_H
#define TEXT_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>


enum class FontColor
{
	White,
	Black,
	Red,
	Green,
	Blue
};

class Text
{
  public:
	Text(const std::string& fontPath);
	~Text();
	
	void setFontSize(int fontSize) { this->fontSize = fontSize; }
	void setFontColor(SDL_Color fontColor) { this->fontColor = fontColor; }  // Set the font color by passing RGB values, e.g. { 255, 0, 0, 255 } (red color)
	void setFontColor(FontColor fontColor);	 // Set the font color by choosing from available colors in FontColor enum class
	void display(int x, int y, std::string& text);  // Display the text on the window in (x, y) position
	void display(int x, int y, const char* text);   // Display the text on the window in (x, y) position
	void display(int x, int y, std::string& text, int number);  // Display the text concatenated with a number on the window in (x, y) position
	void display(int x, int y, const char* text, int number);	// Display the text concatenated with a number on the window in (x, y) position
	int width() const { return rect.w; }
	int height() const { return rect.h; }

  private:
	SDL_Texture* loadFont(std::string& text);  // Convert the text to texture
	std::string& concatenate(std::string& text, int number);  // Convert int to std::string and concatenate strings
	
	SDL_Color fontColor = { 0, 0, 0, 255 };  // Color of the font in RGB values
	int fontSize = 0;				 // Size of the text on the screen
	std::string fontPath = "";		 // Relative path leading to the ttf file
	SDL_Texture* texture = nullptr;  // Text is being rendered onto the screen through this variable
	SDL_Rect rect = { 0, 0, 0, 0 };  // The area the text occupies
};

#endif // TEXT_H
