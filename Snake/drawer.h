#pragma once
#include <SDL3/SDL.h>
#include "int2.h"
class Drawer
{
	SDL_Window* window;
	SDL_Renderer* renderer;
public:
    bool success = false;
	Drawer(SDL_Window* window);
	void draw();
	void quit();

	void draw_snake_eyes(SDL_Renderer* renderer0, const int2& pos, const int2& dir);
	void render_game(SDL_Renderer* renderer0);
};

