#include "item_manager.h"
#include "game_object_manager.h"

Time ItemManager::food_timer = Time(0);

void ItemManager::set_item(int2 pos, ItemType item_type) {
	Item item_set = Item(pos, item_type);
	item_set.is_active = true;
	GameObjectManager::items.emplace(pos, item_set);
}

void ItemManager::init() {
	food_timer = Time();
	for (int i = 0; i < INIT_FOOD_NUMBER; ++i) {
		try_set_item(ItemType::Food);
	}
}

void ItemManager::fixed_update() {
	check_timer();
}

void ItemManager::try_set_item(int2 pos, ItemType item_type){
	Item output;
	if (!GameObjectManager::point_is_unsafe(pos) && !GameObjectManager::point_is_items(pos, output)) {
		set_item(pos, item_type);
	}
}

void ItemManager::try_set_item(ItemType item_type) {
	try_set_item(GameObjectManager::random_pos(), item_type);
}

void ItemManager::try_set_items(int number, ItemType item_type) {
	for (int i = 0; i < number; ++i) {
		try_set_item(item_type);
	}
}

void ItemManager::check_timer() {
	timer_update_set_item(food_timer, FOOD_UPDATE_TIME, ItemType::Food, FOOD_UPDATE_NUMBER);
}

void ItemManager::timer_update_set_item(Time& timer, int update_time, ItemType item_type, int number) {
	if (Time() - timer > update_time) {
		timer = timer + update_time;
		try_set_items(number, item_type);
	}
}