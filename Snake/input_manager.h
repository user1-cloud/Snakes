#pragma once
#include <SDL3/SDL.h>
#include <unordered_set>
#include "input_info.h"
#include "ring_buffer.h"
#include "config.h"

class InputManager {
public:
    static const std::unordered_set<InputInfo> move_dir_input_set;
    static const std::unordered_set<InputInfo> accelerate_input_set;
    static const std::unordered_set<InputInfo> ui_input_set;

    // 四个静态缓冲区（每个长度为4）
    static RingBuffer<InputInfo, INPUT_BUFFER_SIZE> move_direction_buffer;
    static RingBuffer<InputInfo, INPUT_BUFFER_SIZE> accelerate_buffer;
    static RingBuffer<InputInfo, INPUT_BUFFER_SIZE> system_buffer;

    static void init();

    // 更新函数：处理所有输入事件
    static void update();

    static bool get_event(RingBuffer<InputInfo, INPUT_BUFFER_SIZE>& buffer, InputInfo& info);

private:
    // 辅助函数：检查值是否在常量数组中
    static bool is_key_in_set(const InputInfo& key_info, const std::unordered_set<InputInfo>& arr);

    // 将给定InputInfo分发到buffer中
    static void buffer_send(const InputInfo& info);
};