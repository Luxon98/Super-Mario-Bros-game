#include "Player.h"

SDL_Surface* Player::playerImages[74] = { nullptr };

int Player::computeImageIndex() {
	if (this->currentState == Small) {
		return this->model + 37 * this->orientationFlag;
	}
	else if (this->currentState == Tall) {
		return this->model + 37 * this->orientationFlag + 5;
	}
	else if (this->currentState == ArmedFirst || this->currentState == ImmortalFourth) {
		return this->model + 37 * this->orientationFlag + 10;
	}
	else if (this->currentState == ImmortalFirst) {
		return this->model + 37 * this->orientationFlag + 20;
	}
	else if (this->currentState == ImmortalSecond) {
		return this->model + 37 * this->orientationFlag + 15;
	}
	else if (this->currentState == ImmortalThird) {
		return this->model + 37 * this->orientationFlag + 25;
	}
	else if (this->currentState == ArmedSecond) {
		return 37 * this->orientationFlag + 30;
	}
	else if (this->currentState == ArmedThird) {
		return 37 * this->orientationFlag + 31;
	}
	else if (this->currentState == InsensitiveSmall) {
		return 37 * this->orientationFlag + 35;
	}
	else if (this->currentState == InsensitiveTall) {
		return 37 * this->orientationFlag + 36;
	}
	else {
		return 37 * this->orientationFlag + 34;
	}
}

void Player::changeStateDuringAnimation() {
	std::chrono::steady_clock::time_point timePoint = std::chrono::steady_clock::now();
	auto difference = std::chrono::duration_cast<std::chrono::milliseconds>(timePoint - this->lastAnimationStartTime).count();

	if (this->currentAnimationState == DuringGrowingAnimation) {
		this->performGrowingAnimation((int)difference);
	}
	else if (this->currentAnimationState == DuringShrinkingAnimation) {
		this->performShrinkingAnimation((int)difference);
	}
	else if (this->currentAnimationState == DuringArmingAnimation) {
		this->performArmingAnimation((int)difference);
	}
	else if (this->currentAnimationState == DuringImmortalAnimation) {
		this->performImmortalAnimation((int)difference);
	}
}

void Player::performGrowingAnimation(int difference) {
	this->movementBlock = true;
	this->model = 0;

	if ((difference >= 100 && difference <= 200 && this->lastDifference < 100)
		|| (difference >= 300 && difference <= 400 && this->lastDifference < 300)
		|| (difference >= 700 && difference <= 800 && this->lastDifference < 700)) {

		this->height = 48;
		this->positionY -= 8;
		this->lastDifference = difference;
		this->currentState = Average;
	}
	else if ((difference > 200 && difference < 300 && this->lastDifference < 200)
		|| (difference > 600 && difference < 700 && this->lastDifference < 600)) {

		this->height = 32;
		this->positionY += 8;
		this->lastDifference = difference;
		this->currentState = Small;
	}
	else if ((difference > 400 && difference < 500 && this->lastDifference < 400)
		|| (difference > 800 && difference <= 900 && this->lastDifference < 800)) {

		this->height = 64;
		this->positionY -= 8;
		this->lastDifference = difference;
		this->currentState = Tall;
	}
	else if (difference >= 500 && difference <= 600 && this->lastDifference < 500) {

		this->height = 48;
		this->positionY += 8;
		this->lastDifference = difference;
		this->currentState = Average;
	}
	else if (difference > 900) {
		this->currentAnimationState = NoAnimation;
		this->lastDifference = 0;
		this->movementBlock = false;
	}
}

void Player::performShrinkingAnimation(int difference) {
	if (difference <= 1000 && this->lastDifference < 10) {

		this->lastDifference = difference;
		this->currentState = InsensitiveTall;
	}
	else if (difference > 1000 && difference < 2000 && this->lastDifference < 1000) {

		this->height = 32;
		this->positionY += 16;
		this->lastDifference = difference;
		this->currentState = InsensitiveSmall;
	}
	else if (difference >= 2000) {

		this->currentAnimationState = NoAnimation;
		this->currentState = Small;
		this->lastDifference = 0;
		this->movementBlock = false;
	}
}

void Player::performArmingAnimation(int difference) {
	this->movementBlock = true;
	this->model = 0;

	if (isDifferenceInInterval(difference, 0, 600, 3)) {
		this->currentState = ArmedFirst;
	}
	else if (isDifferenceInInterval(difference, 150, 600, 3)) {
		this->currentState = Tall;
	}
	else if (isDifferenceInInterval(difference, 300, 600, 3)) {
		this->currentState = ArmedSecond;
	}
	else if (isDifferenceInInterval(difference, 450, 600, 3)) {
		this->currentState = ArmedThird;
	}
	else {
		this->currentAnimationState = NoAnimation;
		this->currentState = ArmedFirst;
		this->lastDifference = 0;
		this->movementBlock = false;
	}
}

