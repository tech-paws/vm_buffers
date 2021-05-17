#pragma once

#include "vm_buffers.hpp"

struct BytesWriter {
    ByteOrder byte_order;
    uint8_t* buffer;
    size_t buffer_size;
    size_t buffer_cursor;
};

extern "C" BytesWriter vm_buffers_create_bytes_writer(ByteOrder byte_order, uint8_t* buffer, size_t buffer_size);

extern "C" void vm_buffers_bytes_writer_clear(BytesWriter &writer);

extern "C" void vm_buffers_bytes_writer_write_int32_t(BytesWriter &writer, int32_t value);

extern "C" void vm_buffers_bytes_writer_write_int64_t(BytesWriter &writer, int64_t value);

extern "C" void vm_buffers_bytes_writer_write_float(BytesWriter &writer, float value);

extern "C" void vm_buffers_bytes_writer_write_double(BytesWriter &writer, double value);

extern "C" void vm_buffers_bytes_writer_write_byte(BytesWriter &writer, uint8_t byte);

extern "C" void vm_buffers_bytes_writer_write_char(BytesWriter &writer, char ch);

extern "C" size_t vm_buffers_bytes_writer_size(BytesWriter &writer);
