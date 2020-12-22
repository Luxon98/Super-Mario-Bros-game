#include "SoundController.h"

#include "Player.h"
#include "World.h"
#include "LayoutStyle.h"


std::array<Mix_Music*, 8> SoundController::backgroundTracks;
std::array<Mix_Chunk*, 20> SoundController::soundsEffects;

void SoundController::loadBackgroundTracks()
{
	backgroundTracks[0] = Mix_LoadMUS("./sounds/background_open.wav");
	backgroundTracks[1] = Mix_LoadMUS("./sounds/background_underground.wav");
	backgroundTracks[2] = Mix_LoadMUS("./sounds/background_castle.wav");
	backgroundTracks[3] = Mix_LoadMUS("./sounds/background_winter.wav");
	backgroundTracks[4] = Mix_LoadMUS("./sounds/background_summer.wav");
	backgroundTracks[5] = Mix_LoadMUS("./sounds/background_star.wav");
	backgroundTracks[6] = Mix_LoadMUS("./sounds/time_passed.wav");
	backgroundTracks[7] = Mix_LoadMUS("./sounds/game_over.wav");
}

void SoundController::loadSoundEffects()
{
	soundsEffects[0] = Mix_LoadWAV("./sounds/1up_collected.wav");
	soundsEffects[1] = Mix_LoadWAV("./sounds/block_destroyed.wav");
	soundsEffects[2] = Mix_LoadWAV("./sounds/block_hitted.wav");
	soundsEffects[3] = Mix_LoadWAV("./sounds/bonus_appeard.wav");
	soundsEffects[4] = Mix_LoadWAV("./sounds/bonus_collected.wav");
	soundsEffects[5] = Mix_LoadWAV("./sounds/coin_sound.wav");
	soundsEffects[6] = Mix_LoadWAV("./sounds/enemy_destroyed.wav");
	soundsEffects[7] = Mix_LoadWAV("./sounds/fireball_popped.wav");
	soundsEffects[8] = Mix_LoadWAV("./sounds/flag_down.wav");
	soundsEffects[9] = Mix_LoadWAV("./sounds/jump_small.wav");
	soundsEffects[10] = Mix_LoadWAV("./sounds/jump_tall.wav");
	soundsEffects[11] = Mix_LoadWAV("./sounds/mario_dead.wav");
	soundsEffects[12] = Mix_LoadWAV("./sounds/back_to_small.wav");
	soundsEffects[13] = Mix_LoadWAV("./sounds/menu_return.wav");
	soundsEffects[14] = Mix_LoadWAV("./sounds/fire_rocket.wav");
	soundsEffects[15] = Mix_LoadWAV("./sounds/boss_destroyed.wav");
	soundsEffects[16] = Mix_LoadWAV("./sounds/fireworks.wav");
	soundsEffects[17] = Mix_LoadWAV("./sounds/getting_points.wav");
	soundsEffects[18] = Mix_LoadWAV("./sounds/level_finished.wav");
	soundsEffects[19] = Mix_LoadWAV("./sounds/world_finished.wav");
}

int SoundController::getIndexOfBackgroundMusic()
{
	switch (World::LAYOUT_STYLE) {
	case LayoutStyle::OpenWorld:
		return 0;
	case LayoutStyle::Underground:
		return 1;
	case LayoutStyle::Castle:
		return 2;
	case LayoutStyle::CustomWinter:
		return 3;
	default:
		return 4;
	}
}

bool SoundController::initSoundMixer()
{
	bool success = true;
	if (Mix_OpenAudio(16000, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
		success = false;
	}

	return success;
}

void SoundController::loadSounds()
{
	loadBackgroundTracks();
	loadSoundEffects();
}

void SoundController::playBackgroundMusic()
{
	stopMusic();

	int musicIndex = getIndexOfBackgroundMusic();
	Mix_PlayMusic(backgroundTracks[musicIndex], -1);
}

void SoundController::playStarMusic()
{
	stopMusic();
	Mix_PlayMusic(backgroundTracks[5], -1);
}

void SoundController::playTimePassedMusic()
{
	stopMusic();
	Mix_PlayMusic(backgroundTracks[6], -1);
}

void SoundController::playGameOverMusic()
{
	stopMusic();
	Mix_PlayMusic(backgroundTracks[7], -1);
}

void SoundController::playNewLiveAddedEffect()
{
	Mix_PlayChannel(-1, soundsEffects[0], 0);
}

void SoundController::playBlockDestroyedEffect()
{
	Mix_PlayChannel(-1, soundsEffects[1], 0);
}

void SoundController::playBlockHittedEffect()
{
	Mix_PlayChannel(-1, soundsEffects[2], 0);
}

void SoundController::playBonusAppearedEffect()
{
	Mix_PlayChannel(-1, soundsEffects[3], 0);
}

void SoundController::playBonusCollectedEffect()
{
	Mix_PlayChannel(-1, soundsEffects[4], 0);
}

void SoundController::playCoinCollectedEffect()
{
	Mix_PlayChannel(-1, soundsEffects[5], 0);
}

void SoundController::playEnemyDestroyedEffect(bool bossFlag)
{
	Mix_PlayChannel(-1, soundsEffects[bossFlag ? 15 : 6], 0);
}

void SoundController::playFireballPoppedEffect()
{
	Mix_PlayChannel(-1, soundsEffects[7], 0);
}

void SoundController::playFlagDownEffect()
{
	Mix_PlayChannel(-1, soundsEffects[8], 0);
}

void SoundController::playJumpEffect(Player &player)
{
	Mix_PlayChannel(-1, soundsEffects[player.isPerformingJumpAsSmall() ? 9 : 10], 0);
}

void SoundController::playMarioDeadEffect()
{
	Mix_PlayChannel(-1, soundsEffects[11], 0);
}

void SoundController::playBonusLostEffect()
{
	Mix_PlayChannel(-1, soundsEffects[12], 0);
}

void SoundController::playPipeTravelEffect()
{
	Mix_PlayChannel(-1, soundsEffects[12], 0);
}

void SoundController::playSubmenuEffect()
{
	Mix_PlayChannel(-1, soundsEffects[5], 0);
}

void SoundController::playReturnedToMenuEffect()
{
	Mix_PlayChannel(-1, soundsEffects[13], 0);
}

void SoundController::playFireRocketEffect()
{
	Mix_PlayChannel(-1, soundsEffects[14], 0);
}

void SoundController::playFireworksEffect()
{
	Mix_PlayChannel(-1, soundsEffects[16], 0);
}

void SoundController::playBombDroppedEffect()
{
	Mix_PlayChannel(-1, soundsEffects[6], 0);
}

void SoundController::playGettingPointsEffect()
{
	Mix_PlayChannel(-1, soundsEffects[17], 0);
}

void SoundController::playLevelFinishedEffect()
{
	stopMusic();
	Mix_PlayChannel(-1, soundsEffects[18], 0);
}

void SoundController::playWorldFinishedEffect()
{
	stopMusic();
	Mix_PlayChannel(-1, soundsEffects[19], 0);
}

void SoundController::stopMusic()
{
	Mix_HaltMusic();
}

void SoundController::closeSoundController()
{
	for (std::size_t i = 0; i < backgroundTracks.size(); ++i) {
		Mix_FreeMusic(backgroundTracks[i]);
	}

	for (std::size_t j = 0; j < soundsEffects.size(); ++j) {
		Mix_FreeChunk(soundsEffects[j]);
	}

	Mix_Quit();
}