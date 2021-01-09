#ifndef Turtle_H
#define Turtle_H

#include <array>
#include "IndependentMovingObject.h"

enum class Direction;
struct SDL_Surface;


// name in the original game: 'Koopa Troopa'
class Turtle : public IndependentMovingObject
{
private:
	static std::array<SDL_Surface*, 8> turtleImages;
	int model;
	void changeModel();
	int computeImageIndex() const override;

public:
	Turtle(Position position);
	static void loadTurtleImages(SDL_Surface* display);
	bool shouldStartMoving(const Player &player) const override;
	bool isResistantToCollisionWithShell() const override;
	bool isResistantToCollisionWithBlock() const override;
	void startMoving() override;
	void crush(World &world, int index) override;
	void destroy(World &world, Direction direction) override;
	void move(World &world) override;
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //Turtle_H