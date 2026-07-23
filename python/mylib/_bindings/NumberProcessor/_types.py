import ctypes

class NumberProcessor(ctypes.Structure):
    pass
mylib_NumberProcessor_t = ctypes.POINTER(NumberProcessor)

class ProcessAdd2(ctypes.Structure):
    pass
mylib_ProcessAdd2_t = ctypes.POINTER(ProcessAdd2)

class NumberProcessorProxy(ctypes.Structure):
    pass
mylib_NumberProcessorProxy_t = ctypes.POINTER(NumberProcessorProxy)

class NumberProcessorProxy_Callback(ctypes.Structure):
    _fields_ = [
        ("cb_process", ctypes.CFUNCTYPE(None, mylib_NumberProcessorProxy_t)),
        ("cb_print_number", ctypes.CFUNCTYPE(None, mylib_NumberProcessorProxy_t)),
    ]
mylib_NumberProcessorProxy_cb_t = ctypes.POINTER(NumberProcessorProxy_Callback)
