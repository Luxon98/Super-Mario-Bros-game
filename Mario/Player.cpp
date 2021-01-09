#include "Player.h"

#include "SoundController.h"
#include "World.h"
#include "Camera.h"
#include "CollisionHandling.h"
#include "UtilityFunctions.h"
#include "SDL_Utility.h"


std::array<SDL_Surface*, 140> Player::playerImages;

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
	slideFlag = false;
	changeDirectionFlag = false;
	downPipeFlag = false;
	inAirFlag = false;
	rejumpFlag = false;
}

void Player::Flags::setDefaultFlags(bool armedFlag)
{
	orientationFlag = true;
	aliveFlag = true;
	removeLivesFlag = false;
	this->armedFlag = armedFlag;
	slideFlag = false;
	changeDirectionFlag = false;
	downPipeFlag = false;
	inAirFlag = false;
	rejumpFlag = false;
}

Player::StepsCounter::StepsCounter()
{
	stepsLeft = 0;
	stepsRight = 0;
	stepsUp = 0;
}

int Player::computeImageIndexWhenSliding() const
{
	if (currentState == PlayerState::Small) {
		return (68 + 70 * flags.orientationFlag);
	}
	else if (currentState >= PlayerState::ImmortalSmallFirst && currentState <= PlayerState::ImmortalSmallFourth) {
		return (69 + 70 * flags.orientationFlag);
	}
	else if (currentState == PlayerState::Tall) {
		return (66 + 70 * flags.orientationFlag);
	}
	else {
		return (67 + 70 * flags.orientationFlag);
	}
}

int Player::computeImageIndex() const
{
	if (flags.slideFlag) {
		return computeImageIndexWhenSliding();
	}
	else {
		if (currentState >= PlayerState::Small && currentState <= PlayerState::ImmortalSmallFourth) {
			return (model + 70 * flags.orientationFlag + 5 * (static_cast<int>(currentState) - 1));
		}
		else if (currentState == PlayerState::ImmortalFourth) {
			return (model + 70 * flags.orientationFlag + 10);
		}
		else {
			return (70 * flags.orientationFlag + 65);
		}
	}
}

int Player::getModelDuringFall() const
{
	if (changeModelCounter <= 2) {
		return 1;
	}
	else if (changeModelCounter == 3) {
		return 2;
	}
	else {
		return 3;
	}
}

void Player::changeStateDuringAnimation()
{
	auto timePoint = std::chrono::steady_clock::now();
	auto difference = std::chrono::duration_cast<std::chrono::milliseconds>(timePoint - animationStartTime).count();

	if (currentAnimationState == PlayerAnimation::Growing) {
		performGrowingAnimation(static_cast<int>(difference));
	}
	else if (currentAnimationState == PlayerAnimation::Shrinking) {
		performShrinkingAnimation(static_cast<int>(difference));
	}
	else if (currentAnimationState == PlayerAnimation::Arming) {
		performArmingAnimation(static_cast<int>(difference));
	}
	else if (currentAnimationState == PlayerAnimation::Immortal) {
		performImmortalAnimation(static_cast<int>(difference));
	}
	else if (currentAnimationState == PlayerAnimation::ImmortalSmall) {
		performSmallImmortalAnimation(static_cast<int>(difference));
	}
}

void Player::performGrowingAnimation(int difference)
{
	movementBlock = true;
	model = 0;

	if ((difference >= 100 && difference <= 200 && lastDifference < 100) 
		|| (difference >= 300 && difference <= 400 && lastDifference < 300) 
		|| (difference >= 700 && difference <= 800 && lastDifference < 700)) {

		size.setHeight(48);
		position.setY(position.getY() - 8);
		lastDifference = difference;
		currentState = PlayerState::Average;
	}
	else if ((difference > 200 && difference < 300 && lastDifference < 200) 
		|| (difference > 600 && difference < 700 && lastDifference < 600)) {

		size.setHeight(32);
		position.setY(position.getY() + 8);
		lastDifference = difference;
		currentState = PlayerState::Small;
	}
	else if ((difference > 400 && difference < 500 && lastDifference < 400)
		|| (difference > 800 && difference <= 900 && lastDifference < 800)) {

		size.setHeight(64);
		position.setY(position.getY() - 8);
		lastDifference = difference;
		currentState = PlayerState::Tall;
	}
	else if (difference >= 500 && difference <= 600 && lastDifference < 500) {

		size.setHeight(48);
		position.setY(position.getY() + 8);
		lastDifference = difference;
		currentState = PlayerState::Average;
	}
	else if (difference > 900) {

		currentAnimationState = PlayerAnimation::NoAnimation;
		lastDifference = 0;
		movementBlock = false;
		resetMovement();
	}
}

