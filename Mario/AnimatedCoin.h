#ifndef _AnimatedCoin_H
#define _AnimatedCoin_H

#include <string>
#include "SDL_Interface.h"
#include "TemporaryObject.h"


class AnimatedCoin : public TemporaryObject {
private:
	static SDL_Surface* animatedCoinImages[7];
	int slideCounter;
	int auxiliaryCounter;
	int imageIndex;

public:
	AnimatedCoin();
	AnimatedCoin(int x, int y);
	void loadAnimatedCoinImages(SDL_Surface* screen);
	void draw(SDL_Surface* screen, int beginningOfCamera) override;
	bool shouldBeRemoved() override;
	void slide() override;
};

#endif

