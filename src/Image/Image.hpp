#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../Window/Window.hpp"

class Image
{
public:
	// Constructors
	Image(); // Create a image with their default values
	Image(std::string path); // Create a image with their default values and set path as your default path

	// Destructor
	~Image();
	
	// Setters
	void setLogs(bool showLogs); // Suppress or Permit logs on runtime


	// Loaders
	bool load(std::string path, Window* window); //Load a image from path and create texture for it, getting the window render
	bool load(Window* window); // Load a image on (before defined) path, and create a texture for it, getting the window render

	// Commands
	void print(Window* window);

private:

	// Variables
	SDL_Texture* texture;

	SDL_Rect position;
	SDL_Rect cut;

	std::string path;

	bool showLogs;
	bool haveTransparency;

	// Setters
	void setDefaultValues(); // Used by constructors and another functions, don't edit it!

	// Defines
	bool definePNGSupport(); // Start PNG image format support

};