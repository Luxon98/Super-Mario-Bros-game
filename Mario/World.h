#ifndef World_H
#define World_H

#include <chrono>
#include <vector>
#include <memory>
#include "FireBall.h"
#include "Flag.h"

class Player;
class Screen;
class BonusObject;
class Position;
class Level;
class Block;
class InanimateObject;
class TemporaryObject;
class LivingObject;
enum class TextType;
enum class Direction;
enum class BlockType;
enum class LayoutStyle;
struct SDL_Surface;


class World
{
private:
	static constexpr int DISTANCE_FROM_WORLD = 30;
	std::chrono::steady_clock::time_point lastColoursUpdateTime;
	std::vector<Block> blocks;
	std::vector<FireBall> fireballs;
	std::vector<std::shared_ptr<InanimateObject>> inanimateElements;
	std::vector<std::shared_ptr<BonusObject>> bonusElements;
	std::vector<std::shared_ptr<LivingObject>> monsters;
	std::vector<std::shared_ptr<TemporaryObject>> temporaryElements;
	std::shared_ptr<Player> player;
	Screen* screen;
	Flag flag;
	int gameCounter;
	int lastTouchedBlockIndex;
	int slidingCounter;
	bool slideBlockStatus;
	bool fireballStatus;
	bool isTimeToChangeColors() const;
	bool isPlayerCloseEnough(LivingObject &monster) const;
	bool hasLastTouchedBlockCoin() const;
	bool isLastTouchedBlockBonus() const;
	void changeColors();
	void setMovementDirection(LivingObject &monster);
	void deleteTemporaryElements();
	void performBonusElementsActions();
	void performMonstersActions();
	void performFireBallsActions();
	void performWorldActions();
	void slideTemporaryElements();
	void slideBlock();
	void raiseUpMushroom();
	void addShards(Position position);
	void performBlockSliding();
	void subtractCoinFromBlock();
	void createNewBonus();
	void createGreenMushroom();
	void playBlockSoundEffects();
	friend class Level;

public:
	static constexpr int WORLD_WIDTH = 6784;
	static constexpr int WORLD_HEIGHT = 480;
	static LayoutStyle LAYOUT_STYLE;
	World();
	std::vector<Block> const& getBlocks() const;
	std::vector<FireBall> const& getFireBalls() const;
	std::vector<std::shared_ptr<InanimateObject>> const& getInanimateElements() const;
	std::vector<std::shared_ptr<BonusObject>> const& getBonusElements() const;
	std::vector<std::shared_ptr<LivingObject>> const& getMonsters() const;
	int getLastTouchedBlockIndex() const;
	BlockType getLastTouchedBlockType() const;
	Screen* getScreen() const;
	bool isFlagDown() const;
	bool isPlayerFinishingWorld() const;
	void setPlayer(std::shared_ptr<Player> player);
	void setScreen(Screen* screen);
	void setLastTouchedBlock(int index);
	void hitBlock();
	void setFireballStatus();
	void switchOnFlag();
	void changeShellMovementParameters(int index, Direction direction);
	void destroyLastTouchedBlock();
	void deleteInanimateElement(int index);
	void deleteLivingElement(int index);
	void deleteMonster(int index);
	void deleteFireBall(int index);
	void addShell(Position position);
	void addCrushedCreature(Position position);
	void addDestroyedCreature(Position position);
	void addDestroyedTurtle(Position position);
	void addExplosion(Position position);
	void addAnimatedText(TextType type, Position position);
	void performActions();
	void draw(SDL_Surface* display, int beginningOfScreen, int endOfScreen, bool drawPlayer = true);
	~World();
};

#endif //World_H
