#ifndef _Player_H
#define _Player_H

#include <chrono>
#include <string>
#include "SDL_Utility.h"
#include "LivingObject.h"
#include "World.h"
#include "Block.h"
#include "Screen.h"
#include "GameFunctions.h"
#include "Direction.h"


enum Direction;
class World;
class Screen;


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
	InsensitiveSmall = 11
};

enum AnimationState 
{
	NoAnimation = 0,
	DuringGrowingAnimation = 1,
	DuringArmingAnimation = 2,
	DuringShrinkingAnimation = 3,
	DuringImmortalAnimation = 4
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
		bool aliveFlag;
		bool removeLivesFlag;
		bool armedFlag;
		bool inAirFlag;
		Flags();
		void setDefaultFlags();
	};

	class PlayerMovement : public Movement
	{
	public:
		int stepsLeft;
		int stepsRight;
		int stepsUp;
		int stepsDown;
		PlayerMovement();
	};

	static SDL_Surface* playerImages[80];
	Statistics statistics;
	Flags flags;
	PlayerMovement* playerMovement;
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
	void resetMovement();
	void changeModelAndAirFlagStatus(World& world);
	bool isHittingCeiling(int distance);
	bool isFallingIntoAbyss(int distance);
	bool isGoingBeyondCamera(int distance, int beginningOfCamera);
	bool isHittingBlock(int alignment, Direction direction);
	bool isDuringAnimation();

public:
	Player();
	Player(Position* position);
	int getPoints() const;
	int getCoins() const;
	int getLives() const;
	int getStepsLeft() const;
	int getStepsRight() const;
	int getStepsUp() const;
	bool isArmed() const;
	bool isImmortal() const;
	bool isDead() const;
	PlayerState getCurrentState() const;
	Direction getMovementDirection() const;
	void incrementCoins();
	void incrementLives();
	void increaseSpeed();
	void setStepsLeft(int stepsLeft);
	void setStepsRight(int stepsRight);
	void setStepsUp(int stepsUp);
	void setStepsDown(int stepsDown);
	void addPoints(int pts);
	void setCurrentAnimation(AnimationState state);
	void loadPlayerImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera) override;
	void hitBlock(World& world);
	void loseBonusOrLife();
	void performAdditionalJump();
	void move(World& world);
	void reborn();
};

#endif //_Player_H

