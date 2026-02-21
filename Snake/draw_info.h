#pragma once
#include <vector>
#include "single_snake_drawInfo.h"
#include "item.h"
struct DrawInfo
{
	std::vector<SingleSnakeDrawInfo> single_snake_draw_infos;
	std::vector<Item> items;
};