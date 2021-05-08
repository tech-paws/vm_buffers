#pragma once

#include "vm_buffers.hpp"

class BytesReader {
public:
    BytesReader(
        ByteOrder byte_order,
        std::byte* buffer,
        size_t buffer_size
    ) {
        this->byte_order = byte_order;
        this->buffer = buffer;
        this->buffer_size = buffer_size;
    }

    inline void reset() {
        buffer_cursor = 0;
    }

    int32_t read_int32_t();

    int64_t read_int64_t();

    float read_float();

    double read_double();

    std::byte read_byte();

    char read_char();

private:
    ByteOrder byte_order;

    std::byte* buffer;

    size_t buffer_size;
    size_t buffer_cursor = 0;
};
