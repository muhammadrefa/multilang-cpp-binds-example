import ctypes

from .._loader import load_library
from .._errors import check_pointer, check_status
from ._binding_utils import FunctionBinder

from .._types import mylib_circular_buffer_t, mylib_status_t


_bind = FunctionBinder(load_library()).bind_function


create = _bind(
    "MyLib_CircularBuffer_Create",
    mylib_circular_buffer_t,
    [ctypes.c_int],
    check_pointer
)

destroy = _bind(
    "MyLib_CircularBuffer_Destroy",
    mylib_status_t,
    [mylib_circular_buffer_t],
    check_status
)

get_length = _bind(
    "MyLib_CircularBuffer_GetLength",
    mylib_status_t,
    [mylib_circular_buffer_t, ctypes.POINTER(ctypes.c_int)],
    check_status
)

put = _bind(
    "MyLib_CircularBuffer_Put",
    mylib_status_t,
    [mylib_circular_buffer_t, ctypes.c_char_p, ctypes.c_int, ctypes.POINTER(ctypes.c_int)],
    check_status
)

get = _bind(
    "MyLib_CircularBuffer_Get",
    mylib_status_t,
    [mylib_circular_buffer_t, ctypes.c_char_p, ctypes.c_int, ctypes.POINTER(ctypes.c_int)],
    check_status
)

clean = _bind(
    "MyLib_CircularBuffer_Clean",
    mylib_status_t,
    [mylib_circular_buffer_t, ctypes.POINTER(ctypes.c_int)],
    check_status
)
