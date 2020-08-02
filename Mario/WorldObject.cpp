#include "WorldObject.h"

int WorldObject::getPositionX() const {
	return this->position->getX();
}

int WorldObject::getPositionY() const {
	return this->position->getY();
}

int WorldObject::getWidth() const {
	return this->width;
}

int WorldObject::getHeight() const {
	return this->height;
}
