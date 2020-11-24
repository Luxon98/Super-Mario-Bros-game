#ifndef DestroyedBoss_H
#define DestroyedBoss_H

#include <array>
#include "TemporaryObject.h"

class DestroyedBoss : public TemporaryObject
{
private:
	static std::array<SDL_Surface*, 3> destroyedBossImages;
	bool normal;
	int computeImageIndex() const override;

public:
	DestroyedBoss(Position position, bool normal = true);
	static void loadDestroyedBossImages(SDL_Surface * display);
	void draw(SDL_Surface * display, int beginningOfCamera, int endOfCamera) const override;
	bool shouldBeRemoved() const override;
	void slide() override;
};

#endif //DestroyedBoss_H