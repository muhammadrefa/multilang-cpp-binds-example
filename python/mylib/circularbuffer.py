import ctypes
import typing

from ._bindings import circularbuffer as c_circular_buffer

class CircularBuffer:
    """
    Circular buffer - wrapper for C++ class
    """
    def __init__(self, bufsize: int):
        """
        Initialize the circular buffer
        :param bufsize: Buffer size
        :type bufsize: int
        """
        self._ptr = c_circular_buffer.create(bufsize)

    def __del__(self):
        c_circular_buffer.destroy(self._ptr)
    
    def get_length(self) -> int:
        """
        Get current buffer size
        :return: Current buffer size
        :rtype: int
        """
        result = ctypes.c_int()
        c_circular_buffer.get_length(self._ptr, ctypes.byref(result))
        return result.value

    def put(self, data: bytes, length: typing.Union[int, None] = None) -> int:
        """
        Put data into buffer
        :param data: Data to put
        :type data: bytes
        :param length: Data length (optional)
        :type length: int or None
        :return: Number of bytes inserted successfully
        :rtype: int
        """
        if length is None:
            length = len(data)
        result = ctypes.c_int()
        c_circular_buffer.put(self._ptr, data, length, ctypes.byref(result))
        return result.value
    
    def get(self, length: int) -> bytes:
        """
        Get data from buffer
        :param length: Data length to get
        :type length: int
        :return: Data from buffer
        :rtype: bytes
        """
        dest = ctypes.create_string_buffer(length)
        real_length = ctypes.c_int()
        c_circular_buffer.get(self._ptr, dest, length, ctypes.byref(real_length))
        return dest.value[:real_length.value]
    
    def clean(self) -> int:
        """
        Clean up the buffer
        :return: Last buffer size
        :rtype: int
        """
        result = ctypes.c_int()
        c_circular_buffer.clean(self._ptr, ctypes.byref(result))
        return result.value
