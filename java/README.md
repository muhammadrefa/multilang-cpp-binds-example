Object-oriented Java library utilising C wrapper
===

This library utilises `JNI` to bridge Java and the C wrapper. `JNI` used to achieve compatibility. Read the workflow in [WORKFLOW.md](WORKFLOW.md).

Design consideration
---
In this example, the native resource owned by the handle (handle-centric ownership). It is implemented by having the handle class (`NativeHandle`) which stores the pointer to the resource and used by the class which implements `AutoCloseable`. Closing the resource done using `finalize()` (before JDK 9) or `Cleaner` (JDK 9+). By having separate class handle managing the resource, it will be cleaned gracefully even if the class has failed.


Project structure
---
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
        │       ├── animal
        │       │   ├── Animal.java
        │       │   ├── Cat.class
        │       │   ├── Dog.java
        │       │   └── Tiger.java
        │       ├── binding
        │       │   ├── animal
        │       │   │   ├── AnimalNative.java
        │       │   │   ├── CatNative.java
        │       │   │   ├── DogNative.java
        │       │   │   └── TigerNative.java
        │       │   ├── handles
        │       │   │   ├── animal
        │       │   │   │   ├── AnimalHandle.java
        │       │   │   │   ├── CatHandle.java
        │       │   │   │   ├── DogHandle.java
        │       │   │   │   └── TigerHandle.java
        │       │   │   ├── numberprocessor
        │       │   │   │   ├── NumberProcessorHandle.java
        │       │   │   │   ├── NumberProcessorProxyHandle.java
        │       │   │   │   └── ProcessAdd2Handle.java
        │       │   │   ├── CalculatorHandle.java
        │       │   │   ├── CircularBufferHandle.java
        │       │   │   ├── NativeHandle.java
        │       │   │   └── NativeHandleWithCleaner.java.example
        │       │   ├── numberprocessor
        │       │   │   ├── NumberProcessorNative.class
        │       │   │   ├── NumberProcessorProxyCallbacks.class
        │       │   │   ├── NumberProcessorProxyNative.class
        │       │   │   └── ProcessAdd2Native.class
        │       │   ├── refs
        │       │   │   ├── CharRef.java
        │       │   │   └── IntRef.java
        │       │   ├── CalculatorNative.java
        │       │   ├── CircularBufferNative.java
        │       │   ├── Loader.java
        │       │   └── MyLibStatus.java
        │       ├── exceptions
        │       │   └── MyLibException.java
        │       ├── internal
        │       │   └── StatusHelper.java
        │       │── numberprocessor
        │       │   ├── NumberProcessor.java
        │       │   ├── NumberProcessorProxy.java
        │       │   └── ProcessAdd2.java
        │       ├── Calculator.java
        │       └── CircularBuffer.java
        └── jni
            ├── animal
            │   ├── AnimalNative.c
            │   ├── CatNative.c
            │   ├── DogNative.c
            │   └── TigerNative.c
            ├── helpers
            │   ├── ref_helper.c
            │   └── ref_helper.h
            ├── number_processor
            │   ├── number_processor_internal.h
            │   ├── NumberProcessorNative.c
            │   ├── NumberProcessorProxyJNI.cpp
            │   ├── NumberProcessorProxyJNI.hpp
            │   ├── NumberProcessorProxyNative.cpp
            │   └── ProcessAdd2Native.c
            ├── CalculatorNative.c
            ├── CircularBufferNative.c
            ├── mylib_binding_animal_AnimalNative.h
            ├── mylib_binding_animal_CatNative.h
            ├── mylib_binding_animal_DogNative.h
            ├── mylib_binding_animal_TigerNative.h
            ├── mylib_binding_CalculatorNative.h
            ├── mylib_binding_CircularBufferNative.h
            ├── mylib_binding_numberprocessor_NumberProcessorNative.h
            ├── mylib_binding_numberprocessor_NumberProcessorProxyNative.h
            └── mylib_binding_numberprocessor_ProcessAdd2Native.h
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
