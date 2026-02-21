#pragma once
#include "time.h"
class UIManager
{
	static char pause_key_up_count;
	static Time pause_time;
public:
	static void init();

	static bool is_paused;
	static void pause();
	static void resume();

	static void ui_update();

	static void check_pause_event();
	static void check_resume_event();

	static void set_time_offset(Uint64 offset);
};

