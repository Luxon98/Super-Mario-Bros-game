#include "WorldInteractionFunctions.h"

#include "Player.h"
#include "World.h"
#include "Mushroom.h"
#include "SoundController.h"
#include "AnimatedText.h"


TextType getTextTypeFromPoints(int points)
{
	switch (points) {
	case 100:
		return TextType::ONE_HUNDRED;
	case 200:
		return TextType::TWO_HUNDRED;
	case 400:
		return TextType::FOUR_HUNDRED;
	default:
		return TextType::ONE_THOUSAND;
	}
}

void addTextAndPoints(Player &player, World &world, int points)
{
	if (points == 1000) {
		world.addAnimatedText(TextType::ONE_THOUSAND, Position(player.getX(), player.getY() - 30));
		player.addPoints(points);
	}
	else {
		world.addAnimatedText(TextType::ONE_UP, Position(player.getX(), player.getY() - 30));
	}
}

void addTextAndPoints(Player &player, World &world, int points, Position position)
{
	TextType type = getTextTypeFromPoints(points);
	player.addPoints(points);
	world.addAnimatedText(type, position);
}

void collectMushroom(Player &player, World &world, Mushroom &mushroom, int index)
{
	if (!mushroom.isOneUp()) {
		if (player.isSmall()) {
			player.setCurrentAnimation(PlayerAnimation::Growing);
		}

		addTextAndPoints(player, world, 1000);
		SoundController::playBonusCollectedEffect();
	}
	else {
		player.incrementLives();
		addTextAndPoints(player, world, 0);
		SoundController::playNewLiveAddedEffect();
	}

	world.deleteLivingElement(index);
}

void collectFlower(Player &player, World &world, int index)
{
	if (player.isSmall()) {
		player.setCurrentAnimation(PlayerAnimation::Growing);
	}
	else if (!player.isImmortal() && !player.isArmed()) {
		player.setCurrentAnimation(PlayerAnimation::Arming);
	}

	addTextAndPoints(player, world, 1000);
	world.deleteLivingElement(index);
	SoundController::playBonusCollectedEffect();
}

void collectStar(Player &player, World &world, int index)
{
	if (player.isSmall()) {
		player.setCurrentAnimation(PlayerAnimation::ImmortalSmall);
	}
	else {
		player.setCurrentAnimation(PlayerAnimation::Immortal);
	}
	player.increaseSpeed();

	addTextAndPoints(player, world, 1000);
	world.deleteLivingElement(index);
	SoundController::playStarMusic();
}

void collectCoin(Player &player, World &world, int index)
{
	player.incrementCoins();
	player.addPoints(200);
	world.deleteCoin(index);
	SoundController::playCoinCollectedEffect();
}

void collectCoinByCollision(Player &player, World &world, int index)
{
	player.incrementCoins();
	player.addPoints(200);
	world.deleteCoin(index);
	world.addAnimatedCoin();
	SoundController::playCoinCollectedEffect();
}

void getPointsFromFlag(Player &player, World &world)
{
	int points;
	if (player.getY() > 330) {
		points = 100;
	}
	else if (player.getY() <= 330 && player.getY() >= 250) {
		points = 200;
	}
	else if (player.getY() < 250 && player.getY() >= 190) {
		points = 400;
	}
	else {
		points = 1000;
	}

	Position position = Position(player.getX() + 75, player.getY());
	addTextAndPoints(player, world, points, position);
}
