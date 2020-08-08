#include "KeyboardController.h"

void KeyboardController::handleSpacebar(World& world)
{
	if (shotState) {
		world.setFireballStatus();
	}
}

void KeyboardController::handleArrowKeys(Player* player, World& world, Screen* mainScreen)
{
	if (keysState[Left] && player->getStepsRight() == 0) {
		player->setStepsLeft(16);
	}
	else if (keysState[Right] && player->getStepsLeft() == 0) {
		player->setStepsRight(16);
	}
	else if (keysState[Up] && isCharacterStandingOnTheBlock(player, world)) {
		player->setStepsUp(81);
	}

	if (!isCharacterStandingOnTheBlock(player, world) && player->getStepsUp() == 0) {
		player->setStepsDown(1);
	}
}

KeyboardController::KeyboardController()
{
	keysState = { {Left, false}, {Right, false}, {Up, false} };
	shotState = false;
}

void KeyboardController::handleKeysState(const Uint8* state)
{
	if (state[SDL_SCANCODE_SPACE]) {
		shotState = true;
	}

	if (state[SDL_SCANCODE_LEFT] && !keysState[Right]) {
		keysState[Left] = true;
	}
	if (state[SDL_SCANCODE_RIGHT] && !keysState[Left]) {
		keysState[Right] = true;
	}
	if (state[SDL_SCANCODE_UP]) {
		keysState[Up] = true;
	}
}

void KeyboardController::clearKeysState()
{
	keysState[Up] = false;
	keysState[Left] = false;
	keysState[Right] = false;
	shotState = false;
}

void KeyboardController::forceActions(Player* player, World& world, Screen* mainScreen)
{
	handleSpacebar(world);
	handleArrowKeys(player, world, mainScreen);
}

