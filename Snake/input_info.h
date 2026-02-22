#pragma once
#include <functional>

struct InputInfo {
	enum class InputInfoType {
		EMPTY,
		DOWN,
		UP
	};
	int key = 0;
	InputInfoType type = InputInfoType::EMPTY;

	constexpr InputInfo(int key, InputInfoType type) :key(key), type(type) {}
	constexpr InputInfo() :key(0), type(InputInfoType::EMPTY) {}

	bool operator==(const InputInfo& other) const {
		return (this->key == other.key && this->type == other.type);
	}
};

namespace std {
	template<>
	struct hash<InputInfo> {
		size_t operator()(const InputInfo& info) const {
			size_t hash_type = hash<int>()(static_cast<int>(info.type));
			size_t hash_key = hash<int>()(info.key);
			return hash_key ^ (hash_type << 1);
		} 
	};
}