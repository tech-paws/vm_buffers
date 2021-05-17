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
static uint8_t buffer[size];

static auto bytes_writer_be = vm_buffers_create_bytes_writer(ByteOrder::BigEndian, &buffer[0], size);
static auto bytes_writer_le = vm_buffers_create_bytes_writer(ByteOrder::LittleEndian, &buffer[0], size);
static auto bytes_reader_be = vm_buffers_create_bytes_reader(ByteOrder::BigEndian, &buffer[0], size);
static auto bytes_reader_le = vm_buffers_create_bytes_reader(ByteOrder::LittleEndian, &buffer[0], size);

static void reset() {
    vm_buffers_bytes_writer_clear(bytes_writer_be);
    vm_buffers_bytes_writer_clear(bytes_writer_le);
    vm_buffers_bytes_reader_reset(bytes_reader_be);
    vm_buffers_bytes_reader_reset(bytes_reader_le);
}

// Writer ------------------------------------------------------------------------------------------

static void write_byte_le_test() {
    puts("Write byte - little endian test");

    vm_buffers_bytes_writer_write_byte(bytes_writer_le, 0xAB);
    TEST_ASSERT(buffer[0] == 0xAB, "buffer[0] = 0x%.2hhx", buffer[0]);
}

static void write_byte_be_test() {
    puts("Write byte - big endian test");

    vm_buffers_bytes_writer_write_byte(bytes_writer_be, 0xAB);
    TEST_ASSERT(buffer[0] == 0xAB, "buffer[0] = 0x%.2hhx", buffer[0]);
}

static void write_char_le_test() {
    puts("Write char - little endian test");

    vm_buffers_bytes_writer_write_char(bytes_writer_le, 'C');
    TEST_ASSERT(buffer[0] == 0x43, "buffer[0] = 0x%.2hhx", buffer[0]);
}

static void write_char_be_test() {
    puts("Write char - big endian test");

    vm_buffers_bytes_writer_write_char(bytes_writer_be, 'C');
    TEST_ASSERT(buffer[0] == 0x43, "buffer[0] = 0x%.2hhx", buffer[0]);
}

static void write_int32_t_le_test() {
    puts("Write int32_t - little endian test");

    vm_buffers_bytes_writer_write_int32_t(bytes_writer_le, 12);
    TEST_ASSERT(buffer[0] == 0x0C, "buffer[0] = 0x%.2hhx", buffer[0]);
    TEST_ASSERT(buffer[1] == 0x00, "buffer[1] = 0x%.2hhx", buffer[1]);
    TEST_ASSERT(buffer[2] == 0x00, "buffer[2] = 0x%.2hhx", buffer[2]);
    TEST_ASSERT(buffer[3] == 0x00, "buffer[3] = 0x%.2hhx", buffer[3]);

    vm_buffers_bytes_writer_write_int32_t(bytes_writer_le, -1953736185);
    TEST_ASSERT(buffer[4] == 0x07, "buffer[4] = 0x%.2hhx", buffer[4]);
    TEST_ASSERT(buffer[5] == 0x5A, "buffer[5] = 0x%.2hhx", buffer[5]);
    TEST_ASSERT(buffer[6] == 0x8C, "buffer[6] = 0x%.2hhx", buffer[6]);
    TEST_ASSERT(buffer[7] == 0x8B, "buffer[7] = 0x%.2hhx", buffer[7]);
}

static void write_int32_t_be_test() {
    puts("Write int32_t - big endian test");

    vm_buffers_bytes_writer_write_int32_t(bytes_writer_be, 12);
    TEST_ASSERT(buffer[0] == 0x00, "buffer[0] = 0x%.2hhx", buffer[0]);
    TEST_ASSERT(buffer[1] == 0x00, "buffer[1] = 0x%.2hhx", buffer[1]);
    TEST_ASSERT(buffer[2] == 0x00, "buffer[2] = 0x%.2hhx", buffer[2]);
    TEST_ASSERT(buffer[3] == 0x0C, "buffer[3] = 0x%.2hhx", buffer[3]);

    vm_buffers_bytes_writer_write_int32_t(bytes_writer_be, -1953736185);
    TEST_ASSERT(buffer[4] == 0x8B, "buffer[4] = 0x%.2hhx", buffer[4]);
    TEST_ASSERT(buffer[5] == 0x8C, "buffer[5] = 0x%.2hhx", buffer[5]);
    TEST_ASSERT(buffer[6] == 0x5A, "buffer[6] = 0x%.2hhx", buffer[6]);
    TEST_ASSERT(buffer[7] == 0x07, "buffer[7] = 0x%.2hhx", buffer[7]);
}

