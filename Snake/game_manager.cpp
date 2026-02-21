#include "game_manager.h"
#include "input_manager.h"
#include "game_object_manager.h"
#include "item_manager.h"
#include "snake_spawn_manager.h"

RANDOM_ENGINE_TYPE GameManager::random_engine = GameManager::get_random_engine();

RANDOM_ENGINE_TYPE GameManager::get_random_engine() {
	std::random_device rd;
	return RANDOM_ENGINE_TYPE(rd());
}
// init总开关
void GameManager::main_init() {
	TimeManager::init();
	snake_world = SnakeWorld(int2(SNAKE_WORLD_SIZE_X, SNAKE_WORLD_SIZE_Y));
	ItemManager::init();
	SnakeSpawnManager::init();
	GameObjectManager::init();
}

SnakeWorld GameManager::snake_world = SnakeWorld();


// update和fixed_update总开关
void GameManager::main_update() {
	InputManager::update();
	GameObjectManager::update();
}
void GameManager::main_fixed_update() {
	ItemManager::fixed_update();
	SnakeSpawnManager::fixed_update();
	GameObjectManager::fixed_update();
}