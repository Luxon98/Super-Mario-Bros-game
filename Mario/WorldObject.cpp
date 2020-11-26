#include "WorldObject.h"

#include "Position.h"


int WorldObject::getX() const
{
	return position.getX();
}

int WorldObject::getY() const
{
	return position.getY();
}

int WorldObject::getWidth() const
{
	return size.getWidth();
}

int WorldObject::getHeight() const
{
	return size.getHeight();
}

Position WorldObject::getPosition() const
{
	return position;
}