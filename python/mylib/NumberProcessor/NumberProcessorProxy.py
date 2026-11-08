from __future__ import annotations

import abc
import ctypes
import weakref
from threading import Lock
from typing import Dict, Union, Optional

from .NumberProcessor import NumberProcessor
from .._bindings.NumberProcessor import NumberProcessorProxy as c_NumberProcessorProxy
from .._bindings.NumberProcessor._types import mylib_NumberProcessorProxy_t, NumberProcessorProxy_Callback


_g_registry_lock: Lock = Lock()
_g_registry: Dict[int, weakref.ReferenceType[NumberProcessorProxy]] = dict()

class NumberProcessorProxy(NumberProcessor):
    @staticmethod
    def _get_object_from_handle(ptr_npp, raise_error: bool = True) -> Optional[NumberProcessorProxy]:
        obj: Optional[weakref.ReferenceType[NumberProcessorProxy]] = None
        _ptr_npp_val = ctypes.cast(ptr_npp, ctypes.c_void_p).value
        if _ptr_npp_val is None:
            return None
        with _g_registry_lock:
            if _ptr_npp_val in _g_registry:
                obj = _g_registry[_ptr_npp_val]
            else:
                if raise_error:
                    raise TypeError("NumberProcessor is not a NumberProcessorProxy instance!")
                else:
                    return None
        npp_obj = obj()
        if npp_obj:
            return npp_obj
        if raise_error:
            raise ReferenceError("NumberProcessorProxy instance already cleaned up!")
        else:
            return None

    # process
    @staticmethod
    @ctypes.CFUNCTYPE(None, mylib_NumberProcessorProxy_t)
    def _cb_process(_handle):
        npp = NumberProcessorProxy._get_object_from_handle(_handle, raise_error=False)
        if npp:
            npp.process()

    # print number
    @staticmethod
    @ctypes.CFUNCTYPE(None, mylib_NumberProcessorProxy_t)
    def _cb_print_number(_handle):
        npp = NumberProcessorProxy._get_object_from_handle(_handle, raise_error=False)
        if npp:
            npp.print_number()

    def __init__(self, **kwargs):
        self._ptr_NumberProcessorProxy = kwargs.pop('_ptr', None)

        if self._ptr_NumberProcessorProxy is None:
            # --- set callbacks START --- #

            self._NumberProcessorProxy_cb = NumberProcessorProxy_Callback(
                cb_process=self._cb_process,
                cb_print_number=self._cb_print_number
            )

            # --- set callbacks END --- #

            self._ptr_NumberProcessorProxy = c_NumberProcessorProxy.create(ctypes.byref(self._NumberProcessorProxy_cb))

            _npp_ptr_val = ctypes.cast(self._ptr_NumberProcessorProxy, ctypes.c_void_p).value
            with _g_registry_lock:
                _g_registry[_npp_ptr_val] = weakref.ref(self)

            self._finalizer = weakref.finalize(self, NumberProcessorProxy._finalize, self._ptr_NumberProcessorProxy)

        super().__init__(_ptr=c_NumberProcessorProxy.as_NumberProcessor(self._ptr_NumberProcessorProxy), **kwargs)

    @staticmethod
    def _finalize(ptr):
        # remove from registry entry
        _ptr_val = ctypes.cast(ptr, ctypes.c_void_p).value
        if _ptr_val is not None:
            with _g_registry_lock:
                _g_registry.pop(_ptr_val, None)
        c_NumberProcessorProxy.destroy(ptr)

    @classmethod
    def from_NumberProcessor(cls, number_processor: NumberProcessor):
        ptr_npp = c_NumberProcessorProxy.from_NumberProcessor(number_processor._ptr_NumberProcessor)
        return cls._get_object_from_handle(ptr_npp)


    @abc.abstractmethod
    def process(self):
        pass

    def print_number(self):
        c_NumberProcessorProxy.base__print_number(self._ptr_NumberProcessorProxy)
