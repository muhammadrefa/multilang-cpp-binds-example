import weakref

from .NumberProcessor import NumberProcessor
from .._bindings.NumberProcessor import ProcessAdd2 as c_ProcessAdd2
from .._bindings.NumberProcessor import NumberProcessor as c_NumberProcessor
from .._bindings.NumberProcessor._types import mylib_ProcessAdd2_t


class ProcessAdd2(NumberProcessor):
    def __init__(self, **kwargs):
        self._ptr_ProcessAdd2: mylib_ProcessAdd2_t = kwargs.pop('_ptr', None)
        if self._ptr_ProcessAdd2 is None:
            self._ptr_ProcessAdd2 = c_ProcessAdd2.create()
        self._finalizer = weakref.finalize(self, c_ProcessAdd2.destroy, self._ptr_ProcessAdd2)
        super().__init__(_ptr=c_ProcessAdd2.as_NumberProcessor(self._ptr_ProcessAdd2), **kwargs)

    def process(self):
        c_NumberProcessor.process(c_ProcessAdd2.as_NumberProcessor(self._ptr_ProcessAdd2))
