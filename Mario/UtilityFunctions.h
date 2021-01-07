#ifndef UtilityFunctions_H
#define UtilityFunctions_H

class WorldObject;
class MovingObject;
class IndependentMovingObject;
class Block;
class Player;
class Camera;
enum class Direction;


bool isDifferenceInInterval(int difference, int begin, int shift, int repetitions);

bool areAtTheSameWidth(const WorldObject &firstObject, const WorldObject &secondObject);

bool areAtTheSameHeight(const WorldObject &firstObject, const WorldObject &secondObject);

bool areColliding(const WorldObject &firstObject, const WorldObject &secondObject);

bool isElementDirectlyAboveObject(const WorldObject &element, const WorldObject &object);

bool isNpcCloseAboveBlock(const IndependentMovingObject &npc, const Block &block);

bool isInactiveShell(IndependentMovingObject &npc);

bool isObjectOutsideCamera(MovingObject &object, const Camera &camera);

int determineShift(const MovingObject &object, int base);

int determineShift(Direction direction, int base);

Direction determineDirection(const WorldObject &firstObject, const WorldObject &secondObject);

Direction determineDirection(const Player &player);

#endif //UtilityFunctions_H