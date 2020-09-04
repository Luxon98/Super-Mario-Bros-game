#ifndef DestroyedTurtle_H
#define DestroyedTurtle_H

#include "TemporaryObject.h"

class Position;
struct SDL_Surface;


class DestroyedTurtle : public TemporaryObject
{
private:
	static SDL_Surface* destroyedTurtleImage;
	
public:
	DestroyedTurtle() = default;
	DestroyedTurtle(Position position);
	void loadDestroyedTurtleImage(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	bool shouldBeRemoved() const override;
	void slide() override;
};

#endif //DestroyedTurtle_H