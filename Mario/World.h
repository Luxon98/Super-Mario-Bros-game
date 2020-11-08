#ifndef World_H
#define World_H

#include <chrono>
#include <vector>
#include <memory>
#include "FireBall.h"
#include "MovingPlatform.h"
#include "Flag.h"
#include "CheckPoint.h"

class Player;
class BonusObject;
class Position;
class Level;
class Block;
class InanimateObject;
class TemporaryObject;
class LivingObject;
class Camera;
enum class TextType;
enum class Direction;
enum class BlockType;
enum class LayoutStyle;
struct SDL_Surface;


class World
{
private:
	static constexpr int DISTANCE_FROM_WORLD = 30;
	static constexpr int MAX_NUMBER_OF_FIREBALLS = 2;
	static constexpr int SLIDING_BLOCK_VALUE = 81;
	std::chrono::steady_clock::time_point lastColoursUpdateTime;
	std::vector<Block> blocks;
	std::vector<MovingPlatform> platforms;
	std::vector<FireBall> fireballs;
	std::vector<CheckPoint> checkPoints;
	std::vector<std::shared_ptr<InanimateObject>> inanimateElements;
	std::vector<std::shared_ptr<BonusObject>> bonusElements;
	std::vector<std::shared_ptr<LivingObject>> monsters;
	std::vector<std::shared_ptr<TemporaryObject>> temporaryElements;
	std::shared_ptr<Player> player;
	std::shared_ptr<Camera> camera; 
	Flag flag;
	int gameCounter;
	int gameSpeed;
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
	void collectCoin();
	void addShards(Position position);
	void performBlockSliding();
	void subtractCoinFromBlock();
	void createNewBonus();
	void createOneUpMushroom();
	void playBlockSoundEffects();
	friend class Level;

public:
	static constexpr int WORLD_HEIGHT = 480;
	static LayoutStyle LAYOUT_STYLE;
	World();
	std::vector<Block> const& getBlocks() const;
	std::vector<MovingPlatform> const& getPlatforms() const;
	std::vector<FireBall> const& getFireBalls() const;
	std::vector<std::shared_ptr<InanimateObject>> const& getInanimateElements() const;
	std::vector<std::shared_ptr<BonusObject>> const& getBonusElements() const;
	std::vector<std::shared_ptr<LivingObject>> const& getMonsters() const;
	const Player& getPlayer() const;
	int getLastTouchedBlockIndex() const;
	BlockType getLastTouchedBlockType() const;
	bool isFlagDown() const;
	bool isPlayerFinishingWorld() const;
	int getLastReachedCheckPointMark() const;
	void setGameSpeed(int gameSpeed);
	void setPlayer(std::shared_ptr<Player> player);
	void setCamera(std::shared_ptr<Camera> camera);
	void setLastTouchedBlock(int index);
	void hitBlock();
	void setFireballStatus();
	void switchOnFlag();
	void changeShellMovementParameters(int index, Direction direction);
	void resetImages();
	void destroyLastTouchedBlock();
	void deleteCoin(int index);
	void deleteLivingElement(int index);
	void deleteMonster(int index);
	void deleteFireBall(int index);
	void addShell(Position position, bool red = false);
	void addCrushedCreature(Position position);
	void addDestroyedCreature(Position position, Direction slideDirection);
	void addDestroyedTurtle(Position position, Direction slideDirection, bool red = false);
	void addExplosion(Position position);
	void addAnimatedText(TextType type, Position position);
	void addAnimatedCoin();
	void performActions();
	void draw(SDL_Surface* display, bool drawPlayer = true);
};

#endif //World_H
