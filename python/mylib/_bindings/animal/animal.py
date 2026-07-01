import ctypes

from ..._loader import load_library
from ..._errors import check_pointer, check_status
from .._binding_utils import FunctionBinder

from ..._types import mylib_animal_t, mylib_status_t


_bind = FunctionBinder(load_library()).bind_function


create = _bind(
    "MyLib_Animal_Create",
    mylib_animal_t,
    [],
    check_pointer
)

create_with_name = _bind(
    "MyLib_Animal_Create_With_Name",
    mylib_animal_t,
    [ctypes.c_char_p, ctypes.c_int],
    check_pointer
)

destroy = _bind(
    "MyLib_Animal_Destroy",
    mylib_status_t,
    [mylib_animal_t],
    check_status
)

speak = _bind(
    "MyLib_Animal_Speak",
    mylib_status_t,
    [mylib_animal_t],
    check_status
)

speak_multiple_times = _bind(
    "MyLib_Animal_Speak_Multiple_Times",
    mylib_status_t,
    [mylib_animal_t, ctypes.c_int],
    check_status
)

sleep = _bind(
    "MyLib_Animal_Sleep",
    mylib_status_t,
    [],
    check_status
)

set_name = _bind(
    "MyLib_Animal_Set_Name",
    mylib_status_t,
    [mylib_animal_t, ctypes.c_char_p, ctypes.c_int],
    check_status
)

get_name = _bind(
    "MyLib_Animal_Get_Name",
    mylib_status_t,
    [mylib_animal_t, ctypes.c_char_p, ctypes.c_int, ctypes.POINTER(ctypes.c_int)],
    check_status
)
