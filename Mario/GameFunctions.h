#ifndef GameFunctions_H
#define GameFunctions_H

#include <memory>
#include "SDL_Utility.h"

class KeyboardController;
class Player;
class World;
class Screen;
class Camera;


void setCameraPointer(Player &player, World &world, Screen &screen, std::shared_ptr<Camera> camera);

void setPlayerPointer(World &world, Screen &screen, std::shared_ptr<Player> player);

bool isPlayerEnteringPipe(int level, int checkPointMark);

bool isPlayerExitingPipe(int level, int checkPointMark);

void resetScreen(Screen &screen, int level, int checkPointMark);

void changeLevel(int level, World &world, bool playerState);

void setWorld(int level, Player &player, World &world, bool playerState);

void setSubWorld(int level, int checkPointMark, Player &player, World &world);

void adjustCamera(int level, int checkPointMark);

void handleMenu(bool * exitStatus, int * gameSpeed, Screen &screen);

void showLevelFinishingAnimation(Player &player, World &world, Screen &screen, int level);

void showWorldFinishingAnimation(Player &player, World &world, Screen &screen, int level);

void runGame();

#endif //GameFunctions_H