Object-oriented Java library utilising C wrapper
===

This library utilises `JNI` to bridge Java and the C wrapper. `JNI` used to achieve compatibility. Read the workflow in [WORKFLOW.md](WORKFLOW.md).

The structure of the library is as follows.
```
mylib
├── libmylibrary_jni.so
├── Makefile
├── native
│   ├── inc
│   |   └── PUT C HEADERS HERE
│   └── lib
│       └── PUT DLLs HERE
└── src
    └── main
        ├── java
        │   └── mylib
        │       ├── binding
        │       │   ├── handles
        │       │   │   ├── AnimalHandle.java
        │       │   │   ├── CalculatorHandle.java
        │       │   │   ├── CatHandle.java
        │       │   │   ├── CircularBufferHandle.java
        │       │   │   ├── DogHandle.java
        │       │   │   ├── NativeHandle.java
        │       │   │   ├── NativeHandleWithCleaner.java.example
        │       │   │   └── TigerHandle.java
        │       │   ├── refs
        │       │   │   ├── CharRef.java
        │       │   │   └── IntRef.java
        │       │   ├── AnimalNative.java
        │       │   ├── CalculatorNative.java
        │       │   ├── CatNative.java
        │       │   ├── CircularBufferNative.java
        │       │   ├── DogNative.java
        │       │   ├── Loader.java
        │       │   ├── MyLibStatus.java
        │       │   └── TigerNative.java
        │       ├── exceptions
        │       │   └── MyLibException.java
        │       ├── internal
        │       │   └── StatusHelper.java
        │       ├── Animal.java
        │       ├── Calculator.java
        │       ├── Cat.java
        │       ├── CircularBuffer.java
        │       ├── Dog.java
        │       └── Tiger.java
        └── jni
            ├── animal
            │   ├── AnimalNative.c
            │   ├── CatNative.c
            │   ├── DogNative.c
            │   └── TigerNative.c
            ├── CalculatorNative.c
            ├── CircularBufferNative.c
            ├── helpers
            │   ├── ref_helper.c
            │   └── ref_helper.h
            ├── mylib_binding_AnimalNative.h
            ├── mylib_binding_CalculatorNative.h
            ├── mylib_binding_CatNative.h
            ├── mylib_binding_CircularBufferNative.h
            ├── mylib_binding_DogNative.h
            └── mylib_binding_TigerNative.h


```

- `native`
  - `inc` stores the header files from the C wrapper.
  - `lib` stores the DLLs used by the library.
- `src/main/`
  - `java/mylib/` contains Java library files.
    - `bindings/` contains binder to native codes.
      - `handles/` contains handles which wraps opaque handles from the C wrapper.
        - `NativeHandleWithCleaner.java.example` contains code for `NativeHandler` with `Cleaner` implemented. Only supports Java 9+.
      - `refs/` contains classes for C pointers. Only used when calling native codes.
      - `Loader.java` contains DLL loader.
      - `MyLibStatus.java` contains `mylib_status_t` enums.
      - `*Native.java` contains functions to call native code (JNI).
    - `exceptions/` contains custom exceptions.
    - `internal/StatusHelper.java` contains helper to translates status codes into exceptions.
  - `jni/` contains JNI bridges.
    - `helpers/ref_helper.c` contains helper for `IntRef` and `CharRef` Java objects (see `bindings/refs/`).
    - `mylib_binding_*.h` are generated JNI headers. It generated using `make jni_headers` command which calls `javac`.

This folder contains `libtest/` which is useful to test the library.


Design consideration
---
In this example, the native resource owned by the handle (handle-centric ownership). It is implemented by having the handle class (`NativeHandle`) which stores the pointer to the resource and used by the class which implements `AutoCloseable`. Closing the resource done using `finalize()` (before JDK 9) or `Cleaner` (JDK 9+). By having separate class handle managing the resource, it will be cleaned gracefully even if the class has failed.
