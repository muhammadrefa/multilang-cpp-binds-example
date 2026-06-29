import ctypes

from .._loader import load_library
from .._errors import check_pointer, check_status
from ._binding_utils import FunctionBinder

from .._types import mylib_calculator_t, mylib_status_t


_bind = FunctionBinder(load_library()).bind_function


create = _bind(
    "MyLib_Calculator_Create",
    mylib_calculator_t,
    [],
    check_pointer
)

destroy = _bind(
    "MyLib_Calculator_Destroy",
    mylib_status_t,
    [mylib_calculator_t],
    check_status
)

add = _bind(
    "MyLib_Calculator_Add",
    mylib_status_t,
    [mylib_calculator_t, ctypes.c_int, ctypes.c_int, ctypes.POINTER(ctypes.c_int)],
    check_status
)

sub = _bind(
    "MyLib_Calculator_Sub",
    mylib_status_t,
    [mylib_calculator_t, ctypes.c_int, ctypes.c_int, ctypes.POINTER(ctypes.c_int)],
)

cnt_ops_done = _bind(
    "MyLib_Calculator_CntOpsDone",
    mylib_status_t,
    [mylib_calculator_t, ctypes.POINTER(ctypes.c_int)],
)

reset_counter = _bind(
    "MyLib_Calculator_ResetCounter",
    mylib_status_t,
    [mylib_calculator_t, ctypes.POINTER(ctypes.c_int)],
)
