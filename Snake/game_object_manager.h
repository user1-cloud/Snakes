#pragma once
#include <array>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include "snake.h"
#include "item.h"
#include "config.h"
#include "int2.h"
#include "draw_info.h"
#include "game_manager.h"

class GameObjectManager
{
	// 单例模式
private:
	GameObjectManager() = delete;
	~GameObjectManager() = delete;
public:
	inline static Snake player_snake;
	inline static std::array<Snake, MAX_ENEMY_SNAKE_NUMBER> enemy_snakes;
	
	inline static std::unordered_map<int2, Item> items;
	inline static std::vector<int2> enemy_spawn_points;

	inline static std::vector<int2> world_pos_is_safe;
	inline static DrawInfo draw_info;

	static bool point_is_items(int2 pos, Item& item_get);
	static bool point_is_snake_except(int2 pos, const Snake* except_snake);
	static bool point_is_snake(int2 pos);
	static bool point_is_unsafe(int2 pos);

	static void all_snake_update();
	static void all_snake_fixed_update();

	static void draw_info_update();

	static void update();
	static void fixed_update();

	// 蛇的出生位置，预计算的坐标，与蛇无关慎用
	static int2 random_safe_pos();

	static void init();

	static void choose_enemy_spawn_point();

	// 随机坐标（包含）
	static std::vector<int2> random_pos(int2 border_corner_0, int2 border_corner_1, int number);
	static int2 random_pos(int2 border_corner_0, int2 border_corner_1);
	static int2 random_pos();
};

