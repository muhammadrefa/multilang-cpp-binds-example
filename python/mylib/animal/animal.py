import ctypes
import typing
import weakref

from .._bindings.animal import animal as c_animal

class Animal:
    """
    Animal - wrapper for C++ class
    """
    def __init__(self, name: typing.Union[str, None] = None, **kwargs):
        self._ptr_animal = kwargs.pop('_ptr', None)
        if self._ptr_animal is None:
            if name is None:
                self._ptr_animal = c_animal.create()
            elif isinstance(name, str):
                self._ptr_animal = c_animal.create_with_name(name.encode(), len(name))
            else:
                raise TypeError("name must be in string or None!")
            self._finalizer = weakref.finalize(self, c_animal.destroy, self._ptr_animal)
    
    def __enter__(self):
        return self

    def __exit__(self, *args):
        self.close()

    def close(self):
        self._finalizer()

    def _assign_reference(self, ptr) -> None:
        """
        Assign reference from its derivative
        :param ptr: pointer to Animal
        :type ptr: mylib_animal_t
        """
        self._ptr_animal = ptr

    @property
    def name(self) -> str:
        name = ctypes.create_string_buffer(100)
        length = ctypes.c_int()
        try:
            c_animal.get_name(self._ptr_animal, name, len(name), ctypes.byref(length))
            return name.value.decode()
        except BufferError:
            name = ctypes.create_string_buffer(length.value)
            c_animal.get_name(self._ptr_animal, name, len(name), ctypes.byref(length))
            return name.value.decode()

    @name.setter
    def name(self, new_name: str):
        c_animal.set_name(self._ptr_animal, new_name.encode(), len(new_name))
    
    def speak(self, times: typing.Union[int, None] = None) -> None:
        if times is None:
            c_animal.speak(self._ptr_animal)
        elif type(times) is int:
            c_animal.speak_multiple_times(self._ptr_animal, times)
        else:
            raise TypeError("times must be in integer or None!")

    def sleep(self) -> None:
        c_animal.sleep(self._ptr_animal)
