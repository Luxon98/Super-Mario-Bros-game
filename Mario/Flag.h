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
	Flag() = default;
	Flag(Position position);
	static void loadFlagImages(SDL_Surface* display);
	bool isActive() const;
	bool isDown() const;
	void setActiveState();
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	void changePosition();
};

#endif //Flag_H

