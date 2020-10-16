#ifndef Camera_H
#define Camera_H


class Camera
{
private:
	int beginningOfCamera;
	int endOfCamera;

public:
	static constexpr int CAMERA_REFERENCE_POINT = 320;
	Camera() = default;
	Camera(int begX, int endX);
	int getBeginningOfCamera() const;
	int getEndOfCamera() const;
	void setBeginningOfCamera(int begX);
	void setEndOfCamera(int endX);
};

#endif //Camera_H

