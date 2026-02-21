#pragma once
#include <random>
#include "time.h"
#include "config.h"

class SnakeSpawnManager
{
private:
	static std::uniform_int_distribution<> snake_length_distribution;

public:
	static Time snake_spawn_timer;
	static void spawn_snake(int length);
	static void spawn_snakes(int number);

	static void init();
	static void fixed_update();

	static void check_timer();
};

