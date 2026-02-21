#include "int2.h"

// 2. 赋值运算符重载
int2& int2::operator=(const int2& other) noexcept {
    if (this != &other) { // 防止自赋值
        x = other.x;
        y = other.y;
    }
    return *this;
}


// 4. 复合赋值运算符
int2& int2::operator+=(const int2& other) noexcept {
    x += other.x;
    y += other.y;
    return *this;
}

int2& int2::operator-=(const int2& other) noexcept {
    x -= other.x;
    y -= other.y;
    return *this;
}

// 7. 重置为 (0, 0)
void int2::reset() noexcept {
    x = 0;
    y = 0;
}

// 全局运算符重载：标量 * int2（支持交换律）
constexpr int2 operator*(int scalar, const int2& vec) noexcept {
    return vec * scalar; // 复用已实现的 int2 * 标量
}