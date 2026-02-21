#include "snake_spawn_manager.h"
#include "snake.h"
#include "game_object_manager.h"
#include "time_manager.h"

std::uniform_int_distribution<> SnakeSpawnManager::snake_length_distribution(SNAKE_ENEMY_INIT_LENGTH_MIN, SNAKE_ENEMY_INIT_LENGTH_MAX);

void SnakeSpawnManager::spawn_snake(int length) {
	for (Snake& potential_snake : GameObjectManager::enemy_snakes) {
		if (potential_snake.is_active) {
			continue;
		}
		potential_snake.awake(length);
		break;
	}
}

void SnakeSpawnManager::spawn_snakes(int number) {
	for (int i = 0; i < number; ++i) {
		int random_length = snake_length_distribution(GameManager::random_engine);
		spawn_snake(random_length);
	}
}

Time SnakeSpawnManager::snake_spawn_timer = Time(0);

void SnakeSpawnManager::init() {
	// 初始蛇生成在GameObjectManager
	snake_spawn_timer = Time();
}

void SnakeSpawnManager::fixed_update() {
	check_timer();
}

void SnakeSpawnManager::check_timer() {
	TimeManager::check_timer(snake_spawn_timer, ENEMY_SNAKE_SPAWN_INTERVAL, spawn_snakes, 1);
}