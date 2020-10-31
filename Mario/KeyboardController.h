#ifndef KeyboardController_H
#define KeyboardController_H

#include <map>
#include <chrono>
#include "SDL_Utility.h"

class World;
class Player;
enum class Direction;


class KeyboardController
{
private:
	bool doubleJumpFlag;
	bool shotStatusFlag;
	std::chrono::steady_clock::time_point lastShotTime;
	std::map<Direction, bool> keysState;
	void handleSpacebar(World &world);
	void handleDownArrow(Player &player);
	void handleArrows(Player &player, World &world);

public:
	KeyboardController();
	void handleKeysState(const Uint8* state);
	void clearKeysState();
	void forceActions(Player &player, World &world);
};

#endif //KeyboardController_H