void Player::performShrinkingAnimation(int difference)
{
	if (difference <= 100 && lastDifference < 10) {
		size.setHeight(32);
		lastDifference = difference;
		currentState = PlayerState::Insensitive;
		resetSteps();
	}
	else if (difference >= 2000) {
		currentAnimationState = PlayerAnimation::NoAnimation;
		currentState = PlayerState::Small;
		lastDifference = 0;
	}
}

void Player::performArmingAnimation(int difference)
{
	movementBlock = true;

	if (isDifferenceInInterval(difference, 0, 600, 3)) {
		currentState = PlayerState::ArmedFirst;
	}
	else if (isDifferenceInInterval(difference, 150, 600, 3)) {
		currentState = PlayerState::Tall;
	}
	else if (isDifferenceInInterval(difference, 300, 600, 3)) {
		currentState = PlayerState::ArmedSecond;
	}
	else if (isDifferenceInInterval(difference, 450, 600, 3)) {
		currentState = PlayerState::ArmedThird;
	}
	else {
		currentAnimationState = PlayerAnimation::NoAnimation;
		currentState = PlayerState::ArmedFirst;
		flags.armedFlag = true;
		lastDifference = 0;
		movementBlock = false;
		resetMovement();
	}
}

void Player::performImmortalAnimation(int difference)
{
	if (isDifferenceInInterval(difference, 0, 600, 20)) {
		currentState = PlayerState::ImmortalFirst;
	}
	else if (isDifferenceInInterval(difference, 150, 600, 20)) {
		currentState = PlayerState::ImmortalSecond;
	}
	else if (isDifferenceInInterval(difference, 300, 600, 20)) {
		currentState = PlayerState::ImmortalThird;
	}
	else if (isDifferenceInInterval(difference, 450, 600, 20)) {
		currentState = PlayerState::ImmortalFourth;
	}
	else {
		currentAnimationState = PlayerAnimation::NoAnimation;
		currentState = (flags.armedFlag ? PlayerState::ArmedFirst : PlayerState::Tall);
		lastDifference = 0;

		SoundController::playBackgroundMusic();
	}
}

void Player::performSmallImmortalAnimation(int difference)
{
	if (isDifferenceInInterval(difference, 0, 600, 20)) {
		currentState = PlayerState::ImmortalSmallFirst;
	}
	else if (isDifferenceInInterval(difference, 150, 600, 20)) {
		currentState = PlayerState::ImmortalSmallSecond;
	}
	else if (isDifferenceInInterval(difference, 300, 600, 20)) {
		currentState = PlayerState::ImmortalSmallThird;
	}
	else if (isDifferenceInInterval(difference, 450, 600, 20)) {
		currentState = PlayerState::ImmortalSmallFourth;
	}
	else {
		currentAnimationState = PlayerAnimation::NoAnimation;
		currentState = PlayerState::Small;
		lastDifference = 0;

		SoundController::playBackgroundMusic();
	}
}

void Player::resetMovement()
{
	resetSteps();
}

void Player::changeModel(World &world)
{
	if (!isCharacterStandingOnSomething(*this, world)) {
		if (flags.inAirFlag) {
			model = 4;
		}
		else {
			model = getModelDuringFall();
		}
		return;
	}

	if (stepsCounter.stepsLeft == 0 && stepsCounter.stepsRight == 0) {
		model = 0;
		return;
	}

	++changeModelCounter;
	if (changeModelCounter % 12 == 0) {
		++model;
		if (model > 3) {
			model = 1;
		}	

		changeModelCounter = 0;
	}
}

bool Player::isHittingCeiling(int distance) const
{
	return (position.getY() - distance - (getHeight() / 2) < -25);
}

