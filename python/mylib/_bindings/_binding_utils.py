# Binding utils


from ctypes import CDLL
from typing import Any, List


class FunctionBinder:
    """
    Bind C function
    """
    def __init__(self, lib: CDLL):
        """
        Initialize function binder
        :param lib: C library
        :type lib: CDLL
        """
        self.lib = lib

    def bind_function(self, name: str, restype: Any, argtypes: List[Any], errcheck=None):
        """
        Bind functions from a C library
        :param name: C function name inside the library
        :type name: str
        :param restype: Data type for return value
        :type restype: C data types
        :param argtypes: List of data type for function arguments
        :type argtypes: List of C data types
        :param errcheck:
        :type errcheck:
        :return: C function
        :rtype:
        """
        fn = getattr(self.lib, name)
        fn.restype = restype
        fn.argtypes = argtypes

        if errcheck is not None:
            fn.errcheck = errcheck
        
        return fn
