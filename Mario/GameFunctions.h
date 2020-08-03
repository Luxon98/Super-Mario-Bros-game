#ifndef _GameFunctions_H
#define _GameFunctions_H

#include <chrono>
#include "World.h"
#include "SDL_Utility.h"
#include "Player.h"
#include "Level.h"
#include "Screen.h"
#include "KeyboardController.h"
#include "SoundController.h"


bool isDifferenceInInterval(int difference, int begin, int shift, int repetitions);

void loadBonusObjectsImages(SDL_Surface* screen);

void loadInanimateObjectImages(SDL_Surface* screen);

void loadLivingObjectImages(SDL_Surface* screen);

void loadTemporaryObjectImages(SDL_Surface* screen);

void loadBlockImages(SDL_Surface* screen);

void loadImages(SDL_Surface* screen);

void runGame();

#endif //_GameFunctions_H

