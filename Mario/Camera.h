#ifndef Camera_H
#define Camera_H


class Camera
{
private:
	int beginningOfCamera;
	int endOfCamera;
	static int CAMERA_REFERENCE_POINT;

public:
	Camera(int begX, int endX);
	int getReferencePoint() const;
	int getBeginningOfCamera() const;
	int getEndOfCamera() const;
	void setBeginningOfCamera(int begX);
	void setEndOfCamera(int endX);
	static void disableCameraMoving();
	static void enableCameraMoving();
};

#endif //Camera_H