void Player::performImmortalAnimation(int difference) {
	if (isDifferenceInInterval(difference, 0, 600, 20)) {
		this->currentState = ImmortalFirst;
	}
	else if (isDifferenceInInterval(difference, 150, 600, 20)) {
		this->currentState = ImmortalSecond;
	}
	else if (isDifferenceInInterval(difference, 300, 600, 20)) {
		this->currentState = ImmortalThird;
	}
	else if (isDifferenceInInterval(difference, 450, 600, 20)) {
		this->currentState = ImmortalFourth;
	}
	else {
		this->currentAnimationState = NoAnimation;
		this->currentState = ArmedFirst;
		this->lastDifference = 0;
		SoundController::stopMusic();
		SoundController::playBackgroudMarioMusic();
	}
}

void Player::chooseModel(World& world) {
	++this->changeModelCounter;
	if (this->changeModelCounter % 15 == 0) {
		++this->model;
		if (this->model > 3) {
			this->model = 1;
		}
	}
	if (!isCharacterStandingOnTheBlock(this, world)) {
		this->model = 4;
	}
}

bool Player::isHittingCeiling(int distance) {
	return (this->positionY - distance - this->height / 2 < 0);
}

bool Player::isFallingIntoAbyss(int distance) {
	return (this->positionY + distance + this->height / 2 > World::WORLD_HEIGHT);
}

bool Player::isGoingOutBoundariesOfWorld(Direction direction, int distance) {
	if (direction == Left && this->cameraX - distance <= this->width / 2) {
		return true;
	}
	else if (direction == Right && this->positionX + distance > World::WORLD_WIDTH) {
		return true;
	}
	return false;
}

bool Player::isExceedingCameraReferencePoint(int distance) {
	return (this->cameraX + distance > Screen::SCREEN_WIDTH - CAMERA_REFERENCE_POINT);
}

bool Player::isHittingBlock(int alignment, Direction direction) {
	if (alignment > 0 && direction == Up) {
		return true;
	}
	return false;
}

bool Player::isDuringAnimation() {
	return (this->currentAnimationState != NoAnimation);
}

bool Player::isRejumping() {
	return this->rejumpFlag;
}

Player::Player() {}

Player::Player(int x, int y) {
	this->positionX = x;
	this->positionY = y;
	this->cameraX = x;
	this->width = 32;
	this->height = 32;
	this->points = 0;
	this->coins = 0;
	this->model = 0;
	this->lives = 3;
	this->changeModelCounter = 0;
	this->orientationFlag = true;
	this->rejumpFlag = false;
	this->aliveFlag = true;
	this->removeLivesFlag = false;
	this->lastDifference = 0;
	this->currentAnimationState = NoAnimation;
	this->currentState = Small;
	this->movementBlock = false;
}

int Player::getCameraX() const {
	return this->cameraX;
}

int Player::getPoints() const {
	return this->points;
}

int Player::getCoins() const {
	return this->coins;
}

int Player::getLives() const {
	return this->lives;
}

bool Player::isArmed() const {
	return (this->currentState == ArmedFirst);
}

bool Player::isImmortal() const {
	return (this->currentState >= ImmortalFirst && this->currentState <= ImmortalFourth);
}

bool Player::isDead() const {
	return !this->aliveFlag;
}

PlayerState Player::getCurrentState() const {
	return this->currentState;
}

Direction Player::getMovementDirection() const {
	return (this->orientationFlag ? Right : Left);
}

void Player::incrementCoins() {
	++this->coins;
}

void Player::incrementLives() {
	++this->lives;
}

void Player::addPoints(int pts) {
	this->points += pts;
}

void Player::setRejumpFlag() {
	this->rejumpFlag = true;
}

void Player::setCurrentAnimation(AnimationState state) {
	this->currentAnimationState = state;
	this->lastAnimationStartTime = std::chrono::steady_clock::now();
}

void Player::loadPlayerImages(SDL_Surface* screen) {
	for (int i = 0; i < 37; ++i) {
		std::string filename = "./img/mario_left";
		filename += std::to_string(i + 1);
		filename += ".png";
		this->playerImages[i] = loadPNG(filename, screen);
		filename.replace(12, 4, "right");
		this->playerImages[i + 37] = loadPNG(filename, screen);
	}
}

void Player::draw(SDL_Surface* screen, int beginningOfCamera) {
	if (this->isDuringAnimation()) {
		this->changeStateDuringAnimation();
	}
	int index = this->computeImageIndex();

	SDL_Surface* playerImg = playerImages[index];
	drawSurface(screen, playerImg, beginningOfCamera, this->positionY);
}

void Player::hitBlock(World& world, Screen* mainScreen) {
	if ((this->currentState >= Tall && this->currentState <= ImmortalFourth)
		&& world.getBlockModel(world.getLastTouchedBlockIndex()) == Destructible) {

		world.deleteBlock(world.getLastTouchedBlockIndex());
		mainScreen->updateScreen(world);
	}
	else {
		world.setSlidingCounter(124);
	}
}

