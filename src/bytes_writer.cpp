#include "vm_buffers.hpp"
#include "helpers.hpp"
#include "log.hpp"

extern "C" BytesWriter vm_buffers_create_bytes_writer(ByteOrder byte_order, uint8_t* buffer, size_t buffer_size) {
    BytesWriter writer;

    writer.byte_order = byte_order;
    writer.buffer = buffer;
    writer.buffer_size = buffer_size;
    writer.buffer_cursor = 0;

    return writer;
}

extern "C" size_t vm_buffers_bytes_writer_size(BytesWriter *writer) {
    return writer->buffer_cursor;
}

extern "C" void vm_buffers_bytes_writer_clear(BytesWriter *writer) {
    writer->buffer_cursor = 0;
}

extern "C" size_t vm_buffers_bytes_writer_current_offset(BytesWriter *writer) {
    return writer->buffer_cursor;
}

extern "C" void vm_buffers_bytes_writer_write_byte(BytesWriter *writer, uint8_t byte) {
    if (writer->buffer_cursor >= writer->buffer_size) {
        log_error("Buffer overflow");
        exit(EXIT_FAILURE);
    }

    writer->buffer[writer->buffer_cursor] = byte;
    writer->buffer_cursor += 1;
}

extern "C" void vm_buffers_bytes_writer_write_char(BytesWriter *writer, char ch) {
    if (writer->buffer_cursor >= writer->buffer_size) {
        log_error("Buffer overflow");
        exit(EXIT_FAILURE);
    }

    writer->buffer[writer->buffer_cursor] = (uint8_t) ch;
    writer->buffer_cursor += 1;
}

extern "C" void vm_buffers_bytes_writer_write_int32_t(BytesWriter *writer, int32_t value) {
    if (writer->buffer_cursor + sizeof(int32_t) >= writer->buffer_size) {
        log_error("Buffer overflow");
        exit(EXIT_FAILURE);
    }

    if (is_endian_mismatch(writer->byte_order)) {
        swap_endian(value);
    }

    union {
        int32_t val;
        std::array<uint8_t, sizeof(int32_t)> raw;
    } union_value {};

    union_value.val = value;

    for (size_t i = 0; i < sizeof(int32_t); i += 1) {
        writer->buffer[writer->buffer_cursor + i] = union_value.raw[i];
    }

    writer->buffer_cursor += sizeof(int32_t);
}

extern "C" void vm_buffers_bytes_writer_write_int64_t(BytesWriter *writer, int64_t value) {
    if (writer->buffer_cursor + sizeof(int64_t) >= writer->buffer_size) {
        log_error("Buffer overflow");
        exit(EXIT_FAILURE);
    }

    if (is_endian_mismatch(writer->byte_order)) {
        swap_endian(value);
    }

    union {
        int64_t val;
        std::array<uint8_t, sizeof(int64_t)> raw;
    } union_value {};

    union_value.val = value;

    for (size_t i = 0; i < sizeof(int64_t); i += 1) {
        writer->buffer[writer->buffer_cursor + i] = union_value.raw[i];
    }

    writer->buffer_cursor += sizeof(int64_t);
}

extern "C" void vm_buffers_bytes_writer_write_float(BytesWriter *writer, float value) {
    if (writer->buffer_cursor + sizeof(float) >= writer->buffer_size) {
        log_error("Buffer overflow");
        exit(EXIT_FAILURE);
    }

    if (is_endian_mismatch(writer->byte_order)) {
        swap_endian(value);
    }

    union {
        float val;
        std::array<uint8_t, sizeof(float)> raw;
    } union_value {};

    union_value.val = value;

    for (size_t i = 0; i < sizeof(float); i += 1) {
        writer->buffer[writer->buffer_cursor + i] = union_value.raw[i];
    }

    writer->buffer_cursor += sizeof(float);
}

extern "C" void vm_buffers_bytes_writer_write_double(BytesWriter *writer, double value) {
    if (writer->buffer_cursor + sizeof(double) >= writer->buffer_size) {
        log_error("Buffer overflow");
        exit(EXIT_FAILURE);
    }

    if (is_endian_mismatch(writer->byte_order)) {
        swap_endian(value);
    }

    union {
        double val;
        std::array<uint8_t, sizeof(double)> raw;
    } union_value {};

    union_value.val = value;

    for (size_t i = 0; i < sizeof(double); i += 1) {
        writer->buffer[writer->buffer_cursor + i] = union_value.raw[i];
    }

    writer->buffer_cursor += sizeof(double);
}

extern "C" void vm_buffers_bytes_writer_write_int64_t_at(BytesWriter *writer, size_t offset, int64_t value) {
    if (offset + sizeof(int64_t) >= writer->buffer_size) {
        log_error("Buffer overflow");
        exit(EXIT_FAILURE);
    }

    if (is_endian_mismatch(writer->byte_order)) {
        swap_endian(value);
    }

    union {
        int64_t val;
        std::array<uint8_t, sizeof(int64_t)> raw;
    } union_value {};

    union_value.val = value;

    for (size_t i = 0; i < sizeof(int64_t); i += 1) {
        writer->buffer[offset + i] = union_value.raw[i];
    }
}
