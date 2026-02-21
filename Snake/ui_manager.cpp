#include "ui_manager.h"
#include "input_manager.h"
#include "config.h"
#include "time_manager.h"

bool UIManager::is_paused = false;

Time UIManager::pause_time = Time(0);

char UIManager::pause_key_up_count = 0;

void UIManager::init() {
	is_paused = false;
	pause_time = Time();
	pause_key_up_count = 0;
}

void UIManager::ui_update() {
	if (is_paused) {
		check_resume_event();
	}
	else {
		check_pause_event();
	}
}

void UIManager::check_pause_event() {
	bool has_pause_event = false;
	int ui_event;
	while ((ui_event = InputManager::get_ui_down_event()) != -1) {
		switch (ui_event) {
		case key_pause:
			has_pause_event = true;
			break;
		default:
			break;
		}
	}
	if (has_pause_event) {
		pause();
	}
}

void UIManager::check_resume_event() {
	bool has_resume_event = false;
	int ui_event;
	while ((ui_event = InputManager::get_ui_up_event()) != -1) {
		switch (ui_event) {
		case key_pause:
			has_resume_event = true;
			break;
		default:
			break;
		}
	}
	if (has_resume_event) {
		pause_key_up_count += 1;
		if (pause_key_up_count >= 2) {
			pause_key_up_count = 0;
			resume();
		}
	}
}


void UIManager::pause() {
	pause_time = Time();
	is_paused = true;
}

void UIManager::resume() {
	InputManager::init();
	is_paused = false;
	set_time_offset(Time().tick - pause_time.tick);
}

void UIManager::set_time_offset(Uint64 offset) {
	TimeManager::time_offset += offset;
}