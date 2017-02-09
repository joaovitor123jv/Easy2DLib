#pragma once
#include <SDL2/SDL.h>
#include "../Window/Window.hpp"
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
using namespace std;

class Text
{
private:
	string text;
	string path;
//	int maxSize;
	int fontSize;
	bool showLogs;
	SDL_Color color;
	SDL_Rect position;
	SDL_Texture* texture;
	TTF_Font* font;
	Window* window;


	void setDefaultValues();
	void getValuesFromSurface(SDL_Surface* surface);

public:
	//Constructors
	Text();
	Text(string path);
	//Destructors
	~Text();
	//Getters
//	int getMaxSize();
	string getText();
	int getX();
	int getY();
	int getWidth();
	int getHeight();

	//Setters
	void setWindow(Window *window);
//	void setMaxSize(int maxSize);
	void setPosition(int x, int y);
	void setX(int x);
	void setY(int y);
	void setText(string text);
	void setLogs(bool showLogs);
	void setFont(string path, int fontSize);
	void setFont(string path);
	void setFontSize(int fontSize);
	void setColor(SDL_Color color);

	//Commands
	void update();
	void print();
};