#include "AnimatedCoin.h"

#include <string>
#include "Position.h"
#include "SDL_Utility.h"


std::array<SDL_Surface*, 7> AnimatedCoin::animatedCoinImages;

AnimatedCoin::AnimatedCoin(Position position)
{
	creationTime = std::chrono::steady_clock::now();
	this->position = position;
	slideCounter = 0;
	auxiliaryCounter = 0;
	imageIndex = 0;
}

void AnimatedCoin::loadAnimatedCoinImages(SDL_Surface* display)
{
	for (std::size_t i = 0; i < animatedCoinImages.size(); ++i) {
		std::string filename = "./img/a_coin";
		filename += std::to_string(i + 1);
		filename += ".png";
		animatedCoinImages[i] = loadPNG(filename, display);
	}
}

void AnimatedCoin::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 60 && position.getX() < endOfCamera + 60) {
		SDL_Surface* animatedCoinImg = animatedCoinImages[imageIndex];
		drawSurface(display, animatedCoinImg, position.getX() - beginningOfCamera, position.getY());
	}
}

bool AnimatedCoin::shouldBeRemoved() const
{ 
	return (slideCounter > 57); 
}

void AnimatedCoin::slide()
{
	++slideCounter;
	++auxiliaryCounter;
	if (auxiliaryCounter & 1) {
		if (slideCounter <= 3) {
			imageIndex = 0;
		}
		else if (slideCounter <= 13) {
			position.setY(position.getY() - 2);
			imageIndex = 1;
		}
		else if (slideCounter <= 23) {
			position.setY(position.getY() - 1);
			imageIndex = 2;
		}
		else if (slideCounter <= 25) {
			imageIndex = 3;
		}
		else if (slideCounter <= 35) {
			position.setY(position.getY() + 1);
			imageIndex = 4;
		}
		else if (slideCounter <= 45) {
			position.setY(position.getY() + 2);
			imageIndex = 5;
		}
		else if (slideCounter <= 55) {
			imageIndex = 6;
		}
	}
}
