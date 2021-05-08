#include <stdio.h>
#include <cassert>
#include <array>

#include "bytes_writer.hpp"
#include "bytes_reader.hpp"

#define TEST_ASSERT(condition, hint, ...) \
{ \
    if (!(condition)) { \
        printf(hint, __VA_ARGS__); \
        puts(""); \
    } \
    assert(condition); \
}

#define TEST_WRITE_READ(name) \
{ \
    write_ ## name ## _test(); \
    read_ ## name ## _test(); \
    reset(); \
}

static const size_t size = 1024;
static std::byte buffer[size];

static auto bytes_writer_be = BytesWriter(ByteOrder::BigEndian, &buffer[0], size);
static auto bytes_writer_le = BytesWriter(ByteOrder::LittleEndian, &buffer[0], size);
static auto bytes_reader_be = BytesReader(ByteOrder::BigEndian, &buffer[0], size);
static auto bytes_reader_le = BytesReader(ByteOrder::LittleEndian, &buffer[0], size);

static void reset() {
    bytes_writer_be.clear();
    bytes_writer_le.clear();
    bytes_reader_be.reset();
    bytes_reader_le.reset();
}

// Writer ------------------------------------------------------------------------------------------

static void write_byte_le_test() {
    puts("Write byte - little endian test");

    bytes_writer_le.write_byte(std::byte(0xAB));
    TEST_ASSERT(buffer[0] == std::byte(0xAB), "buffer[0] = 0x%.2hhx", buffer[0]);
}

static void write_byte_be_test() {
    puts("Write byte - big endian test");

    bytes_writer_be.write_byte(std::byte(0xAB));
    TEST_ASSERT(buffer[0] == std::byte(0xAB), "buffer[0] = 0x%.2hhx", buffer[0]);
}

static void write_char_le_test() {
    puts("Write char - little endian test");

    bytes_writer_le.write_char('C');
    TEST_ASSERT(buffer[0] == std::byte(0x43), "buffer[0] = 0x%.2hhx", buffer[0]);
}

static void write_char_be_test() {
    puts("Write char - big endian test");

    bytes_writer_be.write_char('C');
    TEST_ASSERT(buffer[0] == std::byte(0x43), "buffer[0] = 0x%.2hhx", buffer[0]);
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
}

static void write_float_le_test() {
    puts("Write float - little endian test");

    bytes_writer_le.write_float(245.5f);
    TEST_ASSERT(buffer[0] == std::byte(0x00), "buffer[0] = 0x%.2hhx", buffer[0]);
    TEST_ASSERT(buffer[1] == std::byte(0x80), "buffer[1] = 0x%.2hhx", buffer[1]);
    TEST_ASSERT(buffer[2] == std::byte(0x75), "buffer[2] = 0x%.2hhx", buffer[2]);
    TEST_ASSERT(buffer[3] == std::byte(0x43), "buffer[3] = 0x%.2hhx", buffer[3]);
}

static void write_float_be_test() {
    puts("Write float - big endian test");

    bytes_writer_be.write_float(245.5f);
    TEST_ASSERT(buffer[0] == std::byte(0x43), "buffer[0] = 0x%.2hhx", buffer[0]);
    TEST_ASSERT(buffer[1] == std::byte(0x75), "buffer[1] = 0x%.2hhx", buffer[1]);
    TEST_ASSERT(buffer[2] == std::byte(0x80), "buffer[2] = 0x%.2hhx", buffer[2]);
    TEST_ASSERT(buffer[3] == std::byte(0x00), "buffer[3] = 0x%.2hhx", buffer[3]);
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
}

// Reader ------------------------------------------------------------------------------------------

static void read_byte_le_test() {
    puts("Read byte - little endian test");

    const auto value = bytes_reader_le.read_byte();
    TEST_ASSERT(value == std::byte(0xAB), "value = 0x%.2hhx", value);
}

static void read_byte_be_test() {
    puts("Read byte - big endian test");

    const auto value = bytes_reader_be.read_byte();
    TEST_ASSERT(value == std::byte(0xAB), "value = 0x%.2hhx", value);
}

static void read_char_le_test() {
    puts("Read char - little endian test");

    const auto value = bytes_reader_le.read_char();
    TEST_ASSERT(value == 'C', "value = %c", value);
}

static void read_char_be_test() {
    puts("Read char - big endian test");

    const auto value = bytes_reader_be.read_char();
    TEST_ASSERT(value == 'C', "value = %c", value);
}

static void read_int32_t_le_test() {
    puts("Read int32_t - little endian test");

    const auto value1 = bytes_reader_le.read_int32_t();
    const auto value2 = bytes_reader_le.read_int32_t();

    TEST_ASSERT(value1 == 12, "value = %d", value1);
    TEST_ASSERT(value2 == -1953736185, "value = %d", value2);
}

static void read_int32_t_be_test() {
    puts("Read int32_t - big endian test");

    const auto value1 = bytes_reader_be.read_int32_t();
    const auto value2 = bytes_reader_be.read_int32_t();

    TEST_ASSERT(value1 == 12, "value = %d", value1);
    TEST_ASSERT(value2 == -1953736185, "value = %d", value2);
}

static void read_int64_t_le_test() {
    puts("Read int64_t - little endian test");

    const auto value = bytes_reader_le.read_int64_t();
    TEST_ASSERT(value == 1934985738392383833, "value = %ld", value);
}

static void read_int64_t_be_test() {
    puts("Read int64_t - big endian test");

    const auto value = bytes_reader_be.read_int64_t();
    TEST_ASSERT(value == 1934985738392383833, "value = %ld", value);
}

static void read_float_le_test() {
    puts("Read float - little endian test");

    const auto value = bytes_reader_le.read_float();
    TEST_ASSERT(value == 245.5f, "value = %f", value);
}

static void read_float_be_test() {
    puts("Read float - big endian test");

    const auto value = bytes_reader_be.read_float();
    TEST_ASSERT(value == 245.5f, "value = %f", value);
}

static void read_double_le_test() {
    puts("Read double - little endian test");

    const auto value = bytes_reader_le.read_double();
    TEST_ASSERT(value == 593928311192.334351, "value = %f", value);
}

static void read_double_be_test() {
    puts("Read double - big endian test");

    const auto value = bytes_reader_be.read_double();
    TEST_ASSERT(value == 593928311192.334351, "value = %f", value);
}

// Tests entry point -------------------------------------------------------------------------------

int main() {
    TEST_WRITE_READ(byte_le);
    TEST_WRITE_READ(byte_be);
    TEST_WRITE_READ(char_le);
    TEST_WRITE_READ(char_be);
    TEST_WRITE_READ(int32_t_le);
    TEST_WRITE_READ(int32_t_be);
    TEST_WRITE_READ(int64_t_le);
    TEST_WRITE_READ(int64_t_be);
    TEST_WRITE_READ(float_le);
    TEST_WRITE_READ(float_be);
    TEST_WRITE_READ(double_le);
    TEST_WRITE_READ(double_be);

    puts("");
    puts("Finished successfully");

    return 0;
}
