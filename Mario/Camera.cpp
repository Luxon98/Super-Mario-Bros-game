#include "Camera.h"


Camera::Camera(int begX, int endX)
{
	beginningOfCamera = begX;
	endOfCamera = endX;
}

int Camera::getBeginningOfCamera() const
{
	return beginningOfCamera;
}

int Camera::getEndOfCamera() const
{
	return endOfCamera;
}

void Camera::setBeginningOfCamera(int begX)
{
	beginningOfCamera = begX;
}

void Camera::setEndOfCamera(int endX)
{
	endOfCamera = endX;
}
