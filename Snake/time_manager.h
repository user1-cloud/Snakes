#pragma once
#include <SDL3/SDL.h>
class TimeManager
{
public:
	static double s_perfFrequencyInv;
	static Uint64 s_perfFrequency;

	static void init();

	static Uint64 time_offset;
	static Uint64 get_current_tick() {
		return SDL_GetPerformanceCounter() - time_offset;
	}
};

