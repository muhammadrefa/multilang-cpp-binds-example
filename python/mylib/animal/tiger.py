import ctypes
import typing
import weakref

from .cat import Cat
from .._bindings.animal import tiger as c_tiger

class Tiger(Cat):
    """
    Tiger - wrapper for C++ class
    """
    def __init__(self, name: typing.Union[str, None] = None, **kwargs):
        self._ptr_tiger = kwargs.pop('_ptr', None)
        if self._ptr_tiger is None:
            if name is None:
                self._ptr_tiger = c_tiger.create()
            elif isinstance(name, str):
                self._ptr_tiger = c_tiger.create_with_name(name.encode(), len(name))
            else:
                raise TypeError("name must be in string or None!")
            self._finalizer = weakref.finalize(self, c_tiger.destroy, self._ptr_tiger)
        super().__init__(_ptr=c_tiger.as_cat(self._ptr_tiger), **kwargs)      # assign reference for parent class

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
