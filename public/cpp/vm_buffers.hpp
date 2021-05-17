#pragma once

#include <cstddef>
#include <cstdint>
#include <array>
#include <algorithm>

enum ByteOrder {
    LittleEndian,
    BigEndian,
    Native,
};

bool is_endian_mismatch(ByteOrder byte_order);

// Original version: https://mklimenko.github.io/english/2018/08/22/robust-endian-swap/
template<typename T>
void swap_endian(T &val) {
    union U {
        T val;
        std::array<std::byte, sizeof(T)> raw;
    } src, dst;

    src.val = val;
    std::reverse_copy(src.raw.begin(), src.raw.end(), dst.raw.begin());
    val = dst.val;
}
