#ifndef AnimatedText_H
#define AnimatedText_H

#include <array>
#include "TemporaryObject.h"

class Position;
struct SDL_Surface;


enum class TextType
{
	ONE_HUNDRED = 1,
	TWO_HUNDRED = 2,
	FOUR_HUNDRED = 3,
	ONE_THOUSAND = 4,
	FIVE_THOUSAND = 5,
	ONE_UP = 6
};


class AnimatedText : public TemporaryObject 
{
private:
	static std::array<SDL_Surface*, 6> animatedTextImages;
	TextType type;
	int computeImageIndex() const override;

public:
	AnimatedText(TextType type, Position position);
	static void loadAnimatedTextImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	bool shouldBeRemoved() const override;
	void slide() override;
};

#endif //AnimatedText_H
