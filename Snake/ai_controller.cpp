#include "ai_controller.h"

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


AIController::AIController(Snake* snake) : snake_(snake) {}

void AIController::update() {
    // 如果蛇即将死亡（被自己或墙撞到），尝试紧急规避
    if (snake_->about_death()) {
        evade_death();
        return;
    }

    // 优先策略：1. 追逐食物 2. 压迫玩家蛇 3. 安全移动
    if (try_chase_food()) {
        return; // 已找到食物并移动
    }
    if (try_pursue_player()) {
        return; // 已靠近玩家蛇
    }
    try_safe_move(); // 无法找到策略时进行安全移动
}

// 1. 追逐最近食物
bool AIController::try_chase_food()  const {
    int2 closest_food = find_closest_food();
    if (closest_food.x == -1) return false; // 无食物

    // 计算到食物的最短路径（避开障碍物）
    int2 current_dir = snake_->get_dir();
    std::vector<int2> path = find_path(snake_->get_head_pos(), closest_food, current_dir);
    if (path.size() < 2) return false; // 无有效路径

    // 获取下一步方向
    int2 next_dir = get_direction(snake_->get_head_pos(), path[1]);
    // 确保方向不是掉头（前后转）
    if (is_safe_move(next_dir) && !is_backwards(next_dir, current_dir)) {
        snake_->turn(next_dir);
        return true;
    }
    return false;
}

// 2. 压迫玩家蛇（当玩家在附近且AI更长时）
bool AIController::try_pursue_player() const {
    const int2& player_head = GameObjectManager::player_snake.get_head_pos();
    const int2& my_head = snake_->get_head_pos();

    // 仅当玩家在10格内且AI更长时触发压制
    if (abs(player_head.x - my_head.x) + abs(player_head.y - my_head.y) > 10)
        return false;

    if (snake_->body.size() <= GameObjectManager::player_snake.body.size())
        return false;

    // 尝试直接靠近玩家蛇头部
    int2 current_dir = snake_->get_dir();
    int2 direction = get_direction(my_head, player_head);

    // 确保方向不是掉头
    if (is_safe_move(direction) && !is_backwards(direction, current_dir)) {
        snake_->turn(direction);
        return true;
    }
    return false;
}

// 3. 紧急规避死亡（禁止前后转）
void AIController::evade_death() const {
    int2 current_dir = snake_->get_dir();

    // 优先尝试左右转（避免向后退）
    int2 left_dir = { current_dir.y, -current_dir.x };
    int2 right_dir = { -current_dir.y, current_dir.x };

    if (is_safe_move(left_dir)) {
        snake_->turn(left_dir);
        return;
    }
    if (is_safe_move(right_dir)) {
        snake_->turn(right_dir);
        return;
    }
}

// 4. 安全移动（无食物/玩家时，禁止前后转）
void AIController::try_safe_move() const {
    int2 current_dir = snake_->get_dir();

    // 优先保持当前方向（如果安全）
    if (is_safe_move(current_dir)) {
        return;
    }

    // 随机尝试其他方向（只允许左右转，禁止前后转）
    std::vector<int2> directions = {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0} // 上、下、左、右
    };
    // 移除掉头方向
    std::erase_if(directions, [current_dir, this](const int2& dir) {
        return is_backwards(dir, current_dir);
        });

    std::shuffle(directions.begin(), directions.end(), GameManager::random_engine);

    for (const auto& dir : directions) {
        if (is_safe_move(dir)) {
            snake_->turn(dir);
            return;
        }
    }
}

// 辅助函数：检查移动方向是否安全（不撞墙/自己）
bool AIController::is_safe_move(const int2& dir) const {
    int2 next_head = { snake_->get_head_pos().x + dir.x, snake_->get_head_pos().y + dir.y };
    return !snake_->is_death(next_head);
}

// 辅助函数：检查方向是否为掉头方向（前后转）
bool AIController::is_backwards(const int2& dir, const int2& current_dir) const {
    return (dir.x == -current_dir.x && dir.y == -current_dir.y);
}

// 辅助函数：找到最近食物
int2 AIController::find_closest_food() const {
    int2 closest = { -1, -1 };
    int min_dist = std::numeric_limits<int>::max();

    for (const auto& pair : GameObjectManager::items) {
        const auto& item = pair.second;
        if (!item.is_active) continue;

        int dist = abs(item.pos.x - snake_->get_head_pos().x) +
            abs(item.pos.y - snake_->get_head_pos().y);
        if (dist < min_dist) {
            min_dist = dist;
            closest = item.pos;
        }
    }
    return closest;
}

// 辅助函数：BFS 寻路（避开所有障碍物，起点处禁止掉头）
std::vector<int2> AIController::find_path(const int2& start, const int2& end, const int2& current_dir) const {
    std::vector<std::vector<bool>> visited(GameManager::snake_world.world_size.y + 1,
        std::vector<bool>(GameManager::snake_world.world_size.x + 1, false));
    std::vector<std::vector<int2>> parent(GameManager::snake_world.world_size.y + 1,
        std::vector<int2>(GameManager::snake_world.world_size.x + 1, { -1, -1 }));

    std::queue<int2> q;
    q.push(start);
    visited[start.x][start.y] = true;

    // 四个移动方向：上、下、左、右
    std::vector<int2> dirs = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
    // 计算掉头方向
    int2 back_dir = { -current_dir.x, -current_dir.y };

    while (!q.empty()) {
        int2 cur = q.front(); q.pop();
        if (cur.x == end.x && cur.y == end.y) break;

        for (const auto& d : dirs) {
            // 起点处禁止掉头
            if (cur == start && d == back_dir) continue;

            int2 next = { cur.x + d.x, cur.y + d.y };
            if (next.x < 0 || next.x >= GameManager::snake_world.world_size.y + 1 ||
                next.y < 0 || next.y >= GameManager::snake_world.world_size.x + 1) continue;

            if (!visited[next.x][next.y] && !snake_->is_death(next)) {
                visited[next.x][next.y] = true;
                parent[next.x][next.y] = cur;
                q.push(next);
            }
        }
    }

    // 重建路径
    std::vector<int2> path;
    int2 cur = end;
    while ((cur.x != start.x || cur.y != start.y) && cur.x > 0 && cur.y > 0) {
        path.push_back(cur);
        cur = parent[cur.x][cur.y];
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}

// 辅助函数：从两点计算方向
int2 AIController::get_direction(const int2& from, const int2& to) const {
    int dx = to.x - from.x;
    int dy = to.y - from.y;

    if (abs(dx) > abs(dy)) {
        // 水平差更大 → 左右走
        return { dx > 0 ? 1 : -1, 0 };
    }
    else {
        // 垂直差更大 → 上下走
        return { 0, dy > 0 ? 1 : -1 };
    }
}