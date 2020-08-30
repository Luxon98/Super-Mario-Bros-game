#ifndef KeyboardController_H
#define KeyboardController_H

#include <map>
#include "SDL_Utility.h"

class World;
class Player;
enum Direction;


class KeyboardController
{
private:
	bool doubleJumpFlag;
	bool shotStatusFlag;
	std::map<Direction, bool> keysState;
	void handleSpacebar(World& world);
	void handleArrowKeys(Player* player, World& world);

public:
	KeyboardController();
	void handleKeysState(const Uint8* state);
	void clearKeysState();
	void handleKeys(Player* player, World& world);
};

#endif //KeyboardController_H