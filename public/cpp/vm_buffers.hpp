#pragma once

#include <cstddef>
#include <cstdint>

enum ByteOrder {
    LittleEndian,
    BigEndian,
    Native,
};

struct BytesWriter {
    ByteOrder byte_order;
    uint8_t* buffer;
    size_t buffer_size;
    size_t buffer_cursor;
};

struct BytesReader {
    ByteOrder byte_order;
    uint8_t* buffer;
    size_t buffer_size;
    size_t buffer_cursor;
};

// Writer

extern "C" BytesWriter vm_buffers_create_bytes_writer(ByteOrder byte_order, uint8_t* buffer, size_t buffer_size);

extern "C" void vm_buffers_bytes_writer_clear(BytesWriter *writer);

extern "C" void vm_buffers_bytes_writer_write_int32_t(BytesWriter *writer, int32_t value);

extern "C" void vm_buffers_bytes_writer_write_int64_t(BytesWriter *writer, int64_t value);

extern "C" void vm_buffers_bytes_writer_write_float(BytesWriter *writer, float value);

extern "C" void vm_buffers_bytes_writer_write_double(BytesWriter *writer, double value);

extern "C" void vm_buffers_bytes_writer_write_byte(BytesWriter *writer, uint8_t byte);

extern "C" void vm_buffers_bytes_writer_write_char(BytesWriter *writer, char ch);

extern "C" size_t vm_buffers_bytes_writer_size(BytesWriter *writer);

extern "C" void vm_buffers_bytes_writer_write_int64_t_at(BytesWriter *writer, size_t offset, int64_t value);

extern "C" size_t vm_buffers_bytes_writer_current_offset(BytesWriter *writer);

// Reader

extern "C" BytesReader vm_buffers_create_bytes_reader(ByteOrder byte_order, uint8_t* buffer, size_t buffer_size);

extern "C" void vm_buffers_bytes_reader_reset(BytesReader *reader);

extern "C" int32_t vm_buffers_bytes_reader_read_int32_t(BytesReader *reader);

extern "C" int64_t vm_buffers_bytes_reader_read_int64_t(BytesReader *reader);

extern "C" int64_t vm_buffers_bytes_reader_read_int64_t_at(BytesReader *reader, size_t offset);

extern "C" float vm_buffers_bytes_reader_read_float(BytesReader *reader);

extern "C" double vm_buffers_bytes_reader_read_double(BytesReader *reader);

extern "C" uint8_t vm_buffers_bytes_reader_read_byte(BytesReader *reader);

extern "C" char vm_buffers_bytes_reader_read_char(BytesReader *reader);

extern "C" uint8_t* vm_buffers_bytes_reader_read_bytes_buffer(BytesReader *reader, size_t len);

extern "C" void vm_buffers_bytes_reader_skip(BytesReader *reader, size_t len);

extern "C" size_t vm_buffers_bytes_reader_current_offset(BytesReader *reader);
