#ifndef Boss_H
#define Boss_H

#include <array>
#include "IndependentLivingObject.h"

class World;
class Position;
enum class Direction;
struct SDL_Surface;


// this class is the counterpart of NPC, which in the original Mario series was called 'Fake Bowser'
class Boss : public IndependentLivingObject
{
private:
	static std::array<SDL_Surface*, 4> bossImages;
	int model;
	int healthPoints;
	int auxiliaryCounter;
	int computeImageIndex() const override;
	void changeModel();
	void moveAndJump(World &world);

public:
	Boss(Position position);
	static void loadBossImages(SDL_Surface* display);
	bool isCrushproof() const override;
	int getHealthPoints() const;
	void setMoveDirection(Direction direction);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	void move(World &world) override;
	void decrementHealthPoints();
};

#endif //Boss_H