#ifndef UtilityFunctions_H
#define UtilityFunctions_H

#include <memory>

class WorldObject;
class LivingObject;
class Block;
class Player;
enum class Direction;


bool isDifferenceInInterval(int difference, int begin, int shift, int repetitions);

bool areAtTheSameWidth(const WorldObject &firstObject, const WorldObject &secondObject);

bool areAtTheSameHeight(const WorldObject &firstObject, const WorldObject &secondObject);

bool isElementDirectlyAboveObject(const WorldObject &element, const WorldObject &object);

bool isMonsterCloseAboveBlock(const LivingObject &monster, const Block &block);

bool isMonsterResistantToKnocks(std::shared_ptr<LivingObject> monster);

bool isMonsterResistantToFireBalls(std::shared_ptr<LivingObject> monster);

bool isMonsterResistantToCollisionWithShell(std::shared_ptr<LivingObject> monster);

int determineShift(const LivingObject &object, int base);

int determineShift(Direction direction, int base);

Direction determineDirection(const WorldObject &firstObject, const WorldObject &secondObject);

Direction determineDirection(const Player &player);

#endif //UtilityFunctions_H