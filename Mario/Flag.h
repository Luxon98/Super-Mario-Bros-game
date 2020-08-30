#ifndef Flag_H
#define Flag_H

#include <array>
#include "InanimateObject.h"

class Position;
struct SDL_Surface;


class Flag : public InanimateObject
{
private:
	static std::array<SDL_Surface*, 2> flagImages;
	int stepsCounter;
	int stickPositionY;
	bool active;

public:
	Flag();
	Flag(Position position);
	bool isActive() const;
	bool isDown() const;
	void setActiveState();
	void loadFlagImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) override;
	void changePosition();
};

#endif //Flag_H

