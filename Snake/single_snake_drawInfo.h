#pragma once
#include <vector>
#include "color.h"
#include "int2.h"
struct SingleSnakeDrawInfo {
	Color color;
	const std::vector<int2> body;
	double move_double_count = 0.0; // 0-1，大于等于1时前进1格
	int2 last_tail_pos;
	int2 old_dir;
	bool is_player_snake;
	bool is_dying;

	SingleSnakeDrawInfo(const Color color,
		const std::vector<int2> body,
		const double move_double_count,
		const int2 old_dir,
		const int2 last_tail_pos,
		const bool is_player_snake,
		const bool is_dying
	):
		color(color), 
		body(body), 
		move_double_count(move_double_count), 
		old_dir(old_dir), 
		last_tail_pos(last_tail_pos), 
		is_player_snake(is_player_snake),
		is_dying(is_dying)
	{}
};


