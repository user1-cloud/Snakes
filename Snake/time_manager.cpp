#include "time_manager.h"

double TimeManager::s_perfFrequencyInv = 0.0;
Uint64 TimeManager::s_perfFrequency = 0;

Uint64 TimeManager::time_offset = 0;

void TimeManager::init() {
	s_perfFrequency = SDL_GetPerformanceFrequency();
	s_perfFrequencyInv = 1.0 / static_cast<double>(s_perfFrequency);
}