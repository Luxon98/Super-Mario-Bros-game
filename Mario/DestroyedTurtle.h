#ifndef DestroyedTurtle_H
#define DestroyedTurtle_H

#include <array>
#include "TemporaryObject.h"

class Position;
struct SDL_Surface;


class DestroyedTurtle : public TemporaryObject
{
private:
	static std::array<SDL_Surface*, 3> destroyedTurtleImages;
	bool red;
	int computeIndex() const;
	
public:
	DestroyedTurtle() = default;
	DestroyedTurtle(Position position, bool red);
	void loadDestroyedTurtleImage(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	bool shouldBeRemoved() const override;
	void slide() override;
};

#endif //DestroyedTurtle_H