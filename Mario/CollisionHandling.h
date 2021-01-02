#ifndef CollisionHandling_H
#define CollisionHandling_H

class World;
class Player;
class WorldObject;
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

bool isMonsterStandingOnBlock(const IndependentLivingObject &monster, const Block &block);

bool isBonusStandingOnBlock(const BonusObject &bonus, const Block &block);

bool isBlockBlockedByAnother(const Block &block, const World &world);

bool isPlayerCloseToFireRocket(const FireMissle &fireRocket, const World &world);

bool isPlayerCloseToPlant(const Plant &plant, const World &world);

bool isPlayerAheadOfMonster(const IndependentLivingObject &monster, const World &world);

bool isPlayerStandingOnThisPlatform(const Player &player, const Platform &platform);

bool isPlayerJumpingOnMonster(const Player &player, const IndependentLivingObject &monster);

void handleMonsterDestroying(IndependentLivingObject &npc, World &world, Player &player, Direction direction);

void handleMonsterDeleting(World &world, int index, bool bossFlag = false);

void handleMonsterHpReducing(IndependentLivingObject &npc, World &world, Player &player, int index);

void handleFireBallDeleting(const FireBall &fireball, World &world, int index);

void handleJumpingOnMonster(IndependentLivingObject &npc, World &world, Player &player, int index);

void handlePlayerAndMonsterCollision(IndependentLivingObject &npc, World &world, Player &player, int index);

void handleCollisionsWithMonsters(Player &player, World &world);

void handleCollisionsWithFireSerpents(Player &player, World &world);

void handlePlayerCollisions(Player &player, World &world);

void handleShellsAndMonstersCollisions(World &world, Player &player);

void handleFireBallsAndMonstersCollisions(World &world, Player &player);

void handleBlockAndMonstersCollisions(World &world, const Block &block, Player &player);

void handleBlockAndBonusesCollisions(World &world, const Block &block, Player &player);

void handleBlockCollisions(World &world, const Block &block, Player &player);

void handleBonusesCollecting(Player &player, World &world);

int getAlignmentForCollisionFromRight(int dist, const WorldObject &obj, const Block &block, const World &world);

int getHorizontalAlignmentForCollisionWithBlocks(Direction dir, int dist, const WorldObject &obj, const World &world);

int getHorizontalAlignmentForCollisionWithPlatforms(Direction dir, int dist, const WorldObject &obj, const World &world);

int computeHorizontalAlignment(Direction dir, int dist, const WorldObject &obj, const World &world);

// this method additionaly set the last touched block's index
int getVerticalAlignmentForCollisionWithBlocks(Direction dir, int dist, const WorldObject &obj, World &world);

// this method additionaly set the last touched block's index to -1
int getVerticalAlignmentForCollisionWithPlatforms(Direction dir, int dist, const WorldObject &obj, World &world);

int computeVerticalAlignment(Direction dir, int dist, const WorldObject &obj, World &world);

#endif //CollisionHandling_H