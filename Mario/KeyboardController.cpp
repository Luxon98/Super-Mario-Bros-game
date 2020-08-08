#include "KeyboardController.h"

void KeyboardController::handleSpacebar(World& world)
{
	if (shotState) {
		world.setFireballStatus();
	}
}

void KeyboardController::handleArrowKeys(Player* player, World& world, Screen* mainScreen)
{
	if (keysState[Left] && player->stepsRight == 0) {
		player->stepsLeft = 16;
	}
	else if (keysState[Right] && player->stepsLeft == 0) {
		player->stepsRight = 16;
	}
	else if (keysState[Up] && isCharacterStandingOnTheBlock(player, world)) {
		player->stepsUp = 81;
	}
	else if (!isCharacterStandingOnTheBlock(player, world) && player->stepsUp == 0) {
		player->stepsDown = 3;
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

