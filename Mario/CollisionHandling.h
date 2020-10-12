#ifndef CollisionHandling_H
#define CollisionHandling_H

class World;
class Player;
class WorldObject;
class LivingObject;
class Mushroom;
class Block;
class Plant;
enum class Direction;


bool isCharacterHittingBlock(const WorldObject &object, const Block &block, Direction direction, int distance);

bool isCharacterStandingOnTheBlock(const WorldObject &object, const World &world);

bool isMonsterStandingOnTheBlock(const LivingObject &object, const Block &block);

bool isMushroomStandingOnTheBlock(const World &world, int index);

bool isPlayerCloseToPlant(const Plant &plant, const World &world);

bool isBlockBlockedByAnother(const Block &block, const World& world);

bool areAtTheSameWidth(const WorldObject &firstObject, const WorldObject &secondObject);

bool areAtTheSameHeight(const WorldObject &firstObject, const WorldObject &secondObject);

bool isPlayerJumpingOnMonster(const Player &player, const LivingObject &monster);

void handlePlayerCollisions(Player &player, World &world);

void handleShellsAndMonstersCollisions(World &world, Player &player);

void handleFireBallsAndMonstersCollisions(World &world, Player &player);

void handleMonstersAndBlockCollisions(World &world, const Block &block, Player &player);

void collectCoinIfPossible(Player &player, World &world);

void collectMushroom(Mushroom &mushroom, int index, Player &player, World &world);

void collectFlower(Player &player, World &world);

void collectStar(Player &player, World &world);

void collectBonusIfPossible(Player &player, World &world);

int getAlignmentForHorizontalMove(Direction direction, int distance, const WorldObject &object, const World &world);

// this method additionaly set the last touched block
int getAlignmentForVerticalMove(Direction direction, int distance, const WorldObject &object, World &world);

#endif //CollisionHandling_H