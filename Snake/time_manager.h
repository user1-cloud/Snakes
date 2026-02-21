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
		using result_type = std::invoke_result_t<std::decay_t<Func>, std::decay_t<Args>...>;
		static_assert(
			std::is_void_v<result_type>,
			"错误：只能调用返回值为void的函数！"
			);
		// Time()为当前时间（修正后的）
		if (Time() - timer > time) {
			timer = timer + time;
			std::forward<Func>(func)(std::forward<Args>(args)...);
		}
	}
};

