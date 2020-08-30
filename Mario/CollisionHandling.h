#ifndef CollisionHandling_H
#define CollisionHandling_H

class World;
class Player;
class WorldObject;
class LivingObject;
class Mushroom;
class Block;
enum Direction;


bool isCharacterHittingBlock(WorldObject* object, Block block, Direction direction, int distance);

bool isCharacterStandingOnTheBlock(WorldObject* object, World& world);

bool isMonsterStandingOnTheBlock(LivingObject* object, Block block);

bool isFlowerStandingOnTheBlock(World& world, int index);

bool isMushroomStandingOnTheBlock(World& world, int index);

bool areAtTheSameWidth(WorldObject* object, Block block);

bool areAtTheSameHeight(WorldObject* object, Block block); 

bool areAtTheSameWidth(WorldObject* firstObject, WorldObject* secondObject);

bool areAtTheSameHeight(WorldObject* firstObject, WorldObject* secondObject);

bool isPlayerJumpingOnMonster(Player* player, LivingObject* monster);

void handlePlayerCollisions(Player* player, World& world);

void handleShellsAndMonstersCollisions(World& world, Player* player);

void handleFireBallsAndMonstersCollisions(World& world, Player* player);

void handleMonstersAndBlockCollisions(World& world, Block block, Player* player);

void collectCoinIfPossible(Player* player, World& world);

void collectMushroom(Mushroom* mushroom, int index, Player* player, World& world);

void collectFlower(Player* player, World& world);

void collectStar(Player* player, World& world);

void collectBonusIfPossible(Player* player, World& world);

int getAlignmentForHorizontalMove(Direction direction, int distance, WorldObject* object, World& world);

// this method additionaly set the last touched block
int getAlignmentForVerticalMove(Direction direction, int distance, WorldObject* object, World& world);

#endif //CollisionHandling_H
