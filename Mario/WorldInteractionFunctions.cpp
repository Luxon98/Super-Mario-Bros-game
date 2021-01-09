#include "WorldInteractionFunctions.h"

#include "SoundController.h"
#include "Player.h"
#include "World.h"
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
	if (points == 200) {
		player.addPoints(200);
	}
	else if (points == 1000) {
		world.addAnimatedText(TextType::ONE_THOUSAND, Position(player.getX(), player.getY() - 35));
		player.addPoints(1000);
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

void collectCoinByCollision(Player &player, World &world, int index)
{
	player.incrementCoins();
	player.addPoints(200);
	world.deleteBonus(index);
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