#include "Window.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
using namespace std;

//Constructors
Window::Window(void)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		cout<<"On: Screen constructor"<<endl;
		cout<<"\tERROR: Failed to init video"<<endl;
		return;
	}
	//Set texture filtering to linear
	if(!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		cout<<"Warning: Linear texture filtering not enabled!"<<endl;
	}
	this->setDefaultValues();
	if(this->upgrade())
	{
		cout<<"Window created with success"<<endl;
	}
	else
	{
		cout<<"On: Screen constructor"<<endl;
		cout<<"\tERROR: Failed to initialize window"<<endl;
		return;
	}
	this->update();
}

Window::Window(int width, int height)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		cout<<"On: Screen constructor"<<endl;
		cout<<"\tERROR: Failed to init video"<<endl;
		return;
	}
	//Set texture filtering to linear
	if(!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY , "1"))
	{
		cout<<"Warning: Linear texture filtering not enabled!"<<endl;
	}
	this->setDefaultValues();
	this->width = width;
	this->height = height;
	this->showWindow = true;
	if(this->upgrade())
	{
		cout<<"Window created with success"<<endl;
	}
	else
	{
		cout<<"On: Screen constructor"<<endl;
		cout<<"\tERROR: Failed to initialize window"<<endl;
		return;
	}
	this->update();
}

Window::Window(std::string title, int width, int height)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		cout<<"On: Screen constructor"<<endl;
		cout<<"\tERROR: Failed to init video"<<endl;
		return;
	}
	//Set texture filtering to linear
	if(!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY , "1"))
	{
		cout<<"Warning: Linear texture filtering not enabled!"<<endl;
	}
	this->setDefaultValues();
	this->width = width;
	this->height = height;
	this->title = title;
	this->showWindow = true;
	if(!this->upgrade())
	{
		cout<<"On: Screen constructor"<<endl;
		cout<<"\tERROR: Failed to initialize window"<<endl;
		return;
	}
	this->update();
}

//Destructor
Window::~Window(void)
{
	if(this->renderer != NULL)
	{
		SDL_DestroyRenderer(this->renderer);
		this->renderer = NULL;
	}
	if(this->window != NULL)
	{
		SDL_DestroyWindow(this->window);
		this->window= NULL;
	}
	SDL_Quit();
}

//Commands

bool Window::upgrade()
{
	if(this->window != NULL)
	{
		SDL_DestroyWindow(this->window);
		this->window=NULL;
	}


	if(this->showWindow)
	{
		if(this->showDecoration)
		{
			this->window = SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height, SDL_WINDOW_SHOWN);
		}
		else
		{
			this->window = SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height, SDL_WINDOW_BORDERLESS);
		}
	}
	else
	{
		this->window = SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height, SDL_WINDOW_HIDDEN);
	}

	if(this->window == NULL)
	{
		if(this->showLogs)
		{
			cout<<"On: Window upgrade"<<endl;
			cout<<"\tFailed to init Window"<<endl;
		}
		return false;
	}
	if(this->renderer != NULL)
	{
		SDL_DestroyRenderer(this->renderer);
	}
	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
	if(this->renderer == NULL)
	{
		if(this->showLogs)
		{
			cout<<"On: Screen upgrade"<<endl;
			cout<<"\tFailed to create renderer"<<endl;
		}
		SDL_DestroyWindow(this->window);
		return false;
	}
	SDL_SetRenderDrawColor(this->renderer, this->color.r, this->color.g, this->color.b, this->color.a);
	return true;
}

bool Window::update()
{
	if(this->window == NULL)
	{
		if(this->showLogs)
		{
			cout<<"On: Screen update"<<endl;
			cout<<"\tERROR: Window doesn't exists"<<endl;
		}
		return false;
	}
	SDL_RenderPresent(this->renderer);
	SDL_RenderClear(this->renderer);
	return true;
}

//Setters
void Window::setDefaultValues()
{
	this->title="Screen";
	this->color.r= 0xFF;
	this->color.g= 0xFF;
	this->color.b= 0xFF;
	this->color.a= 0xFF;
	this->window= NULL;
	this->renderer=NULL;
	this->cursor.x=0;
	this->cursor.y=0;
	this->showDecoration = true;
	this->showWindow = false;
	this->setLogs(false);
}

void Window::setDefaultRenderColor()
{
	this->setDrawColor(this->color);
}

