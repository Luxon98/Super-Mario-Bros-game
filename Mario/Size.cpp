#include "Size.h"


Size::Size(int width, int height) : width(width), height(height) {}

int Size::getWidth() const
{
	return width;
}

int Size::getHeight() const
{
	return height;
}

void Size::setWidth(int width)
{
	this->width = width;
}

void Size::setHeight(int height)
{
	this->height = height;
}

void Size::setSize(int width, int height)
{
	this->width = width;
	this->height = height;
}