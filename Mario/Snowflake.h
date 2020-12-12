#ifndef Snowflake_H
#define Snowflake_H

#include "AnimatedObject.h"


class Snowflake : public AnimatedObject
{
private:
	static SDL_Surface* snowflakeImage;
	int initialPositionX;
	int computeImageIndex() const override;

public:
	Snowflake(Position position);
	static void loadSnowflakeImage(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	bool shouldBeRemoved() const override;
	void slide() override;
};

#endif //Snowflake_H