Workflow for writing C wrapper
===
This document will guide you step-by-step on how to write the C wrapper for the C++ library. It is better if you read this document while looking at the source code to get better understanding.

Important files
---
(You may rename the files)
1. `mylib_export.h` is a header file, created only once, contains macro to export functions to the library. It is needed when compiling the library for Windows. Learn more about it [here](https://learn.microsoft.com/en-us/cpp/build/exporting-from-a-dll?view=msvc-170) (or ask AI for the explanation, that is how I got here).
2. `status_code.h` is a header file contains status codes. Since there is no exceptions in C (CMIIW), status code comes in handy to let you know if something went wrong.

Writing the wrapper
---
1. Create a header file (`.h`). Don't forget `#pragma once` and `extern "C"`.
2. Create an opaque handle `typedef xxx xxx_t` which holds the pointer to the object.
3. Start with constructor (`_Create()`) and destructor (`_Destroy(xxx_t)`). The constructor returns a pointer to the handle, and the destructor asks for the handle. Do not forget the macro to export your function.
4. Write the rest of the **public methods**. Don't forget to ask for the handle. Remember to **use only primitive data types**. (You can go to step 6 and come back later)
5. When dealing with inheritance, there are 2 approaches which are discussed in the [README.md](README.md#design-choice) file. The important thing is to wrap their own methods and wrap the overridden methods.
6. Now it is time to write the implementations. The implementation can be written in C++ (you are wrapping classes so it must be C++). Create a new `.cpp` file.
7. To minimise repetition, write `GetObject(xxx_t)` function to get the object from the handle. This function returns a pointer to the object.
8. Write the implementation for the constructor (`_Create()`) and the destructor (`_Destroy(xxx_t)`) first! The constructor contains `X = new Xxx()` and the destructor contains `delete GetObject(handle)` (which is translated to `delete X`).
9. Write the implementation of other methods (go back to step 4 if you skipped it). **Do not write the C++ implementation into the functions!** You are writing a wrapper, not rewriting the library in C. Just use the handle and call the method like `GetObject(handle)->MyMethod()` and you are good to go.
10. What if the method returns something but your function returns status? Use pointers! I am sure you already know about it (*wink*)
11. What about public class members? Write getters (`_Get_Value(int*)`) and setters (`_Set_Value(int)`) in the wrapper!

Building and shipping the wrapper
---
1. Write the Makefile (or other build system you preffered). You can see the Makefile example in this repository.
2. Build the library/wrapper.
3. Ship the library/wrapper with all the dependencies.

Additional note
---
Test the implementation by writing a test program and **check for memory leaks** that might happen. When writing the program, make sure `_Destroy(handle)` called for every `_Create()`.
```
valgrind -s --leak-check=full --show-leak-kinds=all ./my_test_program > /dev/null
```
You do not want to have memory leaks, do you?
