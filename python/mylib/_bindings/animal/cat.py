import ctypes

from ..._loader import load_library
from ..._errors import check_pointer, check_status
from .._binding_utils import FunctionBinder

from ..._types import mylib_cat_t, mylib_animal_t, mylib_status_t


_bind = FunctionBinder(load_library()).bind_function


create = _bind(
    "MyLib_Cat_Create",
    mylib_cat_t,
    [],
    check_pointer
)

create_with_name = _bind(
    "MyLib_Cat_Create_With_Name",
    mylib_cat_t,
    [ctypes.c_char_p, ctypes.c_int],
    check_pointer
)

destroy = _bind(
    "MyLib_Cat_Destroy",
    mylib_status_t,
    [mylib_cat_t],
    check_status
)

as_animal = _bind(
    "MyLib_Cat_As_Animal",
    mylib_animal_t,
    [mylib_cat_t],
    check_pointer
)

fight = _bind(
    "MyLib_Cat_Fight",
    mylib_status_t,
    [mylib_cat_t, ctypes.c_int, ctypes.POINTER(ctypes.c_int)],
    check_status
)

still_alive = _bind(
    "MyLib_Cat_StillAlive",
    mylib_status_t,
    [mylib_cat_t, ctypes.POINTER(ctypes.c_int)],
    check_status
)

speak = _bind(
    "MyLib_Cat_Speak",
    mylib_status_t,
    [mylib_cat_t],
    check_status
)
