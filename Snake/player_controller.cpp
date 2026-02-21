#include "player_controller.h"
#include <SDL3/SDL.h>
#include "input_manager.h"

void PlayerController::update(){
	int player_event;
	if ((player_event = InputManager::get_player_down_event()) != -1) {
		switch (player_event) {
		case key_up_0:
		case key_up_1:
			snake->turn(int2(0, 1));
			break;
		case key_down_0:
		case key_down_1:
			snake->turn(int2(0, -1));
			break;
		case key_left_0:
		case key_left_1:
			snake->turn(int2(-1, 0));
			break;
		case key_right_0:
		case key_right_1:
			snake->turn(int2(1, 0));
			break;
		case key_speed_up_0:
		case key_speed_up_1:
			snake->change_speed(SNAKE_PLAYER_SPEED_SHIFT_ACCELERATED);
			is_accelerated = true;
			break;
		default:
			break;
		}
	}
	while ((player_event = InputManager::get_player_up_event()) != -1) {
		switch (player_event) {
		case key_speed_up_0:
		case key_speed_up_1:
			snake->change_speed(SNAKE_PLAYER_SPEED);
			is_accelerated = false;
			break;
		default:
			break;
		}
	}
}
