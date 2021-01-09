#include "KeyboardController.h"

#include "SoundController.h"
#include "CollisionHandling.h"
#include "Player.h"
#include "World.h"


void KeyboardController::handleSpacebar(World &world)
{
	if (shotStatusFlag) {
		world.setFireballStatus();
	}
}

void KeyboardController::handleDownArrow(Player &player)
{
	if (keysState[Direction::Down]) {
		player.flags.downPipeFlag = true;
	}
}

void KeyboardController::handleLeftAndRightArrowsWhenStanding(Player &player)
{
	if (player.stepsCounter.stepsLeft > 0) {
		player.stepsCounter.stepsLeft -= 4;
	}
	else if (player.stepsCounter.stepsRight > 0) {
		player.stepsCounter.stepsRight -= 4;
	}
}

void KeyboardController::handleLeftAndUpArrowsWhenStanding(Player &player)
{
	if (player.stepsCounter.stepsLeft > 0) {
		player.stepsCounter.stepsLeft += 18;
		player.stepsCounter.stepsUp = 2 * player.stepsCounter.stepsLeft;
	}
	else {
		player.stepsCounter.stepsLeft = 36;
		player.stepsCounter.stepsUp = 72;
	}

	SoundController::playJumpEffect(player);
}

void KeyboardController::handleRightAndUpArrowsWhenStanding(Player &player)
{
	if (player.stepsCounter.stepsRight > 0) {
		player.stepsCounter.stepsRight += 18;
		player.stepsCounter.stepsUp = 2 * player.stepsCounter.stepsRight;
	}
	else {
		player.stepsCounter.stepsRight = 36;
		player.stepsCounter.stepsUp = 72;
	}

	SoundController::playJumpEffect(player);
}

void KeyboardController::handleLeftArrowWhenStanding(Player &player)
{
	if (player.stepsCounter.stepsLeft > 0 && player.stepsCounter.stepsLeft < 60) {
		player.stepsCounter.stepsLeft += 8;
	}
	else {
		player.stepsCounter.stepsLeft = 56;
	}
}

void KeyboardController::handleRightArrowWhenStanding(Player &player)
{
	if (player.stepsCounter.stepsRight > 0 && player.stepsCounter.stepsRight < 60) {
		player.stepsCounter.stepsRight += 8;
	}
	else {
		player.stepsCounter.stepsRight = 56;
	}
}

void KeyboardController::handleUpArrowWhenStanding(Player &player)
{
	player.stepsCounter.stepsUp = 101;
	SoundController::playJumpEffect(player);
}

void KeyboardController::handleLeftAndRightArrowsWhenInAir(Player &player)
{
	if (keysState[Direction::Left] && player.stepsCounter.stepsLeft == 0) {
		player.stepsCounter.stepsLeft = 24;
	}
	else if (keysState[Direction::Right] && player.stepsCounter.stepsRight == 0) {
		player.stepsCounter.stepsRight = 24;
	}
}

void KeyboardController::handleLeftAndUpArrowsWhenInAir(Player &player)
{
	if (player.stepsCounter.stepsLeft > 0) {
		player.stepsCounter.stepsLeft += 8;
	}
	else {
		player.stepsCounter.stepsLeft = 16;
	}

	if (!doubleJumpFlag) {
		player.stepsCounter.stepsUp += (player.getY() > 200 ? 45 : 20);
		doubleJumpFlag = true;
	}
}

void KeyboardController::handleRightAndUpArrowsWhenInAir(Player &player)
{
	if (player.stepsCounter.stepsRight > 0) {
		player.stepsCounter.stepsRight += 8;
	}
	else {
		player.stepsCounter.stepsRight = 16;
	}

	if (!doubleJumpFlag) {
		player.stepsCounter.stepsUp += (player.getY() > 200 ? 45 : 20);
		doubleJumpFlag = true;
	}
}

void KeyboardController::handleUpArrowWhenInAir(Player &player)
{
	if (!doubleJumpFlag) {
		player.stepsCounter.stepsUp += (player.getY() > 200 ? 65 : 30);
		doubleJumpFlag = true;
	}
}

