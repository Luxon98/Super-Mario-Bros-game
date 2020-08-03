#ifndef _KeyboardController_H
#define _KeyboardController_H

#include <map>
#include "SDL_Utility.h"
#include "CollisionHandling.h"
#include "World.h"
#include "Player.h"
#include "Screen.h"


class KeyboardController
{
private:
	std::map<Direction, bool> keysState;
	bool shotState;
	void handleSpacebar(World& world);
	void handleArrowKeys(Player* player, World& world, Screen* mainScreen);

public:
	KeyboardController();
	void handleKeysState(const Uint8* state);
	void clearKeysState();
	void forceActions(Player* player, World& world, Screen* mainScreen);
};

#endif //_KeyboardController_H