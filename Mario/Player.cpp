#include "Player.h"

SDL_Surface* Player::playerImages[80] = { nullptr };

Player::Statistics::Statistics()
{
	points = 0;
	coins = 0;
	lives = 3;
}

Player::Flags::Flags()
{
	orientationFlag = true;
	aliveFlag = true;
	removeLivesFlag = false;
	armedFlag = false;
	inAirFlag = false;
}

void Player::Flags::setDefaultFlags()
{
	orientationFlag = true;
	aliveFlag = true;
	removeLivesFlag = false;
	armedFlag = false;
	inAirFlag = false;
}

Player::PlayerMovement::PlayerMovement()
{
	stepsLeft = 0;
	stepsRight = 0;
	stepsUp = 0;
	stepsDown = 0;
	speed = 1;
	verticalSpeed = 1;
}

int Player::computeImageIndex()
{
	if (currentState == Small) {
		return model + 40 * flags.orientationFlag;
	}
	else if (currentState == Tall) {
		return model + 40 * flags.orientationFlag + 5;
	}
	else if (currentState == ArmedFirst || currentState == ImmortalFourth) {
		return model + 40 * flags.orientationFlag + 10;
	}
	else if (currentState == ImmortalFirst) {
		return model + 40 * flags.orientationFlag + 20;
	}
	else if (currentState == ImmortalSecond) {
		return model + 40 * flags.orientationFlag + 15;
	}
	else if (currentState == ImmortalThird) {
		return model + 40 * flags.orientationFlag + 25;
	}
	else if (currentState == ArmedSecond) {
		int additionalIndex = (flags.inAirFlag ? 32 : 30);
		return 40 * flags.orientationFlag + additionalIndex;
	}
	else if (currentState == ArmedThird) {
		int additionalIndex = (flags.inAirFlag ? 33 : 31);
		return 40 * flags.orientationFlag + additionalIndex;
	}
	else if (currentState == InsensitiveSmall) {
		return model + 40 * flags.orientationFlag + 35;
	}
	else if (currentState == Average) {
		return 40 * flags.orientationFlag + 34;
	}
	else {
		return model;
	}
}

void Player::changeStateDuringAnimation()
{
	std::chrono::steady_clock::time_point timePoint = std::chrono::steady_clock::now();
	auto difference = std::chrono::duration_cast<std::chrono::milliseconds>(timePoint - lastAnimationStartTime).count();

	if (currentAnimationState == DuringGrowingAnimation) {
		performGrowingAnimation((int)difference);
	}
	else if (currentAnimationState == DuringShrinkingAnimation) {
		performShrinkingAnimation((int)difference);
	}
	else if (currentAnimationState == DuringArmingAnimation) {
		performArmingAnimation((int)difference);
	}
	else if (currentAnimationState == DuringImmortalAnimation) {
		performImmortalAnimation((int)difference);
	}
}

void Player::performGrowingAnimation(int difference)
{
	movementBlock = true;
	model = 0;

	if ((difference >= 100 && difference <= 200 && lastDifference < 100)
		|| (difference >= 300 && difference <= 400 && lastDifference < 300)
		|| (difference >= 700 && difference <= 800 && lastDifference < 700)) {

		size->setHeight(48);
		position->setY(position->getY() - 8);
		lastDifference = difference;
		currentState = Average;
	}
	else if ((difference > 200 && difference < 300 && lastDifference < 200)
		|| (difference > 600 && difference < 700 && lastDifference < 600)) {

		size->setHeight(32);
		position->setY(position->getY() + 8);
		lastDifference = difference;
		currentState = Small;
	}
	else if ((difference > 400 && difference < 500 && lastDifference < 400)
		|| (difference > 800 && difference <= 900 && lastDifference < 800)) {

		size->setHeight(64);
		position->setY(position->getY() - 8);
		lastDifference = difference;
		currentState = Tall;
	}
	else if (difference >= 500 && difference <= 600 && lastDifference < 500) {

		size->setHeight(48);
		position->setY(position->getY() + 8);
		lastDifference = difference;
		currentState = Average;
	}
	else if (difference > 900) {
		currentAnimationState = NoAnimation;
		lastDifference = 0;
		movementBlock = false;
		resetMovement();
	}
}

void Player::performShrinkingAnimation(int difference)
{
	if (difference <= 1000 && lastDifference < 10) {
		size->setHeight(32);
		position->setY(position->getY() + 16);
		lastDifference = difference;
		currentState = InsensitiveSmall;
	}
	else if (difference >= 2000) {
		currentAnimationState = NoAnimation;
		currentState = Small;
		lastDifference = 0;
	}
}

