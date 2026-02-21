# Snakes Game (C++ + SDL3)
![Language](https://img.shields.io/badge/language-C%2B%2B-blue.svg)
![Library](https://img.shields.io/badge/library-SDL3-orange.svg)

一款基于 C++ 和 SDL3 开发的经典贪吃蛇游戏，包含基础的游戏逻辑、图形渲染和键盘交互。

## 📋 项目简介
- **核心技术**：C++ 标准库 + SDL3（图形渲染、事件处理、窗口管理）
- **游戏功能**：
  - 方向键控制蛇的移动，吃掉食物后蛇身变长
  - 碰撞检测（边界/蛇身碰撞触发游戏结束）
  - AI系统
- **开发环境**：支持 GCC/Clang/MSVC 编译器

## 🛠️ 环境准备
### 1. 依赖安装（SDL3）
#### Linux (Ubuntu/Debian)
```bash
# 安装SDL3开发库
sudo apt update
sudo apt install libsdl3-dev
```

#### macOS (Homebrew)
```bash
# 先安装Homebrew（如未安装）
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
# 安装SDL3
brew install sdl3
```

#### Windows
- 方式1：通过[vcpkg](https://vcpkg.io/)安装（推荐）
  ```bash
  # 安装vcpkg（首次使用）
  git clone https://github.com/microsoft/vcpkg.git
  cd vcpkg
  ./bootstrap-vcpkg.bat
  # 安装SDL3
  vcpkg install sdl3:x64-windows
  ```
- 方式2：手动下载 SDL3 开发包  
  从 [SDL3 官方下载页](https://github.com/libsdl-org/SDL/releases) 下载 Windows 版本的开发包，解压后配置头文件和库文件路径。

### 2. 编译器要求
- Linux/macOS：GCC 9+ 或 Clang 10+
- Windows：MSVC (Visual Studio) 或 MinGW-w64

## 🚀 编译与运行
### 方式1：手动编译（使用g++/clang++）
```bash
# 克隆项目
git clone https://github.com/user1-cloud/Snakes.git
cd Snakes

# Linux/macOS 编译
g++ src/*.cpp -o Snakes -lSDL3 -std=c++17
# 运行
./snake_game

# Windows (MinGW) 编译
g++ src/*.cpp -o Snakes.exe -lSDL3 -std=c++17 -I path/to/SDL3/include -L path/to/SDL3/lib
# 运行
snake_game.exe
```

### 方式2：使用 CMake（推荐，跨平台）
```bash
# 克隆项目 (请替换为您的实际仓库地址)
git clone https://github.com/user1-cloud/Snakes.git
cd Snakes

# 创建构建目录
mkdir build && cd build

# 生成构建文件（Linux/macOS）
cmake ..
# Windows (vcpkg)
cmake .. -DCMAKE_TOOLCHAIN_FILE=path/to/vcpkg/scripts/buildsystems/vcpkg.cmake

# 编译
cmake --build . --config Release

# 运行
# Linux/macOS
./snake_game
# Windows
Release\snake_game.exe
```

## 🕹️ 操作说明
| 按键 | 功能 |
|------|------|
| ↑ / W | 蛇向上移动 |
| ↓ / S | 蛇向下移动 |
| ← / A | 蛇向左移动 |
| → / D | 蛇向右移动 |
| Space / Shift | 蛇加速 |
| ESC | 暂停 / 继续游戏 |


## 🐞 常见问题
1. **编译报错：找不到 SDL3 头文件**  
   解决方案：确认 SDL3 已正确安装，编译时通过 `-I` 参数指定头文件路径（如 `-I /usr/include/SDL3`）。
2. **运行时提示缺少 SDL3 动态库**  
   - Linux/macOS：确保系统已安装 SDL3 运行库（`sudo apt install libsdl3-0`）
   - Windows：将 SDL3 的 `SDL3.dll` 复制到可执行文件同目录下。
3. **CMake 配置失败**  
   检查 CMakeLists.txt 中是否正确链接 SDL3，或通过 `-DSDL3_DIR` 指定 SDL3 安装路径。

## ✨ 开发计划
- [x] 添加暂停功能
- [ ] 添加死亡界面
- [ ] 添加背景音乐和音效
- [ ] 实现分数系统
- [ ] 增加不同难度等级
```
