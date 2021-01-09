#ifndef FireBall_H
#define FireBall_H

#include <array>
#include "MovingObject.h"

class World;
enum class Direction;
struct SDL_Surface;


class FireBall : public MovingObject
{
private:
	static std::array<SDL_Surface*, 4> fireBallImages;
	int stepsUp;
	int modelIndex;
	bool stop;
	void changeModelIndex();
	void moveVertically(World &world);
	void moveHorizontally(World &world);

public:
	FireBall(Position position, Direction direction);
	static void loadFireBallImages(SDL_Surface* display);
	bool shouldBeRemoved() const;
	void move(World &world) override;
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //FireBall_H