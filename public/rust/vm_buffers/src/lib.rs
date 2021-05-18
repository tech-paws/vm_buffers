#[allow(warnings)]
#[allow(clippy::all)]
mod vm_buffers;

use vm_memory::BufferAccessor;

pub struct BytesReader {
    instance: vm_buffers::BytesReader,
}

pub struct BytesWriter {
    instance: vm_buffers::BytesWriter,
}

pub enum ByteOrder {
    LittleEndian = vm_buffers::ByteOrder_LittleEndian as isize,
    BigEndian = vm_buffers::ByteOrder_BigEndian as isize,
    Native = vm_buffers::ByteOrder_Native as isize,
}

impl BytesReader {
    pub fn new(byte_order: ByteOrder, buffer_accessor: &dyn BufferAccessor) -> Self {
        let instance = unsafe {
            vm_buffers::vm_buffers_create_bytes_reader(
                byte_order as u32,
                buffer_accessor.get_buffer_ptr(),
                buffer_accessor.get_buffer_size() as vm_buffers::size_t,
            )
        };

        BytesReader { instance }
    }

    pub fn read_byte(&mut self) -> u8 {
        unsafe { vm_buffers::vm_buffers_bytes_reader_read_byte(&mut self.instance) }
    }

    pub fn read_i32(&mut self) -> i32 {
        unsafe { vm_buffers::vm_buffers_bytes_reader_read_int32_t(&mut self.instance) }
    }

    pub fn read_i64(&mut self) -> i64 {
        unsafe { vm_buffers::vm_buffers_bytes_reader_read_int64_t(&mut self.instance) }
    }

    pub fn read_u32(&mut self) -> u32 {
        unsafe { vm_buffers::vm_buffers_bytes_reader_read_int32_t(&mut self.instance) as u32 }
    }

    pub fn read_u64(&mut self) -> u64 {
        unsafe { vm_buffers::vm_buffers_bytes_reader_read_int64_t(&mut self.instance) as u64 }
    }

    pub fn read_f32(&mut self) -> f32 {
        unsafe { vm_buffers::vm_buffers_bytes_reader_read_float(&mut self.instance) }
    }

    pub fn read_f64(&mut self) -> f64 {
        unsafe { vm_buffers::vm_buffers_bytes_reader_read_double(&mut self.instance) }
    }
}

impl BytesWriter {
    pub fn new(byte_order: ByteOrder, buffer_accessor: &dyn BufferAccessor) -> Self {
        let instance = unsafe {
            vm_buffers::vm_buffers_create_bytes_writer(
                byte_order as u32,
                buffer_accessor.get_buffer_ptr(),
                buffer_accessor.get_buffer_size() as vm_buffers::size_t,
            )
        };

        BytesWriter { instance }
    }

    pub fn write_byte(&mut self, value: u8) {
        unsafe {
            vm_buffers::vm_buffers_bytes_writer_write_byte(&mut self.instance, value);
        };
    }

    pub fn write_i32(&mut self, value: i32) {
        unsafe {
            vm_buffers::vm_buffers_bytes_writer_write_int32_t(&mut self.instance, value);
        };
    }

    pub fn write_i64(&mut self, value: i64) {
        unsafe {
            vm_buffers::vm_buffers_bytes_writer_write_int64_t(&mut self.instance, value);
        };
    }

    pub fn write_u32(&mut self, value: u32) {
        unsafe {
            vm_buffers::vm_buffers_bytes_writer_write_int32_t(&mut self.instance, value as i32);
        };
    }

    pub fn write_u64(&mut self, value: u64) {
        unsafe {
            vm_buffers::vm_buffers_bytes_writer_write_int64_t(&mut self.instance, value as i64);
        };
    }

    pub fn write_f32(&mut self, value: f32) {
        unsafe {
            vm_buffers::vm_buffers_bytes_writer_write_float(&mut self.instance, value);
        };
    }

    pub fn write_f64(&mut self, value: f64) {
        unsafe {
            vm_buffers::vm_buffers_bytes_writer_write_double(&mut self.instance, value);
        };
    }
}
