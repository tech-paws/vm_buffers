#[allow(warnings)]
#[allow(clippy::all)]
pub mod c_api;

use std::slice;

use vm_memory::BufferAccessor;

pub trait IntoVMBuffers {
    fn read_from_buffers(bytes_reader: &mut BytesReader) -> Self;

    fn write_to_buffers(&self, bytes_writer: &mut BytesWriter);
}

pub struct BytesReader {
    instance: c_api::BytesReader,
}

pub struct BytesWriter {
    instance: c_api::BytesWriter,
}

pub enum ByteOrder {
    LittleEndian = c_api::ByteOrder_LittleEndian as isize,
    BigEndian = c_api::ByteOrder_BigEndian as isize,
    Native = c_api::ByteOrder_Native as isize,
}

impl BytesReader {
    pub fn new<T: BufferAccessor>(byte_order: ByteOrder, buffer_accessor: &T) -> Self {
        let instance = unsafe {
            c_api::vm_buffers_create_bytes_reader(
                byte_order as u32,
                buffer_accessor.get_buffer_ptr(),
                buffer_accessor.get_buffer_size() as c_api::size_t,
            )
        };

        BytesReader { instance }
    }

    pub fn from_raw(instance: c_api::BytesReader) -> Self {
        BytesReader { instance }
    }

    pub unsafe fn raw(&mut self) -> *mut c_api::BytesReader {
        &mut self.instance
    }

    pub fn reset(&mut self) {
        unsafe { c_api::vm_buffers_bytes_reader_reset(&mut self.instance) };
    }

    pub fn read_byte(&mut self) -> u8 {
        unsafe { c_api::vm_buffers_bytes_reader_read_byte(&mut self.instance) }
    }

    pub fn read_byte_buffer(&mut self, len: u64) -> *mut u8 {
        unsafe { c_api::vm_buffers_bytes_reader_read_bytes_buffer(&mut self.instance, len) }
    }

    pub fn read_i32(&mut self) -> i32 {
        unsafe { c_api::vm_buffers_bytes_reader_read_int32_t(&mut self.instance) }
    }

    pub fn read_i64(&mut self) -> i64 {
        unsafe { c_api::vm_buffers_bytes_reader_read_int64_t(&mut self.instance) }
    }

    pub fn read_i64_at(&mut self, offset: u64) -> i64 {
        unsafe { c_api::vm_buffers_bytes_reader_read_int64_t_at(&mut self.instance, offset) }
    }

    pub fn read_u32(&mut self) -> u32 {
        unsafe { c_api::vm_buffers_bytes_reader_read_int32_t(&mut self.instance) as u32 }
    }

    pub fn read_u64(&mut self) -> u64 {
        unsafe { c_api::vm_buffers_bytes_reader_read_int64_t(&mut self.instance) as u64 }
    }

    pub fn read_u64_at(&mut self, offset: u64) -> u64 {
        unsafe { c_api::vm_buffers_bytes_reader_read_int64_t_at(&mut self.instance, offset) as u64 }
    }

    pub fn read_f32(&mut self) -> f32 {
        unsafe { c_api::vm_buffers_bytes_reader_read_float(&mut self.instance) }
    }

    pub fn read_f64(&mut self) -> f64 {
        unsafe { c_api::vm_buffers_bytes_reader_read_double(&mut self.instance) }
    }

    pub fn current_offset(&mut self) -> u64 {
        unsafe { c_api::vm_buffers_bytes_reader_current_offset(&mut self.instance) }
    }

    pub fn skip(&mut self, len: u64) {
        unsafe { c_api::vm_buffers_bytes_reader_skip(&mut self.instance, len) };
    }
}

impl BytesWriter {
    pub fn new(byte_order: ByteOrder, buffer_accessor: &dyn BufferAccessor) -> Self {
        let instance = unsafe {
            c_api::vm_buffers_create_bytes_writer(
                byte_order as u32,
                buffer_accessor.get_buffer_ptr(),
                buffer_accessor.get_buffer_size() as c_api::size_t,
            )
        };

        BytesWriter { instance }
    }

    pub fn from_raw(instance: c_api::BytesWriter) -> Self {
        BytesWriter { instance }
    }

    pub unsafe fn raw(&mut self) -> *mut c_api::BytesWriter {
        &mut self.instance
    }

    pub fn clear(&mut self) {
        unsafe { c_api::vm_buffers_bytes_writer_clear(&mut self.instance) };
    }

    pub fn write_byte(&mut self, value: u8) {
        unsafe {
            c_api::vm_buffers_bytes_writer_write_byte(&mut self.instance, value);
        };
    }

    pub fn write_i32(&mut self, value: i32) {
        unsafe {
            c_api::vm_buffers_bytes_writer_write_int32_t(&mut self.instance, value);
        };
    }

    pub fn write_i64(&mut self, value: i64) {
        unsafe {
            c_api::vm_buffers_bytes_writer_write_int64_t(&mut self.instance, value);
        };
    }

    pub fn write_u32(&mut self, value: u32) {
        unsafe {
            c_api::vm_buffers_bytes_writer_write_int32_t(&mut self.instance, value as i32);
        };
    }

    pub fn write_u64(&mut self, value: u64) {
        unsafe {
            c_api::vm_buffers_bytes_writer_write_int64_t(&mut self.instance, value as i64);
        };
    }

    pub fn write_f32(&mut self, value: f32) {
        unsafe {
            c_api::vm_buffers_bytes_writer_write_float(&mut self.instance, value);
        };
    }

    pub fn write_f64(&mut self, value: f64) {
        unsafe {
            c_api::vm_buffers_bytes_writer_write_double(&mut self.instance, value);
        };
    }

    pub fn write_u64_at(&mut self, offset: u64, value: u64) {
        unsafe {
            c_api::vm_buffers_bytes_writer_write_int64_t_at(
                &mut self.instance,
                offset,
                value as i64,
            )
        };
    }

    pub fn current_offset(&mut self) -> u64 {
        unsafe { c_api::vm_buffers_bytes_writer_current_offset(&mut self.instance) }
    }
}

impl IntoVMBuffers for String {
    fn read_from_buffers(bytes_reader: &mut BytesReader) -> Self {
        let len = bytes_reader.read_u64();
        let buff = bytes_reader.read_byte_buffer(len);
        let slice = unsafe { slice::from_raw_parts(buff, len as usize) };
        unsafe { String::from_utf8_unchecked(slice.to_vec()) }
    }

    fn write_to_buffers(&self, bytes_writer: &mut BytesWriter) {
        bytes_writer.write_u64(self.len() as u64);

        for byte in self.bytes() {
            bytes_writer.write_byte(byte);
        }
    }
}
