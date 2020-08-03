#include "AnimatedText.h"

SDL_Surface* AnimatedText::animatedTextImages[5] = { nullptr };

AnimatedText::AnimatedText() {}

AnimatedText::AnimatedText(TextType type, Position* position)
{
	this->type = type;
	this->position = position;
	this->auxiliaryCounter = 0;
}

void AnimatedText::loadAnimatedTextImages(SDL_Surface* screen)
{
	this->animatedTextImages[0] = loadPNG("./img/100.png", screen);
	this->animatedTextImages[1] = loadPNG("./img/200.png", screen);
	this->animatedTextImages[2] = loadPNG("./img/400.png", screen);
	this->animatedTextImages[3] = loadPNG("./img/1000.png", screen);
	this->animatedTextImages[4] = loadPNG("./img/1UP.png", screen);
}

void AnimatedText::draw(SDL_Surface* screen, int beginningOfCamera)
{
	SDL_Surface* animatedTextImg = this->animatedTextImages[this->type - 1];
	drawSurface(screen, animatedTextImg, this->position->getX() - beginningOfCamera, this->position->getY());
}

bool AnimatedText::shouldBeRemoved()
{
	std::chrono::steady_clock::time_point timePoint = std::chrono::steady_clock::now();
	return (this->auxiliaryCounter > 150);
}

void AnimatedText::slide()
{
	this->auxiliaryCounter++;
	if (this->auxiliaryCounter % 3 == 0) {
		this->position->setY(this->position->getY() - 1);
	}
}

