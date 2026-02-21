#pragma once
#include <random>
#include "snake_world.h"
#include "config.h"

class GameManager
{
public:
	static SnakeWorld snake_world;
	static RANDOM_ENGINE_TYPE random_engine;
	static RANDOM_ENGINE_TYPE get_random_engine();
	static void main_init();
	static void main_update();
	static void main_fixed_update();
};

