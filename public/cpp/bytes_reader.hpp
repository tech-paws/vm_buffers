#pragma once

#include "vm_buffers.hpp"

struct BytesReader {
    ByteOrder byte_order;
    uint8_t* buffer;
    size_t buffer_size;
    size_t buffer_cursor;
};

extern "C" BytesReader vm_buffers_create_bytes_reader(ByteOrder byte_order, uint8_t* buffer, size_t buffer_size);

extern "C" void vm_buffers_bytes_reader_reset(BytesReader &reader);

extern "C" int32_t vm_buffers_bytes_reader_read_int32_t(BytesReader &reader);

extern "C" int64_t vm_buffers_bytes_reader_read_int64_t(BytesReader &reader);

extern "C" float vm_buffers_bytes_reader_read_float(BytesReader &reader);

extern "C" double vm_buffers_bytes_reader_read_double(BytesReader &reader);

extern "C" uint8_t vm_buffers_bytes_reader_read_byte(BytesReader &reader);

extern "C" char vm_buffers_bytes_reader_read_char(BytesReader &reader);
