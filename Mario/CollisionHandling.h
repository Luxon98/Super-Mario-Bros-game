#ifndef _CollisionHandling_H
#define _CollisionHandling_H

#include <cmath>
#include "WorldObject.h"
#include "Coin.h"
#include "Block.h"
#include "Direction.h"
#include "Player.h"


class World;
class Player;
class LivingObject;


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

void handleIfCollisionWithMonsterOccurs(Player* player, World& world);

void handleIfShellCollideWithMonsters(World& world, Player* player);

void handleIfFireBallCollideWithMonsters(World& world, Player* player);

void handleIfMonsterCollideWithDestroyedBlock(World& world, Block block, Player* player);

void collectCoinIfPossible(Player* player, World& world);

void collectBonusIfPossible(Player* player, World& world);

int getAlignmentIfCollisionOccursDuringMovement(Direction direction, int distance, WorldObject* object, World& world);

int getAlignmentIfCollisionOccursDuringVerticalMovement(Direction direction, int distance, WorldObject* object, World& world);

#endif //_CollisionHandling_H
