import ctypes


# status code
mylib_status_t = ctypes.c_int


# opaque pointers
class Calculator(ctypes.Structure):
    pass
mylib_calculator_t = ctypes.POINTER(Calculator)

class CircularBuffer(ctypes.Structure):
    pass
mylib_circular_buffer_t = ctypes.POINTER(CircularBuffer)
