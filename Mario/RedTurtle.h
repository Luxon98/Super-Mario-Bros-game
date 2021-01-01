#ifndef RedTurtle_H
#define RedTurtle_H

#include <array>
#include "IndependentLivingObject.h"

class World;
class Position;
enum class Direction;
struct SDL_Surface;


// this class is the counterpart of NPC, which in the original Mario series was called 'Koopa Paratroopa'
class RedTurtle : public IndependentLivingObject
{
private:
	static std::array<SDL_Surface*, 6> redTurtleImages;
	bool flying;
	int model;
	int computeImageIndex() const override;
	void fly(World &world);
	void patrol(World &world);
	void changeModel();

public:
	RedTurtle(Position position, bool flying);
	static void loadTurtleImages(SDL_Surface* display);
	bool isFlying() const;
	void loseFlyingAbility();
	void setMoveDirection(Direction direction);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	void move(World &world) override;
	void crush(World &world, int index) override;
	void destroy(World &world, Direction direction) override;
};

#endif //RedTurtle_H