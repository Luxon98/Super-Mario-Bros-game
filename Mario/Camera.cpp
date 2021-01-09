#include "Camera.h"


int Camera::CAMERA_REFERENCE_POINT = 320;

Camera::Camera(int begX, int endX)
{
	beginningOfCamera = begX;
	endOfCamera = endX;
	CAMERA_REFERENCE_POINT = 320;
}

int Camera::getReferencePoint() const
{
	return CAMERA_REFERENCE_POINT;
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

void Camera::disableCameraMoving()
{
	CAMERA_REFERENCE_POINT = 0;
}

void Camera::enableCameraMoving()
{
	CAMERA_REFERENCE_POINT = 320;
}