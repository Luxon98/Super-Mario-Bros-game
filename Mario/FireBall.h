#ifndef FireBall_H
#define FireBall_H

#include <array>
#include "IndependentLivingObject.h"

class World;
class Position;
enum Direction;
struct SDL_Surface;


class FireBall : public IndependentLivingObject
{
private:
	static std::array<SDL_Surface*, 4> fireBallImages;
	int stepsUp;
	int modelIndex;
	bool stop;
	void computeModelIndex();
	void makeVerticalMove(World &world);
	void makeHorizontalMove(World &world);

public:
	FireBall() = default;
	FireBall(Position position, Direction direction);
	bool shouldBeRemoved();
	void loadFireBallImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) override;
	void move(World &world) override;
};

#endif //FireBall_H
