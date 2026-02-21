#pragma once
#include "item_type.h"
#include "int2.h"
struct Item
{
	int2 pos;
	ItemType type;
	bool is_active = false;
	constexpr Item(int2 pos, ItemType type) :pos(pos), type(type) {}
	constexpr Item() : Item(int2(0, 0), ItemType::Food) {}
};

