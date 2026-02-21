#pragma once

#include <vector>

#include "int2.h"
#include "item.h"
#include "controller.h"
#include "time.h"
#include "config.h"
#include "single_snake_drawInfo.h"

class Snake
{
	Time accelerate_erase_tail_timer = Time(0);

	// 当前时刻减去计时器时刻（tick）
	int current_difference = 0;
	// 方向长度必须为1
	int2 old_dir = int2(0, 1);
	int2 new_dir = int2(0, 1);

	bool death_buffer = true;
	bool can_move = true;

	double speed = SNAKE_PLAYER_SPEED; // 速度(格/s)

	double death_buffer_time = SNAKE_DEATH_BUFFER_TIME;

	Time first_about_death_time = Time(0ULL);

	int2 random_dir() const;
	int random_length() const;
	Color random_color() const;

	int2 last_tail_pos;

public:
	Color color;
	// 蛇身
	std::vector<int2> body;// 尾->头

	Controller* controller;

	bool is_invincible = false;
	bool is_active = false;

	Snake(const int2 init_pos, const int length, const int2 dir, const Color color0) {
		awake(init_pos, length, dir, color0);
		is_active = false;
	}
	Snake(const int2 init_pos, const int length, const int2 dir) {
		awake(init_pos, length, dir);
		is_active = false;
	}
	Snake(const int2 init_pos, const int length) {
		awake(init_pos, length);
		is_active = false;
	}
	Snake(const int2 init_pos) {
		awake(init_pos);
		is_active = false;
	}
	Snake(const int length) {
		awake(length);
		is_active = false;
	}

	// 默认构造，以玩家蛇为准
	Snake();

	void awake(const int2 init_pos, const int length, const int2 dir, const Color color0);
	void awake(const int2 init_pos, const int length, const int2 dir);
	void awake(const int2 init_pos, const int length);
	void awake(const int2 init_pos);
	void awake(const int length);
	void awake();

	void Die();

	void turn(int2 direction);
	const int2& get_dir() const{ return old_dir; }
	const int2& get_head_pos() const{ return body.back(); }

	void move();
	void erase_tail();

	void change_speed(double target_speed);

	bool check_collision_with_item(const int2& pos, Item& item_get) const;
	bool check_collision_with_item(Item& item_get) const;

	bool check_collision_with_self(const int2& pos) const;
	bool check_collision_with_self() const;

	bool check_collision_with_others(const int2& pos) const;
	bool check_collision_with_others() const;

	bool check_collision_with_wall(const int2& pos) const;
	bool check_collision_with_wall() const;

	bool is_death(const int2& pos) const;
	bool is_death() const;

	bool about_death();

	void fixed_update();
	void update();
	void check_can_move();

	double move_double_count = 0.0; // 0-1，大于等于1时前进1格

	SingleSnakeDrawInfo get_draw_info() const;
};

