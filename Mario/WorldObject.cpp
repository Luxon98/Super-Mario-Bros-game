#include "WorldObject.h"


bool WorldObject::isWithinRangeOfCamera(int beginningOfCamera, int endOfCamera) const
{
	if ((position.getX() >= beginningOfCamera - size.getWidth() / 2) && (position.getX() <= endOfCamera 
		+ size.getWidth() / 2) && (position.getY() >= -30 && position.getY() <= 530)) {

		return true;
	}

	return false;
}

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