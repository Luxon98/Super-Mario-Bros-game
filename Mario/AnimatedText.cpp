#include "AnimatedText.h"

#include "Position.h"
#include "SDL_Utility.h"


std::array<SDL_Surface*, 5> AnimatedText::animatedTextImages;

AnimatedText::AnimatedText(TextType type, Position position)
{
	this->type = type;
	this->position = position;
	auxiliaryCounter = 0;
}

void AnimatedText::loadAnimatedTextImages(SDL_Surface* display)
{
	animatedTextImages[0] = loadPNG("./img/100.png", display);
	animatedTextImages[1] = loadPNG("./img/200.png", display);
	animatedTextImages[2] = loadPNG("./img/400.png", display);
	animatedTextImages[3] = loadPNG("./img/1000.png", display);
	animatedTextImages[4] = loadPNG("./img/1UP.png", display);
}

void AnimatedText::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 60 && position.getX() < endOfCamera + 60) {
		SDL_Surface* animatedTextImg = animatedTextImages[static_cast<int>(type) - 1];
		drawSurface(display, animatedTextImg, position.getX() - beginningOfCamera, position.getY());
	}
}

bool AnimatedText::shouldBeRemoved() const
{
	auto timePoint = std::chrono::steady_clock::now();
	return (auxiliaryCounter > 150);
}

void AnimatedText::slide()
{
	++auxiliaryCounter;
	if (auxiliaryCounter % 3 == 0) {
		position.setY(position.getY() - 1);
	}
}

