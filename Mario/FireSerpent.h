#ifndef FireSerpent_H
#define FireSerpent_H

#include <array>
#include "WorldObject.h"

struct SDL_Surface;


class FireSerpent : public WorldObject
{
private:
	static std::array<SDL_Surface*, 24> serpentImages;
	bool down;
	int positionCounter;
	int auxiliaryCounter;

public:
	FireSerpent() = default;
	FireSerpent(bool down, Position position);
	static void loadFireSerpentImages(SDL_Surface* display);
	void move();
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif