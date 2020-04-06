#ifndef _SoundController_H
#define _SoundController_H

#include <SDL_mixer.h>
#include "Player.h"


class SoundController {
private:
	static Mix_Music* backgroundTracks[5];
	static Mix_Chunk* soundsEffects[12];
	bool initSoundMixer();
	void loadSounds();
	void closeSoundMixer();

public:
	SoundController();
	static void playBackgroudMarioMusic();
	static void playBackgroudStarMusic();
	static void playWorldFinishedMusic();
	static void playGameoverMusic();
	static void playTimePassedMusic();
	static void play1upCollectedEffect();
	static void playBlockDestroyedEffect();
	static void playBlockHittedEffect();
	static void playBonusAppeardEffect();
	static void playBonusCollectedEffect();
	static void playCoinCollectedEffect();
	static void playEnemyDestroyedEffect();
	static void playFireballPoppedEffect();
	static void playFlagDownEffect();
	static void playJumpEffect(Player* player);
	static void playMarioDeadEffect();
	static void stopMusic();
	~SoundController();
};

#endif
