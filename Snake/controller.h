#pragma once

class Controller
{
public:
	bool is_controlling = true;
	constexpr Controller() {}
	virtual void update(){}
};

