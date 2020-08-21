#include "GameFunctions.h"

bool isDifferenceInInterval(int difference, int begin, int shift, int repetitions)
{
	for (int i = begin, j = 0; j < repetitions; i += shift, ++j) {
		if (difference >= i && difference <= i + 150) {
			return true;
		}
	}
	return false;
}

void loadBonusObjectsImages(SDL_Surface* display)
{
	Flower* tempFlower = new Flower();
	tempFlower->loadFlowerImages(display);
	delete tempFlower;

	Mushroom* tempMushroom = new Mushroom();
	tempMushroom->loadMushroomImages(display);
	delete tempMushroom;

	Star* tempStar = new Star();
	tempStar->loadStarImages(display);
	delete tempStar;

	Coin* tempCoin = new Coin();
	tempCoin->loadCoinImages(display);
	delete tempCoin;
}

void loadInanimateObjectImages(SDL_Surface* display)
{
	Bush* tempBush = new Bush();
	tempBush->loadBushImages(display);
	delete tempBush;

	Cloud* tempCloud = new Cloud();
	tempCloud->loadCloudImages(display);
	delete tempCloud;

	Castle* tempCastle = new Castle();
	tempCastle->loadCastleImages(display);
	delete tempCastle;

	Flag* tempFlag = new Flag();
	tempFlag->loadFlagImages(display);
	delete tempFlag;
}

void loadLivingObjectImages(SDL_Surface* display)
{
	Creature* tempCreature = new Creature();
	tempCreature->loadCreatureImages(display);
	delete tempCreature;

	Turtle* tempTurtle = new Turtle();
	tempTurtle->loadTurtleImages(display);
	delete tempTurtle;

	Shell* tempShell = new Shell();
	tempShell->loadShellImage(display);
	delete tempShell;

	FireBall* tempFireBall = new FireBall();
	tempFireBall->loadFireBallImages(display);
	delete tempFireBall;

	Player* tempPlayer = new Player();
	tempPlayer->loadPlayerImages(display);
	delete tempPlayer;
}

void loadTemporaryObjectImages(SDL_Surface* display)
{
	CrushedCreature* tempCrushedCreature = new CrushedCreature();
	tempCrushedCreature->loadCrushedCreatureImage(display);
	delete tempCrushedCreature;

	DestroyedCreature* tempDestroyedCreature = new DestroyedCreature();
	tempDestroyedCreature->loadDestroyedCreatureImage(display);
	delete tempDestroyedCreature;

	DestroyedTurtle* tempDestroyedTurtle = new DestroyedTurtle();
	tempDestroyedTurtle->loadDestroyedTurtleImage(display);
	delete tempDestroyedTurtle;

	Explosion* tempExplosion = new Explosion();
	tempExplosion->loadExplosionImage(display);
	delete tempExplosion;

	Shards* tempShards = new Shards();
	tempShards->loadShardsImages(display);
	delete tempShards;

	AnimatedCoin* tempAnimatedCoin = new AnimatedCoin();
	tempAnimatedCoin->loadAnimatedCoinImages(display);
	delete tempAnimatedCoin;

	AnimatedText* tempAnimatedText = new AnimatedText();
	tempAnimatedText->loadAnimatedTextImages(display);
	delete tempAnimatedText;
}

void loadBlockImages(SDL_Surface* display)
{
	Block* tempBlock = new Block();
	tempBlock->loadBlockImages(display);
	delete tempBlock;
}

void loadImages(SDL_Surface* display)
{
	loadBonusObjectsImages(display);
	loadInanimateObjectImages(display);
	loadLivingObjectImages(display);
	loadTemporaryObjectImages(display);
	loadBlockImages(display);
}

void runGame()
{
	bool playerState, winStatus = false, timeState = true;
	std::chrono::steady_clock::time_point timePoint, timeBegin;
	SDL_Event event;
	World world = World();
	SoundController soundMixer = SoundController();

	Screen* screen = new Screen();
	screen->setTimeBegin(std::chrono::steady_clock::now());

	KeyboardController controller = KeyboardController();
	const Uint8* state = SDL_GetKeyboardState(NULL);

	loadImages(screen->getDisplay());

	if (!screen->getInitStatus()) {
		Player* player = new Player(new Position(35, 400));
		world.setPlayer(player);
		world.setScreen(screen);
		screen->setPlayer(player);

		while (player->getLives() && !winStatus) {
			controller.clearKeysState();
			player->reborn();
			playerState = true;
			Level::setFirstLevel(world);
			screen->resetScreen();
			timeBegin = std::chrono::steady_clock::now();
			while (std::chrono::duration_cast<std::chrono::milliseconds>(timePoint - timeBegin).count() <= 3000) {
				screen->drawStartScreen();
				timePoint = std::chrono::steady_clock::now();
			}

			SoundController::stopMusic();
			SoundController::playBackgroudMarioMusic();

			while (playerState && timeState && !winStatus) {
				screen->updateScreen(world);

				while (SDL_PollEvent(&event) && playerState) {
					controller.handleKeysState(state);
					controller.handleKeys(player, world);
					if (player->isDead()) {
						playerState = false;
					}
					controller.clearKeysState();
				}

				if (playerState) {
					controller.handleKeys(player, world);
				}

				if (player->getX() >= 6350 && player->getX() <= 6400 && !winStatus) {
					SoundController::playFlagDownEffect();
					world.switchOnFlag();
					winStatus = true;
					player->resetSteps();
					
					while (!world.isFlagDown()) {
						world.performActions();
						screen->updateScreen(world);
					}
					player->setFinishingRunParameters();

					screen->drawWorldFinishedScreen(world);
				}

				if (player->isDead()) {
					playerState = false;
				}
				else if (screen->isTimePassed() && !winStatus) {
					timeState = false;
				}
			}
			if (!playerState) {
				screen->drawDeadMario(world);
			}
			else if (!timeState) {
				screen->drawTimeUpScreen();
				SoundController::stopMusic();
				SoundController::playTimePassedMusic();
			}
		}
	}

	timeBegin = std::chrono::steady_clock::now();
	while (std::chrono::duration_cast<std::chrono::milliseconds>(timePoint - timeBegin).count() <= 3000 && !winStatus) {
		screen->drawGameOverScreen();
		timePoint = std::chrono::steady_clock::now();
	}
}