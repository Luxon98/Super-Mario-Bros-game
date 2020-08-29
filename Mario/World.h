#ifndef _World_H
#define _World_H

#include <chrono>
#include <vector>
#include "FireBall.h"

class Player;
class Screen;
class BonusObject;
class Position;
class Level;
class Block;
class InanimateObject;
class TemporaryObject;
class LivingObject;
class Flag;
enum TextType;
enum Direction;
struct SDL_Surface;


class World
{
private:
	static const int DISTANCE_FROM_WORLD = 30;
	std::chrono::steady_clock::time_point lastColoursUpdateTime;
	std::vector<Block> blocks;
	std::vector<InanimateObject*> inanimateElements;
	std::vector<BonusObject*> bonusElements;
	std::vector<LivingObject*> monsters;
	std::vector<TemporaryObject*> temporaryElements;
	std::vector<FireBall> fireballs;
	Player* player;
	Flag* flag;
	Screen* screen;
	int gameCounter;
	int lastTouchedBlockIndex;
	int slidingCounter;
	bool slideBlockStatus;
	bool fireballStatus;
	bool isTimeToChangeColors();
	bool isPlayerCloseEnough(LivingObject& monster);
	bool hasLastTouchedBlockCoin();
	bool isLastTouchedBlockBonus();
	void changeColors();
	void setMovementDirection(LivingObject& monster);
	void deleteTemporaryElements();
	void performBonusElementsActions();
	void performMonstersActions();
	void performFireBallsActions();
	void performWorldActions();
	void slideTemporaryElements();
	void slideBlock();
	void raiseUpMushroom();
	void addShards(Position* position);
	void performBlockSliding();
	void subtractCoinFromBlock();
	void createNewBonus();
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
	std::vector<LivingObject*> getMonsters() const;
	std::vector<FireBall> getFireBalls() const;
	int getLastTouchedBlockIndex() const;
	int getBlockModel(int index) const;
	bool isFlagDown() const;
	Screen* getScreen() const;
	void setPlayer(Player* player);
	void setScreen(Screen* screen);
	void setLastTouchedBlock(int index);
	void hitBlock();
	void setFireballStatus();
	void switchOnFlag();
	bool isPlayerFinishingWorld();
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
	void draw(SDL_Surface* display, int beginningOfScreen, int endOfScreen, bool playerFlag = true);
};

#endif //_World_H