void Player::loseBonusOrLife() {
	if (this->currentState == Tall || this->currentState == ArmedFirst) {
		this->movementBlock = true;
		this->currentAnimationState = DuringShrinkingAnimation;
		this->lastAnimationStartTime = std::chrono::steady_clock::now();
	}
	else if (!this->isDuringAnimation()) {
		if (!this->removeLivesFlag) {
			this->removeLivesFlag = true;
			--this->lives;
			this->aliveFlag = false;
		}
	}
}

void Player::changePosition(Direction direction, int distance, World& world, Screen* mainScreen) {
	if (!isGoingOutBoundariesOfWorld(direction, distance)) {
		if (direction == Left) {
			this->positionX -= distance;
			this->cameraX -= distance;
		}
		else if (direction == Right) {
			if (this->isExceedingCameraReferencePoint(distance)) {
				mainScreen->setPositionOfTheScreen(mainScreen->getBeginningOfCamera() + distance,
					mainScreen->getEndOfCamera() + distance);
			}
			else {
				this->cameraX += distance;
			}
			this->positionX += distance;
		}
		this->orientationFlag = (direction == Right);
	}
}

void Player::changeVerticalPosition(Direction direction, int distance, World& world) {
	if (direction == Up && !this->isHittingCeiling(distance)) {
		this->positionY -= distance;
	}
	else if (direction == Down && !this->isFallingIntoAbyss(distance)) {
		this->positionY += distance;
	}
	else if (this->isFallingIntoAbyss(distance)) {
		if (!this->removeLivesFlag) {
			this->removeLivesFlag = true;
			--this->lives;
			this->aliveFlag = false;
		}
	}
}

void Player::move(Direction direction, int distance, World& world, Screen* mainScreen) {
	int height, range;
	for (int i = 0; i < distance && !this->movementBlock; ++i) {
		range = 1 - alignIfCollisionOccursDuringMovement(direction, 1, this, world);
		this->changePosition(direction, range, world, mainScreen);

		height = 1 - alignIfCollisionOccursDuringVerticalMovement(Down, 1, this, world);
		if (!isCharacterStandingOnTheBlock(this, world)) {
			changeVerticalPosition(Down, height, world);
		}
		collectCoinIfPossible(this, world);
		mainScreen->updateScreen(world);
		this->chooseModel(world);
	}
	this->model = 0;
}

void Player::jump(Direction direction, int height, World& world, Screen* mainScreen) {
	int alignment = alignIfCollisionOccursDuringVerticalMovement(direction, height, this, world);
	height -= alignment;
	this->model = 4;

	for (int i = 0; i < height && !this->movementBlock; ++i) {
		changeVerticalPosition(direction, 1, world);
		collectCoinIfPossible(this, world);
		mainScreen->updateScreen(world);

		if (this->rejumpFlag) {
			this->rejumpFlag = false;
			this->performAdditionalJump(world, mainScreen);
			break;
		}

	}
	changeVerticalPosition(direction, height % 1, world);
	collectCoinIfPossible(this, world);

	mainScreen->updateScreen(world);

	if (isHittingBlock(alignment, direction)) {
		this->hitBlock(world, mainScreen);
	}

	if (isCharacterStandingOnTheBlock(this, world)) {
		this->model = 0;
	}
}

void Player::moveAndJump(Direction dirX, int distance, int height, World& world, Screen* mainScreen) {
	bool checker = false;
	int steps = 2 * distance, treads = 2 * height;
	int ctr = 0, alignment = 0;
	Direction dirY = Up;
	this->model = 4;

	while ((steps || treads) && !this->movementBlock) {
		if (treads) {
			alignment = alignIfCollisionOccursDuringVerticalMovement(dirY, 1, this, world);
			this->changeVerticalPosition(dirY, 1 - alignment, world);
			--treads;

			if (++ctr > treads) {
				dirY = Down;
			}
			if (this->isHittingBlock(alignment, dirY) && !checker) {
				checker = true;
				this->hitBlock(world, mainScreen);
			}
		}
		if (steps) {
			this->changePosition(dirX, 1 - alignIfCollisionOccursDuringMovement(dirX, 1, this, world), world, mainScreen);
			--steps;
		}
		collectCoinIfPossible(this, world);
		mainScreen->updateScreen(world);

		if (this->rejumpFlag) {
			this->rejumpFlag = false;
			this->performAdditionalJump(world, mainScreen);
			break;
		}
	}

	if (isCharacterStandingOnTheBlock(this, world)) {
		this->model = 0;
	}
}

void Player::performAdditionalJump(World& world, Screen* mainScreen) {
	this->jump(Up, 40, world, mainScreen);
}

void Player::reborn() {
	this->positionX = 35;
	this->positionY = 400;
	this->cameraX = 35;
	this->width = 32;
	this->height = 32;
	this->model = 0;
	this->changeModelCounter = 0;
	this->orientationFlag = true;
	this->rejumpFlag = false;
	this->aliveFlag = true;
	this->removeLivesFlag = false;
	this->lastDifference = 0;
	this->currentState = Small;
	this->movementBlock = false;
}

