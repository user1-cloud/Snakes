#include "snake_world.h"
// 坐标左下角为原点，向右为x轴，向上为y轴
int2 SnakeWorld::screen_size_to_pointSize(const int2& screen_size, bool& if_screen_too_wide) {
	int max_point_size_x = (screen_size.x + 1) / (world_size.x + 1);
	int max_point_size_y = (screen_size.y + 1) / (world_size.y + 1);

	if_screen_too_wide = max_point_size_x > max_point_size_y;
	int point_size_x = (!if_screen_too_wide) ? max_point_size_x : max_point_size_y;

	return int2(point_size_x, point_size_x); // 长宽相等
}

int2 SnakeWorld::world_center() {
	return (world_size + int2(1, 1)) / 2;
}
int2 SnakeWorld::screen_center() {
	return (screen_size + int2(1, 1)) / 2;
}

SnakeWorld::SnakeWorld(int2 size) : world_size(size - int2(1, 1)){
	screen_size_updated(int2(INIT_SCREEN_WIDTH, INIT_SCREEN_HEIGHT));
}
SnakeWorld::SnakeWorld() :SnakeWorld(int2(SNAKE_WORLD_SIZE_X, SNAKE_WORLD_SIZE_Y)) {}

int2 SnakeWorld::get_origin_screen_pos() {
	int center_adjusted_x = screen_center().x;
	int center_adjusted_y = screen_center().y - 1;
	if (world_size.x % 2 == 1) {
		return int2(center_adjusted_x - (world_size.x + 1) / 2 * point_size.x, center_adjusted_y + (world_size.y + 1) / 2 * point_size.y);
	} 
	else {
		return int2(center_adjusted_x - (world_size.x + 1) / 2 * point_size.x - point_size.x / 2, center_adjusted_y + (world_size.y + 1) / 2 * point_size.y + point_size.y / 2);
	}
}

int2 SnakeWorld::world_pos_to_screen_pos(int2 world_pos) {
	return int2(origin_screen_pos.x + world_pos.x * point_size.x, origin_screen_pos.y - world_pos.y * point_size.y);
}

SDL_FRect SnakeWorld::screen_left_down_pos_to_rect(int2 screen_pos0, int x, int y) {
	SDL_FRect rect = { screen_pos0.x, screen_pos0.y - y, x, y };
	return rect;
}

SDL_FRect SnakeWorld::screen_left_down_pos_to_rect(int2 screen_pos0) {
	SDL_FRect rect = { screen_pos0.x, screen_pos0.y - point_size.y, point_size.x, point_size.y };
	return rect;
}

SDL_FRect SnakeWorld::world_pos_to_rect(int2 world_pos0) {
	return screen_left_down_pos_to_rect(world_pos_to_screen_pos(world_pos0));
}

int2 SnakeWorld::world_pos_little_pos_to_screen_pos(int2 world_pos, int2 little_pos) {
	int2 little_point_size = point_size / 8;
	return world_pos_to_screen_pos(world_pos) + int2(little_point_size.x * little_pos.x, little_point_size.y * little_pos.y);
}

SDL_FRect SnakeWorld::world_pos_little_pos_to_little_rect(int2 world_pos, int2 little_pos) {
	int2 little_point_size = point_size / 8;
	return screen_left_down_pos_to_rect(world_pos_to_screen_pos(world_pos) + int2(little_point_size.x * little_pos.x, little_point_size.y * little_pos.y), little_point_size.x, little_point_size.y);
}

SDL_FRect SnakeWorld::screen_left_down_pos_to_little_rect(int2 screen_pos, int2 little_pos) {
	int2 little_point_size = point_size / 8;
	return screen_left_down_pos_to_rect(screen_pos + int2(little_point_size.x * little_pos.x, -little_point_size.y * little_pos.y), little_point_size.x, little_point_size.y);
}

void SnakeWorld::screen_size_updated(const int2& screen_size0) {
	point_size = screen_size_to_pointSize(screen_size0, screen_too_wide);
	screen_size = screen_size0 - int2(1, 1);
	origin_screen_pos = get_origin_screen_pos();
}