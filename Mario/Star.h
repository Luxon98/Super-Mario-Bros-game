#ifndef Star_H
#define Star_H

#include <array>
#include "BonusObject.h"

class World;
struct SDL_Surface;


class Star : public BonusObject 
{
private:
	static std::array<SDL_Surface*, 4> starImages;
	int stepsCounter;
	int stepsUp;
	void makeVerticalMove(World& world);
	void makeHorizontalMove(World& world);

public:
	Star();
	Star(Position position);
	void loadStarImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) override;
	void move(World& world) override;
};

#endif //Star_H
