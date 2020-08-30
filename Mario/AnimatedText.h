#ifndef AnimatedText_H
#define AnimatedText_H

#include <array>
#include "TemporaryObject.h"

class Position;
struct SDL_Surface;

enum TextType
{
	ONE_HUNDRED = 1,
	TWO_HUNDRED = 2,
	FOUR_HUNDRED = 3,
	ONE_THOUSAND = 4,
	ONE_UP = 5
};


class AnimatedText : public TemporaryObject 
{
private:
	static std::array<SDL_Surface*, 5> animatedTextImages;
	TextType type;

public:
	AnimatedText();
	AnimatedText(TextType type, Position position);
	void loadAnimatedTextImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) override;
	bool shouldBeRemoved() override;
	void slide() override;
};

#endif //AnimatedText_H
