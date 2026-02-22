#pragma once
#include <array>
#include <mutex>

#include "config.h"

template<typename T, std::size_t Size>
class RingBuffer
{
    std::array<T, Size> buffer;
    size_t head;
    size_t tail;
    mutable std::mutex mtx;
public:
    RingBuffer() : head(0), tail(0) {}

    RingBuffer(const RingBuffer&) = delete;
    RingBuffer& operator=(const RingBuffer&) = delete;
    RingBuffer(RingBuffer&&) = delete;
    RingBuffer& operator=(RingBuffer&&) = delete;

    void init() {
        head = tail;
    }

    void write(const T& item) {
        std::lock_guard<std::mutex> lock(mtx);
        if ((tail + 1) % Size == head) {
            head = (head + 1) % Size;
        }
        buffer[tail] = item;
        tail = (tail + 1) % Size;
    }

    T read(bool& success) {
        std::lock_guard<std::mutex> lock(mtx);
        if (head == tail) {
            success = false;
            return T{};
        }
        success = true;
        T item = buffer[head];
        head = (head + 1) % Size;
        return item;
    }
};