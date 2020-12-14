#ifndef CustomWinterDecoration_H
#define CustomWinterDecoration_H

#include <array>
#include "InanimateObject.h"

class Position;
struct SDL_Surface;


// these enum and class are responsible for background elements that are not from the original game
// graphics in this class were created to embellish a custom Winter World

enum class WinterDecorationType
{
	YELLOW_STAR = 1,
	GOLDEN_STAR = 2,
	WHITE_STAR = 3,
	CHRISTMAS_TREE = 4,
	SMALL_WINTER_CLOUD = 5,
	WINTER_CLOUD = 6,
	MOON = 7,
	SIGNPOST = 8,
	SECOND_SIGNPOST = 9
};


class CustomWinterDecoration : public InanimateObject
{
private:
	static std::array<SDL_Surface*, 9> decorationImages;
	WinterDecorationType decorationType;

public:
	CustomWinterDecoration(WinterDecorationType type, Position position);
	static void loadDecorationImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //CustomWinterDecoration_H