void KeyboardController::handleLeftArrowWhenInAir(Player &player)
{
	if (player.stepsCounter.stepsLeft > 0) {
		player.stepsCounter.stepsLeft += 12;
	}
	else {
		player.stepsCounter.stepsLeft = 24;
	}
}

void KeyboardController::handleRightArrowWhenInAir(Player &player)
{
	if (player.stepsCounter.stepsRight > 0) {
		player.stepsCounter.stepsRight += 12;
	}
	else {
		player.stepsCounter.stepsRight = 24;
	}
}

void KeyboardController::handleArrowsWhenStanding(Player &player)
{
	if (keysState[Direction::Left] && keysState[Direction::Right]) {
		handleLeftAndRightArrowsWhenStanding(player);
	}
	else if (keysState[Direction::Left] && keysState[Direction::Up]) {
		handleLeftAndUpArrowsWhenStanding(player);
	}
	else if (keysState[Direction::Right] && keysState[Direction::Up]) {
		handleRightAndUpArrowsWhenStanding(player);
	}
	else if (keysState[Direction::Left]) {
		handleLeftArrowWhenStanding(player);
	}
	else if (keysState[Direction::Right]) {
		handleRightArrowWhenStanding(player);
	}
	else if (keysState[Direction::Up]) {
		handleUpArrowWhenStanding(player);
	}
}

void KeyboardController::handleArrowsWhenInAir(Player &player)
{
	if (player.stepsCounter.stepsUp == 0) {
		handleLeftAndRightArrowsWhenInAir(player);
		return;
	}

	if (keysState[Direction::Left] && keysState[Direction::Up]) {
		handleLeftAndUpArrowsWhenInAir(player);
	}
	else if (keysState[Direction::Right] && keysState[Direction::Up]) {
		handleRightAndUpArrowsWhenInAir(player);
	}
	else if (keysState[Direction::Up]) {
		handleUpArrowWhenInAir(player);
	}
	else if (keysState[Direction::Left]) {
		handleLeftArrowWhenInAir(player);
	}
	else if (keysState[Direction::Right]) {
		handleRightArrowWhenInAir(player);
	}
}

void KeyboardController::handleArrows(Player &player, World &world)
{
	if (!player.movementBlock) {
		if (isCharacterStandingOnSomething(player, world)) {
			doubleJumpFlag = false;
			handleArrowsWhenStanding(player);
		}
		else {
			handleArrowsWhenInAir(player);
		}
	}
}

KeyboardController::KeyboardController()
{
	doubleJumpFlag = false;
	shotStatusFlag = false;
	keysState = { {Direction::Left, false}, {Direction::Right, false}, 
		{Direction::Up, false}, {Direction::Down, false} };
	lastShotTime = std::chrono::steady_clock::now();
}

void KeyboardController::handleKeysState(const Uint8* state)
{
	if (state[SDL_SCANCODE_SPACE]) {
		auto timePoint = std::chrono::steady_clock::now();
		auto difference = std::chrono::duration_cast<std::chrono::milliseconds>(timePoint - lastShotTime).count();
		if (difference > 250) {
			shotStatusFlag = true;
			lastShotTime = timePoint;
		}
	}

	if (state[SDL_SCANCODE_DOWN]) {
		keysState[Direction::Down] = true;
	}

	if (state[SDL_SCANCODE_LEFT]) {
		keysState[Direction::Left] = true;
	}
	if (state[SDL_SCANCODE_RIGHT]) {
		keysState[Direction::Right] = true;
	}
	if (state[SDL_SCANCODE_UP]) {
		keysState[Direction::Up] = true;
	}
}

void KeyboardController::clearKeysState()
{
	keysState[Direction::Up] = false;
	keysState[Direction::Left] = false;
	keysState[Direction::Right] = false;
	keysState[Direction::Down] = false;
	shotStatusFlag = false;
}

void KeyboardController::forceActions(Player &player, World &world)
{
	handleSpacebar(world);
	handleDownArrow(player);
	handleArrows(player, world);
}