#pragma once
#include <SDL3/SDL.h>
class Drawer
{
	SDL_Window* window;
	SDL_Renderer* renderer;
public:
    bool success = false;
	Drawer(SDL_Window* window);
	void draw();
	void quit();

	void render_game(SDL_Renderer*);
};

