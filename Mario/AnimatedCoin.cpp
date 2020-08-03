#include "AnimatedCoin.h"

SDL_Surface* AnimatedCoin::animatedCoinImages[7] = { nullptr };

AnimatedCoin::AnimatedCoin() {}

AnimatedCoin::AnimatedCoin(Position* position)
{
	this->creationTime = std::chrono::steady_clock::now();
	this->position = position;
	this->slideCounter = 0;
	this->auxiliaryCounter = 0;
	this->imageIndex = 0;
}

void AnimatedCoin::loadAnimatedCoinImages(SDL_Surface* screen)
{
	for (int i = 0; i < 7; ++i) {
		std::string filename = "./img/a_coin";
		filename += std::to_string(i + 1);
		filename += ".png";
		this->animatedCoinImages[i] = loadPNG(filename, screen);
	}
}

void AnimatedCoin::draw(SDL_Surface* screen, int beginningOfCamera)
{
	SDL_Surface* animatedCoinImg = this->animatedCoinImages[this->imageIndex];
	drawSurface(screen, animatedCoinImg,
		this->position->getX() - beginningOfCamera,
		this->position->getY());
}

bool AnimatedCoin::shouldBeRemoved() { return (this->slideCounter > 57); }

void AnimatedCoin::slide()
{
	this->slideCounter++;
	this->auxiliaryCounter++;
	if (this->auxiliaryCounter & 1) {
		if (this->slideCounter <= 3) {
			this->imageIndex = 0;
		}
		else if (this->slideCounter <= 13) {
			this->position->setY(this->position->getY() - 2);
			this->imageIndex = 1;
		}
		else if (this->slideCounter <= 23) {
			this->position->setY(this->position->getY() - 1);
			this->imageIndex = 2;
		}
		else if (this->slideCounter <= 25) {
			this->imageIndex = 3;
		}
		else if (this->slideCounter <= 35) {
			this->position->setY(this->position->getY() + 1);
			this->imageIndex = 4;
		}
		else if (this->slideCounter <= 45) {
			this->position->setY(this->position->getY() + 2);
			this->imageIndex = 5;
		}
		else if (this->slideCounter <= 55) {
			this->imageIndex = 6;
		}
	}
}