static void write_int64_t_le_test() {
    puts("Write int64_t - little endian test");

    vm_buffers_bytes_writer_write_int64_t(bytes_writer_le, 1934985738392383833);
    TEST_ASSERT(buffer[0] == 0x59, "buffer[0] = 0x%.2hhx", buffer[0]);
    TEST_ASSERT(buffer[1] == 0x31, "buffer[1] = 0x%.2hhx", buffer[1]);
    TEST_ASSERT(buffer[2] == 0x53, "buffer[2] = 0x%.2hhx", buffer[2]);
    TEST_ASSERT(buffer[3] == 0xEE, "buffer[3] = 0x%.2hhx", buffer[3]);
    TEST_ASSERT(buffer[4] == 0x46, "buffer[4] = 0x%.2hhx", buffer[4]);
    TEST_ASSERT(buffer[5] == 0x73, "buffer[5] = 0x%.2hhx", buffer[5]);
    TEST_ASSERT(buffer[6] == 0xDA, "buffer[6] = 0x%.2hhx", buffer[6]);
    TEST_ASSERT(buffer[7] == 0x1A, "buffer[7] = 0x%.2hhx", buffer[7]);
}

static void write_int64_t_be_test() {
    puts("Write int64_t - big endian test");

    vm_buffers_bytes_writer_write_int64_t(bytes_writer_be, 1934985738392383833);
    TEST_ASSERT(buffer[0] == 0x1A, "buffer[0] = 0x%.2hhx", buffer[0]);
    TEST_ASSERT(buffer[1] == 0xdA, "buffer[1] = 0x%.2hhx", buffer[1]);
    TEST_ASSERT(buffer[2] == 0x73, "buffer[2] = 0x%.2hhx", buffer[2]);
    TEST_ASSERT(buffer[3] == 0x46, "buffer[3] = 0x%.2hhx", buffer[3]);
    TEST_ASSERT(buffer[4] == 0xEE, "buffer[4] = 0x%.2hhx", buffer[4]);
    TEST_ASSERT(buffer[5] == 0x53, "buffer[5] = 0x%.2hhx", buffer[5]);
    TEST_ASSERT(buffer[6] == 0x31, "buffer[6] = 0x%.2hhx", buffer[6]);
    TEST_ASSERT(buffer[7] == 0x59, "buffer[7] = 0x%.2hhx", buffer[7]);
}

static void write_float_le_test() {
    puts("Write float - little endian test");

    vm_buffers_bytes_writer_write_float(bytes_writer_le, 245.5f);
    TEST_ASSERT(buffer[0] == 0x00, "buffer[0] = 0x%.2hhx", buffer[0]);
    TEST_ASSERT(buffer[1] == 0x80, "buffer[1] = 0x%.2hhx", buffer[1]);
    TEST_ASSERT(buffer[2] == 0x75, "buffer[2] = 0x%.2hhx", buffer[2]);
    TEST_ASSERT(buffer[3] == 0x43, "buffer[3] = 0x%.2hhx", buffer[3]);
}

static void write_float_be_test() {
    puts("Write float - big endian test");

    vm_buffers_bytes_writer_write_float(bytes_writer_be, 245.5f);
    TEST_ASSERT(buffer[0] == 0x43, "buffer[0] = 0x%.2hhx", buffer[0]);
    TEST_ASSERT(buffer[1] == 0x75, "buffer[1] = 0x%.2hhx", buffer[1]);
    TEST_ASSERT(buffer[2] == 0x80, "buffer[2] = 0x%.2hhx", buffer[2]);
    TEST_ASSERT(buffer[3] == 0x00, "buffer[3] = 0x%.2hhx", buffer[3]);
}

static void write_double_le_test() {
    puts("Write double - little endian test");

    vm_buffers_bytes_writer_write_double(bytes_writer_le, 593928311192.334351);
    TEST_ASSERT(buffer[0] == 0xB3, "buffer[0] = 0x%.2hhx", buffer[0]);
    TEST_ASSERT(buffer[1] == 0x0A, "buffer[1] = 0x%.2hhx", buffer[1]);
    TEST_ASSERT(buffer[2] == 0x33, "buffer[2] = 0x%.2hhx", buffer[2]);
    TEST_ASSERT(buffer[3] == 0x5A, "buffer[3] = 0x%.2hhx", buffer[3]);
    TEST_ASSERT(buffer[4] == 0x1C, "buffer[4] = 0x%.2hhx", buffer[4]);
    TEST_ASSERT(buffer[5] == 0x49, "buffer[5] = 0x%.2hhx", buffer[5]);
    TEST_ASSERT(buffer[6] == 0x61, "buffer[6] = 0x%.2hhx", buffer[6]);
    TEST_ASSERT(buffer[7] == 0x42, "buffer[7] = 0x%.2hhx", buffer[7]);
}

