#ifndef UtilityFunctions_H
#define UtilityFunctions_H

class WorldObject;
class LivingObject;
class Block;
enum class Direction;


bool isDifferenceInInterval(int difference, int begin, int shift, int repetitions);

bool areAtTheSameWidth(const WorldObject &firstObject, const WorldObject &secondObject);

bool areAtTheSameHeight(const WorldObject &firstObject, const WorldObject &secondObject);

bool isElementDirectlyAboveObject(const WorldObject &element, const WorldObject &object);

bool isMonsterCloseAboveBlock(const LivingObject &monster, const Block &block);

Direction determineDirection(const WorldObject &firstObject, const WorldObject &secondObject);

#endif //UtilityFunctions_H