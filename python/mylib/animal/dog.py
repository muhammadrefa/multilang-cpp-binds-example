import ctypes
import typing

from .animal import Animal
from .._bindings.animal import dog as c_dog

class Dog(Animal):
    """
    Dog - wrapper for C++ class
    """
    def __init__(self, name: typing.Union[str, None] = None):
        if name is None:
            self._ptr_dog = c_dog.create()
        elif type(name) is str:
            self._ptr_dog = c_dog.create_with_name(name.encode(), len(name))
        else:
            raise TypeError("name must be in string or None!")
        super()._init_from_ptr(c_dog.as_animal(self._ptr_dog))      # initialise handle for parent class

    def __del__(self):
        c_dog.destroy(self._ptr_dog)

    def _init_from_ptr(self, ptr):
        """
        Initialise handle from its derivative
        :param ptr: pointer to Dog
        :type ptr: mylib_dog_t
        """
        self._ptr_dog = ptr
        super()._init_from_ptr(c_dog.as_animal(self._ptr_dog))      # initialise handle for parent class
    
    def fetch(self) -> bool:
        """
        Fetch!
        :return: fetch result
        :rtype: bool
        """
        success = ctypes.c_int()
        c_dog.fetch(self._ptr_dog, ctypes.byref(success))
        return success.value != 0

    def get_energy(self) -> int:
        """
        Get energy
        :return: energy
        :rtype: int
        """
        energy = ctypes.c_int()
        c_dog.get_energy(self._ptr_dog, ctypes.byref(energy))
        return energy.value
    
    def speak(self, times: typing.Union[int, None] = None) -> None:
        if times is None:
            c_dog.speak(self._ptr_dog)      # only this method overridden by Dog
        else:
            super().speak(times)            # call base class method

    def sleep(self) -> None:
        c_dog.sleep(self._ptr_dog)          # overridden by Dog
