#include "AnimatedCoin.h"

#include "SDL_Utility.h"


std::array<SDL_Surface*, 7> AnimatedCoin::animatedCoinImages;

int AnimatedCoin::computeImageIndex() const
{
	// this inherited function is not really needed in this class, but I left it to keep the code simple
	return imageIndex;
}

AnimatedCoin::AnimatedCoin(Position position)
{
	this->position = position;
	auxiliaryCounter = 0;
	imageIndex = 0;
	size = Size(16, 28);
}

void AnimatedCoin::loadAnimatedCoinImages(SDL_Surface* display)
{
	for (std::size_t i = 0; i < animatedCoinImages.size(); ++i) {
		std::string filename = "./img/temp_imgs/a_coin";
		filename += std::to_string(i + 1);
		filename += ".png";
		animatedCoinImages[i] = loadPNG(filename, display);
	}
}

bool AnimatedCoin::shouldBeRemoved() const
{ 
	return (auxiliaryCounter > 96);
}

bool AnimatedCoin::isAnimatedCoin() const
{
	return true;
}

void AnimatedCoin::slide()
{
	++auxiliaryCounter;
	if (auxiliaryCounter & 1) {
		if (auxiliaryCounter <= 8) {
			imageIndex = 0;
		}
		else if (auxiliaryCounter <= 24) {
			position.setY(position.getY() - 3);
			imageIndex = 1;
		}
		else if (auxiliaryCounter <= 48) {
			position.setY(position.getY() - 2);
			imageIndex = 2;
		}
		else if (auxiliaryCounter <= 58) {
			imageIndex = 3;
		}
		else if (auxiliaryCounter <= 72) {
			position.setY(position.getY() + 2);
			imageIndex = 4;
		}
		else if (auxiliaryCounter <= 88) {
			position.setY(position.getY() + 3);
			imageIndex = 5;
		}
		else if (auxiliaryCounter <= 96) {
			imageIndex = 6;
		}
	}
}

void AnimatedCoin::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (isWithinRangeOfCamera(beginningOfCamera, endOfCamera)) {
		SDL_Surface* animatedCoinImg = animatedCoinImages[computeImageIndex()];
		drawSurface(display, animatedCoinImg, position.getX() - beginningOfCamera, position.getY());
	}
}