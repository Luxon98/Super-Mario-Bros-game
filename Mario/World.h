#ifndef _World_H
#define _World_H

#include <chrono>
#include <vector>
#include "SDL_Utility.h"
#include "Block.h"
#include "Player.h"
#include "InanimateObject.h"
#include "Cloud.h"
#include "Bush.h"
#include "Coin.h"
#include "Flower.h"
#include "Mushroom.h"
#include "Creature.h"
#include "Turtle.h"
#include "Shell.h"
#include "CrushedCreature.h"
#include "DestroyedCreature.h"
#include "DestroyedTurtle.h"
#include "TemporaryObject.h"
#include "Explosion.h"
#include "Shards.h"
#include "AnimatedCoin.h"
#include "AnimatedText.h"
#include "FireBall.h"
#include "Star.h"
#include "Castle.h"
#include "Flag.h"
#include "BonusObject.h"
#include "NonControllableLivingObject.h"


class Player;
class FireBall;


enum Direction
{
	None = 0,
	Left = 1,
	Right = 2,
	Down = 3,
	Up = 4
};


class World
{
private:
	std::chrono::steady_clock::time_point lastColoursUpdateTime;
	std::vector<Block> blocks;
	std::vector<InanimateObject*> inanimateElements;
	std::vector<BonusObject*> bonusElements;
	std::vector<NonControllableLivingObject*> monsters;
	std::vector<TemporaryObject*> temporaryElements;
	std::vector<FireBall> fireballs;
	Player* player;
	Flag* flag;
	int lastTouchedBlockIndex;
	int slidingCounter;
	bool fireballStatus;
	void changeColoursIfAvailable();
	void setMovementDirectionIfPlayerIsCloseEnough(NonControllableLivingObject& monster);
	void deleteTemporaryElementsIfTimePassed();
	void performBonusElementsActions();
	void performMonstersActions();
	void performFireBallsActions();
	void performWorldActions();
	void slideTemporaryElements();
	void slideBlock();
	void addShards(Position* position);
	void subtractCoinFromBlockIfPossible();
	void createNewBonusIfPossible();
	void createGreenMushroom();
	void playBlockSoundEffects();
	friend class Level;

public:
	static const int WORLD_WIDTH = 6784;
	static const int WORLD_HEIGHT = 480;
	World();
	std::vector<Block> getBlocks() const;
	std::vector<InanimateObject*> getInanimateElements() const;
	std::vector<BonusObject*> getBonusElements() const;
	std::vector<NonControllableLivingObject*> getMonsters() const;
	std::vector<FireBall> getFireBalls() const;
	int getLastTouchedBlockIndex() const;
	int getBlockModel(int index) const;
	bool isFlagDown() const;
	void setPlayer(Player* player);
	void setLastTouchedBlock(int index);
	void setSlidingCounter(int ctr);
	void setFireballStatus();
	void setActiveFlag();
	void changeShellMovementParameters(int index, Direction direction);
	void performBlockRemovalActions(int index);
	void deleteInanimateElement(int index);
	void deleteLivingElement(int index);
	void deleteMonster(int index);
	void deleteFireBall(int index);
	void addShell(Position* position);
	void addCrushedCreature(Position* position);
	void addDestroyedCreature(Position* position);
	void addDestroyedTurtle(Position* position);
	void addExplosion(Position* position);
	void addAnimatedText(TextType type, Position* position);
	void performActions();
	void draw(SDL_Surface* screen, int beginningOfScreen, bool playerFlag = true);

	Screen* mainScreen;
};

#endif //_World_H