bool Window::setSize(unsigned int width, unsigned int height)
{
	if(this->window == NULL)
	{
		if(this->showLogs)
		{
			cout<<"At: Screen->setSize(unsigned int,unsigned int)"<<endl;
			cout<<"\tERROR: Window now initialized yet, aborting"<<endl;
		}
		return false;
	}
	if(width <0 || height <0 )
	{
		if(this->showLogs)
		{
			cout<<"At: Screen->setSize(unsigned int, unsigned int)"<<endl;
			cout<<"\tERROR: The values must be greater than zero, aborting"<<endl;
		}
		return false;
	}
	this->width = width;
	this->height = height;
	SDL_SetWindowSize(this->window, this->width, this->height);
	if(this->renderer != NULL)
	{
		SDL_DestroyRenderer(this->renderer);
	}
	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
	if(this->autoUpdate)
	{
		this->update();
	}
	return true;
}

bool Window::setVisible(bool showWindow) { this->showWindow = showWindow; }

bool Window::setDecoration(bool showDecoration) 
{
	this->showDecoration = showDecoration; 
	if(this->autoUpdate)
	{
		if(this->showDecoration)
		{
			SDL_SetWindowBordered(this->window, SDL_TRUE);
		}
		else
		{
			SDL_SetWindowBordered(this->window, SDL_FALSE);
		}
	}
}

bool Window::setTitle(std::string title) 
{
	this->title = title; 
	if(this->window != NULL)
	{
		SDL_SetWindowTitle(this->window, title.c_str());
		return true;
	}
	return true;
}

bool Window::setDrawColor(SDL_Color color)
{
	this->color = color;
	if(this->window != NULL)
	{
		SDL_SetRenderDrawColor(this->renderer, this->color.r, this->color.g, this->color.b, this->color.a);
	}
	return true;
}

bool Window::setAutoUpdate(bool autoUpdate) { this->autoUpdate = autoUpdate; }

bool Window::setFullScreen(bool fullScreen)
{
	this->fullScreen = fullScreen;
	if(this->window == NULL)
	{
		if(this->showLogs)
		{
			cout<<"On: Screen setFullScreen(bool)"<<endl;
			cout<<"\t ERROR: Window not initialized, aborting"<<endl;
		}
		return false;
	}
	if(fullScreen)
	{
		SDL_SetWindowFullscreen(this->window, SDL_WINDOW_FULLSCREEN);
		return true;
	}
	else
	{
		this->setSize(this->width, this->height);
		return true;
	}
}

bool Window::setLogs(bool showLogs) { this->showLogs = showLogs; }

//Getters
unsigned int Window::getWidth() { return this->width; }
unsigned int Window::getHeight() { return this->height; }

int Window::getCursorXPosition() { return this->cursor.x; }
int Window::getCursorYPosition() { return this->cursor.y; }

SDL_Renderer* Window::getRenderer() { return this->renderer; }

bool Window::getEvent()
{
	if(this->window == NULL) return false;
	if(!SDL_PollEvent(&this->event))
	{
		return false;
	}
	if(this->event.type == SDL_MOUSEMOTION)
	{
		if(this->showLogs)
		{
			cout<<"Event: Mouse Motion"<<endl;
		}
		SDL_GetMouseState(&this->cursor.x, &this->cursor.y);//This way, improve many buttons on screen
	}
	else if(this->event.type == SDL_MOUSEBUTTONDOWN)
	{
		if(this->showLogs)
		{
			cout<<"Event: Mouse Button Down"<<endl;
		}
		this->mouseButtonDown = true;
	}
	else if(this->event.type == SDL_MOUSEBUTTONUP)
	{
		if(this->showLogs)
		{
			cout<<"Event: Mouse Button Up"<<endl;
		}
		this->mouseButtonDown = false;
	}
	return true;
}

bool Window::getCursorPosition(int *x, int *y)
{
	if(this->window == NULL) return false;
	*x = this->cursor.x;
	*y = this->cursor.y;
}


bool Window::getMouseButtonDown()
{
	return this->mouseButtonDown;
}

bool Window::getMouseButtonUp()
{
	return !this->mouseButtonDown;
}

bool Window::getMouseClick()
{
	return this->mouseButtonDown;
}

bool Window::getMouseRelease()
{
	return !this->mouseButtonDown;
}

bool Window::getKeyDown()
{
	if(this->event.type == SDL_KEYDOWN) return true;
	return false;
}

bool Window::getKeyUp()
{
	if(this->event.type == SDL_KEYUP) return true;
	return false;
}

SDL_Keycode Window::getKey() { return this->event.key.keysym.sym; }

bool Window::getExit(){ if(this->event.type == SDL_QUIT){ return true;} return false; }
bool Window::getClose() { return this->getExit(); }

SDL_Window* Window::getWindow()
{
	return this->window;
}