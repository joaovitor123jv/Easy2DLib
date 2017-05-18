#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <iostream>

class Window
{
	SDL_Window* window;
	std::string title;
	SDL_Event event;
	SDL_Point cursor;
	SDL_Renderer* renderer;
	unsigned int width;
	unsigned int height;
	bool showDecoration;
	bool showWindow;
	bool showLogs;
	bool autoUpdate;
	bool fullScreen;
	bool click;
	SDL_Color color;


	bool mouseButtonDown;

	//Methods
	void setDefaultValues();

public:
	//Constructors
	Window();
	Window(int width, int height);
	Window(std::string title, int width, int height);

	//Destructors
	~Window();

	//Setters
	bool setSize(unsigned int width, unsigned int height);//working
	bool setVisible(bool showWindow);//working
	bool setDecoration(bool showDecoration);//working
	bool setBorderLess(bool showDecoration);//working
	bool setTitle(std::string title);//working
	bool setDrawColor(SDL_Color color);//working
	bool setAutoUpdate(bool autoUpdate);//working
	bool setLogs(bool showLogs);//working
	bool setFullScreen(bool fullScreen);
	void setDefaultRenderColor();//working
	void setResizable(bool resizable);//If true, the window will be resizable

	//Getters
	unsigned int getWidth();//working
	unsigned int getHeight();//working
	
	int getCursorXPosition();//working
	int getCursorYPosition();//working

	bool getEvent();//working
	bool getCursorPosition(int *x, int *y);//working
	bool getMouseButtonDown();//working
	bool getMouseButtonUp();//working//working
	bool getMouseClick();//working//working
	bool getMouseRelease();//working
	bool getKeyDown();//working
	bool getKeyUp();//working
	bool getExit();//working
	bool getClose();//working

	SDL_Keycode getKey();//working
	SDL_Renderer* getRenderer();//working
	SDL_Window* getWindow();//working
	SDL_Event getRawEvent();//working

	//Commands
	bool upgrade();//Reset Window, destroy the old, create a new window, renderer and other things
	bool update();//Clear screen and render present things
	bool render();//Render the present screen, but not clear it before

	//Control General Use Variables
	// bool textInputEnabled; (USELESS BY NOW)
};
