#include "bytes_reader.hpp"

int32_t BytesReader::read_int32_t() {
    if (buffer_cursor + sizeof(int32_t) >= buffer_size) {
        // TODO(sysint64): Error buffer overflow
    }

    union {
        int32_t val;
        std::array<std::byte, sizeof(int32_t)> raw;
    } union_value {};

    for (size_t i = 0; i < sizeof(int32_t); i += 1) {
        union_value.raw[i] = buffer[buffer_cursor + i];
    }

    buffer_cursor += sizeof(int32_t);

    if (is_endian_mismatch(this->byte_order)) {
        swap_endian(union_value.raw);
    }

    return union_value.val;
}

int64_t BytesReader::read_int64_t() {
    if (buffer_cursor + sizeof(int64_t) >= buffer_size) {
        // TODO(sysint64): Error buffer overflow
    }

    union {
        int64_t val;
        std::array<std::byte, sizeof(int64_t)> raw;
    } union_value {};

    for (size_t i = 0; i < sizeof(int64_t); i += 1) {
        union_value.raw[i] = buffer[buffer_cursor + i];
    }

    buffer_cursor += sizeof(int64_t);

    if (is_endian_mismatch(this->byte_order)) {
        swap_endian(union_value.raw);
    }

    return union_value.val;
}

float BytesReader::read_float() {
    if (buffer_cursor + sizeof(float) >= buffer_size) {
        // TODO(sysint64): Error buffer overflow
    }

    union {
        float val;
        std::array<std::byte, sizeof(float)> raw;
    } union_value {};

    for (size_t i = 0; i < sizeof(float); i += 1) {
        union_value.raw[i] = buffer[buffer_cursor + i];
    }

    buffer_cursor += sizeof(float);

    if (is_endian_mismatch(this->byte_order)) {
        swap_endian(union_value.raw);
    }

    return union_value.val;
}

double BytesReader::read_double() {
    if (buffer_cursor + sizeof(double) >= buffer_size) {
        // TODO(sysint64): Error buffer overflow
    }

    union {
        double val;
        std::array<std::byte, sizeof(double)> raw;
    } union_value {};

    for (size_t i = 0; i < sizeof(double); i += 1) {
        union_value.raw[i] = buffer[buffer_cursor + i];
    }

    buffer_cursor += sizeof(double);

    if (is_endian_mismatch(this->byte_order)) {
        swap_endian(union_value.raw);
    }

    return union_value.val;
}

std::byte BytesReader::read_byte() {
    if (buffer_cursor >= buffer_size) {
        // TODO(sysint64): Error buffer overflow
    }

    auto const value = buffer[buffer_cursor];
    buffer_cursor += 1;;

    return value;
}

char BytesReader::read_char() {
    if (buffer_cursor >= buffer_size) {
        // TODO(sysint64): Error buffer overflow
    }

    auto const value = buffer[buffer_cursor];
    buffer_cursor += 1;;

    return char(value);
}
