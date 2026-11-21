Object-oriented Python library utilising C wrapper
===

This library utilises `ctypes` to load the C wrapper and rewrite the classes to mimic the C++ library. Read the workflow in [WORKFLOW.md](WORKFLOW.md).

Design consideration
---
In this example, the native resource owned by the object (object-centric ownership). It is implemented by having the object store the pointer to the resource. (C)Python Garbage Collector, which counting the references, will cleanup the resource (using `weakref` or `__del__`) when nothing refers to the object.


Project structure
---
```
mylib
├── _bindings
│   ├── animal
│   │   ├── __init__.py
│   │   ├── animal.py
│   │   ├── cat.py
│   │   ├── dog.py
│   │   └── tiger.py
│   ├── NumberProcessor
│   │   ├── __init__.py
│   │   ├── NumberProcessorProxy.py
│   │   ├── NumberProcessor.py
│   │   ├── ProcessAdd2.py
│   │   └── _types.py
│   ├── _binding_utils.py
│   ├── calculator.py
│   └── circularbuffer.py
├── animal
│   ├── __init__.py
│   ├── animal.py
│   ├── cat.py
│   ├── dog.py
│   └── tiger.py
├── native
│   └── PUT DLLs HERE
├── NumberProcessor
│   ├── __init__.py
│   ├── NumberProcessorProxy.py
│   ├── NumberProcessor.py
│   └── ProcessAdd2.py
├── __init__.py
├── _enums.py
├── _errors.py
├── _loader.py
├── _types.py
├── calculator.py
└── circularbuffer.py
```

- `_bindings/` contains the C function binder.
  - `_binding_utils.py` contains helper to bind C functions.
  - `*.py` contains the function bindings, similar to the contents of the header files of the wrapper. The bindings written into several files similar to the C wrapper header files for readability reason.
- `native/` stores the DLL.
- `_enums.py` contains common enums of the library.
- `_errors.py` contains functions for error checking.
- `_loader.py` contains DLL loader.
- `_types.py` contains data type specific to the library.
- `*.py` contains the classes recreated by utilising the bind functions.

This folder contains `libtest.py` which is useful to test the library.
