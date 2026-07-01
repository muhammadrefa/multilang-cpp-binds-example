Object-oriented C# library utilising C wrapper
===

This library utilises `DllImport` to load the C wrapper and rewrite the classes to mimic the C++ library. `DllImport` used to achieve compatibility for apps using legacy .NET framework. Read the workflow in [WORKFLOW.md](WORKFLOW.md).

The structure of the library is as follows.
```
MyLib
├── runtimes
│   ├── linux-x64
│   │   └── native
│   │       └── PUT LINUX DLLs HERE
│   └── win-x64
│       └── native
│           └── PUT WINDOWS DLLs HERE
├── src
│   ├── Animal
│   │   ├── Animal.cs
│   │   ├── Cat.cs
│   │   ├── Dog.cs
│   │   └── Tiger.cs
│   ├── Exceptions
│   │   └── MyLibException.cs
│   ├── Interop
│   │   ├── Animal
│   │   │   ├── AnimalNative.cs
│   │   │   ├── CatNative.cs
│   │   │   ├── DogNative.cs
│   │   │   └── TigerNative.cs
│   │   ├── Handles
│   │   │   ├── SafeAnimalHandle.cs
│   │   │   ├── SafeCalculatorHandle.cs
│   │   │   └── SafeCircularBufferHandle.cs
│   │   ├── CalculatorNative.cs
│   │   ├── CircularBufferNative.cs
│   │   ├── NativeConstants.cs
│   │   ├── NativeEnums.cs
│   │   └── StatusExtensions.cs
│   ├── Calculator.cs
│   └── CircularBuffer.cs
└── MyLib.csproj

```

- `runtimes/<rid>/native` stores the DLLs used by the library.
- `src/`
  - `Exceptions/` contains custom exceptions.
  - `Interop/` contains bindings to the C library.
    - `Handles/` contains `SafeHandle` for every handles in the C wrapper.
    - `*Native.cs` contains bindings for C functions.
    - `NativeConstants.cs` contains common constants. It also stores the DLL name to load/
    - `NativeEnums.cs` contains common enums.
    - `StatusExtensions.cs` contains extension of status returned by the C wrapper. It translates the status into exception.
  - `*.cs` contains the classes recreated by utilising the bind functions.

This folder contains `LibTest/` which is useful to test the library.
