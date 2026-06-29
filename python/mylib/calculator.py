import ctypes

from ._bindings import calculator as c_calculator

class Calculator:
    """
    Calculator - wrapper for C++ class
    """
    def __init__(self):
        self._ptr = c_calculator.create()

    def __del__(self):
        c_calculator.destroy(self._ptr)
    
    def add(self, a: int, b: int) -> int:
        """
        Do addition
        :param a: First number
        :type a: int
        :param b: Second number
        :type b: int
        :return: Result of a+b
        :rtype: int
        """
        result = ctypes.c_int()
        c_calculator.add(self._ptr, a, b, ctypes.byref(result))
        return result.value

    def sub(self, a: int, b: int) -> int:
        """
        Do subtraction
        :param a: First number
        :type a: int
        :param b: Second number
        :type b: int
        :return: Result of a-b
        :rtype: int
        """
        result = ctypes.c_int()
        c_calculator.sub(self._ptr, a, b, ctypes.byref(result))
        return result.value
    
    def cnt_ops_done(self) -> int:
        """
        Counter for the number of operation done
        :return: Counter for the number of operation done
        :rtype: int
        """
        result = ctypes.c_int()
        c_calculator.cnt_ops_done(self._ptr, ctypes.byref(result))
        return result.value
    
    def reset_counter(self) -> int:
        """
        Reset the counter
        :return: Last counter number
        :rtype: int
        """
        result = ctypes.c_int()
        c_calculator.reset_counter(self._ptr, ctypes.byref(result))
        return result.value
