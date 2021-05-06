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

static const size_t size = 1024;
static std::byte buffer[size];

static auto bytes_writer_be = BytesWriter(ByteOrder::BigEndian, &buffer[0], size);
static auto bytes_writer_le = BytesWriter(ByteOrder::LittleEndian, &buffer[0], size);

static void write_byte_le_test() {
    puts("Write byte - little endian test");

    bytes_writer_le.write_byte(std::byte(0xAB));
    TEST_ASSERT(buffer[0] == std::byte(0xAB), "buffer[0] = 0x%.2hhx", buffer[0]);

    bytes_writer_le.clear();
}

static void write_byte_be_test() {
    puts("Write byte - big endian test");

    bytes_writer_be.write_byte(std::byte(0xAB));
    TEST_ASSERT(buffer[0] == std::byte(0xAB), "buffer[0] = 0x%.2hhx", buffer[0]);

    bytes_writer_be.clear();
}

static void write_char_le_test() {
    puts("Write char - little endian test");

    bytes_writer_le.write_char('C');
    TEST_ASSERT(buffer[0] == std::byte(0x43), "buffer[0] = 0x%.2hhx", buffer[0]);

    bytes_writer_le.clear();
}

static void write_char_be_test() {
    puts("Write char - big endian test");

    bytes_writer_be.write_char('C');
    TEST_ASSERT(buffer[0] == std::byte(0x43), "buffer[0] = 0x%.2hhx", buffer[0]);

    bytes_writer_be.clear();
}

static void write_int32_t_le_test() {
    puts("Write int32_t - little endian test");

    bytes_writer_le.write_int32_t(12);
    TEST_ASSERT(buffer[0] == std::byte(0x0C), "buffer[0] = 0x%.2hhx", buffer[0]);
    TEST_ASSERT(buffer[1] == std::byte(0x00), "buffer[1] = 0x%.2hhx", buffer[1]);
    TEST_ASSERT(buffer[2] == std::byte(0x00), "buffer[2] = 0x%.2hhx", buffer[2]);
    TEST_ASSERT(buffer[3] == std::byte(0x00), "buffer[3] = 0x%.2hhx", buffer[3]);

    bytes_writer_le.write_int32_t(-1953736185);
    TEST_ASSERT(buffer[4] == std::byte(0x07), "buffer[4] = 0x%.2hhx", buffer[4]);
    TEST_ASSERT(buffer[5] == std::byte(0x5A), "buffer[5] = 0x%.2hhx", buffer[5]);
    TEST_ASSERT(buffer[6] == std::byte(0x8C), "buffer[6] = 0x%.2hhx", buffer[6]);
    TEST_ASSERT(buffer[7] == std::byte(0x8B), "buffer[7] = 0x%.2hhx", buffer[7]);

    bytes_writer_le.clear();
}

static void write_int32_t_be_test() {
    puts("Write int32_t - big endian test");

    bytes_writer_be.write_int32_t(12);
    TEST_ASSERT(buffer[0] == std::byte(0x00), "buffer[0] = 0x%.2hhx", buffer[0]);
    TEST_ASSERT(buffer[1] == std::byte(0x00), "buffer[1] = 0x%.2hhx", buffer[1]);
    TEST_ASSERT(buffer[2] == std::byte(0x00), "buffer[2] = 0x%.2hhx", buffer[2]);
    TEST_ASSERT(buffer[3] == std::byte(0x0C), "buffer[3] = 0x%.2hhx", buffer[3]);

    bytes_writer_be.write_int32_t(-1953736185);
    TEST_ASSERT(buffer[4] == std::byte(0x8B), "buffer[4] = 0x%.2hhx", buffer[4]);
    TEST_ASSERT(buffer[5] == std::byte(0x8C), "buffer[5] = 0x%.2hhx", buffer[5]);
    TEST_ASSERT(buffer[6] == std::byte(0x5A), "buffer[6] = 0x%.2hhx", buffer[6]);
    TEST_ASSERT(buffer[7] == std::byte(0x07), "buffer[7] = 0x%.2hhx", buffer[7]);

    bytes_writer_be.clear();
}

static void write_int64_t_le_test() {
    puts("Write int64_t - little endian test");

    bytes_writer_le.write_int64_t(1934985738392383833);
    TEST_ASSERT(buffer[0] == std::byte(0x59), "buffer[0] = 0x%.2hhx", buffer[0]);
    TEST_ASSERT(buffer[1] == std::byte(0x31), "buffer[1] = 0x%.2hhx", buffer[1]);
    TEST_ASSERT(buffer[2] == std::byte(0x53), "buffer[2] = 0x%.2hhx", buffer[2]);
    TEST_ASSERT(buffer[3] == std::byte(0xEE), "buffer[3] = 0x%.2hhx", buffer[3]);
    TEST_ASSERT(buffer[4] == std::byte(0x46), "buffer[4] = 0x%.2hhx", buffer[4]);
    TEST_ASSERT(buffer[5] == std::byte(0x73), "buffer[5] = 0x%.2hhx", buffer[5]);
    TEST_ASSERT(buffer[6] == std::byte(0xDA), "buffer[6] = 0x%.2hhx", buffer[6]);
    TEST_ASSERT(buffer[7] == std::byte(0x1A), "buffer[7] = 0x%.2hhx", buffer[7]);

    bytes_writer_le.clear();
}

