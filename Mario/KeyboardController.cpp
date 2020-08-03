#include "KeyboardController.h"

void KeyboardController::handleSpacebar(World& world)
{
	if (this->shotState) {
		world.setFireballStatus();
	}
}

void KeyboardController::handleArrowKeys(Player* player, World& world, Screen* mainScreen)
{
	if (this->keysState[Left]) {
		if (this->keysState[Up] && isCharacterStandingOnTheBlock(player, world)) {
			SoundController::playJumpEffect(player);
			player->moveAndJump(Left, 80, 80, world, mainScreen);
		}
		else {
			player->move(Left, 32 + (player->getCurrentState() >= ImmortalFirst && player->getCurrentState()
				<= ImmortalFourth) * 32, world, mainScreen);
		}
	}
	else if (this->keysState[Right]) {
		if (this->keysState[Up] && isCharacterStandingOnTheBlock(player, world)) {
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
	this->keysState = { {Left, false}, {Right, false}, {Up, false} };
	this->shotState = false;
}

void KeyboardController::handleKeysState(const Uint8* state)
{
	if (state[SDL_SCANCODE_SPACE]) {
		this->shotState = true;
	}

	if (state[SDL_SCANCODE_LEFT] && !this->keysState[Right]) {
		this->keysState[Left] = true;
	}
	if (state[SDL_SCANCODE_RIGHT] && !keysState[Left]) {
		this->keysState[Right] = true;
	}
	if (state[SDL_SCANCODE_UP]) {
		this->keysState[Up] = true;
	}
}

void KeyboardController::clearKeysState()
{
	this->keysState[Up] = false;
	this->keysState[Left] = false;
	this->keysState[Right] = false;
	this->shotState = false;
}

void KeyboardController::forceActions(Player* player, World& world, Screen* mainScreen)
{
	this->handleSpacebar(world);
	this->handleArrowKeys(player, world, mainScreen);
}

