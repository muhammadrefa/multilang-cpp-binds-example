import ctypes

from ..._loader import load_library
from ..._errors import check_pointer, check_status
from .._binding_utils import FunctionBinder

from ..._types import mylib_tiger_t, mylib_cat_t, mylib_status_t


_bind = FunctionBinder(load_library()).bind_function


create = _bind(
    "MyLib_Tiger_Create",
    mylib_tiger_t,
    [],
    check_pointer
)

create_with_name = _bind(
    "MyLib_Tiger_Create_With_Name",
    mylib_tiger_t,
    [ctypes.c_char_p, ctypes.c_int],
    check_pointer
)

destroy = _bind(
    "MyLib_Tiger_Destroy",
    mylib_status_t,
    [mylib_tiger_t],
    check_status
)

as_cat = _bind(
    "MyLib_Tiger_As_Cat",
    mylib_cat_t,
    [mylib_tiger_t],
    check_pointer
)

hunt = _bind(
    "MyLib_Tiger_Hunt",
    mylib_status_t,
    [mylib_tiger_t],
    check_status
)

get_hunger = _bind(
    "MyLib_Tiger_GetHunger",
    mylib_status_t,
    [mylib_tiger_t, ctypes.POINTER(ctypes.c_int)],
    check_status
)

speak = _bind(
    "MyLib_Tiger_Speak",
    mylib_status_t,
    [mylib_tiger_t],
    check_status
)

sleep = _bind(
    "MyLib_Tiger_Sleep",
    mylib_status_t,
    [mylib_tiger_t],
    check_status
)
