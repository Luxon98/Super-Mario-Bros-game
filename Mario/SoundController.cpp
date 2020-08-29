#include "SoundController.h"

#include "Player.h"


Mix_Music* SoundController::backgroundTracks[6] = { nullptr };

Mix_Chunk* SoundController::soundsEffects[13] = { nullptr };

bool SoundController::initSoundMixer()
{
	bool success = true;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		success = false;
	}

	return success;
}

void SoundController::loadSounds()
{
	backgroundTracks[0] = Mix_LoadMUS("./sounds/background.wav");
	backgroundTracks[1] = Mix_LoadMUS("./sounds/background_normal.wav");
	backgroundTracks[2] = Mix_LoadMUS("./sounds/background_star.wav");
	backgroundTracks[3] = Mix_LoadMUS("./sounds/world_finished.wav");
	backgroundTracks[4] = Mix_LoadMUS("./sounds/gameover.wav");
	backgroundTracks[5] = Mix_LoadMUS("./sounds/time_passed.wav");

	soundsEffects[0] = Mix_LoadWAV("./sounds/1up_collected.wav");
	soundsEffects[1] = Mix_LoadWAV("./sounds/block_destroyed.wav");
	soundsEffects[2] = Mix_LoadWAV("./sounds/block_hitted.wav");
	soundsEffects[3] = Mix_LoadWAV("./sounds/bonus_appeard.wav");
	soundsEffects[4] = Mix_LoadWAV("./sounds/bonus_collected.wav");
	soundsEffects[5] = Mix_LoadWAV("./sounds/coin_collected.wav");
	soundsEffects[6] = Mix_LoadWAV("./sounds/enemy_destroyed.wav");
	soundsEffects[7] = Mix_LoadWAV("./sounds/fireball_popped.wav");
	soundsEffects[8] = Mix_LoadWAV("./sounds/flag_down.wav");
	soundsEffects[9] = Mix_LoadWAV("./sounds/jump_small.wav");
	soundsEffects[10] = Mix_LoadWAV("./sounds/jump_tall.wav");
	soundsEffects[11] = Mix_LoadWAV("./sounds/mario_dead.wav");
	soundsEffects[12] = Mix_LoadWAV("./sounds/back_to_small.wav");
}

void SoundController::closeSoundMixer()
{
	for (int i = 1; i < 6; ++i) {
		Mix_FreeMusic(backgroundTracks[i]);
		backgroundTracks[i] = nullptr;
	}

	for (int i = 0; i < 12; ++i) {
		Mix_FreeChunk(soundsEffects[i]);
		soundsEffects[i] = nullptr;
	}

	Mix_Quit();
}

SoundController::SoundController()
{
	if (initSoundMixer()) {
		loadSounds();
	}
}

void SoundController::playBackgroudMarioMusic()
{
	Mix_PlayMusic(backgroundTracks[1], -1);
}

void SoundController::playBackgroudStarMusic()
{
	Mix_PlayMusic(backgroundTracks[2], -1);
}

void SoundController::playWorldFinishedMusic()
{
	Mix_PlayMusic(backgroundTracks[3], -1);
}

void SoundController::playGameoverMusic()
{
	Mix_PlayMusic(backgroundTracks[4], -1);
}

void SoundController::playTimePassedMusic()
{
	Mix_PlayMusic(backgroundTracks[5], -1);
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

void SoundController::playBonusAppeardEffect()
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

void SoundController::playEnemyDestroyedEffect()
{
	Mix_PlayChannel(-1, soundsEffects[6], 0);
}

void SoundController::playFireballPoppedEffect()
{
	Mix_PlayChannel(-1, soundsEffects[7], 0);
}

void SoundController::playFlagDownEffect()
{
	Mix_PlayChannel(-1, soundsEffects[8], 0);
}

void SoundController::playJumpEffect(Player* player)
{
	Mix_PlayChannel(-1, soundsEffects[player->isSmall() ? 9 : 10], 0);
}

void SoundController::playBonusLostEffect()
{
	Mix_PlayChannel(-1, soundsEffects[12], 0);
}

void SoundController::playMarioDeadEffect()
{
	Mix_PlayChannel(-1, soundsEffects[11], 0);
}

void SoundController::stopMusic()
{
	Mix_HaltMusic();
}

SoundController::~SoundController()
{
	closeSoundMixer();
}
