#pragma once
#include "controller.h"
#include "snake.h"

class PlayerController : public Controller
{
	Snake* snake = nullptr;
public:
	bool is_accelerated = false;
	PlayerController(Snake* snake) : snake(snake){}
	virtual void update() override;
};

