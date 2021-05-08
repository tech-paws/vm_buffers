#include <array>
#include <algorithm>

#include "bytes_writer.hpp"

// https://stackoverflow.com/questions/1001307/detecting-endianness-programmatically-in-a-c-program
bool is_big_endian() {
    union {
        uint32_t i;
        char c[4];
    } bint = {0x01020304};

    return bint.c[0] == 1;
}

bool is_little_endian() {
    return !is_big_endian();
}

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

bool BytesWriter::is_endian_mismatch() {
    bool mismatch_big_endian = is_big_endian() &&
        this->byte_order == ByteOrder::LittleEndian;

    bool mismatch_little_endian = is_little_endian() &&
        this->byte_order == ByteOrder::BigEndian;

    return mismatch_big_endian || mismatch_little_endian;
}

void BytesWriter::write_byte(std::byte byte) {
    if (buffer_cursor >= buffer_size) {
        // TODO(sysint64): Error buffer overflow
    }

    buffer[buffer_cursor] = byte;
    buffer_cursor += 1;
}

void BytesWriter::write_char(char ch) {
    if (buffer_cursor >= buffer_size) {
        // TODO(sysint64): Error buffer overflow
    }

    buffer[buffer_cursor] = std::byte(ch);
    buffer_cursor += 1;
}

void BytesWriter::write_int32_t(int32_t value) {
    if (buffer_cursor + sizeof(int32_t) >= buffer_size) {
        // TODO(sysint64): Error buffer overflow
    }

    if (this->is_endian_mismatch()) {
        swap_endian(value);
    }

    union {
        int32_t val;
        std::array<std::byte, sizeof(int32_t)> raw;
    } union_value {};

    union_value.val = value;

    for (size_t i = 0; i < sizeof(int32_t); i += 1) {
        buffer[buffer_cursor + i] = union_value.raw[i];
    }

    buffer_cursor += sizeof(int32_t);
}

void BytesWriter::write_int64_t(int64_t value) {
    if (buffer_cursor + sizeof(int64_t) >= buffer_size) {
        // TODO(sysint64): Error buffer overflow
    }

    if (this->is_endian_mismatch()) {
        swap_endian(value);
    }

    union {
        int64_t val;
        std::array<std::byte, sizeof(int64_t)> raw;
    } union_value {};

    union_value.val = value;

    for (size_t i = 0; i < sizeof(int64_t); i += 1) {
        buffer[buffer_cursor + i] = union_value.raw[i];
    }

    buffer_cursor += sizeof(int64_t);
}

void BytesWriter::write_float(float value) {
    if (buffer_cursor + sizeof(float) >= buffer_size) {
        // TODO(sysint64): Error buffer overflow
    }

    if (this->is_endian_mismatch()) {
        swap_endian(value);
    }

    union {
        float val;
        std::array<std::byte, sizeof(float)> raw;
    } union_value {};

    union_value.val = value;

    for (size_t i = 0; i < sizeof(float); i += 1) {
        buffer[buffer_cursor + i] = union_value.raw[i];
    }

    buffer_cursor += sizeof(float);
}

void BytesWriter::write_double(double value) {
    if (buffer_cursor + sizeof(double) >= buffer_size) {
        // TODO(sysint64): Error buffer overflow
    }

    if (this->is_endian_mismatch()) {
        swap_endian(value);
    }

    union {
        double val;
        std::array<std::byte, sizeof(double)> raw;
    } union_value {};

    union_value.val = value;

    for (size_t i = 0; i < sizeof(double); i += 1) {
        buffer[buffer_cursor + i] = union_value.raw[i];
    }

    buffer_cursor += sizeof(double);
}
