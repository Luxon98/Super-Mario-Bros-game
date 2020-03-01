#ifndef _AnimatedText_H
#define _AnimatedText_H

#include "SDL_Interface.h"
#include "TemporaryObject.h"


enum TextType {
	ONE_HUNDRED = 1,
	TWO_HUNDRED = 2,
	FOUR_HUNDRED = 3,
	ONE_THOUSAND = 4,
	ONE_UP = 5
};


class AnimatedText : public TemporaryObject {
private:
	static SDL_Surface* animatedTextImages[5];
	TextType type;
	int auxiliaryCounter;

public:
	AnimatedText();
	AnimatedText(TextType type, int x, int y);
	void loadAnimatedTextImages(SDL_Surface* screen);
	void draw(SDL_Surface* screen, int beginningOfCamera) override;
	bool shouldBeRemoved() override;
	void slide() override;
};

#endif
