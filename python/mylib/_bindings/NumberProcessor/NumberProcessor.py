import ctypes

from ..._loader import load_library
from ..._errors import check_pointer, check_status
from .._binding_utils import FunctionBinder

from ._types import mylib_NumberProcessor_t
from ..._types import mylib_status_t


_bind = FunctionBinder(load_library()).bind_function


destroy = _bind(
    "MyLib_NumberProcessor_Destroy",
    mylib_status_t,
    [mylib_NumberProcessor_t],
    check_status
)

process = _bind(
    "MyLib_NumberProcessor_Process",
    mylib_status_t,
    [mylib_NumberProcessor_t],
    check_status
)

get_number = _bind(
    "MyLib_NumberProcessor_GetNumber",
    mylib_status_t,
    [mylib_NumberProcessor_t, ctypes.POINTER(ctypes.c_int)],
)

set_number = _bind(
    "MyLib_NumberProcessor_SetNumber",
    mylib_status_t,
    [mylib_NumberProcessor_t, ctypes.c_int],
)

print_number = _bind(
    "MyLib_NumberProcessor_PrintNumber",
    mylib_status_t,
    [mylib_NumberProcessor_t],
)