static void write_int64_t_be_test() {
    puts("Write int64_t - big endian test");

    bytes_writer_be.write_int64_t(1934985738392383833);
    TEST_ASSERT(buffer[0] == std::byte(0x1A), "buffer[0] = 0x%.2hhx", buffer[0]);
    TEST_ASSERT(buffer[1] == std::byte(0xdA), "buffer[1] = 0x%.2hhx", buffer[1]);
    TEST_ASSERT(buffer[2] == std::byte(0x73), "buffer[2] = 0x%.2hhx", buffer[2]);
    TEST_ASSERT(buffer[3] == std::byte(0x46), "buffer[3] = 0x%.2hhx", buffer[3]);
    TEST_ASSERT(buffer[4] == std::byte(0xEE), "buffer[4] = 0x%.2hhx", buffer[4]);
    TEST_ASSERT(buffer[5] == std::byte(0x53), "buffer[5] = 0x%.2hhx", buffer[5]);
    TEST_ASSERT(buffer[6] == std::byte(0x31), "buffer[6] = 0x%.2hhx", buffer[6]);
    TEST_ASSERT(buffer[7] == std::byte(0x59), "buffer[7] = 0x%.2hhx", buffer[7]);

    bytes_writer_be.clear();
}

static void write_float_le_test() {
    puts("Write float - little endian test");

    bytes_writer_le.write_float(245.5f);
    TEST_ASSERT(buffer[0] == std::byte(0x00), "buffer[0] = 0x%.2hhx", buffer[0]);
    TEST_ASSERT(buffer[1] == std::byte(0x80), "buffer[1] = 0x%.2hhx", buffer[1]);
    TEST_ASSERT(buffer[2] == std::byte(0x75), "buffer[2] = 0x%.2hhx", buffer[2]);
    TEST_ASSERT(buffer[3] == std::byte(0x43), "buffer[3] = 0x%.2hhx", buffer[3]);

    bytes_writer_le.clear();
}

static void write_float_be_test() {
    puts("Write float - big endian test");

    bytes_writer_be.write_float(245.5f);
    TEST_ASSERT(buffer[0] == std::byte(0x43), "buffer[0] = 0x%.2hhx", buffer[0]);
    TEST_ASSERT(buffer[1] == std::byte(0x75), "buffer[1] = 0x%.2hhx", buffer[1]);
    TEST_ASSERT(buffer[2] == std::byte(0x80), "buffer[2] = 0x%.2hhx", buffer[2]);
    TEST_ASSERT(buffer[3] == std::byte(0x00), "buffer[3] = 0x%.2hhx", buffer[3]);

    bytes_writer_be.clear();
}

static void write_double_le_test() {
    puts("Write double - little endian test");

    bytes_writer_le.write_double(593928311192.334351);
    TEST_ASSERT(buffer[0] == std::byte(0xB3), "buffer[0] = 0x%.2hhx", buffer[0]);
    TEST_ASSERT(buffer[1] == std::byte(0x0A), "buffer[1] = 0x%.2hhx", buffer[1]);
    TEST_ASSERT(buffer[2] == std::byte(0x33), "buffer[2] = 0x%.2hhx", buffer[2]);
    TEST_ASSERT(buffer[3] == std::byte(0x5A), "buffer[3] = 0x%.2hhx", buffer[3]);
    TEST_ASSERT(buffer[4] == std::byte(0x1C), "buffer[4] = 0x%.2hhx", buffer[4]);
    TEST_ASSERT(buffer[5] == std::byte(0x49), "buffer[5] = 0x%.2hhx", buffer[5]);
    TEST_ASSERT(buffer[6] == std::byte(0x61), "buffer[6] = 0x%.2hhx", buffer[6]);
    TEST_ASSERT(buffer[7] == std::byte(0x42), "buffer[7] = 0x%.2hhx", buffer[7]);

    bytes_writer_le.clear();
}

static void write_double_be_test() {
    puts("Write double - big endian test");

    bytes_writer_be.write_double(593928311192.334351);
    TEST_ASSERT(buffer[0] == std::byte(0x42), "buffer[0] = 0x%.2hhx", buffer[0]);
    TEST_ASSERT(buffer[1] == std::byte(0x61), "buffer[1] = 0x%.2hhx", buffer[1]);
    TEST_ASSERT(buffer[2] == std::byte(0x49), "buffer[2] = 0x%.2hhx", buffer[2]);
    TEST_ASSERT(buffer[3] == std::byte(0x1C), "buffer[3] = 0x%.2hhx", buffer[3]);
    TEST_ASSERT(buffer[4] == std::byte(0x5A), "buffer[4] = 0x%.2hhx", buffer[4]);
    TEST_ASSERT(buffer[5] == std::byte(0x33), "buffer[5] = 0x%.2hhx", buffer[5]);
    TEST_ASSERT(buffer[6] == std::byte(0x0A), "buffer[6] = 0x%.2hhx", buffer[6]);
    TEST_ASSERT(buffer[7] == std::byte(0xB3), "buffer[7] = 0x%.2hhx", buffer[7]);

    bytes_writer_be.clear();
}

int main() {
    write_byte_le_test();
    write_byte_be_test();
    write_char_le_test();
    write_char_be_test();
    write_int32_t_le_test();
    write_int32_t_be_test();
    write_int64_t_le_test();
    write_int64_t_be_test();
    write_float_le_test();
    write_float_be_test();
    write_double_le_test();
    write_double_be_test();

    puts("");
    puts("Finished successfully");

    return 0;
}
