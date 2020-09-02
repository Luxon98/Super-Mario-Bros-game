#ifndef SoundController_H
#define SoundController_H

#include <SDL_mixer.h>
#include <array>

class Player;


class SoundController
{
private:
	// track and sound effect are declared as static here, because SDL_mixer library requires it
	static std::array<Mix_Music*, 5> backgroundTracks;
	static std::array<Mix_Chunk*, 13> soundsEffects;
	bool initSoundMixer();

public:
	SoundController();
	void loadSounds();
	static void playBackgroudMarioMusic();
	static void playBackgroudStarMusic();
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
