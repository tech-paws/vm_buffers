#include "vm_buffers.hpp"

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

bool is_endian_mismatch(ByteOrder byte_order) {
    bool mismatch_big_endian = is_big_endian() &&
        byte_order == ByteOrder::LittleEndian;

    bool mismatch_little_endian = is_little_endian() &&
        byte_order == ByteOrder::BigEndian;

    return mismatch_big_endian || mismatch_little_endian;
}
