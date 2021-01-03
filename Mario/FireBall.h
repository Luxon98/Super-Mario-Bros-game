#ifndef FireBall_H
#define FireBall_H

#include <array>
#include "IndependentMovingObject.h"

class World;
class Position;
enum class Direction;
struct SDL_Surface;


class FireBall : public IndependentMovingObject
{
private:
	static std::array<SDL_Surface*, 4> fireBallImages;
	int stepsUp;
	int modelIndex;
	bool stop;
	int computeImageIndex() const override;
	void changeModelIndex();
	void moveVertically(World &world);
	void moveHorizontally(World &world);

public:
	FireBall(Position position, Direction direction);
	static void loadFireBallImages(SDL_Surface* display);
	bool shouldBeRemoved() const;
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	void move(World &world) override;
};

#endif //FireBall_H