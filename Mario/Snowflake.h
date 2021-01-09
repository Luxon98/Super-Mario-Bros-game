#ifndef Snowflake_H
#define Snowflake_H

#include "AnimatedObject.h"


class Snowflake : public AnimatedObject
{
private:
	static SDL_Surface* snowflakeImage;
	int initialPositionX;
	int auxiliaryCounter;

public:
	Snowflake(Position position);
	static void loadSnowflakeImage(SDL_Surface* display);
	void move() override;
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //Snowflake_H