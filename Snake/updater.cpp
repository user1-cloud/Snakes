#include "updater.h"
#include "game_manager.h"
#include "config.h"

Time Updater::last_time = Time(0);

void Updater::update() {
	GameManager::main_update();
}
void Updater::fixed_update() {
	GameManager::main_fixed_update();
}
void Updater::updater_init(){
	last_time = Time();
}
void Updater::updater_update() {
	update();
	// Time()为当前时间
	Time current_time = Time();
	if (current_time - last_time >= FIXED_DELTA_TIME) {
		last_time = last_time + FIXED_DELTA_TIME;
		fixed_update();
	}
}