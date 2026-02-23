#include <unordered_set>
#include <algorithm>
#include <cmath>
#include "game_object_manager.h"
#include "game_manager.h"
#include "player_controller.h"
#include "ai_controller.h"
#include "time_manager.h"

Time GameObjectManager::choose_enemy_spawn_point_timer = Time(0);

std::unordered_set<Color> GameObjectManager::nonexistent_colors(std::begin(SNAKE_COLORS), std::end(SNAKE_COLORS));

bool GameObjectManager::point_is_items(int2 pos, Item& item_get) {
	auto it = items.find(pos);
	if (it != items.end()) {
		item_get = it->second;
		return true;
	}
	return false;
}

bool GameObjectManager::point_is_snake_except(int2 pos, const Snake* except_snake) {
	for (const Snake& snake : enemy_snakes) {
		if (snake.is_active) {
			if (&snake == except_snake) {
				continue;
			}
			for (const int2& snake_pos : snake.body) {
				if (pos == snake_pos) {
					return true;
				}
			}
		}
	}
	if (&player_snake != except_snake) {
		if (player_snake.is_active) {
			for (const int2& snake_pos : player_snake.body) {
				if (pos == snake_pos) {
					return true;
				}
			}
		}
	}
	return false;
}

bool GameObjectManager::point_is_snake(int2 pos) {
	return point_is_snake_except(pos, nullptr);
}

bool GameObjectManager::point_is_unsafe(int2 pos) {
	return point_is_snake(pos);
}

void GameObjectManager::all_snake_update() {
	if (player_snake.is_active) {
		player_snake.update();
	}
	for (Snake& snake : enemy_snakes) {
		if (snake.is_active) {
			snake.update();
		}
	}
}

void GameObjectManager::all_snake_fixed_update() {
	if (player_snake.is_active) {
		player_snake.fixed_update();
	}
	for (Snake& snake : enemy_snakes) {
		if (snake.is_active) {
			snake.fixed_update();
		}
	}
}

void GameObjectManager::draw_info_update() {
	draw_info.single_snake_draw_infos.clear();
	if (player_snake.is_active) {
		draw_info.single_snake_draw_infos.push_back(player_snake.get_draw_info());
	}
	for (Snake& snake : enemy_snakes) {
		if (snake.is_active) {
			draw_info.single_snake_draw_infos.push_back(snake.get_draw_info());
		}
	}

	draw_info.items.clear();
	for (const auto& pair : items) {
		const Item& item = pair.second;
		if (item.is_active) {
			draw_info.items.push_back(item);
		}
	}
}

void GameObjectManager::update() {
	all_snake_update();
	draw_info_update();
}

void GameObjectManager::fixed_update() {
	all_snake_fixed_update();
	TimeManager::check_timer(choose_enemy_spawn_point_timer, ENEMY_SNAKE_SPAWN_INTERVAL * 2, choose_enemy_spawn_point);
}

int2 GameObjectManager::random_safe_pos() {
	std::vector<int2> safe_pos;
	for (int2 potential_pos : enemy_spawn_points) {
		if (!point_is_unsafe(potential_pos)) {
			safe_pos.push_back(potential_pos);
		}
	}
	if (safe_pos.empty()) {
		return int2(-1, -1); // 未找到合适的坐标
	}
	else {
		std::uniform_int_distribution<int> dist(0, safe_pos.size() - 1);
		return safe_pos[dist(GameManager::random_engine)];
	}
}

void GameObjectManager::init() {
	choose_enemy_spawn_point();
	player_snake.awake(GameManager::snake_world.world_center(), SNAKE_PLAYER_INIT_LENGTH, SNAKE_PLAYER_INIT_DIR, PLAYER_SNAKE_COLOR);
	player_snake.controller = new PlayerController(&player_snake);
	for (int i = 0; i < enemy_snakes.size(); ++i) {
		enemy_snakes[i].awake(SNAKE_ENEMY_INIT_LENGTH);
		if (i >= INIT_ENEMY_SNAKE_NUMBER) {
			enemy_snakes[i].is_active = false;
		}
		enemy_snakes[i].controller = new AIController(&enemy_snakes[i]);
	}
}

void GameObjectManager::choose_enemy_spawn_point() {
	enemy_spawn_points.clear();
	int2 center = GameManager::snake_world.world_center();
	int2 world_size = GameManager::snake_world.world_size;
	for (int2 corner : {int2(0, 0), int2(0, world_size.y), int2(world_size.x, 0), int2(world_size.x, world_size.y)}) {
		int2 start_center = center + int2(corner.x > 0, corner.y > 0);
		std::vector<int2> single_region_points = random_pos(start_center, corner, REGION_SPAWN_POINT_NUMBER);
		enemy_spawn_points.insert(enemy_spawn_points.end(), single_region_points.begin(), single_region_points.end());
	}
}


std::vector<int2> GameObjectManager::random_pos(int2 border_corner_0, int2 border_corner_1, int number) {
	std::vector<int2> target;
	if (std::abs((border_corner_0.x - border_corner_1.x) * (border_corner_0.y - border_corner_1.y)) < number) {
		return target;
	}
	std::unordered_set<int2> selected;
	while (selected.size() < number) {
		auto [x_min, x_max] = std::minmax({ border_corner_0.x, border_corner_1.x });
		auto [y_min, y_max] = std::minmax({ border_corner_0.y, border_corner_1.y });
		std::uniform_int_distribution<int> dist_x(x_min, x_max);
		std::uniform_int_distribution<int> dist_y(y_min, y_max);
		int2 pos_random = int2(dist_x(GameManager::random_engine), dist_y(GameManager::random_engine));
		if (selected.insert(pos_random).second) {
			target.push_back(pos_random);
		}
	}
	return target;
}

int2 GameObjectManager::random_pos(int2 border_corner_0, int2 border_corner_1) {
	return random_pos(border_corner_0, border_corner_1, 1).back();
}

int2 GameObjectManager::random_pos() {
	return random_pos(int2(0, 0), int2(GameManager::snake_world.world_size.x, GameManager::snake_world.world_size.y));
}