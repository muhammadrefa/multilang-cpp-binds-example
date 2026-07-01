Workflow for writing Python bindings
===
This document will guide you step-by-step on how to write the Python bindings by utilising the C wrapper. The goal is to write the library as object-oriented, mimicking the original C++ library. It is better if you read this document while looking at the source code to get better understanding.

Important files and directories
---
(You may rename the files and directories)
1. `_loader.py` contains the `CDLL` loader. The library filepath is written inside the file.
2. `_types.py` contains `ctypes` data type conversion to mimic `typedef` in C.
3. `_enums.py` contains general enum from the library, with status as one of them.
4. `_errors.py` contains error checker. It also translates the status codes into Python exceptions.
5. `_bindings/` contains the binding to native C functions **(important!!!)**
6. `_binding_utils.py` contains helper to bind the native C functions.
7. `native/` contains the DLLs loaded by `_loader.py` (you can move the DLL path as long as you fix the `_loader.py`)

Writing the bindings
---
1. Starts with creating a new file in `bindings/`. In this repo, the filename follows the C wrapper header filename. Import the helpers to make life easier.
```python
# (e.g. bindings/mywrapper.py)

import ctypes

from .._loader import load_library
from .._errors import check_pointer, check_status
from ._binding_utils import FunctionBinder

_bind = FunctionBinder(load_library()).bind_function
```
2. Define the new data type for opaque handles in `_types.py`. And then import it in the binding file.
3. Define every functions by using `_bind()` (of `FunctionBinder(CDLL).bind_function`) which does `getattr()` and set the `restypes`, `argtypes`, and `errcheck` behind the scene. Read more about `errcheck` [here](https://docs.python.org/3/library/ctypes.html#ctypes._CFuncPtr.errcheck). You may give different function name with the C wrapper, but it is better to have similar name to avoid confusion.
```python
# (e.g. bindings/mywrapper.py)

my_py_func = _bind(
    "The_Function_Name_In_C",
    xxx_t,
    [argtype1, argtype2],
    errcheck_func_py
)
```
4. Create new file which will be imported by the user. In this case, a file contains the class we will implement. Do not forget to import the binder we created earlier.
```python
# (e.g. my_cool_class.py)

import ctypes

from ._bindings import mywrapper as c_mywrapper

class MyCoolClass:
```
5. Add the constructor and the destructor. Store the opaque handle as (private) class member (I know, python does not understand privates. That is why [leading underscore (`_`) become a convention to make it 'private'](https://peps.python.org/pep-0008/#method-names-and-instance-variables)).
```python
# (e.g. my_cool_class.py)

def __init__(self):
    self._ptr = c_mywrapper.create()

def __del__(self):
    c_mywrapper.destroy(self._ptr)
```
6. Continue to work on other methods. Use [primitive data types from `ctypes`](https://docs.python.org/3/library/ctypes.html#fundamental-data-types) if you need, and [`ctypes.byref`](https://docs.python.org/3/library/ctypes.html#ctypes.byref) if you have to pass a pointer.
7. C++ public class members can be re-implemented as property. Call the getter and setter inside the property's getter and setter respectively.
```C
// In the C header file

status_t MyWrapper_Set_Age(mytype_t* handle, int age);
status_t MyWrapper_Get_Age(mytype_t* handle, int* age);

```
```python
# In the function binder

set_age = _bind(
    "MyWrapper_Set_Age",
    status_t,
    [mytype_t, ctypes.c_int],
    check_status
)

get_age = _bind(
    "MyWrapper_Get_Age",
    status_t,
    [mytype_t, ctypes.POINTER(ctypes.c_int)],
    check_status
)
```
```python
# Inside the class

@property
def age(self) -> int:
    _age = ctypes.c_int()
    c_mywrapper.get_age(self._ptr, ctypes.byref(_age))
    return age.value

@age.setter
def age(self, new_age: int):
    c_mywrapper.set_name(self._ptr, new_age)

```
8. For inheritance, remember there are 2 approaches [(they are mentioned when writing the C wrapper)](../c_wrapper/README.md#design-choice)? If you choose to use upcasting (which is more reflecting the nature of OO), you have to set the pointers. Let me tell you by example.
```python
# In the base class (e.g. base.py)

class MyBaseClass:
    def __init__(self):
        self._ptr_base = c_mywrapper_base.create()

    def __del__(self):
        c_mywrapper_base.destroy(self._ptr_base)

    # self._ptr_base is needed when calling the inherited method
    def _init_from_ptr(self, ptr) -> None:
        self._ptr_base = ptr

    # inherited class can use this method since self._ptr_base is defined
    def base_method(self) -> None:
        c_mywrapper_base.method(self._ptr_base)
```
```python
# In the inherited class (e.g. inherited.py)

class MyInheritedClass(MyBaseClass):
    def __init__(self):
        self._ptr_inherited = c_mywrapper_inherited.create()
        super()._init_from_ptr(c_my_wrapper_inherited.as_base(self._ptr_inherited))      # upcasting; initialise handle for parent class

    def __del__(self):
        c_mywrapper_inherited.destroy(self._ptr_inherited)

    # needed when calling the inherited method
    def _init_from_ptr(self, ptr) -> None:
        self._ptr_inherited = ptr

    # no need to reimplement base_method()
```

Building and shipping the library
---

1. Ship the library/wrapper with all the dependencies.

That's all what I'm thinking on how to ship it (at least when this I write this document)...
