import ctypes
import typing
import weakref

from .animal import Animal
from .._bindings.animal import cat as c_cat

class Cat(Animal):
    """
    Cat - wrapper for C++ class
    """
    def __init__(self, name: typing.Union[str, None] = None, **kwargs):
        self._ptr_cat = kwargs.pop('_ptr', None)
        if self._ptr_cat is None:
            if name is None:
                self._ptr_cat = c_cat.create()
            elif type(name) is str:
                self._ptr_cat = c_cat.create_with_name(name.encode(), len(name))
            else:
                raise TypeError("name must be in string or None!")
            self._finalizer = weakref.finalize(self, c_cat.destroy, self._ptr_cat)
        super().__init__(_ptr=c_cat.as_animal(self._ptr_cat), **kwargs)

    def fight(self, bigger_cat: bool) -> bool:
        """
        Fight!
        :param bigger_cat: is the cat bigger?
        :type bigger_cat: bool
        :return: fight result
        :rtype: bool
        """
        success = ctypes.c_int()
        c_cat.fight(self._ptr_cat, (1 if bigger_cat else 0), ctypes.byref(success))
        return success.value != 0

    def still_alive(self) -> bool:
        """
        Is the cat still alive?
        :return: is alive
        :rtype: bool
        """
        is_alive = ctypes.c_int()
        c_cat.still_alive(self._ptr_cat, ctypes.byref(is_alive))
        return is_alive.value != 0

    def speak(self, times: typing.Union[int, None] = None) -> None:
        if times is None:
            c_cat.speak(self._ptr_cat)      # only this method overridden by Cat
        else:
            super().speak(times)            # call base class method
