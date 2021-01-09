#ifndef RedTurtle_H
#define RedTurtle_H

#include <array>
#include "IndependentMovingObject.h"

enum class Direction;
struct SDL_Surface;


// name in the original game: 'Koopa Paratroopa'
class RedTurtle : public IndependentMovingObject
{
private:
	static std::array<SDL_Surface*, 6> redTurtleImages;
	bool flying;
	int model;
	void fly(World &world);
	void patrol(World &world);
	void loseFlyingAbility();
	void changeModel();
	int computeImageIndex() const override;

public:
	RedTurtle(Position position, bool flying);
	static void loadTurtleImages(SDL_Surface* display);
	bool isResistantToCollisionWithShell() const override;
	bool isResistantToCollisionWithBlock() const override;
	void crush(World &world, int index) override;
	void destroy(World &world, Direction direction) override;
	void move(World &world) override;
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //RedTurtle_H