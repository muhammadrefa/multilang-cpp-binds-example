import abc
import ctypes
import typing
import weakref

from .._bindings.NumberProcessor import NumberProcessor as c_NumberProcessor
from .._bindings.NumberProcessor._types import mylib_NumberProcessor_t


class NumberProcessor(abc.ABC):
    _finalizer: typing.Optional[weakref.finalize]

    def __init__(self, **kwargs):
        self._ptr_NumberProcessor: mylib_NumberProcessor_t = kwargs.pop('_ptr', None)

        if not hasattr(self, '_finalizer'):
            raise AttributeError("Register a destructor using self._finalizer! The destructor will be called by close().\n"
                                 "For example: self._finalizer = weakref.finalize(self, native_destroy_func, self._handle)\n"
                                 "If this class has no destructor, explicitly write: self._finalizer = None")

    def __enter__(self):
        return self

    def __exit__(self, *args):
        self.close()

    @typing.final
    def close(self):
        if hasattr(self, '_finalizer') and self._finalizer is not None:
            self._finalizer()

    @abc.abstractmethod
    def process(self):
        pass

    def set_number(self, number: int):
        c_NumberProcessor.set_number(self._ptr_NumberProcessor, number)

    def get_number(self) -> int:
        number = ctypes.c_int()
        c_NumberProcessor.get_number(self._ptr_NumberProcessor, ctypes.byref(number))
        return number.value

    def print_number(self):
        c_NumberProcessor.print_number(self._ptr_NumberProcessor)
