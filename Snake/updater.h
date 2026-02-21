#pragma once
#include "time.h"
class Updater
{
	static Time last_time;
	static void update();
	static void fixed_update();
public:
	static void updater_init();
	static void updater_update();
};

