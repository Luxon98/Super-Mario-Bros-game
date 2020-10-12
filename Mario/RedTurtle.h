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
	void chooseModel();

public:
	RedTurtle() = default;
	RedTurtle(Position position, bool flying);
	bool isFlying() const;
	void loseFlyingAbility();
	void setMoveDirection(Direction direction);
	void loadTurtleImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	void move(World &world) override;
};

#endif //RedTurtle_H

