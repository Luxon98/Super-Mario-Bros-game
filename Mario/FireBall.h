#ifndef FireBall_H
#define FireBall_H

#include <array>
#include "IndependentLivingObject.h"

class World;
class Position;
enum class Direction;
struct SDL_Surface;


class FireBall : public IndependentLivingObject
{
private:
	static std::array<SDL_Surface*, 4> fireBallImages;
	int stepsUp;
	int modelIndex;
	bool stop;
	int computeImageIndex() const override;
	void changeModelIndex();
	void makeVerticalMove(World &world);
	void makeHorizontalMove(World &world);

public:
	FireBall() = default;
	FireBall(Position position, Direction direction);
	static void loadFireBallImages(SDL_Surface* display);
	bool shouldBeRemoved() const;
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	void move(World &world) override;
};

#endif //FireBall_H
