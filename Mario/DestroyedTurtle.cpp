#include "DestroyedTurtle.h"

#include "Position.h"
#include "SDL_Utility.h"
#include "World.h"
#include "LayoutStyle.h"


std::array<SDL_Surface*, 3> DestroyedTurtle::destroyedTurtleImages;

int DestroyedTurtle::computeIndex() const
{
	if (!red) {
		return (World::LAYOUT_STYLE == LayoutStyle::OpenWorld ? 0 : 1);
	}
	else {
		return 2;
	}
}

DestroyedTurtle::DestroyedTurtle(Position position, Direction slideDirection, bool red)
{
	this->position = position;
	this->slideDirection = slideDirection;
	this->red = red;
	creationTime = std::chrono::steady_clock::now();
	auxiliaryCounter = 0;
}

void DestroyedTurtle::loadDestroyedTurtleImage(SDL_Surface* display)
{
	for (std::size_t i = 0; i < destroyedTurtleImages.size(); ++i) {
		std::string filename = "./img/destroyed_turtle";
		filename += std::to_string(i + 1);
		filename += ".png";
		destroyedTurtleImages[i] = loadPNG(filename, display);
	}
}

void DestroyedTurtle::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (position.getX() > beginningOfCamera - 70 && position.getX() < endOfCamera + 70) {
		SDL_Surface* dtImg = nullptr;
		dtImg = destroyedTurtleImages[computeIndex()];
		drawSurface(display, dtImg, position.getX() - beginningOfCamera, position.getY());
	}
}

bool DestroyedTurtle::shouldBeRemoved() const
{
	auto timePoint = std::chrono::steady_clock::now();
	return (creationTime + std::chrono::milliseconds(2000) < timePoint);
}

void DestroyedTurtle::slide()
{
	++auxiliaryCounter;

	int shift = (slideDirection == Direction::Left ? -2 : 2);

	if (auxiliaryCounter & 1) {
		if (auxiliaryCounter <= 12) {
			position.setY(position.getY() - 2);
		}
		else if (auxiliaryCounter >= 13 && auxiliaryCounter <= 24) {
			position.setX(position.getX() + shift);
			position.setY(position.getY() - 3);
		}
		else if (auxiliaryCounter >= 25 && auxiliaryCounter <= 32) {
			position.setX(position.getX() + shift);
		}
		else if (auxiliaryCounter >= 33 && auxiliaryCounter <= 44) {
			position.setX(position.getX() + shift);
			position.setY(position.getY() + 2);
		}
		else {
			position.setY(position.getY() + 3);
			if (auxiliaryCounter % 6 == 0) {
				position.setX(position.getX() + shift);
			}
		}
	}
}

