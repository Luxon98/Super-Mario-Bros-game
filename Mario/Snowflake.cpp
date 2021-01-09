#include "Snowflake.h"

#include "SDL_Utility.h"


SDL_Surface* Snowflake::snowflakeImage = nullptr;

Snowflake::Snowflake(Position position)
{
	this->position = position;
	initialPositionX = position.getX();
	auxiliaryCounter = 0;
	size = Size(4, 4);
}

void Snowflake::loadSnowflakeImage(SDL_Surface* display)
{
	snowflakeImage = loadPNG("./img/anm_imgs/snowflake.png", display);
}

void Snowflake::move()
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

void Snowflake::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (isWithinRangeOfCamera(beginningOfCamera, endOfCamera)) {
		drawSurface(display, snowflakeImage, position.getX() - beginningOfCamera, position.getY());
	}
}