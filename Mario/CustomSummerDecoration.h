#ifndef CustomSummerDecoration_H
#define CustomSummerDecoration_H

#include <array>
#include "InanimateObject.h"

class Position;
struct SDL_Surface;


// these enum and class are responsible for background elements that are not from the original game
// graphics in this class were created to embellish a custom Summer World

enum class SummerDecorationType
{
	PALM = 1,
	FENCE = 2
};


class CustomSummerDecoration : public InanimateObject
{
private:
	static std::array<SDL_Surface*, 2> decorationImages;
	SummerDecorationType decorationType;

public:
	CustomSummerDecoration(SummerDecorationType type, Position position);
	static void loadDecorationImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //CustomSummerDecoration_H