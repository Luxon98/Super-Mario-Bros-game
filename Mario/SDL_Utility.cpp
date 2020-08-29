#include "SDL_Utility.h"

#include <iostream>


void drawSurface(SDL_Surface* display, SDL_Surface* sprite, int x, int y)
{
	SDL_Rect destination;
	destination.x = x - sprite->w / 2;
	destination.y = y - sprite->h / 2;
	destination.w = sprite->w;
	destination.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, display, &destination);
}

SDL_Surface* loadBMP(std::string path)
{
	const char* converted_path = path.c_str();
	SDL_Surface* bitmap = SDL_LoadBMP(converted_path);

	return bitmap != nullptr ? bitmap : nullptr;
}

SDL_Surface* loadPNG(std::string path, SDL_Surface* display)
{
	SDL_Surface* optimizedSurface = nullptr;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface != nullptr) {
		optimizedSurface = SDL_ConvertSurface(loadedSurface, display->format, 0);
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}


