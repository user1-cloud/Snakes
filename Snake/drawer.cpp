#include "drawer.h"
#include "config.h"
#include "snake_world.h"
#include "game_manager.h"
#include "game_object_manager.h"
#include "ui_manager.h"
#include "game_stat.h"

Drawer::Drawer(SDL_Window* window) : window(window) {
    renderer = SDL_CreateRenderer(window, NULL); 

    if (renderer) {
        if (SDL_SetRenderVSync(renderer, 1) < 0) {
            SDL_Log("Warning: Unable to enable VSync: %s", SDL_GetError());
        }
        if (!SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND)) {
            SDL_Log("Warning: Unable to enable blend mode: %s", SDL_GetError());
        }
        success = true;
    }
    else {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}


void Drawer::draw() {
    // 绘制游戏
    SDL_SetRenderDrawColor(renderer, REAL_BACKGROUND_COLOR.r, REAL_BACKGROUND_COLOR.g, REAL_BACKGROUND_COLOR.b, 255); // 世界外背景
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, 255);

    // 屏幕大小（减去1后的）
    int2 screen_size = GameManager::snake_world.screen_size + int2(1, 1);

    render_game(renderer);
    if (GameObjectManager::player_snake.is_dying) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 50);
        SDL_FRect target_rect = { 0, 0, screen_size.x, screen_size.y };
        SDL_RenderFillRect(renderer, &target_rect);
    }
    if (UIManager::is_paused) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 127);
        SDL_FRect target_rect = { 0, 0, screen_size.x, screen_size.y };
        SDL_RenderFillRect(renderer, &target_rect);
    }
    SDL_RenderPresent(renderer);
}

void Drawer::quit() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Drawer::render_game(SDL_Renderer* renderer0) {

    SnakeWorld snake_world = GameManager::snake_world;

    int2 pos0 = snake_world.get_origin_screen_pos();
    int2 world_screen_size = int2((snake_world.world_size.x + 1) * snake_world.point_size.x, (snake_world.world_size.y + 1) * snake_world.point_size.y);

    SDL_FRect world_rect = { pos0.x, pos0.y - world_screen_size.y, world_screen_size.x, world_screen_size.y };
    SDL_RenderFillRect(renderer0, &world_rect);

    // 游戏画面渲染逻辑
    for (const SingleSnakeDrawInfo& single_snake_draw_info : GameObjectManager::draw_info.single_snake_draw_infos) {
        const std::vector<int2>& body = single_snake_draw_info.body;

        Color color = single_snake_draw_info.color;
        SDL_SetRenderDrawColor(renderer0, color.r, color.g, color.b, 255);
        int body_size = body.size();
        double back_offset_rate = 1 - single_snake_draw_info.move_double_count;

        if (body_size == 1) {
            int2 head_dir = single_snake_draw_info.old_dir;
            int2 target_pos = snake_world.world_pos_to_screen_pos(body.back())
                - int2(snake_world.point_size.x * head_dir.x, -snake_world.point_size.y * head_dir.y)
                * back_offset_rate;
            SDL_FRect target_rect = snake_world.screen_left_down_pos_to_rect(target_pos);
            SDL_RenderFillRect(renderer0, &target_rect);
            if (single_snake_draw_info.is_player_snake && !single_snake_draw_info.is_dying) {
                draw_snake_eyes(renderer0, target_pos, head_dir);
            }
        }
        else if (body_size > 1) {
            for (int i = 0; i < body_size - 1; i++) {
                SDL_FRect target_rect_body = snake_world.world_pos_to_rect(body[i]);
                SDL_RenderFillRect(renderer0, &target_rect_body);
            }
            int2 head_dir = body.back() - body[body_size - 2];
            int2 target_pos = snake_world.world_pos_to_screen_pos(body.back())
                - int2(snake_world.point_size.x * head_dir.x, -snake_world.point_size.y * head_dir.y)
                * back_offset_rate;
            SDL_FRect target_rect = snake_world.screen_left_down_pos_to_rect(target_pos);
            SDL_RenderFillRect(renderer0, &target_rect);
            // 如果是玩家蛇，绘制眼睛
            if (single_snake_draw_info.is_player_snake && !single_snake_draw_info.is_dying) {
                draw_snake_eyes(renderer0, target_pos, single_snake_draw_info.old_dir);
            }

            int2 tail_dir = body[0] - single_snake_draw_info.last_tail_pos;
            target_pos = snake_world.world_pos_to_screen_pos(body[0])
                - int2(snake_world.point_size.x * tail_dir.x, -snake_world.point_size.y * tail_dir.y)
                * back_offset_rate;
            target_rect = snake_world.screen_left_down_pos_to_rect(target_pos);
            SDL_RenderFillRect(renderer0, &target_rect);
        }
    }

    for (const Item& item : GameObjectManager::draw_info.items) {
        if (item.is_active) {
            SDL_FRect target_rect = snake_world.world_pos_to_rect(item.pos);
            Color color;
            switch (item.type)
            {
            case ItemType::Food:
                color = FOOD_COLOR;
                break;
            default:
                break;
            }
            SDL_SetRenderDrawColor(renderer0, color.r, color.g, color.b, 255);
            SDL_RenderFillRect(renderer0, &target_rect);
        }
    }
}


void Drawer::draw_snake_eyes(SDL_Renderer* renderer0, const int2& pos, const int2& dir) {
    Uint8 r, g, b, a;
    SDL_GetRenderDrawColor(renderer0, &r, &g, &b, &a);
    SDL_SetRenderDrawColor(renderer0, PLAYER_SNAKE_EYES_COLOR.r, PLAYER_SNAKE_EYES_COLOR.g, PLAYER_SNAKE_EYES_COLOR.b, 255);
    std::vector<int2> eye_pos;
    if (dir == int2(1, 0)) {
        eye_pos.assign({ int2(6, 3), int2(7, 3), int2(6, 6), int2(7, 6) });
    }
    else if (dir == int2(-1, 0)) {
        eye_pos.assign({ int2(2, 3), int2(3, 3), int2(2, 6), int2(3, 6) });
    }
    else if (dir == int2(0, 1)) {
        eye_pos.assign({ int2(3, 6), int2(3, 7), int2(6, 6), int2(6, 7) });
    }
    else if (dir == int2(0, -1)) {
        eye_pos.assign({ int2(3, 2), int2(3, 3), int2(6, 2), int2(6, 3) });
    }
    for (int2 e_pos : eye_pos) {
        SDL_FRect target_rect = GameManager::snake_world.screen_left_down_pos_to_little_rect(pos, e_pos);
        SDL_RenderFillRect(renderer0, &target_rect);
    }
    SDL_SetRenderDrawColor(renderer0, r, g, b, a);
}