#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "config.h"
#include "updater.h"
#include "running.h"
#include "game_manager.h"
#include "game_object_manager.h"
#include "drawer.h"

int main(int argc, char* argv[]) {
    // 初始化 SDL3
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init Error: %s", SDL_GetError());
        return 1;
    }

    // 创建窗口
    SDL_Window* window = SDL_CreateWindow(
        "蛇对蛇",
        INIT_SCREEN_WIDTH,
        INIT_SCREEN_HEIGHT,
        SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE
    );
    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateWindow Error: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // 创建渲染器
    Drawer drawer(window);
    if (!drawer.success) {
        return 1;
    }
    
    GameManager::main_init();
    Updater::updater_init();
    while (Running::running) {
        Updater::updater_update();
        drawer.draw();
    }
    drawer.quit();
    return 0;
}