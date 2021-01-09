#include "DestroyedTurtle.h"

#include "SDL_Utility.h"
#include "World.h"
#include "LayoutStyle.h"
#include "UtilityFunctions.h"


std::array<SDL_Surface*, 3> DestroyedTurtle::destroyedTurtleImages;

int DestroyedTurtle::computeImageIndex() const
{
	if (!red) {
		return (World::LAYOUT_STYLE == LayoutStyle::OpenWorld ? 0 : 1);
	}
	else {
		return 2;
	}
}

DestroyedTurtle::DestroyedTurtle(Position position, Direction direction, bool red)
{
	this->position = position;
	this->direction = direction;
	this->red = red;
	auxiliaryCounter = 0;
	size = Size(32, 28);
}

void DestroyedTurtle::loadDestroyedTurtleImages(SDL_Surface* display)
{
	for (std::size_t i = 0; i < destroyedTurtleImages.size(); ++i) {
		std::string filename = "./img/temp_imgs/destroyed_turtle";
		filename += std::to_string(i + 1);
		filename += ".png";
		destroyedTurtleImages[i] = loadPNG(filename, display);
	}
}

void DestroyedTurtle::slide()
{
	++auxiliaryCounter;
	int shift = determineShift(direction, 2);

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
			if (auxiliaryCounter % 3 == 0) {
				position.setX(position.getX() + shift);
			}
		}
	}
}

void DestroyedTurtle::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (isWithinRangeOfCamera(beginningOfCamera, endOfCamera)) {
		SDL_Surface* dtImg = destroyedTurtleImages[computeImageIndex()];
		drawSurface(display, dtImg, position.getX() - beginningOfCamera, position.getY());
	}
}