#ifndef _Player_H
#define _Player_H

#include <chrono>
#include <string>
#include "SDL_Utility.h"
#include "LivingObject.h"
#include "World.h"
#include "Block.h"
#include "Screen.h"
#include "CollisionHandling.h"
#include "GameFunctions.h"


enum Direction;
class World;
class Screen;
class LivingObject;

enum AnimationState 
{
	NoAnimation = 0,
	DuringGrowingAnimation = 1,
	DuringArmingAnimation = 2,
	DuringShrinkingAnimation = 3,
	DuringImmortalAnimation = 4
};

enum PlayerState
{
	Small = 1,
	Tall = 2,
	ArmedFirst = 3,
	ArmedSecond = 4,
	ArmedThird = 5,
	ImmortalFirst = 6,
	ImmortalSecond = 7,
	ImmortalThird = 8,
	ImmortalFourth = 9,
	Average = 10,
	InsensitiveSmall = 11,
	InsensitiveTall = 12,
};


class Player : public LivingObject
{
private:
	class Statistics
	{
	public:
		int points;
		int coins;
		int lives;
		Statistics();
	};

	class Flags
	{
	public:
		bool orientationFlag;
		bool rejumpFlag;
		bool aliveFlag;
		bool removeLivesFlag;
		Flags();
		void setDefaultFlags();
	};

	static SDL_Surface* playerImages[74];
	Statistics statistics;
	Flags flags;
	int cameraX;
	int model;
	std::chrono::steady_clock::time_point lastAnimationStartTime;
	AnimationState currentAnimationState;
	PlayerState currentState;
	int computeImageIndex();
	void changeStateDuringAnimation();
	void performGrowingAnimation(int difference);
	void performShrinkingAnimation(int difference);
	void performArmingAnimation(int difference);
	void performImmortalAnimation(int difference);
	long long int lastDifference;
	bool movementBlock;
	void changeModel(World& world);
	bool isHittingCeiling(int distance);
	bool isFallingIntoAbyss(int distance);
	bool isGoingOutBoundariesOfWorld(Direction direction, int distance);
	bool isExceedingCameraReferencePoint(int distance);
	bool isHittingBlock(int alignment, Direction direction);
	bool isDuringAnimation();
	bool isRejumping();

	

public:
	int stepsLeft;
	int stepsRight;
	int stepsUp;
	int stepsDown;
	int speed;

	Player();
	Player(Position* position);
	int getCameraX() const;
	int getPoints() const;
	int getCoins() const;
	int getLives() const;
	bool isArmed() const;
	bool isImmortal() const;
	bool isDead() const;
	PlayerState getCurrentState() const;
	Direction getMovementDirection() const;
	void incrementCoins();
	void incrementLives();
	void addPoints(int pts);
	void setRejumpFlag();
	void setCurrentAnimation(AnimationState state);
	void loadPlayerImages(SDL_Surface* screen);
	void draw(SDL_Surface* screen, int beginningOfCamera) override;
	void hitBlock(World& world, Screen* mainScreen);
	void loseBonusOrLife();
	//void changePosition(Direction direction, int distance, World& world, Screen* mainScreen);
	//void changeVerticalPosition(Direction direction, int distance, World& world);
	//void move(Direction direction, int distance, World& world, Screen* mainScreen) override;
	//void jump(Direction direction, int height, World& world, Screen* mainScreen);
	//void moveAndJump(Direction dirX, int distance, int height, World& world, Screen* mainScreen);
	//void performAdditionalJump(World& world, Screen* mainScreen);

	void move(Direction direction, int distance, World& world, Screen* mainScreen);
	void reborn();
};

#endif //_Player_H

