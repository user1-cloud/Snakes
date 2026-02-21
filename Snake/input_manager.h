#pragma once
#include <SDL3/SDL.h>

class InputManager {
public:

    // 四个静态缓冲区（每个长度为4）
    static int player_down_buffer[4];
    static int player_up_buffer[4];
    static int ui_down_buffer[4];
    static int ui_up_buffer[4];

    // 静态指针（环形缓冲区实现）
    static int player_down_head;
    static int player_down_tail;
    static int player_up_head;
    static int player_up_tail;
    static int ui_down_head;
    static int ui_down_tail;
    static int ui_up_head;
    static int ui_up_tail;

    // 更新函数：处理所有输入事件
    static void update();

    // 获取玩家控制器按下事件
    static int get_player_down_event();
    // 获取玩家控制器抬起事件
    static int get_player_up_event();
    // 获取UI控制器按下事件
    static int get_ui_down_event();
    // 获取UI控制器抬起事件
    static int get_ui_up_event();

private:
    // 辅助函数：检查值是否在常量数组中
    static bool is_key_in_array(int key, const int* arr, int size);
};