#ifndef SDL_Utility_H
#define SDL_Utility_H

#include <SDL.h>
#include <SDL_main.h>
#include <SDL_image.h>
#include <string>


void drawSurface(SDL_Surface* display, SDL_Surface* sprite, int x, int y);

void showFileErrorWindow(std::string errorText);

void showScreenErrorWindow();

void showSoundErrorWindow();

SDL_Surface* loadBMP(std::string filename);

SDL_Surface* loadPNG(std::string filename, SDL_Surface* display);

#endif //SDL_Utility_H