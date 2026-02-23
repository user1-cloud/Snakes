#pragma once
#include <SDL3/SDL.h>
#include <type_traits>
#include <utility>
#include "time.h"


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

	template <typename Func, typename... Args>
	static void check_timer(Time& timer, double time, Func&& func, Args&&... args) {
		// Time()为当前时间（修正后的）
		if (Time() - timer > time) {
			timer = timer + time;
			std::forward<Func>(func)(std::forward<Args>(args)...);
		}
	}
};

