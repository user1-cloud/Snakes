#include "player_controller.h"
#include "input_manager.h"

PlayerController::PlayerController(Snake* snake):snake(snake) {
	command_map = {
		{INPUT_UP_0, [snake]() {snake->turn(int2(0, 1)); }},
		{INPUT_UP_1, [snake]() {snake->turn(int2(0, 1)); }},
		{INPUT_DOWN_0, [snake]() {snake->turn(int2(0, -1)); }},
		{INPUT_DOWN_1, [snake]() {snake->turn(int2(0, -1)); }},
		{INPUT_LEFT_0, [snake]() {snake->turn(int2(-1, 0)); }},
		{INPUT_LEFT_1, [snake]() {snake->turn(int2(-1, 0)); }},
		{INPUT_RIGHT_0, [snake]() {snake->turn(int2(1, 0)); }},
		{INPUT_RIGHT_1, [snake]() {snake->turn(int2(1, 0)); }},

		{INPUT_LSHIFT_DOWN, [snake, this]() {
			snake->change_speed(SNAKE_PLAYER_SPEED_SHIFT_ACCELERATED); 
			is_accelerated = true;
		}},
		{INPUT_SPACE_DOWN, [snake, this]() {
			snake->change_speed(SNAKE_PLAYER_SPEED_SHIFT_ACCELERATED);
			is_accelerated = true;
		}},
		{INPUT_LSHIFT_UP, [snake, this]() {
			snake->change_speed(SNAKE_PLAYER_SPEED); 
			is_accelerated = false;
		}},
		{INPUT_SPACE_UP, [snake, this]() {
			snake->change_speed(SNAKE_PLAYER_SPEED);
			is_accelerated = false;
		}}
	};
}

void PlayerController::turn_update() {
	if (InputManager::get_event(InputManager::move_direction_buffer, player_event)) {
		auto it = command_map.find(player_event);
		if (it != command_map.end()) {
			it->second();
		}
	}
}

void PlayerController::accelerate_update() {
	while (InputManager::get_event(InputManager::accelerate_buffer, player_event)){
		auto it = command_map.find(player_event);
		if (it != command_map.end()) {
			it->second();
		}
	}
}
