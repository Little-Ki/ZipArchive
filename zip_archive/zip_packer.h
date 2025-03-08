#pragma once
#include <iostream>
#include <stdint.h>

namespace zip {

    constexpr bool is_big_endian() {
        union {
            uint32_t i;
            char c[4];
        } u = {0x1};
        return u.c[0] == 0;
    }

    void reverse() {};

    template <typename T, size_t N = sizeof(T)>
    void reverse(T *val) {
        auto buf = reinterpret_cast<char *>(val);

        for (auto i = 0; i < (N >> 1); i++) {
            std::swap(buf[i], buf[N - 1 - i]);
        }
    }

    template <typename T, typename... Args>
    void reverse(T *val, Args... args) {
        reverse(val);
        reverse(args...);
    }

    template <typename T>
    void pack(std::ostream stream, T value) {
        if (!is_big_endian()) {
            reverse(&value);
        }

        stream << value;
    }

}