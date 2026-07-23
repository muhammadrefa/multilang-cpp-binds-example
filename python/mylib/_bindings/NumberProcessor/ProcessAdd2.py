import ctypes

from ..._loader import load_library
from ..._errors import check_pointer, check_status
from .._binding_utils import FunctionBinder

from ._types import mylib_ProcessAdd2_t, mylib_NumberProcessor_t
from ..._types import mylib_status_t


_bind = FunctionBinder(load_library()).bind_function


create = _bind(
    "MyLib_ProcessAdd2_Create",
    mylib_ProcessAdd2_t,
    [],
    check_pointer
)

destroy = _bind(
    "MyLib_ProcessAdd2_Destroy",
    mylib_status_t,
    [mylib_ProcessAdd2_t],
    check_status
)

as_NumberProcessor = _bind(
    "MyLib_ProcessAdd2_As_NumberProcessor",
    mylib_NumberProcessor_t,
    [mylib_ProcessAdd2_t],
    check_pointer
)
