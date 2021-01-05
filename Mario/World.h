#ifndef World_H
#define World_H

#include <chrono>
#include <vector>
#include <memory>
#include "FireBall.h"
#include "Platform.h"
#include "CheckPoint.h"
#include "FireSerpent.h"
#include "Button.h"
#include "Flag.h"
#include "Block.h"

class Player;
class BonusObject;
class Position;
class Level;
class InanimateObject;
class TemporaryObject;
class AnimatedObject;
class IndependentMovingObject;
class MovingObject;
class Camera;
enum class TextType;
enum class Direction;
enum class BlockType;
enum class LayoutStyle;
struct SDL_Surface;


class World
{
private:
	static constexpr int DISTANCE_FROM_WORLD = 100;
	static constexpr int MAX_NUMBER_OF_FIREBALLS = 2;
	static constexpr int SLIDING_BLOCK_VALUE = 81;
	std::chrono::steady_clock::time_point lastColoursUpdateTime;
	std::vector<Block> blocks;
	std::vector<Platform> platforms;
	std::vector<FireBall> fireballs;
	std::vector<CheckPoint> checkPoints;
	std::vector<FireSerpent> fireSerpents;
	std::vector<std::shared_ptr<InanimateObject>> inanimateElements;
	std::vector<std::shared_ptr<BonusObject>> bonuses;
	std::vector<std::shared_ptr<IndependentMovingObject>> npcs;
	std::vector<std::shared_ptr<TemporaryObject>> temporaryElements;
	std::vector<std::shared_ptr<TemporaryObject>> destroyedElements;
	std::vector<std::shared_ptr<AnimatedObject>> animatedElements;
	std::shared_ptr<Player> player;
	std::shared_ptr<Camera> camera; 
	std::unique_ptr<Flag> flag;
	std::unique_ptr<Button> button;
	int gameCounter;
	int gameSpeed;
	int lastTouchedBlockIndex;
	int slidingCounter;
	bool slideBlockStatus;
	bool fireballStatus;
	bool isTimeToChangeColors() const;
	bool isPlayerCloseEnough(IndependentMovingObject &npc) const;
	bool isObjectOutsideCamera(MovingObject &object) const;
	bool isObjectOutsideWorld(MovingObject &object) const;
	bool hasLastTouchedBlockCoin() const;
	bool isLastTouchedBlockBonus() const;
	void changeColors();
	void deleteTemporaryElements();
	void handleFireballStatus();
	void performBonusElementsActions();
	void performSpecificNpcsActions(int index);
	void performNpcsActions();
	void performFireBallsActions();
	void performPlatformsActions();
	void performFireSerpentsActions();
	void performAnimatedElementsActions();
	void performWorldActions(bool playerActionFlag = true);
	void slideTemporaryElements();
	void slideBlock();
	void collectCoin();
	void addShards(Position position);
	void performBlockSliding();
	void subtractCoinFromBlock();
	void createNewBonus();
	void createOneUpMushroom();
	void playBlockSoundEffects();
	void drawInanimateElements(SDL_Surface* display);
	void drawBonusesAndNpcs(SDL_Surface* display);
	void drawPlatformsAndFireballs(SDL_Surface* display);
	void drawOtherObjects(SDL_Surface* display, bool drawPlayer);
	void drawTemporaryElements(SDL_Surface* display);
	void drawDestroyedElements(SDL_Surface* display);
	void drawAnimatedElements(SDL_Surface* display);
	friend class Level;

public:
	static int WORLD_HEIGHT;
	static LayoutStyle LAYOUT_STYLE;
	World();
	std::vector<Block> const& getBlocks() const;
	std::vector<Platform> const& getPlatforms() const;
	std::vector<FireBall> const& getFireBalls() const;
	std::vector<FireSerpent> const& getFireSerpents() const;
	std::vector<std::shared_ptr<InanimateObject>> const& getInanimateElements() const;
	std::vector<std::shared_ptr<BonusObject>> const& getBonusElements() const;
	std::vector<std::shared_ptr<IndependentMovingObject>> const& getNpcs() const;
	const Player& getPlayer() const;
	int getLastTouchedBlockIndex() const;
	BlockType getLastTouchedBlockType() const;
	bool isFlagDown() const;
	bool isPlayerFinishingWorld() const;
	bool isBridgeDestroyedAlready() const;
	bool areAnimatedElementsEmpty() const;
	int getLastReachedCheckPointMark() const;
	void setGameSpeed(int gameSpeed);
	void setPlayer(std::shared_ptr<Player> player);
	void setCamera(std::shared_ptr<Camera> camera);
	void setLastTouchedBlock(int index);
	void hitBlock();
	void setFireballStatus();
	void switchOnFlag();
	void spoilBridgeAndBoss();
	void resetImages();
	void destroyLastTouchedBlock();
	void deleteBonus(int index);
	void deleteNpc(int index);
	void deleteFireBall(int index);
	void addShell(Position position, bool red = false);
	void addCrushedCreature(Position position);
	void addDestroyedCreature(Position position, Direction slideDirection);
	void addDestroyedTurtle(Position position, Direction slideDirection, bool red = false);
	void addDestroyedBoss(Position position, Direction direction, bool normal = true);
	void addDestroyedFish(Position position, bool directionFlag);
	void addDestroyedBombardier(Position position, bool leftSide);
	void addExplosion(Position position);
	void addAnimatedText(TextType type, Position position);
	void addAnimatedCoin();
	void performActions(bool playerActionFlag = true);
	void draw(SDL_Surface* display, bool drawPlayer = true);
};

#endif //World_H