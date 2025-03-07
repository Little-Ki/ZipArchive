#pragma once

#include <stdint.h>

namespace zip {

    constexpr bool is_big_endian() {
        union {
            uint32_t i;
            char c[4];
        } var = {0x1};

        return var.c[0] == 0;
    }

    template <typename T, size_t N = sizeof(T)>
    void reverse(T *val) {
        auto buf = reinterpret_cast<uint8_t *>(val);

        for (auto i = 0; i < (N >> 1); i++) {
            std::swap(buf[i], buf[N - 1 - i]);
        }
    }

    

}