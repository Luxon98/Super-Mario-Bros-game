#include "Position.h"


Position::Position(int x, int y) : x(x), y(y) {}

int Position::getX() const
{
	return x;
}

int Position::getY() const
{
	return y;
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
