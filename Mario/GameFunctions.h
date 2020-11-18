#ifndef GameFunctions_H
#define GameFunctions_H

#include <memory>
#include "SDL_Utility.h"

class KeyboardController;
class Player;
class World;
class Screen;
class Camera;


void loadBonusObjectsImages(SDL_Surface* display);

void loadInanimateObjectImages(SDL_Surface* display);

void loadLivingObjectImages(SDL_Surface* display);

void loadTemporaryObjectImages(SDL_Surface* display);

void loadOtherImages(SDL_Surface* display);

void loadImages(SDL_Surface* display);

void setCameraPointer(std::shared_ptr<Player> player, World &world, Screen &screen, std::shared_ptr<Camera> camera);

void setPlayerPointer(World &world, Screen &screen, std::shared_ptr<Player> player);

bool isPlayerEnteringPipe(int level, int checkPointMark);

bool isPlayerExitingPipe(int level, int checkPointMark);

void resetScreen(Screen &screen, int level, int checkPointMark);

void changeLevel(int level, World &world, bool playerState);

void setWorld(int level, Player &player, World &world, bool playerState);

void setSubWorld(int level, int checkPointMark, Player &player, World &world);

void adjustCamera(int level, int checkPointMark);

void handleMenu(bool * exitStatus, int * gameSpeed, Screen &screen);

void runGame();

#endif //GameFunctions_H

