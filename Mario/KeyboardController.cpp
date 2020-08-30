#include "KeyboardController.h"

#include "CollisionHandling.h"
#include "Player.h"
#include "SoundController.h"
#include "World.h"


void KeyboardController::handleSpacebar(World& world)
{
	if (shotStatusFlag) {
		world.setFireballStatus();
	}
}

void KeyboardController::handleArrowKeys(Player* player, World& world)
{
	if (!player->movementBlock) {
		if (isCharacterStandingOnTheBlock(player, world)) {
			doubleJumpFlag = false;

			if (keysState[Left] && keysState[Right]) {
				if (player->playerMovement.stepsLeft > 0) {
					player->playerMovement.stepsLeft -= 4;
				}
				else if (player->playerMovement.stepsRight > 0) {
					player->playerMovement.stepsRight -= 4;
				}
				return;
			}
			else if (keysState[Left] && keysState[Up]) {
				if (player->playerMovement.stepsLeft > 0) {
					player->playerMovement.stepsLeft += 18;
					player->playerMovement.stepsUp = 2 * player->playerMovement.stepsLeft;
				}
				else {
					player->playerMovement.stepsLeft = 36;
					player->playerMovement.stepsUp = 72;
				}

				SoundController::playJumpEffect(player);
				return;
			}
			else if (keysState[Right] && keysState[Up]) {
				if (player->playerMovement.stepsRight > 0) {
					player->playerMovement.stepsRight += 18;
					player->playerMovement.stepsUp = 2 * player->playerMovement.stepsRight;
				}
				else {
					player->playerMovement.stepsRight = 36;
					player->playerMovement.stepsUp = 72;
				}

				SoundController::playJumpEffect(player);
				return;
			}
			else if (keysState[Left]) {
				if (player->playerMovement.stepsLeft > 0 && player->playerMovement.stepsLeft < 60) {
					player->playerMovement.stepsLeft += 8;
				}
				else {
					player->playerMovement.stepsLeft = 32;
				}
				return;
			}
			else if (keysState[Right]) {
				if (player->playerMovement.stepsRight > 0 && player->playerMovement.stepsRight < 60) {
					player->playerMovement.stepsRight += 8;
				}
				else {
					player->playerMovement.stepsRight = 32;
				}
				return;
			}
			else if (keysState[Up]) {
				player->playerMovement.stepsUp = 101;
				SoundController::playJumpEffect(player);
				return;
			}
		}
		else {
			if (player->playerMovement.stepsUp == 0) {
				player->playerMovement.stepsDown = 1;

				if (keysState[Left] && player->playerMovement.stepsLeft == 0) {
					player->playerMovement.stepsLeft = 24;
				}
				else if (keysState[Right] && player->playerMovement.stepsRight == 0) {
					player->playerMovement.stepsRight = 24;
				}
				return;
			}

			if (keysState[Left] && keysState[Up]) {
				if (player->playerMovement.stepsLeft > 0) {
					player->playerMovement.stepsLeft += 8;
				}
				else {
					player->playerMovement.stepsLeft = 16;
				}

				if (!doubleJumpFlag && player->getY() > 200 && !player->isImmortal()) {
					player->playerMovement.stepsUp += 65;
					doubleJumpFlag = true;
				}
				return;
			}
			else if (keysState[Right] && keysState[Up]) {
				if (player->playerMovement.stepsRight > 0) {
					player->playerMovement.stepsRight += 8;
				}
				else {
					player->playerMovement.stepsRight = 16;
				}

				if (!doubleJumpFlag && player->getY() > 200 && !player->isImmortal()) {
					player->playerMovement.stepsUp += 65;
					doubleJumpFlag = true;
				}
				return;
			}
			else if (keysState[Up]) {
				if (!doubleJumpFlag && player->getY() > 200 && !player->isImmortal()) {
					player->playerMovement.stepsUp += 65;
					doubleJumpFlag = true;
				}
				return;
			}
			else if (keysState[Left]) {
				if (player->playerMovement.stepsLeft > 0) {
					player->playerMovement.stepsLeft += 12;
				}
				else {
					player->playerMovement.stepsLeft = 24;
				}
				return;
			}
			else if (keysState[Right]) {
				if (player->playerMovement.stepsRight > 0) {
					player->playerMovement.stepsRight += 12;
				}
				else {
					player->playerMovement.stepsRight = 24;
				}
				return;
			}
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

