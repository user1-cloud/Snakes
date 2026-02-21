#pragma once
#include <SDL3/SDL.h>
#include "time_manager.h"
struct Time
{
	struct RawTime {};
	Uint64 tick;

	constexpr Time(Uint64 tick) :tick(tick) {}
	Time();
	Time(RawTime) :tick(SDL_GetPerformanceCounter()) {}


	double operator-(const Time& other) const noexcept;

	Time operator+(const double& other) const noexcept;
};
