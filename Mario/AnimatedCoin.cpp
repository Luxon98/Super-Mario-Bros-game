#include "AnimatedCoin.h"

#include <string>
#include "Position.h"
#include "SDL_Utility.h"


std::array<SDL_Surface*, 7> AnimatedCoin::animatedCoinImages;

int AnimatedCoin::computeImageIndex() const
{
	// this inherited function is not really needed in this class, but I left it to keep the code simple
	return imageIndex;
}

AnimatedCoin::AnimatedCoin(Position position)
{
	creationTime = std::chrono::steady_clock::now();
	this->position = position;
	size = Size(16, 28);
	slideCounter = 0;
	auxiliaryCounter = 0;
	imageIndex = 0;
}

void AnimatedCoin::loadAnimatedCoinImages(SDL_Surface* display)
{
	for (std::size_t i = 0; i < animatedCoinImages.size(); ++i) {
		std::string filename = "./img/anm_imgs/a_coin";
		filename += std::to_string(i + 1);
		filename += ".png";
		animatedCoinImages[i] = loadPNG(filename, display);
	}
}

void AnimatedCoin::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (isWithinRangeOfCamera(beginningOfCamera, endOfCamera)) {
		SDL_Surface* animatedCoinImg = animatedCoinImages[computeImageIndex()];
		drawSurface(display, animatedCoinImg, position.getX() - beginningOfCamera, position.getY());
	}
}

bool AnimatedCoin::shouldBeRemoved() const
{ 
	return (slideCounter > 96); 
}

void AnimatedCoin::slide()
{
	++slideCounter;
	++auxiliaryCounter;
	if (auxiliaryCounter & 1) {
		if (slideCounter <= 8) {
			imageIndex = 0;
		}
		else if (slideCounter <= 24) {
			position.setY(position.getY() - 3);
			imageIndex = 1;
		}
		else if (slideCounter <= 48) {
			position.setY(position.getY() - 2);
			imageIndex = 2;
		}
		else if (slideCounter <= 58) {
			imageIndex = 3;
		}
		else if (slideCounter <= 72) {
			position.setY(position.getY() + 2);
			imageIndex = 4;
		}
		else if (slideCounter <= 88) {
			position.setY(position.getY() + 3);
			imageIndex = 5;
		}
		else if (slideCounter <= 96) {
			imageIndex = 6;
		}
	}
}
