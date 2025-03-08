#include <iostream>

constexpr bool is_big_endian() {
    union {
        uint32_t i;
        char c[4];
    } u = { 0x1 };
    return u.c[0] == 0;
}

int main() {
    std::cout << is_big_endian();
}