#ifndef CollisionHandling_H
#define CollisionHandling_H

class World;
class Player;
class WorldObject;
class IndependentMovingObject;
class BonusObject;
class Block;
class Plant;
class FireMissle;
class Platform;
class FireBall;
enum class Direction;


bool isCharacterHittingObject(const WorldObject &object, const WorldObject &block, Direction direction, int distance);

bool isCharacterStandingOnSomething(const WorldObject &object, const World &world);

bool isNpcStandingOnBlock(const IndependentMovingObject &npc, const Block &block);

bool isBonusStandingOnBlock(const BonusObject &bonus, const Block &block);

bool isBlockBlockedByAnother(const Block &block, const World &world);

bool isPlayerCloseToFireRocket(const FireMissle &fireRocket, const World &world);

bool isPlayerCloseToPlant(const Plant &plant, const World &world);

bool isPlayerAheadOfNpc(const IndependentMovingObject &npc, const World &world);

bool isPlayerStandingOnThisPlatform(const Player &player, const Platform &platform);

bool isPlayerJumpingOnNpc(const Player &player, const IndependentMovingObject &npc);

void handleNpcDestroying(IndependentMovingObject &npc, World &world, Player &player, Direction direction);

void handleNpcDeleting(World &world, int index, bool bossFlag = false);

void handleNpcHpReducing(IndependentMovingObject &npc, World &world, Player &player, Direction direction, int index);

void handleFireBallDeleting(const FireBall &fireball, World &world, int index);

void handleJumpingOnNpc(IndependentMovingObject &npc, World &world, Player &player, int index);

void handlePlayerAndNpcCollision(IndependentMovingObject &npc, World &world, Player &player, int index);

void handleCollisionsWithNpcs(Player &player, World &world);

void handleCollisionsWithFireSerpents(Player &player, World &world);

void handlePlayerCollisions(Player &player, World &world);

void handleShellsAndNpcsCollisions(World &world, Player &player);

void handleFireBallsAndNpcsCollisions(World &world, Player &player);

void handleBlockAndNpcsCollisions(World &world, const Block &block, Player &player);

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