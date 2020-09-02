#ifndef Cloud_H
#define Cloud_H

#include <array>
#include "InanimateObject.h"

class Position;
struct SDL_Surface;


class Cloud : public InanimateObject
{
private:
	static std::array<SDL_Surface*, 3> cloudImages;

public:
	Cloud() = default;
	Cloud(int type, Position position);
	void loadCloudImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) override;
};

#endif //Cloud_H