void Player::performArmingAnimation(int difference)
{
	movementBlock = true;
	model = (flags.inAirFlag ? 4 : 0);

	if (isDifferenceInInterval(difference, 0, 600, 3)) {
		currentState = ArmedFirst;
	}
	else if (isDifferenceInInterval(difference, 150, 600, 3)) {
		currentState = Tall;
	}
	else if (isDifferenceInInterval(difference, 300, 600, 3)) {
		currentState = ArmedSecond;
	}
	else if (isDifferenceInInterval(difference, 450, 600, 3)) {
		currentState = ArmedThird;
	}
	else {
		currentAnimationState = NoAnimation;
		currentState = ArmedFirst;
		flags.armedFlag = true;
		lastDifference = 0;
		movementBlock = false;
		resetMovement();
	}
}

void Player::performImmortalAnimation(int difference)
{
	if (isDifferenceInInterval(difference, 0, 600, 20)) {
		currentState = ImmortalFirst;
	}
	else if (isDifferenceInInterval(difference, 150, 600, 20)) {
		currentState = ImmortalSecond;
	}
	else if (isDifferenceInInterval(difference, 300, 600, 20)) {
		currentState = ImmortalThird;
	}
	else if (isDifferenceInInterval(difference, 450, 600, 20)) {
		currentState = ImmortalFourth;
	}
	else {
		currentAnimationState = NoAnimation;
		currentState = ArmedFirst;
		lastDifference = 0;
		SoundController::stopMusic();
		SoundController::playBackgroudMarioMusic();
		playerMovement->setSpeed(1);
		playerMovement->setVerticalSpeed(1);
	}
}

void Player::resetMovement()
{
	playerMovement->stepsLeft = 0;
	playerMovement->stepsRight = 0;
	playerMovement->stepsUp = 0;
	playerMovement->stepsDown = 0;
	playerMovement->setSpeed(1);
	playerMovement->setVerticalSpeed(1);
}

void Player::changeModelAndAirFlagStatus(World& world)
{
	if (!isCharacterStandingOnTheBlock(this, world)) {
		model = 4;
		flags.inAirFlag = true;
		return;
	}
	else {
		flags.inAirFlag = false;
	}

	if (playerMovement->stepsLeft == 0 && playerMovement->stepsRight == 0) {
		model = 0;
		return;
	}

	changeModelCounter++;
	if (changeModelCounter % 12 == 0) {
		model++;
		if (model > 3) {
			model = 1;
		}	
	}
}

bool Player::isHittingCeiling(int distance)
{
	return (position->getY() - distance - getHeight() / 2 < 0);
}

bool Player::isFallingIntoAbyss(int distance)
{
	return (position->getY() + distance + getHeight() / 2 > World::WORLD_HEIGHT);
}

bool Player::isGoingBeyondCamera(int distance, int beginningOfCamera)
{
	if (position->getX() - beginningOfCamera - distance <= getWidth() / 2) {
		return true;
	}

	return false;
}

bool Player::isHittingBlock(int alignment, Direction direction)
{
	if (alignment > 0 && direction == Up) {
		return true;
	}

	return false;
}

bool Player::isDuringAnimation()
{
	return (currentAnimationState != NoAnimation);
}

Player::Player() {}

Player::Player(Position* position)
{
	size = new Size(32, 32);
	statistics = Statistics();
	flags = Flags();
	playerMovement = new PlayerMovement();
	this->position = position;
	model = 0;
	changeModelCounter = 0;
	lastDifference = 0;
	currentAnimationState = NoAnimation;
	currentState = Small;
	movementBlock = false;
}

int Player::getPoints() const
{
	return statistics.points;
}

int Player::getCoins() const
{
	return statistics.coins;
}

int Player::getLives() const
{
	return statistics.lives;
}

int Player::getStepsLeft() const
{
	return playerMovement->stepsLeft;
}

int Player::getStepsRight() const
{
	return playerMovement->stepsRight;
}

int Player::getStepsUp() const
{
	return playerMovement->stepsUp;
}

bool Player::isArmed() const
{
	return flags.armedFlag;
}

bool Player::isImmortal() const
{
	return (currentState >= ImmortalFirst && currentState <= ImmortalFourth);
}

bool Player::isDead() const
{
	return !flags.aliveFlag;
}

PlayerState Player::getCurrentState() const
{
	return currentState;
}

Direction Player::getMovementDirection() const
{
	return (flags.orientationFlag ? Right : Left);
}

void Player::incrementCoins()
{
	if (statistics.coins == 99) {
		statistics.coins = 0;
		statistics.lives++;
		SoundController::playNewLiveAddedEffect();
	}
	else {
		statistics.coins++;
	}
}

void Player::incrementLives()
{
	statistics.lives++;
}

void Player::increaseSpeed()
{
	playerMovement->setSpeed(2);
	playerMovement->setVerticalSpeed(2);
}

void Player::setStepsLeft(int stepsLeft)
{
	playerMovement->stepsLeft = stepsLeft;
}

void Player::setStepsRight(int stepsRight)
{
	playerMovement->stepsRight = stepsRight;
}

void Player::setStepsUp(int stepsUp)
{
	playerMovement->stepsUp = stepsUp;
}

