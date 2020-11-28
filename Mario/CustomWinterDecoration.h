#ifndef CustomWinterDecoration_H
#define CustomWinterDecoration_H

#include <array>
#include "InanimateObject.h"

class Position;
struct SDL_Surface;


enum class DecorationType
{
	YELLOW_STAR = 1,
	GOLD_STAR = 2,
	CHRISTMAS_TREE = 3,
	WINTER_CLOUD = 4,
	MOON = 5,
	SIGNPOST = 6
};


class CustomWinterDecoration : public InanimateObject
{
private:
	static std::array<SDL_Surface*, 6> decorationImages;
	DecorationType decorationType;

public:
	CustomWinterDecoration(DecorationType type, Position position);
	static void loadDecorationImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //CustomWinterDecoration_H