#include "WorldObject.h"

int WorldObject::getX() const {
	return this->position->getX();
}

int WorldObject::getY() const {
	return this->position->getY();
}

int WorldObject::getWidth() const {
	return this->size->getWidth();
}

int WorldObject::getHeight() const {
	return this->size->getHeight();
}
