#pragma once
#include "config.h"
#include "int2.h"

struct SnakeWorld
{
	bool screen_too_wide;
	// 坐标左下角为原点，向右为x轴，向上为y轴
	// 世界长宽（减去1后的）
	int2 world_size;
	int2 screen_size;

	int2 point_size;
	// 原点屏幕坐标
	int2 origin_screen_pos;

	/// <summary>
	/// 根据屏幕尺寸和全局 world_size 计算每个点的最大整数尺寸，并将全局 point_size 设置为正方形尺寸。
	/// </summary>
	/// <param name="screen_size">表示屏幕像素尺寸的二维整数向量（x 为宽度，y 为高度）。</param>
	int2 screen_size_to_pointSize(const int2& screen_size, bool& if_screen_too_wide);

	int2 world_center();
	int2 screen_center();

	SnakeWorld(int2 size);
	SnakeWorld();

	void screen_size_updated(const int2& screen_size);

	// 获取世界坐标原点对应的屏幕坐标
	int2 get_origin_screen_pos();
	int2 world_pos_to_screen_pos(int2 world_pos);

	SDL_FRect screen_left_down_pos_to_rect(int2 screen_pos, int x, int y);
	SDL_FRect screen_left_down_pos_to_rect(int2 screen_pos);
	SDL_FRect world_pos_to_rect(int2 world_pos);
};

