#include "game_stat.h"
#include "config.h"
#include "game_object_manager.h"

int GameStat::player_snake_length = 0;

void GameStat::init() {
	player_snake_length = SNAKE_PLAYER_INIT_LENGTH;
}

void GameStat::fixed_update() {
	player_snake_length = GameObjectManager::player_snake.body.size();
}