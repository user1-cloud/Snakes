#pragma once
#include "controller.h"
#include "snake.h"
#include "input_info.h"
#include "config.h"

class PlayerController : public Controller
{
	InputInfo player_event;
	Snake* snake = nullptr;

	std::unordered_map<InputInfo, std::function<void()>> command_map;
public:
	bool is_accelerated = false;
	PlayerController(Snake* snake);
	virtual void turn_update() override;
	void accelerate_update() override;
};

