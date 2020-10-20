#ifndef RedTurtle_H
#define RedTurtle_H

#include <array>
#include "IndependentLivingObject.h"

class World;
class Position;
enum class Direction;
struct SDL_Surface;


class RedTurtle : public IndependentLivingObject
{
private:
	static std::array<SDL_Surface*, 6> redTurtleImages;
	bool flying;
	int model;
	int computeIndex() const;
	void fly();
	void patrol(World &world);
	void changeModel();

public:
	RedTurtle() = default;
	RedTurtle(Position position, bool flying);
	static void loadTurtleImages(SDL_Surface* display);
	bool isFlying() const;
	void loseFlyingAbility();
	void setMoveDirection(Direction direction);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	void move(World &world) override;
};

#endif //RedTurtle_H

