#ifndef CollisionHandling_H
#define CollisionHandling_H

#include <memory>

class World;
class Player;
class WorldObject;
class LivingObject;
class IndependentLivingObject;
class BonusObject;
class Block;
class Plant;
class FireMissle;
class Mushroom;
class Platform;
class FireBall;
enum class Direction;


bool isCharacterHittingObject(const WorldObject &figure, const WorldObject &block, Direction direction, int distance);

bool isCharacterStandingOnSomething(const WorldObject &figure, const World &world);

bool isMonsterStandingOnBlock(const LivingObject &monster, const Block &block);

bool isMushroomStandingOnBlock(const World &world, const Block &block);

bool isPlayerCloseToFireRocket(const FireMissle &fireRocket, const World &world);

bool isPlayerCloseToPlant(const Plant &plant, const World &world);

bool isPlayerAheadOfMonster(const LivingObject &monster, const World &world);

bool isPlayerStandingOnThisPlatform(const Player &player, const Platform &platform);

bool isBlockBlockedByAnother(const Block &block, const World &world);

bool isPlayerJumpingOnMonster(const Player &player, const LivingObject &monster);

bool isBonusStandingOnBlock(const BonusObject &bonus, const Block &block);

void handleJumpingOnMonster(std::shared_ptr<IndependentLivingObject> monster, World &world, Player &player, int index);

void handlePlayerAndMonstersCollisions(std::shared_ptr<IndependentLivingObject> monster, World &world, Player &player, int index);

void handleCollisionsWithMonsters(Player &player, World &world);

void handleCollisionsWithFireSerpents(Player &player, World &world);

void handlePlayerCollisions(Player &player, World &world);

void handleShellsAndMonstersCollisions(World &world, Player &player);

void handleFireBallDestruction(const FireBall &fireball, World &world, int fireballIndex);

void handleFireBallsAndMonstersCollisions(World &world, Player &player);

void handleMonsterDestruction(const Block &block, std::shared_ptr<LivingObject> monster, World &world, int * pts);

void handleBlockAndMonstersCollisions(World &world, const Block &block, Player &player);

void handleBlockAndBonusesCollisions(World &world, const Block &block, Player &player);

void handleBlockCollisions(World &world, const Block &block, Player &player);

void handleBonusesCollecting(Player &player, World &world);

int getAlignmentForCollisionFromRight(int distance, const WorldObject &object, const Block &block, const World &world);

int getHorizontalAlignmentForCollisionWithBlocks(Direction direction, int distance, const WorldObject &object, const World &world);

int getHorizontalAlignmentForCollisionWithPlatforms(Direction direction, int distance, const WorldObject &object, const World &world);

int computeHorizontalAlignment(Direction direction, int distance, const WorldObject &object, const World &world);

// this method additionaly set the last touched block's index
int getVerticalAlignmentForCollisionWithBlocks(Direction direction, int distance, const WorldObject &object, World &world);

// this method additionaly set the last touched block's index to -1
int getVerticalAlignmentForCollisionWithPlatforms(Direction direction, int distance, const WorldObject &object, World &world);

int computeVerticalAlignment(Direction direction, int distance, const WorldObject &object, World &world);

#endif //CollisionHandling_H