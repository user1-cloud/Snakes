#pragma once
#include "controller.h"
#include "snake.h"

class PlayerController : public Controller
{
	Snake* snake = nullptr;
public:
	PlayerController(Snake* snake) : snake(snake){}
	virtual void update() const override;
};

