#include "vm_buffers.hpp"
#include <stdio.h>
#include <cassert>
#include <array>

#define TEST_ASSERT(condition, hint, ...) \
{\
    if (!(condition)) {            \
        printf(hint, __VA_ARGS__); \
        puts(""); \
    } \
    assert(condition); \
} \

static void write_big_endian() {
    puts("Write big endian test");

    const size_t size = 1024;
    std::byte buffer[size];

    auto bytes_writer = BytesWriter(ByteOrder::BigEndian, &buffer[0], size);

    bytes_writer.write_byte(std::byte(0xAB));
    TEST_ASSERT(buffer[0] == std::byte(0xAB), "buffer[0] = 0x%.2hhx", buffer[0]);

    bytes_writer.write_char('C');
    TEST_ASSERT(buffer[1] == std::byte(0x43), "buffer[1] = 0x%.2hhx", buffer[2]);

    bytes_writer.write_int32_t(12);
    TEST_ASSERT(buffer[2] == std::byte(0x00), "buffer[2] = 0x%.2hhx", buffer[2]);
    TEST_ASSERT(buffer[3] == std::byte(0x00), "buffer[3] = 0x%.2hhx", buffer[3]);
    TEST_ASSERT(buffer[4] == std::byte(0x00), "buffer[4] = 0x%.2hhx", buffer[4]);
    TEST_ASSERT(buffer[5] == std::byte(0x0C), "buffer[5] = 0x%.2hhx", buffer[5]);

    bytes_writer.write_int32_t(-1953736185);
    TEST_ASSERT(buffer[6] == std::byte(0x8B), "buffer[6] = 0x%.2hhx", buffer[6]);
    TEST_ASSERT(buffer[7] == std::byte(0x8C), "buffer[7] = 0x%.2hhx", buffer[7]);
    TEST_ASSERT(buffer[8] == std::byte(0x5A), "buffer[8] = 0x%.2hhx", buffer[8]);
    TEST_ASSERT(buffer[9] == std::byte(0x07), "buffer[9] = 0x%.2hhx", buffer[9]);

    bytes_writer.write_int64_t(1934985738392383833);
    TEST_ASSERT(buffer[10] == std::byte(0x1A), "buffer[10] = 0x%.2hhx", buffer[10]);
    TEST_ASSERT(buffer[11] == std::byte(0xdA), "buffer[11] = 0x%.2hhx", buffer[11]);
    TEST_ASSERT(buffer[12] == std::byte(0x73), "buffer[12] = 0x%.2hhx", buffer[12]);
    TEST_ASSERT(buffer[13] == std::byte(0x46), "buffer[13] = 0x%.2hhx", buffer[13]);
    TEST_ASSERT(buffer[14] == std::byte(0xEE), "buffer[14] = 0x%.2hhx", buffer[14]);
    TEST_ASSERT(buffer[15] == std::byte(0x53), "buffer[15] = 0x%.2hhx", buffer[15]);
    TEST_ASSERT(buffer[16] == std::byte(0x31), "buffer[16] = 0x%.2hhx", buffer[16]);
    TEST_ASSERT(buffer[17] == std::byte(0x59), "buffer[17] = 0x%.2hhx", buffer[17]);

    bytes_writer.write_float(245.5f);
    TEST_ASSERT(buffer[18] == std::byte(0x43), "buffer[18] = 0x%.2hhx", buffer[18]);
    TEST_ASSERT(buffer[19] == std::byte(0x75), "buffer[19] = 0x%.2hhx", buffer[19]);
    TEST_ASSERT(buffer[20] == std::byte(0x80), "buffer[20] = 0x%.2hhx", buffer[20]);
    TEST_ASSERT(buffer[21] == std::byte(0x00), "buffer[21] = 0x%.2hhx", buffer[21]);

    bytes_writer.write_double(593928311192.334351);
    TEST_ASSERT(buffer[22] == std::byte(0x42), "buffer[22] = 0x%.2hhx", buffer[22]);
    TEST_ASSERT(buffer[23] == std::byte(0x61), "buffer[23] = 0x%.2hhx", buffer[23]);
    TEST_ASSERT(buffer[24] == std::byte(0x49), "buffer[24] = 0x%.2hhx", buffer[24]);
    TEST_ASSERT(buffer[25] == std::byte(0x1C), "buffer[25] = 0x%.2hhx", buffer[25]);
    TEST_ASSERT(buffer[26] == std::byte(0x5A), "buffer[26] = 0x%.2hhx", buffer[26]);
    TEST_ASSERT(buffer[27] == std::byte(0x33), "buffer[27] = 0x%.2hhx", buffer[27]);
    TEST_ASSERT(buffer[28] == std::byte(0x0A), "buffer[28] = 0x%.2hhx", buffer[28]);
    TEST_ASSERT(buffer[29] == std::byte(0xB3), "buffer[29] = 0x%.2hhx", buffer[29]);

    TEST_ASSERT(bytes_writer.size() == 30, "size = %zu", bytes_writer.size());
}

