#ifndef DestroyedTurtle_H
#define DestroyedTurtle_H

#include <array>
#include "TemporaryObject.h"
#include "Direction.h"

struct SDL_Surface;


class DestroyedTurtle : public TemporaryObject
{
private:
	static std::array<SDL_Surface*, 3> destroyedTurtleImages;
	bool red;
	Direction direction;
	int computeImageIndex() const override;
	
public:
	DestroyedTurtle(Position position, Direction direction, bool red);
	static void loadDestroyedTurtleImages(SDL_Surface* display);
	void slide() override;
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //DestroyedTurtle_H