Sample C++ library

This folder contains sample C++ library. The primary goal of the library is to demonstrate how the C++ library can be wrapped into C and loaded into other languages. Class function is not the primary focus.

This library compiles into dynamically-linked library. When wrapped, this approach resulting 2 files needed to use the library:
- `libmylibrary.so`, which is the C++ library
- `libmylibraryc.so`, which is the C wrapper

Other approach is to compile this library into statically-linked library. By doing so, the C++ library will be linked into the C wrapper statically, resulting only one DLL (`libmylibraryc.so`) needed to use the library.

This library contains `main.cpp` file to test the library. It can be compiled using `make libtest` command.
