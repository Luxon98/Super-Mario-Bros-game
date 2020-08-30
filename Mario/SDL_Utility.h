#ifndef SDL_Utility_H
#define SDL_Utility_H

#include <SDL.h>
#include <SDL_main.h>
#include <SDL_image.h>
#include <string>


void drawSurface(SDL_Surface* display, SDL_Surface* sprite, int x, int y);

SDL_Surface* loadBMP(std::string path);

SDL_Surface* loadPNG(std::string path, SDL_Surface* display);

#endif //SDL_Utility_H

