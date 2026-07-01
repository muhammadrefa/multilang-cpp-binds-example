C wrapper for C++ library
===

This wrapper wraps C++ library into C. The C wrapper can be used as an interface for C/other language to the C++ library.

In this example, the C wrapper loads the C++ library which is compiled as DLL. This approach resulting 2 files needed to use the library:
- `libmylibrary.so`, which is the C++ library
- `libmylibraryc.so`, which is the C wrapper

This library contains `main.c` file to test the library. It can be compiled using `make libtest` command.


Design choice
---
When dealing with inheritance, the wrapping can be done in 2 ways: upcasting and listing every methods. Both methods have pros and cons:
- Upcasting. Pros: No need to write every methods, prevents repeating. Cons: The user have to know the inheritance.
- List every methods. Pros: The user can use the functions directly. Cons: Repeating codes, prone to errors.
The `animal` example implements both of them to demonstration purpose. The Python and C# bindings utilise upcasting to make bindings simpler and utilise the object-oriented nature of the language. When using the wrapper in pure C, listing every methods will be helpful since the user does not have to think about inheritance.


MinGW notes
---
If the library compiled using MinGW, make sure the MinGW runtime DLL dependencies are also copied with the library. [Dependencies](https://github.com/lucasg/Dependencies) is a great tool to check the dependencies. To minimise the dependencies, link `libstdc++` and `libgcc` statically, or use MSVC instead.
