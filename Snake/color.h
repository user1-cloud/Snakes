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
	constexpr Color() :Color(0, 0, 0) {}
};