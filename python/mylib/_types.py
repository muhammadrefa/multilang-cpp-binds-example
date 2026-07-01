import ctypes


# status code
mylib_status_t = ctypes.c_int


# opaque pointers
class Calculator(ctypes.Structure):
    pass
mylib_calculator_t = ctypes.POINTER(Calculator)

class CircularBuffer(ctypes.Structure):
    pass
mylib_circular_buffer_t = ctypes.POINTER(CircularBuffer)

class Animal(ctypes.Structure):
    pass
mylib_animal_t = ctypes.POINTER(Animal)

class Dog(ctypes.Structure):
    pass
mylib_dog_t = ctypes.POINTER(Dog)

class Cat(ctypes.Structure):
    pass
mylib_cat_t = ctypes.POINTER(Cat)

class Tiger(ctypes.Structure):
    pass
mylib_tiger_t = ctypes.POINTER(Tiger)
