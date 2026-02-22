#include <SDL3/SDL.h>
#include "input_manager.h"
#include "config.h"
#include "running.h"
#include "game_manager.h"

const std::unordered_set<InputInfo> InputManager::move_dir_input_set(MOVE_DIR_INPUT_ARR.begin(), MOVE_DIR_INPUT_ARR.end());
const std::unordered_set<InputInfo> InputManager::accelerate_input_set(ACCELERATE_INPUT_ARR.begin(), ACCELERATE_INPUT_ARR.end());
const std::unordered_set<InputInfo> InputManager::ui_input_set(UI_INPUT_ARR.begin(), UI_INPUT_ARR.end());

RingBuffer<InputInfo, INPUT_BUFFER_SIZE> InputManager::move_direction_buffer = RingBuffer<InputInfo, INPUT_BUFFER_SIZE>();
RingBuffer<InputInfo, INPUT_BUFFER_SIZE> InputManager::accelerate_buffer = RingBuffer<InputInfo, INPUT_BUFFER_SIZE>();
RingBuffer<InputInfo, INPUT_BUFFER_SIZE> InputManager::system_buffer = RingBuffer<InputInfo, INPUT_BUFFER_SIZE>();

void InputManager::init() {
    move_direction_buffer.init();
}

// 实现函数
void InputManager::update() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        InputInfo input_info;
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
                input_info = InputInfo(event.key.key, InputInfo::InputInfoType::DOWN);
                buffer_send(input_info);
                break;
            case SDL_EVENT_KEY_UP:
                input_info = InputInfo(event.key.key, InputInfo::InputInfoType::UP);
                buffer_send(input_info);
                break;
            default:
                break;
        }
    }
}

bool InputManager::is_key_in_set(const InputInfo& key_info, const std::unordered_set<InputInfo>& set) {
    return set.find(key_info) != set.end();
}

bool InputManager::get_event(RingBuffer<InputInfo, INPUT_BUFFER_SIZE>& buffer, InputInfo& info) {
    bool is_success;
    info = buffer.read(is_success);
    return is_success;
}

void InputManager::buffer_send(const InputInfo& input_info) {
    if (is_key_in_set(input_info, move_dir_input_set)) {
        move_direction_buffer.write(input_info);
    }
    else if (is_key_in_set(input_info, accelerate_input_set)) {
        accelerate_buffer.write(input_info);
    }
    else if (is_key_in_set(input_info, ui_input_set)) {
        system_buffer.write(input_info);
    }
}