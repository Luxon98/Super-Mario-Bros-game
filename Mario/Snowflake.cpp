#include "Snowflake.h"

#include "Position.h"
#include "SDL_Utility.h"


SDL_Surface* Snowflake::snowflakeImage = nullptr;

int Snowflake::computeImageIndex() const
{
	// this inherited function is not really needed in this class, but I left it to keep the code simple
	return 0;
}

Snowflake::Snowflake(Position position)
{
	creationTime = std::chrono::steady_clock::now();
	this->position = position;
	initialPositionX = position.getX();
	auxiliaryCounter = 0;
	size = Size(4, 4);
}

void Snowflake::loadSnowflakeImage(SDL_Surface* display)
{
	snowflakeImage = loadPNG("./img/anm_imgs/snowflake.png", display);
}

void Snowflake::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (isWithinRangeOfCamera(beginningOfCamera, endOfCamera)) {
		drawSurface(display, snowflakeImage, position.getX() - beginningOfCamera, position.getY());
	}
}

bool Snowflake::shouldBeRemoved() const
{
	return false;
}

void Snowflake::slide()
{
	++auxiliaryCounter;
	if (auxiliaryCounter % 3 == 0) {
		position.setY(position.getY() + 1);

		if (position.getY() == 480) {
			position.setY(0);
			position.setX(initialPositionX);
		}
	}
	else if (auxiliaryCounter % 5 == 0) {
		position.setX(position.getX() - 1);
	}
}