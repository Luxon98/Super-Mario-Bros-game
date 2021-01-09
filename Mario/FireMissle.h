#ifndef FireMissle_H
#define FireMissle_H

#include <array>
#include <chrono>
#include "IndependentMovingObject.h"

enum class Direction;
struct SDL_Surface;


enum class MissleType
{
	Rocket,
	Bomb
};


class FireMissle : public IndependentMovingObject
{
private:
	static std::array<SDL_Surface*, 3> missleImages;
	bool inactive;
	int model;
	MissleType missleType;
	std::chrono::steady_clock::time_point lastSoundTime;
	bool isRightTime();
	void changeModel();
	void fallDown(World &world);
	void moveLeft(World &world);
	int computeImageIndex() const override;

public:
	FireMissle(Position position, MissleType type);
	static void loadFireRocketImages(SDL_Surface* display);
	bool shouldStartMoving(const Player &player) const override;
	bool isCrushproof() const override;
	bool isResistantToImmortalPlayer() const override;
	bool isResistantToFireBalls() const override;
	void startMoving() override;
	void performSpecificActions(World &world, int index) override;
	void move(World &world) override;
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //FireMissle_H