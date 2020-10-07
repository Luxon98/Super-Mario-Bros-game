#ifndef SoundController_H
#define SoundController_H

#include <SDL_mixer.h>
#include <array>

class Player;


class SoundController
{
private:
	// tracks and sound effects are declared as static here, because functions from SDL_mixer library require it
	static std::array<Mix_Music*, 7> backgroundTracks;
	static std::array<Mix_Chunk*, 13> soundsEffects;
	bool initSoundMixer();
	void loadBackgroundTracks();
	void loadSoundEffects();

public:
	SoundController();
	void loadSounds();
	static void playOpenWorldMusic();
	static void playUndergroundMusic();
	static void playCastleMusic();
	static void playStarMusic();
	static void playWorldFinishedMusic();
	static void playGameoverMusic();
	static void playTimePassedMusic();
	static void playNewLiveAddedEffect();
	static void playBlockDestroyedEffect();
	static void playBlockHittedEffect();
	static void playBonusAppeardEffect();
	static void playBonusCollectedEffect();
	static void playCoinCollectedEffect();
	static void playEnemyDestroyedEffect();
	static void playFireballPoppedEffect();
	static void playFlagDownEffect();
	static void playJumpEffect(Player &player);
	static void playBonusLostEffect();
	static void playMarioDeadEffect();
	static void stopMusic();
	~SoundController();
};

#endif //SoundController_H