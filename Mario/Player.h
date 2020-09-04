#ifndef Player_H
#define Player_H

#include <chrono>
#include <array>
#include "Movement.h"
#include "LivingObject.h"

class World;
class KeyboardController;
class Position;
enum class Direction;
struct SDL_Surface;


enum class PlayerAnimation 
{
	NoAnimation = 0,
	Growing = 1,
	Arming = 2,
	Shrinking = 3,
	Immortal = 4,
	ImmortalSmall = 5
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

	static std::array<SDL_Surface*, 132> playerImages;
	Statistics statistics;
	Flags flags;
	PlayerMovement playerMovement;
	int model;
	std::chrono::steady_clock::time_point animationStartTime;
	PlayerAnimation currentAnimationState;
	PlayerState currentState;
	int computeImageIndex() const;
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
	bool isGoingBeyondCamera(int distance, int beginningOfCamera) const;
	bool isHittingBlock(int alignment, Direction direction) const;
	bool isDuringAnimation() const;
	void moveLeft(World &world);
	void moveRight(World &world);
	void moveUp(World &world);
	void moveDown(World &world);
	friend class KeyboardController;

public:
	Player() = default;
	Player(Position position);
	int getPoints() const;
	int getCoins() const;
	int getLives() const;
	bool isSmall() const;
	bool isArmed() const;
	bool isInsensitive() const;
	bool isImmortal() const;
	bool isDead() const;
	bool isTurnedRight() const;
	int getDeadMarioImageIndex() const;
	void incrementCoins();
	void incrementLives();
	void increaseSpeed();
	void addPoints(int pts);
	void setCurrentAnimation(PlayerAnimation animation);
	void loadPlayerImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	void hitBlock(World &world);
	void loseBonusOrLife();
	void performAdditionalJump();
	void move(World &world) override;
	void reborn();
	void resetSteps();
	void setFinishingRunParameters();
};

#endif //Player_H

