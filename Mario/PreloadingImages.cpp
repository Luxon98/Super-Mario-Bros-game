#include "PreloadingImages.h"

#include "Player.h"
#include "Coin.h"
#include "Flower.h"
#include "Mushroom.h"
#include "Star.h"
#include "FireBall.h"
#include "Turtle.h"
#include "RedTurtle.h"
#include "Creature.h"
#include "Plant.h"
#include "FireMissle.h"
#include "Shell.h"
#include "JumpingFish.h"
#include "CloudBombardier.h"
#include "Boss.h"
#include "Flag.h"
#include "Button.h"
#include "AnimatedText.h"
#include "AnimatedCoin.h"
#include "Snowflake.h"
#include "Shards.h"
#include "Explosion.h"
#include "CrushedCreature.h"
#include "DestroyedCreature.h"
#include "DestroyedTurtle.h"
#include "DestroyedBoss.h"
#include "DestroyedFish.h"
#include "DestroyedBombardier.h"
#include "Bush.h"
#include "Cloud.h"
#include "Rock.h"
#include "Lava.h"
#include "Castle.h"
#include "Princess.h"
#include "CustomWinterDecoration.h"
#include "CustomSummerDecoration.h"
#include "Block.h"
#include "Platform.h"
#include "FireSerpent.h"
#include "MenuManager.h"
#include "AnimationsPlayer.h"


void preloadBonusObjectsImages(SDL_Surface* display)
{
	Flower::loadFlowerImages(display);
	Mushroom::loadMushroomImages(display);
	Star::loadStarImages(display);
	Coin::loadCoinImages(display);
}

void preloadInanimateObjectImages(SDL_Surface* display)
{
	Bush::loadBushImages(display);
	Cloud::loadCloudImages(display);
	Rock::loadRockImage(display);
	Lava::loadLavaImage(display);
	Flag::loadFlagImages(display);
	Button::loadButtonImages(display);
	Castle::loadCastleImages(display);
	Princess::loadPrincessImages(display);
	CustomWinterDecoration::loadDecorationImages(display);
	CustomSummerDecoration::loadDecorationImages(display);
}

void preloadLivingObjectImages(SDL_Surface* display)
{
	Creature::loadCreatureImages(display);
	Turtle::loadTurtleImages(display);
	RedTurtle::loadTurtleImages(display);
	Plant::loadPlantImages(display);
	FireMissle::loadFireRocketImages(display);
	Boss::loadBossImages(display);
	JumpingFish::loadFishImages(display);
	CloudBombardier::loadBombardierImages(display);
	Shell::loadShellImage(display);
	FireBall::loadFireBallImages(display);
	Player::loadPlayerImages(display);
}

void preloadTemporaryObjectImages(SDL_Surface* display)
{
	CrushedCreature::loadCrushedCreatureImages(display);
	DestroyedCreature::loadDestroyedCreatureImages(display);
	DestroyedTurtle::loadDestroyedTurtleImages(display);
	DestroyedBoss::loadDestroyedBossImages(display);
	DestroyedFish::loadDestroyedFishImages(display);
	DestroyedBombardier::loadDestroyedBombardierImages(display);
	Explosion::loadExplosionImages(display);
	Shards::loadShardsImages(display);
	AnimatedCoin::loadAnimatedCoinImages(display);
	AnimatedText::loadAnimatedTextImages(display);
}

void preloadAnimatedObjectImages(SDL_Surface* display)
{
	Snowflake::loadSnowflakeImage(display);
}

void preloadOtherImages(SDL_Surface* display)
{
	Block::loadBlockImages(display);
	Platform::loadPlatformImage(display);
	FireSerpent::loadFireSerpentImages(display);
	MenuManager::loadMenuImages(display);
	AnimationsPlayer::loadAnimationsPlayerImages(display);
}

void preloadImages(SDL_Surface* display)
{
	preloadBonusObjectsImages(display);
	preloadInanimateObjectImages(display);
	preloadLivingObjectImages(display);
	preloadTemporaryObjectImages(display);
	preloadAnimatedObjectImages(display);
	preloadOtherImages(display);
}