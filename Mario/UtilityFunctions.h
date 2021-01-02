#ifndef UtilityFunctions_H
#define UtilityFunctions_H

class WorldObject;
class IndependentLivingObject;
class Block;
class Player;
enum class Direction;


bool isDifferenceInInterval(int difference, int begin, int shift, int repetitions);

bool areAtTheSameWidth(const WorldObject &firstObject, const WorldObject &secondObject);

bool areAtTheSameHeight(const WorldObject &firstObject, const WorldObject &secondObject);

bool areColliding(const WorldObject &firstObject, const WorldObject &secondObject);

bool isElementDirectlyAboveObject(const WorldObject &element, const WorldObject &object);

bool isMonsterCloseAboveBlock(const IndependentLivingObject &monster, const Block &block);

bool isInactiveShell(IndependentLivingObject &npc);

int determineShift(const IndependentLivingObject &object, int base);

int determineShift(Direction direction, int base);

Direction determineDirection(const WorldObject &firstObject, const WorldObject &secondObject);

Direction determineDirection(const Player &player);

#endif //UtilityFunctions_H