#ifndef Player_H
#define Player_H

#include <chrono>
#include <array>
#include "Movement.h"
#include "LivingObject.h"

class World;
class KeyboardController;
class Position;
class Camera;
enum class Direction;
struct SDL_Surface;


enum class PlayerAnimation 
{
	NoAnimation,
	Growing,
	Arming,
	Shrinking,
	Immortal,
	ImmortalSmall
};


class Player : public LivingObject
{
private:
	enum class PlayerState
	{
		Small = 1,
		Tall = 2,
		ArmedFirst = 3,
		ArmedSecond = 4,
		ArmedThird = 5,
		ImmortalFirst = 6,
		ImmortalSecond = 7,
		ImmortalThird = 8,
		Insensitive = 9,
		ImmortalSmallFirst = 10,
		ImmortalSmallSecond = 11,
		ImmortalSmallThird = 12,
		ImmortalSmallFourth = 13,
		ImmortalFourth = 14,
		Average = 15
	};

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
		bool slideFlag;
		bool changeDirectionFlag;
		bool downPipeFlag;
		Flags();
		void setDefaultFlags(bool armedFlag);
	};

	class PlayerMovement : public Movement
	{
	public:
		int stepsLeft;
		int stepsRight;
		int stepsUp;
		PlayerMovement();
	};

	static std::array<SDL_Surface*, 140> playerImages;
	int model;
	Statistics statistics;
	Flags flags;
	PlayerMovement playerMovement;
	PlayerAnimation currentAnimationState;
	PlayerState currentState;
	std::shared_ptr<Camera> camera;
	std::chrono::steady_clock::time_point animationStartTime;
	int computeImageIndexWhenSliding() const;
	int computeImageIndex() const override;
	void changeStateDuringAnimation();
	void performGrowingAnimation(int difference);
	void performShrinkingAnimation(int difference);
	void performArmingAnimation(int difference);
	void performImmortalAnimation(int difference);
	void performSmallImmortalAnimation(int difference);
	long long int lastDifference;
	bool movementBlock;
	void resetMovement();
	void changeModelAndAirFlagStatus(World &world);
	bool isHittingCeiling(int distance) const;
	bool isFallingIntoAbyss(int distance) const;
	bool isGoingBeyondCamera(int distance) const;
	bool isHittingBlock(int alignment, Direction direction) const;
	bool isDuringAnimation() const;
	bool isAbleToDestroyBlock() const;
	void moveLeft(World &world);
	void moveRight(World &world);
	void moveUp(World &world);
	void moveDown(World &world);
	void slide(World &world);
	friend class KeyboardController;

public:
	Player() = default;
	Player(Position position);
	static void loadPlayerImages(SDL_Surface* display);
	int getPoints() const;
	int getCoins() const;
	int getLives() const;
	int getDeadMarioImageIndex() const;
	int getStepsRight() const;
	bool isSmall() const;
	bool isArmed() const;
	bool isInsensitive() const;
	bool isImmortal() const;
	bool isDead() const;
	bool isTurnedRight() const;
	bool isPerformingJumpAsSmall() const;
	bool isGoingToPipe() const;
	void incrementCoins();
	void incrementLives();
	void increaseSpeed();
	void addPoints(int pts);
	void setCurrentAnimation(PlayerAnimation animation);
	void setCamera(std::shared_ptr<Camera> camera);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	void forceMovement(Direction direction);
	void hitBlock(World &world);
	void loseBonusOrLife();
	void performAdditionalJump();
	void move(World &world) override;
	void setPositionXY(int level);
	void setPositionXY(int level, int checkPointMark);
	void reborn(int level);
	void resetSteps();
	void setSlidingParameters();
	void setFinishingRunParameters(); 
};

#endif //Player_H

