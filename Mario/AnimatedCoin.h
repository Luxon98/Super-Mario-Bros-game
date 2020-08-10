#ifndef _AnimatedCoin_H
#define _AnimatedCoin_H

#include <string>
#include "SDL_Utility.h"
#include "TemporaryObject.h"


class AnimatedCoin : public TemporaryObject 
{
private:
	static SDL_Surface* animatedCoinImages[7];
	int slideCounter;
	int auxiliaryCounter;
	int imageIndex;

public:
	AnimatedCoin();
	AnimatedCoin(Position* position);
	void loadAnimatedCoinImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera) override;
	bool shouldBeRemoved() override;
	void slide() override;
};

#endif //_AnimatedCoin_H

