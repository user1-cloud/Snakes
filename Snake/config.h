#pragma once

#include <random>
#include <cstddef>
#include <array>

#include <SDL3/SDL.h>

#include "color.h"
#include "int2.h"
#include "input_info.h"

// 随机数引擎
typedef std::mt19937 RANDOM_ENGINE_TYPE;

constexpr int SNAKE_WORLD_SIZE_X = 50;
constexpr int SNAKE_WORLD_SIZE_Y = 50;

// 速度（格 / s）
constexpr double SNAKE_PLAYER_SPEED = 6;
constexpr double SNAKE_PLAYER_SPEED_SHIFT_ACCELERATED = 12;
constexpr double SNAKE_ENEMY_SPEED = 1.6;

constexpr double SNAKE_DEATH_BUFFER_TIME = 0.6;

// 玩家加速时长度减少时间（s / 格）
constexpr double PLAYER_ACCELERATE_ERASE_TAIL_TIME = 3;

// 蛇初始长度
constexpr int SNAKE_PLAYER_INIT_LENGTH = 3;
constexpr int SNAKE_ENEMY_INIT_LENGTH = 3;
constexpr int SNAKE_ENEMY_INIT_LENGTH_MIN = 3;
constexpr int SNAKE_ENEMY_INIT_LENGTH_MAX = 12;

// 蛇初始方向
constexpr int2 SNAKE_PLAYER_INIT_DIR = int2(1, 0);

// 蛇死亡时长度减少时间（s / 格）
constexpr double SNAKE_DYING_LENGTH_REDUCE_TIME = 0.1;

// 敌人蛇数量限制
constexpr int INIT_ENEMY_SNAKE_NUMBER = 4;
constexpr int MAX_ENEMY_SNAKE_NUMBER = 8;
constexpr int MIN_ENEMY_SNAKE_NUMBER = 2;

// 敌人蛇生成间隔
constexpr int ENEMY_SNAKE_SPAWN_INTERVAL = 5;

// 蛇死亡时身体部分变为食物的概率
constexpr double BODY_TO_FOOD_PROBABILITY = 0.4;

// 敌人蛇每区域的随机生成生成点数量设置（世界坐标按照田字分为四个区域，因此总生成点数量为4倍这个）
constexpr int REGION_SPAWN_POINT_NUMBER = 3;

// 颜色
// 基础背景色
constexpr Color SOFT_LEMON = Color(255, 248, 225);

constexpr Color INDIAN_RED = Color(205, 92, 92);
// 所有蛇身色
constexpr Color AQUA_GREEN = Color(80, 200, 120);
constexpr Color SKY_CYAN = Color(70, 180, 250);
constexpr Color PEACHY_ORANGE = Color(255, 179, 102);
constexpr Color LAVENDER_PINK = Color(240, 147, 205);
constexpr Color MINT_PURPLE = Color(180, 142, 255);
constexpr Color HONEY_YELLOW = Color(255, 204, 102);
constexpr Color TEAL_GREEN = Color(20, 180, 166);
constexpr Color SLATE_BLUE = Color(100, 120, 245);
constexpr Color VIBRANT_TURQUOISE = Color(64, 224, 208);
constexpr Color CHERRY_BLOSSOM_PINK = Color(255, 182, 193);

// 所有道具色
constexpr Color STRAWBERRY_RED = Color(255, 80, 80);
constexpr Color MANGO_YELLOW = Color(255, 190, 70);
constexpr Color ENERGY_GREEN = Color(50, 210, 90);
constexpr Color SHIELD_BLUE = Color(60, 130, 240);
constexpr Color SLOW_PINK = Color(255, 120, 180);
constexpr Color APRICOT_ORANGE = Color(255, 165, 0);
constexpr Color BERRY_PURPLE = Color(153, 102, 255);

constexpr Color GRAPE_PURPLE = Color(140, 80, 220);

// 蛇身色数组
constexpr Color SNAKE_COLORS[] = {
    AQUA_GREEN,
    SKY_CYAN,
    PEACHY_ORANGE,
    LAVENDER_PINK,
    MINT_PURPLE,
    HONEY_YELLOW,
    TEAL_GREEN,
    SLATE_BLUE,
    VIBRANT_TURQUOISE,
    CHERRY_BLOSSOM_PINK
};
constexpr Color REAL_BACKGROUND_COLOR = MANGO_YELLOW;
constexpr Color BACKGROUND_COLOR = SOFT_LEMON;

constexpr Color PLAYER_SNAKE_COLOR = INDIAN_RED;

// 食物颜色
constexpr Color FOOD_COLOR = SLOW_PINK;

// 物品数量限制
constexpr int MAX_ITEM_NUMBER = 16;

// 初始食物数量
constexpr int INIT_FOOD_NUMBER = 8;

// 食物更新时间
constexpr int FOOD_UPDATE_TIME = 3;

