#include "Position.h"

Position::Position(int x, int y)
{
	this->x = x;
	this->y = y;
}

int Position::getX() const
{
	return this->x;
}

int Position::getY() const
{
	return this->y;
}

void Position::setX(int x)
{
	this->x = x;
}

void Position::setY(int y)
{
	this->y = y;
}

void Position::setXY(int x, int y)
{
	this->x = x;
	this->y = y;
}