bool Player::isFallingIntoAbyss(int distance) const
{
	return (position.getY() + distance + (getHeight() / 2) > World::WORLD_HEIGHT);
}

bool Player::isGoingBeyondCamera(int distance) const
{
	if (position.getX() - camera->getBeginningOfCamera() - distance <= getWidth() / 2) {
		return true;
	}

	return false;
}

bool Player::isHittingBlock(int alignment, Direction direction) const
{
	if (alignment > 0 && direction == Direction::Up) {
		return true;
	}

	return false;
}

bool Player::isDuringAnimation() const
{
	return (currentAnimationState != PlayerAnimation::NoAnimation);
}

bool Player::isAbleToDestroyBlock() const
{
	if ((currentState >= PlayerState::Tall && currentState <= PlayerState::ImmortalThird) 
		|| currentState == PlayerState::ImmortalFourth) {
		
		return true;
	}

	return false;
}

void Player::moveLeft(World &world)
{
	int alignment = computeHorizontalAlignment(Direction::Left, movement.getSpeed(), *this, world);
	int distance = movement.getSpeed() - alignment;

	if (!isGoingBeyondCamera(distance)) {
		position.setX(position.getX() - distance);
	}

	if (alignment != 0 && stepsCounter.stepsUp == 0) {
		stepsCounter.stepsLeft = 0;
	}
	else {
		--stepsCounter.stepsLeft;
	}

	flags.orientationFlag = false;
}

void Player::moveRight(World &world)
{
	int alignment = computeHorizontalAlignment(Direction::Right, movement.getSpeed(), *this, world);
	int distance = movement.getSpeed() - alignment;

	position.setX(position.getX() + distance);

	if (alignment != 0 && stepsCounter.stepsUp == 0) {
		stepsCounter.stepsRight = 0;
	}
	else {
		--stepsCounter.stepsRight;
	}

	flags.orientationFlag = true;
}

void Player::moveUp(World &world)
{
	int alignment = computeVerticalAlignment(Direction::Up, movement.getVerticalSpeed(), *this, world);
	int distance = movement.getVerticalSpeed() - alignment;
	
	if (distance < 0) {
		stepsCounter.stepsUp = 0;
		return;
	}

	if (!isHittingCeiling(distance)) {
		position.setY(position.getY() - distance);
	}
	else {
		stepsCounter.stepsUp = 1;
	}

	if (isHittingBlock(alignment, Direction::Up)) {
		hitBlock(world);
		stepsCounter.stepsUp = 0;
	}
	else {
		--stepsCounter.stepsUp;
	}
	
	if (isCharacterStandingOnSomething(*this, world)) {
		model = 0;
	}
	else if (!flags.rejumpFlag) {
		flags.inAirFlag = true;
	}
}

void Player::moveDown(World &world)
{
	int alignment = computeVerticalAlignment(Direction::Down, movement.getVerticalSpeed(), *this, world);
	int distance = movement.getVerticalSpeed() - alignment;

	if (!isFallingIntoAbyss(distance)) {
		position.setY(position.getY() + distance);
	}
	else {
		if (!flags.removeLivesFlag) {
			flags.removeLivesFlag = true;
			--statistics.lives;
			flags.aliveFlag = false;
		}
	}
}

void Player::slide(World &world)
{
	int alignment = computeVerticalAlignment(Direction::Down, movement.getVerticalSpeed(), *this, world);
	int distance = movement.getVerticalSpeed() - alignment;
	
	if (distance == 0 && !flags.changeDirectionFlag) {
		flags.orientationFlag = false;
		flags.changeDirectionFlag = true;
		position.setX(position.getX() + 16);
	}
	else {
		position.setY(position.getY() + distance);
	}
}

Player::Player(Position position)
{
	size = Size(32, 32);
	movement = Movement(1, 1, Direction::None, Direction::None);
	statistics = Statistics();
	flags = Flags();
	stepsCounter = StepsCounter();
	this->position = position;
	model = 0;
	changeModelCounter = 0;
	lastDifference = 0;
	currentAnimationState = PlayerAnimation::NoAnimation;
	currentState = PlayerState::Small;
	movementBlock = false;
}