static void write_little_endian() {
    puts("Write little endian test");

    const size_t size = 1024;
    std::byte buffer[size];

    auto bytes_writer = BytesWriter(ByteOrder::LittleEndian, &buffer[0], size);

    bytes_writer.write_byte(std::byte(0xAB));
    TEST_ASSERT(buffer[0] == std::byte(0xAB), "buffer[0] = 0x%.2hhx", buffer[0]);

    bytes_writer.write_char('C');
    TEST_ASSERT(buffer[1] == std::byte(0x43), "buffer[1] = 0x%.2hhx", buffer[2]);

    bytes_writer.write_int32_t(12);
    TEST_ASSERT(buffer[2] == std::byte(0x0C), "buffer[2] = 0x%.2hhx", buffer[2]);
    TEST_ASSERT(buffer[3] == std::byte(0x00), "buffer[3] = 0x%.2hhx", buffer[3]);
    TEST_ASSERT(buffer[4] == std::byte(0x00), "buffer[4] = 0x%.2hhx", buffer[4]);
    TEST_ASSERT(buffer[5] == std::byte(0x00), "buffer[5] = 0x%.2hhx", buffer[5]);

    bytes_writer.write_int32_t(-1953736185);
    TEST_ASSERT(buffer[6] == std::byte(0x07), "buffer[6] = 0x%.2hhx", buffer[6]);
    TEST_ASSERT(buffer[7] == std::byte(0x5A), "buffer[7] = 0x%.2hhx", buffer[7]);
    TEST_ASSERT(buffer[8] == std::byte(0x8C), "buffer[8] = 0x%.2hhx", buffer[8]);
    TEST_ASSERT(buffer[9] == std::byte(0x8B), "buffer[9] = 0x%.2hhx", buffer[9]);

    bytes_writer.write_int64_t(1934985738392383833);
    TEST_ASSERT(buffer[10] == std::byte(0x59), "buffer[10] = 0x%.2hhx", buffer[10]);
    TEST_ASSERT(buffer[11] == std::byte(0x31), "buffer[11] = 0x%.2hhx", buffer[11]);
    TEST_ASSERT(buffer[12] == std::byte(0x53), "buffer[12] = 0x%.2hhx", buffer[12]);
    TEST_ASSERT(buffer[13] == std::byte(0xEE), "buffer[13] = 0x%.2hhx", buffer[13]);
    TEST_ASSERT(buffer[14] == std::byte(0x46), "buffer[14] = 0x%.2hhx", buffer[14]);
    TEST_ASSERT(buffer[15] == std::byte(0x73), "buffer[15] = 0x%.2hhx", buffer[15]);
    TEST_ASSERT(buffer[16] == std::byte(0xDA), "buffer[16] = 0x%.2hhx", buffer[16]);
    TEST_ASSERT(buffer[17] == std::byte(0x1A), "buffer[17] = 0x%.2hhx", buffer[17]);

    bytes_writer.write_float(245.5f);
    TEST_ASSERT(buffer[18] == std::byte(0x00), "buffer[18] = 0x%.2hhx", buffer[18]);
    TEST_ASSERT(buffer[19] == std::byte(0x80), "buffer[19] = 0x%.2hhx", buffer[19]);
    TEST_ASSERT(buffer[20] == std::byte(0x75), "buffer[20] = 0x%.2hhx", buffer[20]);
    TEST_ASSERT(buffer[21] == std::byte(0x43), "buffer[21] = 0x%.2hhx", buffer[21]);

    bytes_writer.write_double(593928311192.334351);
    TEST_ASSERT(buffer[22] == std::byte(0xB3), "buffer[22] = 0x%.2hhx", buffer[22]);
    TEST_ASSERT(buffer[23] == std::byte(0x0A), "buffer[23] = 0x%.2hhx", buffer[23]);
    TEST_ASSERT(buffer[24] == std::byte(0x33), "buffer[24] = 0x%.2hhx", buffer[24]);
    TEST_ASSERT(buffer[25] == std::byte(0x5A), "buffer[25] = 0x%.2hhx", buffer[25]);
    TEST_ASSERT(buffer[26] == std::byte(0x1C), "buffer[26] = 0x%.2hhx", buffer[26]);
    TEST_ASSERT(buffer[27] == std::byte(0x49), "buffer[27] = 0x%.2hhx", buffer[27]);
    TEST_ASSERT(buffer[28] == std::byte(0x61), "buffer[28] = 0x%.2hhx", buffer[28]);
    TEST_ASSERT(buffer[29] == std::byte(0x42), "buffer[29] = 0x%.2hhx", buffer[29]);

    TEST_ASSERT(bytes_writer.size() == 30, "size = %zu", bytes_writer.size());
}

int main() {
    write_little_endian();
    write_big_endian();

    puts("");
    puts("Finished successfully");

    return 0;
}
