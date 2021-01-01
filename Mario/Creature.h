#ifndef Creature_H
#define Creature_H

#include <array>
#include "IndependentLivingObject.h"

class World;
class Position;
enum class Direction;
struct SDL_Surface;


// this class is the counterpart of NPC, which in the original Mario series was called 'Goomba'
class Creature : public IndependentLivingObject
{
private:
	static std::array<SDL_Surface*, 8> creatureImages; 
	int model;
	int computeBaseIndex() const;
	int computeImageIndex() const override;
	void changeModel();

public:
	Creature(Position position);
	static void loadCreatureImages(SDL_Surface* display);
	int getPointsForCrushing() const override;
	int getPointsForDestroying() const override;
	bool isMonsterResistantToCollisionWithShell() const override;
	void setMoveDirection(Direction direction);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
	void move(World &world) override;
	void crush(World &world, int index) override;
	void destroy(World &world, Direction direction) override;
};

#endif //Creature_H