void Player::loadPlayerImages(SDL_Surface* display)
{
	for (std::size_t i = 0; i < playerImages.size() / 2; ++i) {
		std::string filename = "./img/mario_imgs/mario_left";
		filename += std::to_string(i + 1);
		filename += ".png";
		playerImages[i] = loadPNG(filename, display);
		filename.replace(23, 4, "right");
		playerImages[i + (playerImages.size() / 2)] = loadPNG(filename, display);
	}
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

int Player::getDeadMarioImageIndex() const
{
	if (currentState == PlayerState::ArmedFirst || currentState == PlayerState::ImmortalFourth
		|| currentState == PlayerState::ImmortalSmallFourth) {
		return 1;
	}
	else if (currentState == PlayerState::ImmortalFirst || currentState == PlayerState::ImmortalSmallFirst) {
		return 2;
	}
	else if (currentState == PlayerState::ImmortalSecond || currentState == PlayerState::ImmortalSmallSecond) {
		return 3;
	}
	else if (currentState == PlayerState::ImmortalThird || currentState == PlayerState::ImmortalSmallThird) {
		return 4;
	}

	return 0;
}

bool Player::isSmall() const
{
	return (currentState == PlayerState::Small);
}

bool Player::isArmed() const
{
	return flags.armedFlag;
}

bool Player::isInsensitive() const
{
	if (currentState == PlayerState::Insensitive || currentAnimationState == PlayerAnimation::Growing) {
		return true;
	}
	
	return false;
}

bool Player::isImmortal() const
{
	return ((currentState >= PlayerState::ImmortalFirst && currentState <= PlayerState::ImmortalFourth) 
		&& currentState != PlayerState::Insensitive);
}

bool Player::isDead() const
{
	return !flags.aliveFlag;
}

bool Player::isTurnedRight() const
{
	return flags.orientationFlag;
}

bool Player::isPerformingJumpAsSmall() const
{
	if (isSmall() || isInsensitive()) {
		return true;
	}
	else if (currentState >= PlayerState::ImmortalSmallFirst && currentState <= PlayerState::ImmortalSmallFourth) {
		return true;
	}

	return false;
}

bool Player::isGoingToPipe() const
{
	if (flags.downPipeFlag && stepsCounter.stepsUp == 0 && currentState != PlayerState::Insensitive) {
		return true;
	}

	return false;
}

bool Player::isNotJumpingUp() const
{
	if (stepsCounter.stepsUp < 50) {
		return true;
	}

	return false;
}

bool Player::isStillRunning()
{
	return (stepsCounter.stepsRight != 0);
}

SDL_Surface* Player::getImage() const
{
	return playerImages[computeImageIndex()];
}

void Player::incrementCoins()
{
	if (statistics.coins == 99) {
		statistics.coins = 0;
		++statistics.lives;
		SoundController::playNewLiveAddedEffect();
	}
	else {
		++statistics.coins;
	}
}

void Player::incrementLives()
{
	++statistics.lives;
}

void Player::addPoints(int pts)
{
	statistics.points += pts;
}

void Player::setCurrentAnimation(PlayerAnimation animation)
{
	currentAnimationState = animation;
	animationStartTime = std::chrono::steady_clock::now();
}

void Player::setCamera(std::shared_ptr<Camera> camera)
{
	this->camera = std::move(camera);
}

void Player::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	int index = computeImageIndex();
	SDL_Surface* playerImg = playerImages[index];
	drawSurface(display, playerImg, position.getX() - beginningOfCamera, position.getY());
}

void Player::forceMovement(Direction direction)
{
	if (direction == Direction::Left) {
		if (!isGoingBeyondCamera(1)) {
			position.setX(position.getX() - 1);
		}
	}
	else if (direction == Direction::Right) {
		position.setX(position.getX() + 1);
	}
	else if (direction == Direction::Up) {
		if (!isHittingCeiling(1)) {
			position.setY(position.getY() - 1);
		}
	}
	else {
		if (!isFallingIntoAbyss(1)) {
			position.setY(position.getY() + 1);
		}
	}
}

void Player::hitBlock(World &world)
{
	if (isAbleToDestroyBlock() && world.getLastTouchedBlockType() == BlockType::Destructible) {
		world.destroyLastTouchedBlock();
	}
	else {
		world.hitBlock();
	}
}

