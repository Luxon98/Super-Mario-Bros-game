#include "SoundController.h"

Mix_Music* SoundController::backgroundTracks[5] = { nullptr };

Mix_Chunk* SoundController::soundsEffects[12] = { nullptr };

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
	this->backgroundTracks[0] = Mix_LoadMUS("./sounds/background_normal.wav");
	this->backgroundTracks[1] = Mix_LoadMUS("./sounds/background_star.wav");
	this->backgroundTracks[2] = Mix_LoadMUS("./sounds/world_finished.wav");
	this->backgroundTracks[3] = Mix_LoadMUS("./sounds/gameover.wav");
	this->backgroundTracks[4] = Mix_LoadMUS("./sounds/time_passed.wav");

	this->soundsEffects[0] = Mix_LoadWAV("./sounds/1up_collected.wav");
	this->soundsEffects[1] = Mix_LoadWAV("./sounds/block_destroyed.wav");
	this->soundsEffects[2] = Mix_LoadWAV("./sounds/block_hitted.wav");
	this->soundsEffects[3] = Mix_LoadWAV("./sounds/bonus_appeard.wav");
	this->soundsEffects[4] = Mix_LoadWAV("./sounds/bonus_collected.wav");
	this->soundsEffects[5] = Mix_LoadWAV("./sounds/coin_collected.wav");
	this->soundsEffects[6] = Mix_LoadWAV("./sounds/enemy_destroyed.wav");
	this->soundsEffects[7] = Mix_LoadWAV("./sounds/fireball_popped.wav");
	this->soundsEffects[8] = Mix_LoadWAV("./sounds/flag_down.wav");
	this->soundsEffects[9] = Mix_LoadWAV("./sounds/jump_small.wav");
	this->soundsEffects[10] = Mix_LoadWAV("./sounds/jump_tall.wav");
	this->soundsEffects[11] = Mix_LoadWAV("./sounds/mario_dead.wav");
}

void SoundController::closeSoundMixer()
{
	for (int i = 0; i < 5; ++i) {
		Mix_FreeMusic(this->backgroundTracks[0]);
		this->backgroundTracks[0] = nullptr;
	}

	for (int i = 0; i < 12; ++i) {
		Mix_FreeChunk(this->soundsEffects[i]);
		this->soundsEffects[i] = nullptr;
	}

	Mix_Quit();
}

SoundController::SoundController()
{
	if (this->initSoundMixer()) {
		this->loadSounds();
	}
}

void SoundController::playBackgroudMarioMusic()
{
	Mix_PlayMusic(backgroundTracks[0], -1);
}

void SoundController::playBackgroudStarMusic()
{
	Mix_PlayMusic(backgroundTracks[1], -1);
}

void SoundController::playWorldFinishedMusic()
{
	Mix_PlayMusic(backgroundTracks[2], -1);
}

void SoundController::playGameoverMusic()
{
	Mix_PlayMusic(backgroundTracks[3], -1);
}

void SoundController::playTimePassedMusic()
{
	Mix_PlayMusic(backgroundTracks[4], -1);
}

void SoundController::play1upCollectedEffect()
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
	Mix_PlayChannel(-1, soundsEffects[player->getCurrentState() != Small ? 10 : 9], 0);
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
	this->closeSoundMixer();
}
