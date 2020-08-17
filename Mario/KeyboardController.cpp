#include "KeyboardController.h"

void KeyboardController::handleSpacebar(World& world)
{
	if (shotStatusFlag) {
		world.setFireballStatus();
	}
}

void KeyboardController::handleArrowKeys(Player* player, World& world)
{
	if (isCharacterStandingOnTheBlock(player, world)) {
		doubleJumpFlag = false;

		if (keysState[Left] && keysState[Right]) {
			if (player->getStepsLeft() > 0) {
				player->setStepsLeft(player->getStepsLeft() - 4);
			}
			else if (player->getStepsRight() > 0) {
				player->setStepsRight(player->getStepsRight() - 4);
			}
			return;
		}
		else if (keysState[Left] && keysState[Up]) {
			if (player->getStepsLeft() > 0) {
				player->setStepsLeft(player->getStepsLeft() + 18);
				player->setStepsUp(player->getStepsLeft() * 2);
			}
			else {
				player->setStepsLeft(36);
				player->setStepsUp(72);
			}

			SoundController::playJumpEffect(player);
			return;
		}
		else if (keysState[Right] && keysState[Up]) {
			if (player->getStepsRight() > 0) {
				player->setStepsRight(player->getStepsRight() + 18);
				player->setStepsUp(player->getStepsRight() * 2);
			}
			else {
				player->setStepsRight(36);
				player->setStepsUp(72);
			}

			SoundController::playJumpEffect(player);
			return;
		}
		else if (keysState[Left]) {
			if (player->getStepsLeft() > 0) {
				player->setStepsLeft(player->getStepsLeft() + 8);
			}
			else {
				player->setStepsLeft(16);
			}
			return;
		}
		else if (keysState[Right]) {
			if (player->getStepsRight() > 0) {
				player->setStepsRight(player->getStepsRight() + 8);
			}
			else {
				player->setStepsRight(16);
			}
			return;
		}
		else if (keysState[Up]) {
			player->setStepsUp(101);
			SoundController::playJumpEffect(player);
			return;
		}
	}
	else {
		if (player->getStepsUp() == 0) {
			player->setStepsDown(1);

			if (keysState[Left] && player->getStepsLeft() == 0) {
				player->setStepsLeft(24);
			}
			else if (keysState[Right] && player->getStepsRight() == 0) {
				player->setStepsRight(24);
			}
			return;
		}

		if (keysState[Left] && keysState[Up]) {
			if (player->getStepsLeft() > 0) {
				player->setStepsLeft(player->getStepsLeft() + 8);
			}
			else {
				player->setStepsLeft(16);
			}

			if (!doubleJumpFlag && player->getY() > 200) {
				player->setStepsUp(player->getStepsUp() + 65);
				doubleJumpFlag = true;
			}
			return;
		}
		else if (keysState[Right] && keysState[Up]) {
			if (player->getStepsRight() > 0) {
				player->setStepsRight(player->getStepsRight() + 8);
			}
			else {
				player->setStepsRight(16);
			}

			if (!doubleJumpFlag && player->getY() > 200) {
				player->setStepsUp(player->getStepsUp() + 65);
				doubleJumpFlag = true;
			}
			return;
		}
		else if (keysState[Up]) {
			if (!doubleJumpFlag && player->getY() > 200) {
				player->setStepsUp(player->getStepsUp() + 65);
				doubleJumpFlag = true;
			}
			return;
		}
		else if (keysState[Left]) {
			if (player->getStepsLeft() > 0) {
				player->setStepsLeft(player->getStepsLeft() + 12);
			}
			else {
				player->setStepsLeft(24);
			}
			return;
		}
		else if (keysState[Right]) {
			if (player->getStepsRight() > 0) {
				player->setStepsRight(player->getStepsRight() + 12);
			}
			else {
				player->setStepsRight(24);
			}
			return;
		}
	}
}

KeyboardController::KeyboardController()
{
	doubleJumpFlag = false;
	shotStatusFlag = false;
	keysState = { {Left, false}, {Right, false}, {Up, false} };
}

void KeyboardController::handleKeysState(const Uint8* state)
{
	if (state[SDL_SCANCODE_SPACE]) {
		shotStatusFlag = true;
	}

	if (state[SDL_SCANCODE_LEFT]) {
		keysState[Left] = true;
	}
	if (state[SDL_SCANCODE_RIGHT]) {
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
	shotStatusFlag = false;
}

void KeyboardController::handleKeys(Player* player, World& world)
{
	handleSpacebar(world);
	handleArrowKeys(player, world);
}

