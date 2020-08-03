#ifndef _CollisionHandling_H
#define _CollisionHandling_H

#include <cmath>
#include "World.h"
#include "WorldObject.h"
#include "NonControllableLivingObject.h"
#include "BonusObject.h"
#include "Player.h"
#include "Block.h"
#include "Coin.h"
#include "FireBall.h"


enum Direction;
class World;
class Player;


bool isCharacterHittingBlock(WorldObject* object, Block block, Direction direction, int distance);

bool isCharacterStandingOnTheBlock(WorldObject* object, World& world);

bool isMonsterStandingOnTheBlock(NonControllableLivingObject* object, Block block);

bool isFlowerStandingOnTheBlock(World& world, int index);

bool areAtTheSameWidth(WorldObject* object, Block block);

bool areAtTheSameHeight(WorldObject* object, Block block); 

bool areAtTheSameWidth(WorldObject* firstObject, WorldObject* secondObject);

bool areAtTheSameHeight(WorldObject* firstObject, WorldObject* secondObject);

bool isPlayerJumpingOnMonster(Player* player, NonControllableLivingObject* monster);

void handleIfCollisionWithMonsterOccurs(Player* player, World& world);

void handleIfShellCollideWithMonsters(World& world, Player* player);

void handleIfFireBallCollideWithMonsters(World& world, Player* player);

void handleIfMonsterCollideWithDestroyedBlock(World& world, Block block, Player* player);

void collectCoinIfPossible(Player* player, World& world);

void collectBonusIfPossible(Player* player, World& world);

int getAlignmentIfCollisionOccursDuringMovement(Direction direction, int distance, WorldObject* object, World& world);

int getAlignmentIfCollisionOccursDuringVerticalMovement(Direction direction, int distance, WorldObject* object, World& world);

#endif //_CollisionHandling_H
