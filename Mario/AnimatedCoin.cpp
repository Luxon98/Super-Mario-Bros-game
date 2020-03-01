#include "AnimatedCoin.h"

SDL_Surface* AnimatedCoin::animatedCoinImages[7] = { nullptr };

AnimatedCoin::AnimatedCoin() {}

AnimatedCoin::AnimatedCoin(int x, int y) {
	this->creationTime = std::chrono::steady_clock::now();
	this->positionX = x;
	this->positionY = y;
	this->slideCounter = 0;
	this->auxiliaryCounter = 0;
	this->imageIndex = 0;
}

void AnimatedCoin::loadAnimatedCoinImages(SDL_Surface* screen) {
	for (int i = 0; i < 7; ++i) {
		std::string filename = "./img/a_coin";
		filename += std::to_string(i + 1);
		filename += ".png";
		this->animatedCoinImages[i] = loadPNG(filename, screen);
	}
}

void AnimatedCoin::draw(SDL_Surface* screen, int beginningOfCamera) {
	SDL_Surface* animatedCoinImg = this->animatedCoinImages[this->imageIndex];
	drawSurface(screen, animatedCoinImg, this->positionX - beginningOfCamera, this->positionY);
}

bool AnimatedCoin::shouldBeRemoved() {
	return (this->slideCounter > 57);
}

void AnimatedCoin::slide() {
	++this->slideCounter;
	++this->auxiliaryCounter;
	if (this->auxiliaryCounter & 1) {
		if (this->slideCounter <= 3) {
			this->imageIndex = 0;
		}
		else if (this->slideCounter <= 13) {
			this->positionY -= 2;
			this->imageIndex = 1;
		}
		else if (this->slideCounter <= 23) {
			--this->positionY;
			this->imageIndex = 2;
		}
		else if (this->slideCounter <= 25) {
			this->imageIndex = 3;
		}
		else if (this->slideCounter <= 35) {
			++this->positionY;
			this->imageIndex = 4;
		}
		else if (this->slideCounter <= 45) {
			this->positionY += 2;
			this->imageIndex = 5;
		}
		else if (this->slideCounter <= 55) {
			this->imageIndex = 6;
		}
	}
}

