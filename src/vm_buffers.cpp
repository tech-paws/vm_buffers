#include <cstddef>
#include <cstdint>

enum class ByteOrder {
    LittleEndian,
    BigEndian,
    Native,
};

class BytesWriter {
public:
    BytesWriter(ByteOrder byte_order) {
        this->byte_order = byte_order;
    }

    void clear();

    void write_int32_t(int32_t value);

    void write_int64_t(int32_t value);

    void write_float(float value);

    void write_double(float value);

    void write_byte(std::byte byte);

    void write_char(char ch);

private:
    ByteOrder byte_order;
    bool is_endian_mismatch();
};
