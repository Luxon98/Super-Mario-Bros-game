#ifndef AnimatedCoin_H
#define AnimatedCoin_H

#include <array>
#include "TemporaryObject.h"

class Position;
struct SDL_Surface;


class AnimatedCoin : public TemporaryObject 
{
private:
	static std::array<SDL_Surface*, 7> animatedCoinImages;
	int slideCounter;
	int imageIndex;

public:
	AnimatedCoin() = default;
	AnimatedCoin(Position position);
	void loadAnimatedCoinImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) override;
	bool shouldBeRemoved() override;
	void slide() override;
};

#endif //AnimatedCoin_H

