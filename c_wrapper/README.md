C wrapper for C++ library

This wrapper wraps C++ library into C. The C wrapper can be used as an interface for C/other language to the C++ library.

In this example, the C wrapper loads the C++ library which is compiled as DLL. This approach resulting 2 files needed to use the library:
- `libmylibrary.so`, which is the C++ library
- `libmylibraryc.so`, which is the C wrapper

This library contains `main.c` file to test the library. It can be compiled using `make libtest` command.


MinGW notes

If the library compiled using MinGW, make sure the MinGW runtime DLL dependencies are also copied with the library. [Dependencies](https://github.com/lucasg/Dependencies) is a great tool to check the dependencies. To minimise the dependencies, link `libstdc++` and `libgcc` statically, or use MSVC instead.
