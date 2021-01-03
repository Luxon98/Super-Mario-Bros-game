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
	BLUE_STAR = 4,
	CHRISTMAS_TREE = 5,
	SMALL_WINTER_CLOUD = 6,
	WINTER_CLOUD = 7,
	MOON = 8,
	SIGNPOST = 9,
	SECOND_SIGNPOST = 10
};


class CustomWinterDecoration : public InanimateObject
{
private:
	static std::array<SDL_Surface*, 10> decorationImages;
	WinterDecorationType decorationType;
	Size getSizeFromDecorationType() const;

public:
	CustomWinterDecoration(WinterDecorationType type, Position position);
	static void loadDecorationImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //CustomWinterDecoration_H