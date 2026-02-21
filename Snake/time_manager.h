#pragma once
#include <SDL3/SDL.h>
class TimeManager
{
public:
	static double s_perfFrequencyInv;
	static Uint64 s_perfFrequency;

	static void init();
};

