#include "AnimatedText.h"

SDL_Surface* AnimatedText::animatedTextImages[5] = { nullptr };

AnimatedText::AnimatedText() {}

AnimatedText::AnimatedText(TextType type, Position* position)
{
	this->type = type;
	this->position = position;
	auxiliaryCounter = 0;
}

void AnimatedText::loadAnimatedTextImages(SDL_Surface* screen)
{
	animatedTextImages[0] = loadPNG("./img/100.png", screen);
	animatedTextImages[1] = loadPNG("./img/200.png", screen);
	animatedTextImages[2] = loadPNG("./img/400.png", screen);
	animatedTextImages[3] = loadPNG("./img/1000.png", screen);
	animatedTextImages[4] = loadPNG("./img/1UP.png", screen);
}

void AnimatedText::draw(SDL_Surface* screen, int beginningOfCamera)
{
	SDL_Surface* animatedTextImg = animatedTextImages[type - 1];
	drawSurface(screen, animatedTextImg, position->getX() - beginningOfCamera, position->getY());
}

bool AnimatedText::shouldBeRemoved()
{
	std::chrono::steady_clock::time_point timePoint = std::chrono::steady_clock::now();
	return (auxiliaryCounter > 150);
}

void AnimatedText::slide()
{
	auxiliaryCounter++;
	if (auxiliaryCounter % 3 == 0) {
		position->setY(position->getY() - 1);
	}
}