static void write_double_be_test() {
    puts("Write double - big endian test");

    vm_buffers_bytes_writer_write_double(bytes_writer_be, 593928311192.334351);
    TEST_ASSERT(buffer[0] == 0x42, "buffer[0] = 0x%.2hhx", buffer[0]);
    TEST_ASSERT(buffer[1] == 0x61, "buffer[1] = 0x%.2hhx", buffer[1]);
    TEST_ASSERT(buffer[2] == 0x49, "buffer[2] = 0x%.2hhx", buffer[2]);
    TEST_ASSERT(buffer[3] == 0x1C, "buffer[3] = 0x%.2hhx", buffer[3]);
    TEST_ASSERT(buffer[4] == 0x5A, "buffer[4] = 0x%.2hhx", buffer[4]);
    TEST_ASSERT(buffer[5] == 0x33, "buffer[5] = 0x%.2hhx", buffer[5]);
    TEST_ASSERT(buffer[6] == 0x0A, "buffer[6] = 0x%.2hhx", buffer[6]);
    TEST_ASSERT(buffer[7] == 0xB3, "buffer[7] = 0x%.2hhx", buffer[7]);
}

// Reader ------------------------------------------------------------------------------------------

static void read_byte_le_test() {
    puts("Read byte - little endian test");

    const auto value = vm_buffers_bytes_reader_read_byte(bytes_reader_le);
    TEST_ASSERT(value == 0xAB, "value = 0x%.2hhx", value);
}

static void read_byte_be_test() {
    puts("Read byte - big endian test");

    const auto value = vm_buffers_bytes_reader_read_byte(bytes_reader_be);
    TEST_ASSERT(value == 0xAB, "value = 0x%.2hhx", value);
}

static void read_char_le_test() {
    puts("Read char - little endian test");

    const auto value = vm_buffers_bytes_reader_read_char(bytes_reader_le);
    TEST_ASSERT(value == 'C', "value = %c", value);
}

static void read_char_be_test() {
    puts("Read char - big endian test");

    const auto value = vm_buffers_bytes_reader_read_char(bytes_reader_be);
    TEST_ASSERT(value == 'C', "value = %c", value);
}

static void read_int32_t_le_test() {
    puts("Read int32_t - little endian test");

    const auto value1 = vm_buffers_bytes_reader_read_int32_t(bytes_reader_le);
    const auto value2 = vm_buffers_bytes_reader_read_int32_t(bytes_reader_le);

    TEST_ASSERT(value1 == 12, "value = %d", value1);
    TEST_ASSERT(value2 == -1953736185, "value = %d", value2);
}

static void read_int32_t_be_test() {
    puts("Read int32_t - big endian test");

    const auto value1 = vm_buffers_bytes_reader_read_int32_t(bytes_reader_be);
    const auto value2 = vm_buffers_bytes_reader_read_int32_t(bytes_reader_be);

    TEST_ASSERT(value1 == 12, "value = %d", value1);
    TEST_ASSERT(value2 == -1953736185, "value = %d", value2);
}

static void read_int64_t_le_test() {
    puts("Read int64_t - little endian test");

    const auto value = vm_buffers_bytes_reader_read_int64_t(bytes_reader_le);
    TEST_ASSERT(value == 1934985738392383833, "value = %ld", value);
}

static void read_int64_t_be_test() {
    puts("Read int64_t - big endian test");

    const auto value = vm_buffers_bytes_reader_read_int64_t(bytes_reader_be);
    TEST_ASSERT(value == 1934985738392383833, "value = %ld", value);
}

static void read_float_le_test() {
    puts("Read float - little endian test");

    const auto value = vm_buffers_bytes_reader_read_float(bytes_reader_le);
    TEST_ASSERT(value == 245.5f, "value = %f", value);
}

static void read_float_be_test() {
    puts("Read float - big endian test");

    const auto value = vm_buffers_bytes_reader_read_float(bytes_reader_be);
    TEST_ASSERT(value == 245.5f, "value = %f", value);
}

static void read_double_le_test() {
    puts("Read double - little endian test");

    const auto value = vm_buffers_bytes_reader_read_double(bytes_reader_le);
    TEST_ASSERT(value == 593928311192.334351, "value = %f", value);
}

static void read_double_be_test() {
    puts("Read double - big endian test");

    const auto value = vm_buffers_bytes_reader_read_double(bytes_reader_be);
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
