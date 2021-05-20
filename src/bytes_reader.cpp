#include "vm_buffers.hpp"
#include "helpers.hpp"

extern "C" BytesReader vm_buffers_create_bytes_reader(ByteOrder byte_order, uint8_t* buffer, size_t buffer_size) {
    BytesReader reader;

    reader.byte_order = byte_order;
    reader.buffer = buffer;
    reader.buffer_size = buffer_size;
    reader.buffer_cursor = 0;

    return reader;
}

extern "C" void vm_buffers_bytes_reader_reset(BytesReader &reader) {
    reader.buffer_cursor = 0;
}

extern "C" size_t vm_buffers_bytes_reader_current_offset(BytesReader &reader) {
    return reader.buffer_cursor;
}

extern "C" int32_t vm_buffers_bytes_reader_read_int32_t(BytesReader &reader) {
    if (reader.buffer_cursor + sizeof(int32_t) >= reader.buffer_size) {
        // TODO(sysint64): Error buffer overflow
    }

    union {
        int32_t val;
        std::array<uint8_t, sizeof(int32_t)> raw;
    } union_value {};

    for (size_t i = 0; i < sizeof(int32_t); i += 1) {
        union_value.raw[i] = reader.buffer[reader.buffer_cursor + i];
    }

    reader.buffer_cursor += sizeof(int32_t);

    if (is_endian_mismatch(reader.byte_order)) {
        swap_endian(union_value.raw);
    }

    return union_value.val;
}

extern "C" int64_t vm_buffers_bytes_reader_read_int64_t(BytesReader &reader) {
    if (reader.buffer_cursor + sizeof(int64_t) >= reader.buffer_size) {
        // TODO(sysint64): Error buffer overflow
    }

    union {
        int64_t val;
        std::array<uint8_t, sizeof(int64_t)> raw;
    } union_value {};

    for (size_t i = 0; i < sizeof(int64_t); i += 1) {
        union_value.raw[i] = reader.buffer[reader.buffer_cursor + i];
    }

    reader.buffer_cursor += sizeof(int64_t);

    if (is_endian_mismatch(reader.byte_order)) {
        swap_endian(union_value.raw);
    }

    return union_value.val;
}

extern "C" int64_t vm_buffers_bytes_reader_read_int64_t_at(BytesReader &reader, size_t offset) {
    if (offset + sizeof(int64_t) >= reader.buffer_size) {
        // TODO(sysint64): Error buffer overflow
    }

    union {
        int64_t val;
        std::array<uint8_t, sizeof(int64_t)> raw;
    } union_value {};

    for (size_t i = 0; i < sizeof(int64_t); i += 1) {
        union_value.raw[i] = reader.buffer[offset + i];
    }

    if (is_endian_mismatch(reader.byte_order)) {
        swap_endian(union_value.raw);
    }

    return union_value.val;
}

extern "C" float vm_buffers_bytes_reader_read_float(BytesReader &reader) {
    if (reader.buffer_cursor + sizeof(float) >= reader.buffer_size) {
        // TODO(sysint64): Error buffer overflow
    }

    union {
        float val;
        std::array<uint8_t, sizeof(float)> raw;
    } union_value {};

    for (size_t i = 0; i < sizeof(float); i += 1) {
        union_value.raw[i] = reader.buffer[reader.buffer_cursor + i];
    }

    reader.buffer_cursor += sizeof(float);

    if (is_endian_mismatch(reader.byte_order)) {
        swap_endian(union_value.raw);
    }

    return union_value.val;
}

extern "C" double vm_buffers_bytes_reader_read_double(BytesReader &reader) {
    if (reader.buffer_cursor + sizeof(double) >= reader.buffer_size) {
        // TODO(sysint64): Error buffer overflow
    }

    union {
        double val;
        std::array<uint8_t, sizeof(double)> raw;
    } union_value {};

    for (size_t i = 0; i < sizeof(double); i += 1) {
        union_value.raw[i] = reader.buffer[reader.buffer_cursor + i];
    }

    reader.buffer_cursor += sizeof(double);

    if (is_endian_mismatch(reader.byte_order)) {
        swap_endian(union_value.raw);
    }

    return union_value.val;
}

extern "C" uint8_t vm_buffers_bytes_reader_read_byte(BytesReader &reader) {
    if (reader.buffer_cursor >= reader.buffer_size) {
        // TODO(sysint64): Error buffer overflow
    }

    auto const value = reader.buffer[reader.buffer_cursor];
    reader.buffer_cursor += 1;;

    return value;
}

extern "C" char vm_buffers_bytes_reader_read_char(BytesReader &reader) {
    if (reader.buffer_cursor >= reader.buffer_size) {
        // TODO(sysint64): Error buffer overflow
    }

    auto const value = reader.buffer[reader.buffer_cursor];
    reader.buffer_cursor += 1;

    return char(value);
}

extern "C" uint8_t* vm_buffers_bytes_reader_read_bytes_buffer(BytesReader &reader, size_t len) {
    if (reader.buffer_cursor + len >= reader.buffer_size) {
        // TODO(sysint64): Error buffer overflow
    }

    auto buf = reader.buffer + reader.buffer_cursor;
    reader.buffer_cursor += len;
    return buf;
}

extern "C" void vm_buffers_bytes_reader_skip(BytesReader &reader, size_t len) {
    if (reader.buffer_cursor + len >= reader.buffer_size) {
        // TODO(sysint64): Error buffer overflow
    }

    reader.buffer_cursor += len;
}
