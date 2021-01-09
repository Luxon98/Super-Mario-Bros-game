#ifndef Cloud_H
#define Cloud_H

#include <array>
#include "InanimateObject.h"

struct SDL_Surface;


class Cloud : public InanimateObject
{
private:
	static std::array<SDL_Surface*, 3> cloudImages;
	Size getSizeFromModel() const;

public:
	Cloud(int type, Position position);
	static void loadCloudImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //Cloud_H