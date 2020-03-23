#include "GameFunctions.h"

bool isDifferenceInInterval(int difference, int begin, int shift, int repetitions) {
	for (int i = begin, j = 0; j < repetitions; i += shift, ++j) {
		if (difference >= i && difference <= i + 150) {
			return true;
		}
	}
	return false;
}

void loadBonusObjectsImages(SDL_Surface* screen) {
	Flower* tempFlower = new Flower();
	tempFlower->loadFlowerImages(screen);
	delete tempFlower;

	Mushroom* tempMushroom = new Mushroom();
	tempMushroom->loadMushroomImages(screen);
	delete tempMushroom;

	Star* tempStar = new Star();
	tempStar->loadStarImages(screen);
	delete tempStar;

	Coin* tempCoin = new Coin();
	tempCoin->loadCoinImages(screen);
	delete tempCoin;
}

void loadInanimateObjectImages(SDL_Surface* screen) {
	Bush* tempBush = new Bush();
	tempBush->loadBushImages(screen);
	delete tempBush;

	Cloud* tempCloud = new Cloud();
	tempCloud->loadCloudImages(screen);
	delete tempCloud;

	Castle* tempCastle = new Castle();
	tempCastle->loadCastleImages(screen);
	delete tempCastle;

	Flag* tempFlag = new Flag();
	tempFlag->loadFlagImage(screen);
	delete tempFlag;
}

void loadLivingObjectImages(SDL_Surface* screen) {
	Creature* tempCreature = new Creature();
	tempCreature->loadCreatureImages(screen);
	delete tempCreature;

	Turtle* tempTurtle = new Turtle();
	tempTurtle->loadTurtleImages(screen);
	delete tempTurtle;

	Shell* tempShell = new Shell();
	tempShell->loadShellImage(screen);
	delete tempShell;

	FireBall* tempFireBall = new FireBall();
	tempFireBall->loadFireBallImages(screen);
	delete tempFireBall;

	Player* tempPlayer = new Player();
	tempPlayer->loadPlayerImages(screen);
	delete tempPlayer;
}

void loadTemporaryObjectImages(SDL_Surface* screen) {
	CrushedCreature* tempCrushedCreature = new CrushedCreature();
	tempCrushedCreature->loadCrushedCreatureImage(screen);
	delete tempCrushedCreature;

	DestroyedCreature* tempDestroyedCreature = new DestroyedCreature();
	tempDestroyedCreature->loadDestroyedCreatureImage(screen);
	delete tempDestroyedCreature;

	DestroyedTurtle* tempDestroyedTurtle = new DestroyedTurtle();
	tempDestroyedTurtle->loadDestroyedTurtleImage(screen);
	delete tempDestroyedTurtle;

	Explosion* tempExplosion = new Explosion();
	tempExplosion->loadExplosionImage(screen);
	delete tempExplosion;

	Shards* tempShards = new Shards();
	tempShards->loadShardsImages(screen);
	delete tempShards;

	AnimatedCoin* tempAnimatedCoin = new AnimatedCoin();
	tempAnimatedCoin->loadAnimatedCoinImages(screen);
	delete tempAnimatedCoin;

	AnimatedText* tempAnimatedText = new AnimatedText();
	tempAnimatedText->loadAnimatedTextImages(screen);
	delete tempAnimatedText;
}

void loadBlockImages(SDL_Surface* screen) {
	Block* tempBlock = new Block();
	tempBlock->loadBlockImages(screen);
	delete tempBlock;
}

void loadImages(SDL_Surface* screen) {
	loadBonusObjectsImages(screen);
	loadInanimateObjectImages(screen);
	loadLivingObjectImages(screen);
	loadTemporaryObjectImages(screen);
	loadBlockImages(screen);
}

void runGame() {
	bool playerState, winStatus = false, timeState = true;
	std::chrono::steady_clock::time_point timePoint, timeBegin;
	SDL_Event event;
	World world = World();
	SoundController soundMixer = SoundController();

	Screen* windowScreen = new Screen();
	windowScreen->setTimeBegin(std::chrono::steady_clock::now());

	KeyboardController controller = KeyboardController();
	const Uint8* state = SDL_GetKeyboardState(NULL);

	loadImages(windowScreen->getScreen());

	if (!windowScreen->getInitStatus()) {
		Player* player = new Player(35, 400);
		world.setPlayer(player);
		windowScreen->setPlayer(player);

		while (player->getLives() && !winStatus) {
			controller.clearKeysState();
			player->reborn();
			playerState = true;
			Level::setFirstLevel(world);
			windowScreen->resetScreen();
			timeBegin = std::chrono::steady_clock::now();
			while (std::chrono::duration_cast<std::chrono::milliseconds>(timePoint - timeBegin).count() <= 3000) {
				windowScreen->drawStartScreen(world);
				timePoint = std::chrono::steady_clock::now();
			}

			SoundController::stopMusic();
			SoundController::playBackgroudMarioMusic();

			while (playerState && timeState && !winStatus) {
				windowScreen->updateScreen(world);

				while (SDL_PollEvent(&event) && playerState) {
					controller.handleKeysState(state);
					controller.forceActions(player, world, windowScreen);
					if (player->isDead()) {
						playerState = false;
					}
					controller.clearKeysState();
				}

				if (playerState) {
					controller.forceActions(player, world, windowScreen);
				}

				if (player->getPositionX() >= 6350 && player->getPositionX() <= 6400 && !winStatus) {
					SoundController::playFlagDownEffect();
					world.setActiveFlag();
					winStatus = true;
					while (!world.isFlagDown()) {
						world.performActions();
						windowScreen->updateScreen(world);
					}
					player->move(Right, 25, world, windowScreen);
					player->jump(Down, 35, world, windowScreen);
					player->move(Right, 6540 - player->getPositionX(), world, windowScreen);

					windowScreen->drawWorldFinishedScreen(world);
				}

				if (player->isDead()) {
					playerState = false;
				}
				else if (windowScreen->isTimePassed() && !winStatus) {
					timeState = false;
				}
			}
			if (!playerState) {
				windowScreen->drawDeadMario(world);
			}
			else if (!timeState) {
				windowScreen->drawTimeUpScreen(world);
				SoundController::stopMusic();
				SoundController::playTimePassedMusic();
			}
		}
	}

	timeBegin = std::chrono::steady_clock::now();
	while (std::chrono::duration_cast<std::chrono::milliseconds>(timePoint - timeBegin).count() <= 3000 && !winStatus) {
		windowScreen->drawGameOverScreen(world);
		timePoint = std::chrono::steady_clock::now();
	}
}