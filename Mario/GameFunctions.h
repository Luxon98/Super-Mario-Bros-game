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

bool isLevelClassic(int level);

bool isLevelTheLast(int level);

bool isLevelCustom(int level);

bool isCheckPointLeadingToHiddenStage(int level, int checkPointMark);

bool isPlayerEnteringPipe(int level, int checkPointMark);

bool isPlayerExitingPipe(int level, int checkPointMark);

void resetScreenForClassicLevels(Screen &screen, int level, int checkPointMark);

void resetScreenForCustomLevels(Screen &screen, int level, int checkPointMark);

void resetScreen(Screen &screen, int level, int checkPointMark);

void changeLevel(int level, World &world, bool playerState);

void setWorld(int level, Player &player, World &world, bool playerState);

void setSubWorldForClassicLevels(int level, int checkPointMark, World &world);

void setSubWorldForCustomLevels(int level, int checkPointMark, World &world);

void setSubWorld(int level, int checkPointMark, Player &player, World &world);

void adjustCamera(int level, int checkPointMark);

void handleMenu(bool * exitStatus, int * gameSpeed, int * level, Screen &screen);

void showLevelFinishingAnimation(Player &player, World &world, Screen &screen, int level);

void showWorldFinishingAnimation(Player &player, World &world, Screen &screen);

void runGame();

#endif //GameFunctions_H