#ifndef Boss_H
#define Boss_H

#include <array>
#include "IndependentMovingObject.h"

enum class Direction;
struct SDL_Surface;


// name in the original game: 'Fake Bowser'
class Boss : public IndependentMovingObject
{
private:
	static std::array<SDL_Surface*, 4> bossImages;
	int model;
	int auxiliaryCounter;
	int computeImageIndex() const override;
	void changeModel();
	void moveAndJump(World &world);

public:
	Boss(Position position);
	static void loadBossImages(SDL_Surface* display);
	bool shouldStartMoving(const Player &player) const override;
	bool isCrushproof() const override;
	bool isResistantToImmortalPlayer() const override;
	bool isBoss() const override;
	int getPointsForDestroying() const override;
	void startMoving() override;
	void destroy(World &world, Direction direction) override;
	void move(World &world) override;
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //Boss_H