void Player::setStepsDown(int stepsDown)
{
	playerMovement->stepsDown = stepsDown;
}

void Player::addPoints(int pts)
{
	statistics.points += pts;
}

void Player::setCurrentAnimation(AnimationState state)
{
	currentAnimationState = state;
	lastAnimationStartTime = std::chrono::steady_clock::now();
}

void Player::loadPlayerImages(SDL_Surface* display)
{
	for (int i = 0; i < 40; ++i) {
		std::string filename = "./img/mario_left";
		filename += std::to_string(i + 1);
		filename += ".png";
		playerImages[i] = loadPNG(filename, display);
		filename.replace(12, 4, "right");
		playerImages[i + 40] = loadPNG(filename, display);
	}
}

void Player::draw(SDL_Surface* display, int beginningOfCamera)
{
	if (isDuringAnimation()) {
		changeStateDuringAnimation();
	}
	int index = computeImageIndex();

	SDL_Surface* playerImg = playerImages[index];
	drawSurface(display, playerImg, position->getX() - beginningOfCamera, position->getY());
}

void Player::hitBlock(World& world)
{
	if ((currentState >= Tall && currentState <= ImmortalFourth)
		&& world.getBlockModel(world.getLastTouchedBlockIndex()) == Destructible) {
		
		world.performBlockRemovalActions(world.getLastTouchedBlockIndex());
	}
	else {
		world.hitBlock();
	}
}

void Player::loseBonusOrLife()
{
	if (currentState == Tall || currentState == ArmedFirst) {
		currentAnimationState = DuringShrinkingAnimation;
		flags.armedFlag = false;
		lastAnimationStartTime = std::chrono::steady_clock::now();
	}
	else if (!isDuringAnimation()) {
		if (!flags.removeLivesFlag) {
			flags.removeLivesFlag = true;
			statistics.lives--;
			flags.aliveFlag = false;
		}
	}
}

void Player::performAdditionalJump()
{
	playerMovement->stepsDown = 0;
	playerMovement->stepsUp = 40;
}

void Player::move(World& world)
{
	if (!movementBlock) {
		if (playerMovement->stepsLeft > 0) {
			int alignment = getAlignmentIfCollisionOccursDuringMovement(Left, playerMovement->getSpeed(), this, world);
			int distance = playerMovement->getSpeed() - alignment;

			if (!isGoingBeyondCamera(distance, world.getScreen()->getBeginningOfCamera())) {
				position->setX(position->getX() - distance);
			}

			if (alignment != 0 && playerMovement->stepsUp == 0) {
				playerMovement->stepsLeft = 0;
			}
			else {
				playerMovement->stepsLeft--;
			}

			flags.orientationFlag = false;
		}

		if (playerMovement->stepsRight > 0) {
			int alignment = getAlignmentIfCollisionOccursDuringMovement(Right, playerMovement->getSpeed(), this, world);
			int distance = playerMovement->getSpeed() - alignment;

			position->setX(position->getX() + distance);

			if (alignment != 0 && playerMovement->stepsUp == 0) {
				playerMovement->stepsRight = 0;
			}
			else {
				playerMovement->stepsRight--;
			}

			flags.orientationFlag = true;
		}

		if (playerMovement->stepsUp > 0) {
			int alignment = getAlignmentIfCollisionOccursDuringVerticalMovement(Up, playerMovement->getVerticalSpeed(), this, world);
			int distance = playerMovement->getVerticalSpeed() - alignment;

			if (!isHittingCeiling(distance)) {
				position->setY(position->getY() - distance);
			}
			else {
				playerMovement->stepsUp = 1;
			}

			if (isHittingBlock(alignment, Up)) {
				hitBlock(world);
				playerMovement->stepsUp = 0;
			}
			else {
				playerMovement->stepsUp--;
			}

			if (isCharacterStandingOnTheBlock(this, world)) {
				model = 0;
				flags.inAirFlag = false;
			}
		}
		 
		if (playerMovement->stepsDown > 0) {
			int alignment = getAlignmentIfCollisionOccursDuringVerticalMovement(Down, playerMovement->getVerticalSpeed(), this, world);
			int distance = playerMovement->getVerticalSpeed() - alignment;

			if (!isFallingIntoAbyss(distance)) {
				position->setY(position->getY() + distance);
			}
			else {
				if (!flags.removeLivesFlag) {
					flags.removeLivesFlag = true;
					statistics.lives--;
					flags.aliveFlag = false;
				}
			}

			playerMovement->stepsDown--;
		}

		changeModelAndAirFlagStatus(world);

		collectCoinIfPossible(this, world);
	}
}

void Player::reborn()
{
	size->setSize(32, 32);
	position->setXY(35, 400);
	model = 0;
	changeModelCounter = 0;
	flags.setDefaultFlags();
	lastDifference = 0;
	currentState = Small;
	movementBlock = false;
	resetMovement();
}
