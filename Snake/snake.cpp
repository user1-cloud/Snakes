#include <random>
#include "snake.h"
#include "game_object_manager.h"
#include "snake_world.h"
#include "game_manager.h"
#include "player_controller.h"
#include "time_manager.h"
#include "item_manager.h"

Snake::Snake() {
	awake(GameManager::snake_world.world_center(), SNAKE_PLAYER_INIT_LENGTH, SNAKE_PLAYER_INIT_DIR, PLAYER_SNAKE_COLOR);
	is_active = false;
}

int2 Snake::random_dir() const{
	std::discrete_distribution<> dis({ 1, 1, 1, 1 });
	int index = dis(GameManager::random_engine);
	const int2 dir[4] = { int2(1, 0), int2(-1, 0), int2(0, 1), int2(0, -1) };
	return dir[index];
}

int Snake::random_length() const{
	std::uniform_int_distribution<> dis(SNAKE_ENEMY_INIT_LENGTH_MIN, SNAKE_ENEMY_INIT_LENGTH_MAX);
	return dis(GameManager::random_engine);
}

Color Snake::random_color() const {
	std::lock_guard<std::mutex> lock(random_colors_mutex);
	auto& colors = GameObjectManager::nonexistent_colors;
	if (colors.empty())
	{
		std::uniform_int_distribution<> dis(0, sizeof(SNAKE_COLORS) / sizeof(SNAKE_COLORS[0]) - 1);
		return SNAKE_COLORS[dis(GameManager::random_engine)];
	}
	else {
		Color color = *colors.begin();
		colors.erase(color);
		return color;
	}
}

void Snake::awake(const int2 init_pos, const int length, const int2 dir, const Color color0) {
	if (init_pos == int2(-1, -1)) {
		is_active = false;
	}
	else {
		is_active = true;
	}
	is_dying = false;
	body.assign(length, init_pos);
	last_tail_pos = init_pos;
	old_dir = dir;
	new_dir = dir;
	color = color0;
	death_buffer_time = SNAKE_DEATH_BUFFER_TIME;
}

void Snake::awake(const int2 init_pos, const int length, const int2 dir) {
	awake(init_pos, length, dir, random_color());
}

void Snake::awake(const int2 init_pos, const int length) {
	awake(init_pos, length, random_dir());
}

void Snake::awake(const int2 init_pos) {
	awake(init_pos, random_length());
}

void Snake::awake(const int length) {
	awake(GameObjectManager::random_safe_pos(), length);
}

void Snake::awake() {
	awake(GameObjectManager::random_safe_pos());
}

void Snake::Die() {
	GameObjectManager::nonexistent_colors.insert(color);
	is_active = false;

}

void Snake::turn(int2 direction) {
	if (direction == -old_dir) { return; }
	new_dir = direction;
}

void Snake::move() {
	int2 new_head_position = body.back() + new_dir;
	body.push_back(new_head_position);
	old_dir = new_dir;
}

void Snake::erase_tail() {
	last_tail_pos = *body.begin();
	body.erase(body.begin());
}

void Snake::erase_head() {
	body.pop_back();
}

void Snake::change_speed(double target_speed) {
	speed = target_speed;
}

bool Snake::check_collision_with_item(const int2& pos, Item& item_get) const{
	return GameObjectManager::point_is_items(pos, item_get);
}
bool Snake::check_collision_with_item(Item& item_get) const {
	return check_collision_with_item(body.back(), item_get);
}


bool Snake::check_collision_with_self(const int2& pos) const {
	for (int i = 0; i < (body.size() > 3 ? body.size() - 3 : 0); ++i) {
		if (body[i] == pos) {
			return true;
		}
	}
	return false;
}
bool Snake::check_collision_with_self() const {
	return check_collision_with_self(body.back());
}


bool Snake::check_collision_with_others(const int2& pos) const {
	return GameObjectManager::point_is_snake_except(pos, this);
}
bool Snake::check_collision_with_others() const {
	return check_collision_with_others(body.back());
}


bool Snake::check_collision_with_wall(const int2& pos) const {
	return pos.x > GameManager::snake_world.world_size.x || pos.y > GameManager::snake_world.world_size.y || pos.x < 0 || pos.y < 0;
}
bool Snake::check_collision_with_wall() const {
	return check_collision_with_wall(body.back());
}

bool Snake::about_death() {
	return is_death(body.back() + new_dir);
}

bool Snake::is_death(const int2& pos) const {
	return (((Snake::check_collision_with_others(pos) || check_collision_with_self(pos)) && !is_invincible) || check_collision_with_wall(pos));
}
bool Snake::is_death() const {
	return is_death(body.back());
}

void Snake::check_can_move() {
	if (about_death()) {
		if (can_move) {
			can_move = false;
			first_about_death_time = Time();
			return;
		}
		if (Time() - first_about_death_time < death_buffer_time) {
			return;
		}
		else {
			can_move = true;
			return;
		}
	}
	else {
		can_move = true;
	}
}

void Snake::erase_head_leave_food() {
	int2 current_head_pos = body.back();
	erase_head();
	probably_leave_food(current_head_pos);
}

void Snake::probably_leave_food(int2 pos) {
	std::bernoulli_distribution dist(BODY_TO_FOOD_PROBABILITY);
	if (dist(GameManager::random_engine)) {
		ItemManager::try_set_item(pos, ItemType::Food);
	}
}

void Snake::dying() {
	if (body.size() == 1) {
		Die();
		probably_leave_food(body.back());
	}
	else {
		erase_head_leave_food();
	}
}

void Snake::fixed_update() {
	if (is_dying) {
		TimeManager::check_timer(dying_leave_food_timer, SNAKE_DYING_LENGTH_REDUCE_TIME, [this](){dying(); });
		return;
	}
	move_double_count += speed * FIXED_DELTA_TIME;
	if (move_double_count > 1.0) {
		move_double_count -= 1.0;
		controller->turn_update();
		check_can_move();
		if (can_move) {
			move();
			if (is_death()) {
				body.pop_back();
				dying_leave_food_timer = Time();
				if (body.size() != 1) {
					old_dir = body[1] - body[0];
				}
				is_dying = true;
			}
			Item item;
			bool need_to_erase_tail = true;
			if (check_collision_with_item(item)) {
				switch (item.type)
				{
				case ItemType::Food:
					need_to_erase_tail = false;
					break;
				default:
					break;
				}
			}
			int2 pos = item.pos;
			GameObjectManager::items.erase(pos);
			if (need_to_erase_tail) {
				erase_tail();
			}
		}
	}
	if (PlayerController* pc = dynamic_cast<PlayerController*>(controller); pc && pc->is_accelerated && body.size() > 1) {
		TimeManager::check_timer(accelerate_erase_tail_timer, PLAYER_ACCELERATE_ERASE_TAIL_TIME, std::bind(&Snake::erase_tail, this));
		current_difference = Time().tick - accelerate_erase_tail_timer.tick;
	}
	accelerate_erase_tail_timer = Time(Time().tick - current_difference);
}

void Snake::update() {
	controller->accelerate_update();
}

SingleSnakeDrawInfo Snake::get_draw_info() const {
	return SingleSnakeDrawInfo(color, body, move_double_count, old_dir, last_tail_pos, is_player(), is_dying);
}

bool Snake::is_player() const{
	return dynamic_cast<PlayerController*>(controller) != nullptr;
}