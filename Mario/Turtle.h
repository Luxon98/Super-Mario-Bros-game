#ifndef Turtle_H
#define Turtle_H

#include <array>
#include "IndependentLivingObject.h"

class World;
class Position;
enum class Direction;
struct SDL_Surface;


class Turtle : public IndependentLivingObject
{
private:
	static std::array<SDL_Surface*, 8> turtleImages;
	int model;
	int computeBaseIndex() const;
	void chooseModel();

public:
	Turtle() = default;
	Turtle(Position position);
	void setMoveDirection(Direction direction);
	void loadTurtleImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	void move(World &world) override;
};

#endif //Turtle_H