void Player::loseBonusOrLife()
{
	if (currentState == PlayerState::Tall || currentState == PlayerState::ArmedFirst) {
		currentAnimationState = PlayerAnimation::Shrinking;
		flags.armedFlag = false;
		animationStartTime = std::chrono::steady_clock::now();
		SoundController::playBonusLostEffect();
	}
	else if (!isDuringAnimation()) {
		if (!flags.removeLivesFlag) {
			flags.removeLivesFlag = true;
			--statistics.lives;
			flags.aliveFlag = false;
		}
	}
}

void Player::performAdditionalJump()
{
	stepsCounter.stepsUp = 40;
	flags.rejumpFlag = true;
}

void Player::move(World &world)
{
	if (isDuringAnimation()) {
		changeStateDuringAnimation();
	}

	if (!movementBlock) {
		if (flags.slideFlag) {
			slide(world);
		}
		else {
			if (stepsCounter.stepsUp > 0) {
				moveUp(world);
			}
			else if (!isCharacterStandingOnSomething(*this, world)) {
				moveDown(world);
			}
			else {
				flags.inAirFlag = false;
				flags.rejumpFlag = false;
			}

			if (stepsCounter.stepsLeft > 0) {
				moveLeft(world);
			}
			else if (stepsCounter.stepsRight > 0) {
				moveRight(world);
			}

			changeModel(world);
		}

		flags.downPipeFlag = false;
	}
}

void Player::setPositionXY(int level)
{
	if (level == 1) {
		position.setXY(35, 400);
	}
	else if (level == 2) {
		position.setXY(80, 140);
	}
	else if (level == 3) {
		position.setXY(80, 400);
	}
	else if (level == 4) {
		int posY = (this->isSmall() ? 208 : 192);
		position.setXY(50, posY);
	}
	else if (level == 77) {
		position.setXY(145, 400);
	}
	else if (level == 88) {
		position.setXY(245, 160);
	}
}

void Player::setPositionXY(int level, int checkPointMark)
{
	int posY = (this->isSmall() ? 337 : 321);
	if (level == 1) {
		if (checkPointMark == 1) {
			position.setXY(70, 60);
		}
		else if (checkPointMark == 2) {
			position.setXY(5246, posY);
		}
	}
	else if (level == 2) {
		if (checkPointMark == 1) {
			position.setXY(70, 60);
		}
		else if (checkPointMark == 2) {
			position.setXY(3712, posY);
		}
		else if (checkPointMark == 3) {
			position.setXY(128, posY);
		}
	}
	else if (level == 77) {
		if (checkPointMark == 1) {
			position.setXY(85, 60);
		}
		else if (checkPointMark == 2) {
			position.setXY(6960, posY);
		}
		else if (checkPointMark == 3) {
			position.setXY(77, posY - 32);
		}
	}
	else if (level == 88) {
		if (checkPointMark == 1 || checkPointMark == 4) {
			position.setXY(96, posY);
		}
		else if (checkPointMark == 2) {
			position.setXY(3184, posY - 224);
		}
		else if (checkPointMark == 3 || checkPointMark == 5) {
			position.setXY(160, posY);
		}
		else if (checkPointMark == 6) {
			position.setXY(304, posY - 128);
		}
	}
}

void Player::reborn(int level)
{
	size.setSize(32, 32);
	setPositionXY(level);
	model = 0;
	changeModelCounter = 0;
	flags.setDefaultFlags(false);
	lastDifference = 0;
	currentState = PlayerState::Small;
	currentAnimationState = PlayerAnimation::NoAnimation;
	movementBlock = false;
	resetMovement();
}

void Player::resetModel()
{
	model = 0;
	flags.orientationFlag = true;
}

void Player::resetSteps()
{
	stepsCounter.stepsLeft = 0;
	stepsCounter.stepsRight = 0;
	stepsCounter.stepsUp = 0;
}

void Player::setSlidingParameters()
{
	resetSteps();
	flags.slideFlag = true;
	position.setX(position.getX() - 8);
}

void Player::setFinishingRunParameters(int distance)
{
	resetMovement();
	stepsCounter.stepsRight = distance;
	changeModelCounter = 0;
	model = 0;
	flags.setDefaultFlags(flags.armedFlag);
}