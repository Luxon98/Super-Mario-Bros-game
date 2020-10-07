#include "KeyboardController.h"

#include "CollisionHandling.h"
#include "Player.h"
#include "SoundController.h"
#include "World.h"


void KeyboardController::handleSpacebar(World &world)
{
	if (shotStatusFlag) {
		world.setFireballStatus();
	}
}

void KeyboardController::handleArrowKeys(Player &player, World &world)
{
	if (!player.movementBlock) {
		if (isCharacterStandingOnTheBlock(player, world)) {
			doubleJumpFlag = false;

			if (keysState[Direction::Left] && keysState[Direction::Right]) {
				if (player.playerMovement.stepsLeft > 0) {
					player.playerMovement.stepsLeft -= 4;
				}
				else if (player.playerMovement.stepsRight > 0) {
					player.playerMovement.stepsRight -= 4;
				}
				return;
			}
			else if (keysState[Direction::Left] && keysState[Direction::Up]) {
				if (player.playerMovement.stepsLeft > 0) {
					player.playerMovement.stepsLeft += 18;
					player.playerMovement.stepsUp = 2 * player.playerMovement.stepsLeft;
				}
				else {
					player.playerMovement.stepsLeft = 36;
					player.playerMovement.stepsUp = 72;
				}

				SoundController::playJumpEffect(player);
				return;
			}
			else if (keysState[Direction::Right] && keysState[Direction::Up]) {
				if (player.playerMovement.stepsRight > 0) {
					player.playerMovement.stepsRight += 18;
					player.playerMovement.stepsUp = 2 * player.playerMovement.stepsRight;
				}
				else {
					player.playerMovement.stepsRight = 36;
					player.playerMovement.stepsUp = 72;
				}

				SoundController::playJumpEffect(player);
				return;
			}
			else if (keysState[Direction::Left]) {
				if (player.playerMovement.stepsLeft > 0 && player.playerMovement.stepsLeft < 60) {
					player.playerMovement.stepsLeft += 8;
				}
				else {
					player.playerMovement.stepsLeft = 40;
				}
				return;
			}
			else if (keysState[Direction::Right]) {
				if (player.playerMovement.stepsRight > 0 && player.playerMovement.stepsRight < 60) {
					player.playerMovement.stepsRight += 8;
				}
				else {
					player.playerMovement.stepsRight = 40;
				}
				return;
			}
			else if (keysState[Direction::Up]) {
				player.playerMovement.stepsUp = 101;
				SoundController::playJumpEffect(player);
				return;
			}
		}
		else {
			if (player.playerMovement.stepsUp == 0) {
				player.playerMovement.stepsDown = 1;

				if (keysState[Direction::Left] && player.playerMovement.stepsLeft == 0) {
					player.playerMovement.stepsLeft = 24;
				}
				else if (keysState[Direction::Right] && player.playerMovement.stepsRight == 0) {
					player.playerMovement.stepsRight = 24;
				}
				return;
			}

			if (keysState[Direction::Left] && keysState[Direction::Up]) {
				if (player.playerMovement.stepsLeft > 0) {
					player.playerMovement.stepsLeft += 8;
				}
				else {
					player.playerMovement.stepsLeft = 16;
				}

				if (!doubleJumpFlag && player.getY() > 200) {
					player.playerMovement.stepsUp += 65;
					doubleJumpFlag = true;
				}
				return;
			}
			else if (keysState[Direction::Right] && keysState[Direction::Up]) {
				if (player.playerMovement.stepsRight > 0) {
					player.playerMovement.stepsRight += 8;
				}
				else {
					player.playerMovement.stepsRight = 16;
				}

				if (!doubleJumpFlag && player.getY() > 200) {
					player.playerMovement.stepsUp += 65;
					doubleJumpFlag = true;
				}
				return;
			}
			else if (keysState[Direction::Up]) {
				if (!doubleJumpFlag && player.getY() > 200) {
					player.playerMovement.stepsUp += 65;
					doubleJumpFlag = true;
				}
				return;
			}
			else if (keysState[Direction::Left]) {
				if (player.playerMovement.stepsLeft > 0) {
					player.playerMovement.stepsLeft += 12;
				}
				else {
					player.playerMovement.stepsLeft = 24;
				}
				return;
			}
			else if (keysState[Direction::Right]) {
				if (player.playerMovement.stepsRight > 0) {
					player.playerMovement.stepsRight += 12;
				}
				else {
					player.playerMovement.stepsRight = 24;
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
	keysState = { {Direction::Left, false}, {Direction::Right, false}, {Direction::Up, false} };
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
	shotStatusFlag = false;
}

void KeyboardController::handleKeys(Player &player, World &world)
{
	handleSpacebar(world);
	handleArrowKeys(player, world);
}

