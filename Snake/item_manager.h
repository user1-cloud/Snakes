#pragma once
#include "item.h"
#include "time.h"
class ItemManager
{
private:
	static void set_item(int2 pos, ItemType item_type);
public:
	static Time food_timer;

	static void init();
	static void fixed_update();

	static void try_set_item(int2 pos, ItemType item_type);
	static void try_set_item(ItemType item_type);

	static void try_set_items(int number, ItemType item_type);

	static void check_timer();
};

