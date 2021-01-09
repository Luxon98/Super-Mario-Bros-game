#ifndef Creature_H
#define Creature_H

#include <array>
#include "IndependentMovingObject.h"

enum class Direction;
struct SDL_Surface;


// name in the original game: 'Goomba'
class Creature : public IndependentMovingObject
{
private:
	static std::array<SDL_Surface*, 8> creatureImages; 
	int model;
	void changeModel();
	int computeBaseIndex() const;
	int computeImageIndex() const override;

public:
	Creature(Position position);
	static void loadCreatureImages(SDL_Surface* display);
	int getPointsForCrushing() const override;
	int getPointsForDestroying() const override;
	bool shouldStartMoving(const Player &player) const override;
	bool isResistantToCollisionWithShell() const override;
	bool isResistantToCollisionWithBlock() const override;
	void startMoving() override;
	void crush(World &world, int index) override;
	void destroy(World &world, Direction direction) override;
	void move(World &world) override;
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif //Creature_H