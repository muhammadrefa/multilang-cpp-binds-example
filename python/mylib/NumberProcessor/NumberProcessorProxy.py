import abc
import ctypes
import weakref

from .NumberProcessor import NumberProcessor
from .._bindings.NumberProcessor import NumberProcessorProxy as c_NumberProcessorProxy
from .._bindings.NumberProcessor._types import mylib_NumberProcessorProxy_t, NumberProcessorProxy_Callback


class NumberProcessorProxy(NumberProcessor):
    def __init__(self, **kwargs):
        self._ptr_NumberProcessorProxy: mylib_NumberProcessorProxy_t = kwargs.pop('_ptr', None)

        if self._ptr_NumberProcessorProxy is None:
            # --- set callbacks START --- #

            # process
            @ctypes.CFUNCTYPE(None, mylib_NumberProcessorProxy_t)
            def _cb_process(_handle: mylib_NumberProcessorProxy_t):
                self.process()

            # print number
            @ctypes.CFUNCTYPE(None, mylib_NumberProcessorProxy_t)
            def _cb_print_number(_handle: mylib_NumberProcessorProxy_t):
                self.print_number()

            _NumberProcessorProxy_cb = NumberProcessorProxy_Callback(
                cb_process=_cb_process,
                cb_print_number=_cb_print_number
            )

            # --- set callbacks END --- #

            self._ptr_NumberProcessorProxy = c_NumberProcessorProxy.create(ctypes.byref(_NumberProcessorProxy_cb))
            self._finalizer = weakref.finalize(self, c_NumberProcessorProxy.destroy, self._ptr_NumberProcessorProxy)

        super().__init__(_ptr=c_NumberProcessorProxy.as_NumberProcessor(self._ptr_NumberProcessorProxy), **kwargs)

    @abc.abstractmethod
    def process(self):
        pass

    def print_number(self):
        c_NumberProcessorProxy.base__print_number(self._ptr_NumberProcessorProxy)
