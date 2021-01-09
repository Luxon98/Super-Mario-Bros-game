#ifndef JumpingFish_H
#define JumpingFish_H

#include <array>
#include "IndependentMovingObject.h"

struct SDL_Surface;


// name in the original game: 'Cheep Cheep'
class JumpingFish : public IndependentMovingObject
{
private:
	static std::array<SDL_Surface*, 4> fishImages;
	bool movingFlag;
	int model;
	Direction direction;
	void changeParametersDuringJump();
	void jump();
	void changeModel();
	int computeImageIndex() const override;

public:
	JumpingFish(Position position, Direction direction);
	static void loadFishImages(SDL_Surface* display);
	int getPointsForCrushing() const override;
	bool shouldStartMoving(const Player &player) const override;
	void startMoving() override;
	void crush(World &world, int index) override;
	void destroy(World &world, Direction direction) override;
	void move(World &world) override;
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //JumpingFish_H