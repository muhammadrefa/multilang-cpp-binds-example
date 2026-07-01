import ctypes

from ..._loader import load_library
from ..._errors import check_pointer, check_status
from .._binding_utils import FunctionBinder

from ..._types import mylib_dog_t, mylib_animal_t, mylib_status_t


_bind = FunctionBinder(load_library()).bind_function


create = _bind(
    "MyLib_Dog_Create",
    mylib_dog_t,
    [],
    check_pointer
)

create_with_name = _bind(
    "MyLib_Dog_Create_With_Name",
    mylib_dog_t,
    [ctypes.c_char_p, ctypes.c_int],
    check_pointer
)

destroy = _bind(
    "MyLib_Dog_Destroy",
    mylib_status_t,
    [mylib_dog_t],
    check_status
)

as_animal = _bind(
    "MyLib_Dog_As_Animal",
    mylib_animal_t,
    [mylib_dog_t],
    check_pointer
)

fetch = _bind(
    "MyLib_Dog_Fetch",
    mylib_status_t,
    [mylib_dog_t, ctypes.POINTER(ctypes.c_int)],
    check_status
)

get_energy = _bind(
    "MyLib_Dog_GetEnergy",
    mylib_status_t,
    [mylib_dog_t, ctypes.POINTER(ctypes.c_int)],
    check_status
)

speak = _bind(
    "MyLib_Dog_Speak",
    mylib_status_t,
    [mylib_dog_t],
    check_status
)

sleep = _bind(
    "MyLib_Dog_Sleep",
    mylib_status_t,
    [mylib_dog_t],
    check_status
)
