#ifndef JumpingFish_H
#define JumpingFish_H

#include <array>
#include "IndependentMovingObject.h"

class World;
class Position;
struct SDL_Surface;


class JumpingFish : public IndependentMovingObject
{
private:
	static std::array<SDL_Surface*, 4> fishImages;
	bool directionFlag;
	bool movingFlag;
	int model;
	int computeImageIndex() const override;
	void changeModel();

public:
	JumpingFish(Position position, bool directionFlag);
	static void loadFishImages(SDL_Surface* display);
	int getPointsForCrushing() const override;
	bool isGoingLeft() const;
	void setMoveDirection();
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	void move(World &world) override;
	void crush(World &world, int index) override;
	void destroy(World &world, Direction direction) override;
};

#endif //JumpingFish_H