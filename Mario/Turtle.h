#ifndef Turtle_H
#define Turtle_H

#include <array>
#include "IndependentLivingObject.h"

class World;
class Position;
enum class Direction;
struct SDL_Surface;


// this class is the counterpart of NPC, which in the original Mario series was called 'Koopa Troopa'
class Turtle : public IndependentLivingObject
{
private:
	static std::array<SDL_Surface*, 8> turtleImages;
	int model;
	int computeImageIndex() const override;
	void changeModel();

public:
	Turtle(Position position);
	static void loadTurtleImages(SDL_Surface* display);
	bool isResistantToCollisionWithShell() const override;
	bool isResistantToCollisionWithBlock() const override;
	void setMoveDirection(Direction direction);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	void move(World &world) override;
	void crush(World &world, int index) override;
	void destroy(World &world, Direction direction) override;
};

#endif //Turtle_H