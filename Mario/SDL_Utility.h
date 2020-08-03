#ifndef _SDL_Utility_H
#define _SDL_Utility_H

#include <iostream>
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_image.h>


void drawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y);

SDL_Surface* loadBMP(std::string path);

SDL_Surface* loadPNG(std::string path, SDL_Surface* screen);

#endif //_SDL_Utility_H

