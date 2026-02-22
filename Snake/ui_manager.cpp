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
	InputInfo ui_event;
	while (InputManager::get_event(InputManager::system_buffer, ui_event)) {
		if (ui_event == INPUT_ESC_DOWN){
			has_pause_event = true;
		}
	}
	if (has_pause_event) {
		pause();
	}
}

void UIManager::check_resume_event() {
	bool has_resume_event = false;
	InputInfo ui_event;
	while (InputManager::get_event(InputManager::system_buffer, ui_event)) {
		if (ui_event == INPUT_ESC_UP) {
			has_resume_event = true;
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