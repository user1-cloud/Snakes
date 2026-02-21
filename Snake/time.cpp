#include "time.h"
#include "time_manager.h"

// 初始化为当前时刻
Time::Time() {
	tick = TimeManager::get_current_tick();
}

double Time::operator-(const Time& other) const noexcept {
	return (tick - other.tick) * TimeManager::s_perfFrequencyInv;
}

Time Time::operator+(const double& other) const noexcept {
	return Time(tick + other * static_cast<double>(TimeManager::s_perfFrequency));
}