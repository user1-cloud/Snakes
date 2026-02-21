#pragma once
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <random>
#include <limits>

#include "controller.h"
#include "game_object_manager.h"
#include "game_manager.h"
#include "snake.h"

class AIController:public Controller {
public:
    AIController(Snake* snake);
    virtual void update() const override;

private:
    Snake* snake_ = nullptr;

    // 1. 追逐最近食物
    bool try_chase_food() const;

    // 2. 压迫玩家蛇（当玩家在附近且AI更长时）
    bool try_pursue_player() const;

    // 3. 紧急规避死亡
    void evade_death() const;

    // 4. 安全移动（无食物/玩家时）
    void try_safe_move() const;

    // 辅助函数：检查移动方向是否安全
    bool is_safe_move(const int2& dir) const;

    // 辅助函数：找到最近食物
    int2 find_closest_food() const;

    // 辅助函数：BFS 寻路（避开所有障碍物）
    std::vector<int2> find_path(const int2& start, const int2& end, const int2& current_dir) const;

    // 辅助函数：从两点计算方向
    int2 get_direction(const int2& from, const int2& to) const;

    bool is_backwards(const int2& dir, const int2& current_dir) const;
};

