#ifndef _GameFunctions_H
#define _GameFunctions_H

#include "SDL_Utility.h"

class KeyboardController;
class Player;
class World;
class Screen;


bool isDifferenceInInterval(int difference, int begin, int shift, int repetitions);

void loadBonusObjectsImages(SDL_Surface* display);

void loadInanimateObjectImages(SDL_Surface* display);

void loadLivingObjectImages(SDL_Surface* display);

void loadTemporaryObjectImages(SDL_Surface* display);

void loadBlockImages(SDL_Surface* display);

void loadImages(SDL_Surface* display);

void resetGame(KeyboardController controller, Player* player, World& world, Screen* screen, bool* playerState);

void runGame();

#endif //_GameFunctions_H

