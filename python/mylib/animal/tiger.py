import ctypes
import typing

from .cat import Cat
from .._bindings.animal import tiger as c_tiger

class Tiger(Cat):
    """
    Tiger - wrapper for C++ class
    """
    def __init__(self, name: typing.Union[str, None] = None):
        if name is None:
            self._ptr_tiger = c_tiger.create()
        elif type(name) is str:
            self._ptr_tiger = c_tiger.create_with_name(name.encode(), len(name))
        else:
            raise TypeError("name must be in string or None!")
        super()._init_from_ptr(c_tiger.as_cat(self._ptr_tiger))      # initialise handle for parent class

    def __del__(self):
        c_tiger.destroy(self._ptr_tiger)

    def _init_from_ptr(self, ptr):
        """
        Initialise handle from its derivative
        :param ptr: pointer to Cat
        :type ptr: mylib_cat_t
        """
        self._ptr_tiger = ptr
        super()._init_from_ptr(c_tiger.as_cat(self._ptr_tiger))      # initialise handle for parent class

    def hunt(self) -> None:
        c_tiger.hunt(self._ptr_tiger)

    def get_hunger(self) -> int:
        """
        Get hunger level
        :return: hunger level
        :rtype: int
        """
        hunger = ctypes.c_int()
        c_tiger.get_hunger(self._ptr_tiger, ctypes.byref(hunger))
        return hunger.value

    def speak(self, times: typing.Union[int, None] = None) -> None:
        if times is None:
            c_tiger.speak(self._ptr_tiger)        # only this method overridden by Tiger
        else:
            super().speak(times)                # call base class method
