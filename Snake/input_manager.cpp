#include <SDL3/SDL.h>
#include "input_manager.h"
#include "config.h"
#include "running.h"
#include "game_manager.h"

// 静态成员初始化
std::array<int, 4> InputManager::player_down_buffer = {};
std::array<int, 4> InputManager::player_up_buffer = {};
std::array<int, 4> InputManager::ui_down_buffer = {};
std::array<int, 4> InputManager::ui_up_buffer = {};
int InputManager::player_down_head = 0;
int InputManager::player_down_tail = 0;
int InputManager::player_up_head = 0;
int InputManager::player_up_tail = 0;
int InputManager::ui_down_head = 0;
int InputManager::ui_down_tail = 0;
int InputManager::ui_up_head = 0;
int InputManager::ui_up_tail = 0;

void InputManager::init() {
    player_down_buffer = {};
    player_up_buffer = {};
    ui_down_buffer = {};
    ui_up_buffer = {};
    player_down_head = 0;
    player_down_tail = 0;
    player_up_head = 0;
    player_up_tail = 0;
    ui_down_head = 0;
    ui_down_tail = 0;
    ui_up_head = 0;
    ui_up_tail = 0;
}

// 实现函数
void InputManager::update() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                Running::running = 0;
                break;
            case SDL_EVENT_WINDOW_RESIZED: {
                // 窗口大小变化时更新分辨率和缩放因子
                int2 window = int2(event.window.data1, event.window.data2);
                GameManager::snake_world.screen_size_updated(window);
                break;
            }
            case SDL_EVENT_KEY_DOWN: 
                // 检查是否属于玩家控制器按下键
                if (is_key_in_array(event.key.key, player_down_keys, PLAYER_DOWN_KEYS_SIZE)) {
                    // 环形缓冲区写入逻辑（满则覆盖）
                    if ((player_down_tail + 1) % 4 == player_down_head) {
                        player_down_head = (player_down_head + 1) % 4;
                    }
                    player_down_buffer[player_down_tail] = event.key.key;
                    player_down_tail = (player_down_tail + 1) % 4;
                }
                // 检查是否属于UI控制器按下键
                else if (is_key_in_array(event.key.key, ui_down_keys, UI_DOWN_KEYS_SIZE)) {
                    // 环形缓冲区写入逻辑（满则覆盖）
                    if ((ui_down_tail + 1) % 4 == ui_down_head) {
                        ui_down_head = (ui_down_head + 1) % 4;
                    }
                    ui_down_buffer[ui_down_tail] = event.key.key;
                    ui_down_tail = (ui_down_tail + 1) % 4;
                }
                break;
            case SDL_EVENT_KEY_UP:
                // 检查是否属于玩家控制器抬起键
                if (is_key_in_array(event.key.key, player_up_keys, PLAYER_UP_KEYS_SIZE)) {
                    // 环形缓冲区写入逻辑（满则覆盖）
                    if ((player_up_tail + 1) % 4 == player_up_head) {
                        player_up_head = (player_up_head + 1) % 4;
                    }
                    player_up_buffer[player_up_tail] = event.key.key;
                    player_up_tail = (player_up_tail + 1) % 4;
                }
                // 检查是否属于UI控制器抬起键
                else if (is_key_in_array(event.key.key, ui_up_keys, UI_UP_KEYS_SIZE)) {
                    // 环形缓冲区写入逻辑（满则覆盖）
                    if ((ui_up_tail + 1) % 4 == ui_up_head) {
                        ui_up_head = (ui_up_head + 1) % 4;
                    }
                    ui_up_buffer[ui_up_tail] = event.key.key;
                    ui_up_tail = (ui_up_tail + 1) % 4;
                }
                break;
        }
    }
}

bool InputManager::is_key_in_array(int key, const int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == key) {
            return true;
        }
    }
    return false;
}

int InputManager::get_player_down_event() {
    if (player_down_head == player_down_tail) {
        return -1; // 没有事件
    }
    int event = player_down_buffer[player_down_head];
    player_down_head = (player_down_head + 1) % 4;
    return event;
}

int InputManager::get_player_up_event() {
    if (player_up_head == player_up_tail) {
        return -1; // 没有事件
    }
    int event = player_up_buffer[player_up_head];
    player_up_head = (player_up_head + 1) % 4;
    return event;
}

int InputManager::get_ui_down_event() {
    if (ui_down_head == ui_down_tail) {
        return -1; // 没有事件
    }
    int event = ui_down_buffer[ui_down_head];
    ui_down_head = (ui_down_head + 1) % 4;
    return event;
}

int InputManager::get_ui_up_event() {
    if (ui_up_head == ui_up_tail) {
        return -1; // 没有事件
    }
    int event = ui_up_buffer[ui_up_head];
    ui_up_head = (ui_up_head + 1) % 4;
    return event;
}