// 食物更新数量
constexpr int FOOD_UPDATE_NUMBER = 6;

// 固定更新时刻间隔/s
constexpr double FIXED_DELTA_TIME = 0.02;

// 默认分辨率设置
constexpr int INIT_SCREEN_WIDTH = 1280;
constexpr int INIT_SCREEN_HEIGHT = 720;

// 键位设置
constexpr InputInfo INPUT_EMPTY;
constexpr InputInfo INPUT_UP_0(SDLK_UP, InputInfo::InputInfoType::DOWN);
constexpr InputInfo INPUT_UP_1(SDLK_W, InputInfo::InputInfoType::DOWN);
constexpr InputInfo INPUT_DOWN_0(SDLK_DOWN, InputInfo::InputInfoType::DOWN);
constexpr InputInfo INPUT_DOWN_1(SDLK_S, InputInfo::InputInfoType::DOWN);
constexpr InputInfo INPUT_LEFT_0(SDLK_LEFT, InputInfo::InputInfoType::DOWN);
constexpr InputInfo INPUT_LEFT_1(SDLK_A, InputInfo::InputInfoType::DOWN);
constexpr InputInfo INPUT_RIGHT_0(SDLK_RIGHT, InputInfo::InputInfoType::DOWN);
constexpr InputInfo INPUT_RIGHT_1(SDLK_D, InputInfo::InputInfoType::DOWN);

constexpr InputInfo INPUT_LSHIFT_DOWN(SDLK_LSHIFT, InputInfo::InputInfoType::DOWN);
constexpr InputInfo INPUT_LSHIFT_UP(SDLK_LSHIFT, InputInfo::InputInfoType::UP);
constexpr InputInfo INPUT_SPACE_DOWN(SDLK_SPACE, InputInfo::InputInfoType::DOWN);
constexpr InputInfo INPUT_SPACE_UP(SDLK_SPACE, InputInfo::InputInfoType::UP);

constexpr InputInfo INPUT_ESC_DOWN(SDLK_ESCAPE, InputInfo::InputInfoType::DOWN);
constexpr InputInfo INPUT_ESC_UP(SDLK_ESCAPE, InputInfo::InputInfoType::UP);

constexpr std::array<InputInfo, 8> MOVE_DIR_INPUT_ARR = {
    INPUT_UP_0,
    INPUT_UP_1,
    INPUT_DOWN_0,
    INPUT_DOWN_1,
    INPUT_LEFT_0,
    INPUT_LEFT_1,
    INPUT_RIGHT_0,
    INPUT_RIGHT_1
};

constexpr std::array<InputInfo, 4> ACCELERATE_INPUT_ARR = {
    INPUT_LSHIFT_DOWN,
    INPUT_LSHIFT_UP,
    INPUT_SPACE_DOWN,
    INPUT_SPACE_UP
};

constexpr std::array<InputInfo, 2> UI_INPUT_ARR = {
    INPUT_ESC_DOWN,
    INPUT_ESC_UP
};
//// 键位分类
//constexpr int player_down_keys[] = {
//    SDLK_UP,
//    SDLK_DOWN,
//    SDLK_LEFT,
//    SDLK_RIGHT,
//	SDLK_W, 
//    SDLK_S, 
//    SDLK_A, 
//    SDLK_D, 
//    SDLK_SPACE, 
//    SDLK_LSHIFT
//};
//constexpr size_t PLAYER_DOWN_KEYS_SIZE = std::size(player_down_keys);
//
//static constexpr int player_up_keys[] = {
//    SDLK_SPACE,
//    SDLK_LSHIFT
//};
//constexpr size_t PLAYER_UP_KEYS_SIZE = std::size(player_up_keys);
//
//constexpr int ui_down_keys[] = {
//	SDLK_ESCAPE
//};
//constexpr size_t UI_DOWN_KEYS_SIZE = std::size(ui_down_keys);
//
//constexpr int ui_up_keys[] = {
//	SDLK_ESCAPE
//};
//constexpr size_t UI_UP_KEYS_SIZE = std::size(ui_up_keys);
//
//// 具体键位设置
//constexpr int key_up_0 = SDLK_W;
//constexpr int key_up_1 = SDLK_UP;
//constexpr int key_down_0 = SDLK_S;
//constexpr int key_down_1 = SDLK_DOWN;
//constexpr int key_left_0 = SDLK_A;
//constexpr int key_left_1 = SDLK_LEFT;
//constexpr int key_right_0 = SDLK_D;
//constexpr int key_right_1 = SDLK_RIGHT;
//constexpr int key_speed_up_0 = SDLK_SPACE;
//constexpr int key_speed_up_1 = SDLK_LSHIFT;
//
//constexpr int key_pause = SDLK_ESCAPE;

constexpr size_t INPUT_BUFFER_SIZE = 4;