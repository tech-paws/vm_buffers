#pragma once

#include "vm_buffers.hpp"

class BytesWriter {
public:
    BytesWriter(
        ByteOrder byte_order,
        std::byte* buffer,
        size_t buffer_size
    ) {
        this->byte_order = byte_order;
        this->buffer = buffer;
        this->buffer_size = buffer_size;
    }

    inline void clear() {
        buffer_cursor = 0;
    }

    void write_int32_t(int32_t value);

    void write_int64_t(int64_t value);

    void write_float(float value);

    void write_double(double value);

    void write_byte(std::byte byte);

    void write_char(char ch);

    inline size_t size() {
        return buffer_cursor;
    }

private:
    ByteOrder byte_order;

    std::byte* buffer;

    size_t buffer_size;
    size_t buffer_cursor = 0;

    bool is_endian_mismatch();
};
