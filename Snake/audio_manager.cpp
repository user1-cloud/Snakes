#include "audio_manager.h"
#include "audio_resource.h"

std::unordered_map<AudioManager::SoundEffect, MIX_Audio*> AudioManager::effect_map;
MIX_Track* AudioManager::sound_track_pool[16];
MIX_Mixer* AudioManager::mixer;

void AudioManager::init() {
	clean();
	if (!MIX_Init()) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_MIXER_Init Error: %s", SDL_GetError());
		return;
	}
	mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);

	load_audio(AudioResource::PLAYER_TURN, AudioResource::PLAYER_TURN_SIZE, SoundEffect::PlayerTurn);

	for (MIX_Track*& track : sound_track_pool) {
		track = MIX_CreateTrack(mixer);
	}
}

void AudioManager::load_audio(unsigned char* audio_data, int size, SoundEffect effect_enum) {
	void* data = audio_data;
	SDL_IOStream* data_io = SDL_IOFromMem(data, size);
	if (!data_io) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_IOFromMem failed.");
		return;
	}
	MIX_Audio* audio = MIX_LoadAudio_IO(mixer, data_io, true, false);
	if (!audio) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "MIX_LoadAudio_IO failed.");
		return;
	}
	effect_map[effect_enum] = audio;
}

void AudioManager::play_sound(SoundEffect sound_effect) {
	for (MIX_Track*& track : sound_track_pool) {
		if (!MIX_TrackPlaying(track)) {
			MIX_SetTrackAudio(track, effect_map[sound_effect]);
			MIX_PlayTrack(track, 0);
			return;
		}
	}
}

void AudioManager::quit() {
	clean();

	// 退出 SDL_mixer
	MIX_Quit();
}

void AudioManager::clean() {
	for (MIX_Track*& track : sound_track_pool) {
		if (track) {
			MIX_DestroyTrack(track);
			track = NULL;
		}
	}

	if (mixer) {
		MIX_DestroyMixer(mixer);
		mixer = NULL;
	}
}
