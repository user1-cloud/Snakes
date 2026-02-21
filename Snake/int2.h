#pragma once
#include <functional>

// 表示二维整数对的 int2 类
class int2 {
public:
    // 成员变量：存储两个整数（x和y分量）
    int x;
    int y;

    // 1. 构造函数
    // 默认构造函数：初始化为 (0, 0)
    constexpr int2() noexcept : x(0), y(0) {}

    // 带参数的构造函数：初始化指定值
    constexpr int2(int x_val, int y_val) noexcept : x(x_val), y(y_val) {}

    // 拷贝构造函数
    //constexpr int2(const int2& other) noexcept : x(other.x), y(other.y) {}

    // 2. 赋值运算符重载
    int2& operator=(const int2& other) noexcept;

    // 3. 常用运算符重载（算术运算）
    // 加法：int2 + int2
    constexpr int2 operator+(const int2& other) const noexcept {
        return int2(x + other.x, y + other.y);
    }

    // 减法：int2 - int2
    constexpr int2 operator-(const int2& other) const noexcept {
        return int2(x - other.x, y - other.y);
    }

    // 乘法：int2 * 标量
    constexpr int2 operator*(int scalar) const noexcept {
        return int2(x * scalar, y * scalar);
    }

    constexpr int2 operator*(double scalar) const noexcept {
        return int2(x * scalar, y * scalar); // 精度可能丢失
    }

    // 除法：int2 / 标量（注意除数不能为0）
    constexpr int2 operator/(int scalar) const {
        if (scalar == 0) {
            return int2(0, 0);
        }
        return int2(x / scalar, y / scalar);
    }

    constexpr int2 operator/(double scalar) const {
        if (scalar == 0) {
            return int2(0, 0);
        }
        return int2(x / scalar, y / scalar); // 精度可能丢失
    }

    constexpr int2 operator - () const noexcept {
        // 返回一个新的int2对象，其x和y分别是原对象的-x和-y
        return int2(-x, -y);
    }

    // 4. 复合赋值运算符
    int2& operator+=(const int2& other) noexcept;

    int2& operator-=(const int2& other) noexcept;

    // 5. 比较运算符
    constexpr bool operator==(const int2& other) const noexcept {
        return (x == other.x) && (y == other.y);
    }

    constexpr bool operator!=(const int2& other) const noexcept {
        return !(*this == other);
    }

    // 6. 辅助方法：计算模长的平方（避免浮点运算）
    constexpr int length_squared() const noexcept {
        return x * x + y * y;
    }
    // 7. 重置为 (0, 0)
    void reset() noexcept;
};

namespace std {
    template<>
    struct hash<int2> {
        size_t operator()(const int2& pos) const noexcept {
            size_t hash_x = hash<int>()(pos.x);
            size_t hash_y = hash<int>()(pos.y);
            return hash_x ^ (hash_y + 0x9e3779b9 + (hash_x << 6) + (hash_x >> 2));
        }
    };
}