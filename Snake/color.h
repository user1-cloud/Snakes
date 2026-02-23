#pragma once
#include <functional>

#pragma once
struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;

private:
    constexpr unsigned char clamp(int value) {
        if (value < 0) return 0;
        if (value > 255) return 255;
        return static_cast<unsigned char>(value);
    }

public:
    constexpr Color(int r, int g, int b) : r(clamp(r)), g(clamp(g)), b(clamp(b)) {}
    constexpr Color() : Color(0, 0, 0) {}
};

inline bool operator==(const Color& lhs, const Color& rhs) noexcept {
    return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b;
}

namespace std {
    template<>
    struct hash<Color> {
        std::size_t operator()(const Color& c) const noexcept {
            std::size_t h1 = std::hash<unsigned char>{}(c.r);
            std::size_t h2 = std::hash<unsigned char>{}(c.g);
            std::size_t h3 = std::hash<unsigned char>{}(c.b);

            return h1 ^ (h2 << 4) ^ (h3 << 8);
        }
    };
}