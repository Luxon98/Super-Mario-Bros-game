#ifndef FireSerpent_H
#define FireSerpent_H

#include <array>
#include "WorldObject.h"

struct SDL_Surface;


class FireSerpent : public WorldObject
{
private:
	static std::array<SDL_Surface*, 24> fireSerpentImages;
	static std::array<int, 24> xDifferences;
	static std::array<int, 24> yDifferences;
	int positionCounter;
	int auxiliaryCounter;	
	Position initialPosition;
	void changePosition();

public:
	FireSerpent(int counter, Position position);
	static void loadFireSerpentImages(SDL_Surface* display);
	void move();
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //FireSerpent_H