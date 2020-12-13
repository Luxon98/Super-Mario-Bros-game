#ifndef SoundController_H
#define SoundController_H

#include <SDL_mixer.h>
#include <array>

class Player;
class World;


class SoundController final
{
private:
	// tracks and sound effects are declared as static here, because functions from SDL_mixer library require it
	static std::array<Mix_Music*, 8> backgroundTracks;
	static std::array<Mix_Chunk*, 20> soundsEffects;
	static void loadBackgroundTracks();
	static void loadSoundEffects();
	static int getIndexOfBackgroundMusic();

public:
	SoundController() = delete;
	static bool initSoundMixer();
	static void loadSounds();
	static void playBackgroundMusic();
	static void playStarMusic();
	static void playTimePassedMusic();
	static void playGameOverMusic();
	static void playNewLiveAddedEffect();
	static void playBlockDestroyedEffect();
	static void playBlockHittedEffect();
	static void playBonusAppearedEffect();
	static void playBonusCollectedEffect();
	static void playCoinCollectedEffect();
	static void playEnemyDestroyedEffect(bool bossFlag = false);
	static void playFireballPoppedEffect();
	static void playFlagDownEffect();
	static void playJumpEffect(Player &player);
	static void playMarioDeadEffect();
	static void playBonusLostEffect();
	static void playPipeTravelEffect();
	static void playSubmenuEffect();
	static void playReturnedToMenuEffect();
	static void playFireRocketEffect();
	static void playFireworksEffect();
	static void playGettingPointsEffect();
	static void playLevelFinishedEffect();
	static void playWorldFinishedEffect();
	static void stopMusic();
	static void closeSoundController();
};

#endif //SoundController_H