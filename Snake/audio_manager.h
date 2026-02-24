#pragma once
#include <unordered_map>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3/SDL.h>

class AudioManager
{
public:
	enum class SoundEffect {
		PlayerTurn,
		PlayerAccelerate,
		PlayerGetFood,
		SnakeDying,
	};
private:
	static void load_audio(unsigned char* audio_data, int size, SoundEffect effect_enum);

	static std::unordered_map<SoundEffect, MIX_Audio*> effect_map;
	static MIX_Track* sound_track_pool[16];

public:
	static MIX_Mixer* mixer;

	static void init();

	static void play_sound(SoundEffect sound_effect);

	static void quit();
	static void clean();
};

