#include "KeyboardController.h"

void KeyboardController::handleSpacebar(World& world)
{
	if (shotState) {
		world.setFireballStatus();
	}
}

void KeyboardController::handleArrowKeys(Player* player, World& world, Screen* mainScreen)
{
	if (keysState[Left]) {
		if (keysState[Up] && isCharacterStandingOnTheBlock(player, world)) {
			SoundController::playJumpEffect(player);
			player->moveAndJump(Left, 80, 80, world, mainScreen);
		}
		else {
			player->move(Left, 32 + (player->getCurrentState() >= ImmortalFirst && player->getCurrentState()
				<= ImmortalFourth) * 32, world, mainScreen);
		}
	}
	else if (keysState[Right]) {
		if (keysState[Up] && isCharacterStandingOnTheBlock(player, world)) {
			SoundController::playJumpEffect(player);
			player->moveAndJump(Right, 80, 80, world, mainScreen);
		}
		else {
			player->move(Right, 32 + (player->getCurrentState() >= ImmortalFirst && player->getCurrentState()
				<= ImmortalFourth) * 32, world, mainScreen);
		}
	}
	else if (keysState[Up] && isCharacterStandingOnTheBlock(player, world)) {
		SoundController::playJumpEffect(player);
		player->jump(Up, 160, world, mainScreen);
	}
	else if (!isCharacterStandingOnTheBlock(player, world)) {
		player->jump(Down, 15, world, mainScreen);
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

