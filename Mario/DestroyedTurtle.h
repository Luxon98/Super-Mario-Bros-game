#ifndef DestroyedTurtle_H
#define DestroyedTurtle_H

#include <array>
#include "TemporaryObject.h"
#include "Direction.h"

class Position;
struct SDL_Surface;


class DestroyedTurtle : public TemporaryObject
{
private:
	static std::array<SDL_Surface*, 3> destroyedTurtleImages;
	bool red;
	Direction slideDirection;
	int computeImageIndex() const override;
	
public:
	DestroyedTurtle(Position position, Direction slideDirection, bool red);
	static void loadDestroyedTurtleImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	bool shouldBeRemoved() const override;
	void slide() override;
};

#endif //DestroyedTurtle_H