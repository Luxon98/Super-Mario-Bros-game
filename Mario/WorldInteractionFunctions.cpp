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
	case 1000:
		return TextType::ONE_THOUSAND;
	default:
		return TextType::FIVE_THOUSAND;
	}
}

void addTextAndPoints(Player &player, World &world, int points)
{
	if (points == 1000) {
		world.addAnimatedText(TextType::ONE_THOUSAND, Position(player.getX(), player.getY() - 35));
		player.addPoints(points);
	}
	else {
		world.addAnimatedText(TextType::ONE_UP, Position(player.getX(), player.getY() - 35));
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
	if (player.isSmall() || player.isInsensitive()) {
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
	else if (player.getY() <= 330 && player.getY() >= 280) {
		points = 200;
	}
	else if (player.getY() < 280 && player.getY() >= 230) {
		points = 400;
	}
	else if (player.getY() < 230 && player.getY() >= 180) {
		points = 1000;
	}
	else {
		points = 5000;
	}

	Position position = Position(player.getX() + 75, player.getY());
	addTextAndPoints(player, world, points, position);
}
