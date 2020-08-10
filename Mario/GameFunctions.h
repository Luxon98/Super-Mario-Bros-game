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

void loadBonusObjectsImages(SDL_Surface* display);

void loadInanimateObjectImages(SDL_Surface* display);

void loadLivingObjectImages(SDL_Surface* display);

void loadTemporaryObjectImages(SDL_Surface* display);

void loadBlockImages(SDL_Surface* display);

void loadImages(SDL_Surface* display);

void runGame();

#endif //_GameFunctions_H

