#include <iostream>
#include <string>
#include "Image.hpp"

using namespace std;

// Constructors
Image::Image()
{
	cout<<"No parameters passed, setting Default Variables"<<endl;
	this->definePNGSupport();
	this->setDefaultValues();
}

Image::Image(string path)
{
	definePNGSupport();
	setDefaultValues();
	this->path = path;
}


// Destructors
Image::~Image()
{
	if(this->texture != NULL)
	{
		SDL_DestroyTexture(this->texture);
		this->texture = NULL;
	}
	IMG_Quit();
}



// Setters

void Image::setDefaultValues()
{
	this->path = "img/logo.png";
	this->texture = NULL;
	this->showLogs = false;

	this->position.x = 0;
	this->position.y = 0;
	this->position.w = 0;
	this->position.h = 0;

	this->cut.x = 0;
	this->cut.y = 0;
	this->cut.w = 0;
	this->cut.h = 0;

	this->haveTransparency = true;
}

void Image::setLogs(bool showLogs)
{
	this->showLogs = showLogs;
}



// Loaders

bool Image::load(string path, Window* window)
{
	if (this->texture != NULL)
	{
		if(this->showLogs)
		{
			cout<<"On: Image -> load"<<endl;
			cout<<"\tWarning: Image already loaded"<<endl;
		}
		SDL_DestroyTexture(this->texture);
		this->texture = NULL;
	}
	this->path = path;
	SDL_Surface* surface = IMG_Load( path.c_str() );
	if(surface == NULL)
	{
		if(this->showLogs)
		{
			cout<<"At: Image -> load(string path, Window* window)"<<endl;
			cout<<"\tERROR: Failed to load Image"<<endl;
			cout<<"\tIMG Error: "<<IMG_GetError()<<endl;
			cout<<"Aborting!"<<endl;
		}
		return false;
	}


	if(this->haveTransparency)
	{
		SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
	}


	this->texture = SDL_CreateTextureFromSurface(window->getRenderer(), surface);
	if(this->texture == NULL)
	{
		if(this->showLogs)
		{
			cout<<"At: Image -> load(string path, Window* window)"<<endl;
			cout<<"\tERROR: Failed to create texture from loaded Image"<<endl;
			cout<<"\tAborting"<<endl;
		}
		SDL_FreeSurface(surface);
		surface = NULL;
		return false;
	}
	SDL_FreeSurface(surface);
	surface = NULL;

	this->cut = this->position;

	return true;
}

bool Image::load(Window* window)
{
	return load(this->path, window);
}



// Defines
bool Image::definePNGSupport()
{
	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init( imgFlags) & imgFlags))
	{
		cout<<"ERROR: SDL support for PNG not initialized"<<endl;
		return false;
	}
	else return true;
}

//Commands

void Image::print(Window* window)
{
	SDL_RenderCopy(window->getRenderer(), this->texture, NULL, NULL);
}