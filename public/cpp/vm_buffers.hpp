#pragma once

#include <cstddef>
#include <cstdint>

enum class ByteOrder {
    LittleEndian,
    BigEndian,
    Native,
};

extern "C"
struct BytesBuffer {
    std::byte const* data;
    size_t length;
};
