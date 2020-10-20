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
	static void loadAnimatedCoinImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	bool shouldBeRemoved() const override;
	void slide() override;
};

#endif //AnimatedCoin_H

