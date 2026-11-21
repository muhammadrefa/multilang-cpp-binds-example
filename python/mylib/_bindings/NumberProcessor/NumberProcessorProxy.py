import ctypes

from ..._loader import load_library
from ..._errors import check_pointer, check_status
from .._binding_utils import FunctionBinder

from ._types import mylib_NumberProcessorProxy_t, mylib_NumberProcessorProxy_cb_t, mylib_NumberProcessor_t
from ..._types import mylib_status_t


_bind = FunctionBinder(load_library()).bind_function


create = _bind(
    "MyLib_NumberProcessorProxy_Create",
    mylib_NumberProcessorProxy_t,
    [mylib_NumberProcessorProxy_cb_t],
    check_pointer
)

destroy = _bind(
    "MyLib_NumberProcessorProxy_Destroy",
    mylib_status_t,
    [mylib_NumberProcessorProxy_t],
    check_status
)

as_NumberProcessor = _bind(
    "MyLib_NumberProcessorProxy_As_NumberProcessor",
    mylib_NumberProcessor_t,
    [mylib_NumberProcessorProxy_t],
    check_pointer
)

from_NumberProcessor = _bind(
    "MyLib_NumberProcessorProxy_From_NumberProcessor",
    mylib_NumberProcessorProxy_t,
    [mylib_NumberProcessor_t],
    check_pointer
)

base__print_number = _bind(
    "MyLib_NumberProcessorProxy_CallBase_PrintNumber",
    mylib_status_t,
    [mylib_NumberProcessorProxy_t],
    check_status
)
