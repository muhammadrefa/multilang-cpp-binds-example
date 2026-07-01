Workflow for writing C# bindings
===
This document will guide you step-by-step on how to write the C# bindings by utilising the C wrapper. The goal is to write the library as object-oriented, mimicking the original C++ library. It is better if you read this document while looking at the source code to get better understanding.

Important files and directories
---
(You may rename the files and directories)
1. `runtimes/<rid>/native` stores the DLL libraries. Click [here](https://learn.microsoft.com/en-us/dotnet/core/rid-catalog) to see the .NET RID catalog.
2. `src/Interop/Handles/` contains `SafeHandle` for every handles. It also manages handle disposal.
3. `src/Interop/*Native.cs` contains the binding to native C functions **(important!!!)**
4. `src/Interop/NativeConstants.cs` contains the library filepath that will be loaded by `*Native.cs`.
4. `src/Interop/NativeEnums.cs` contains general enum from the library, with status as one of them.
5. `src/Interop/StatusExtensions.cs` contains the extension of `status` which is defined in the `NativeEnums.cs`. This extension translates status codes into C# exceptions.
6. `src/Exceptions/` contains custom exceptions.

Writing the bindings
---
1. Starts with write a class for the handle, inheriting from `SafeHandle`. You can copy an example from `src/Interop/Handles/` straight away and make some modification. Make sure you write the implementation of `ReleaseHandle()` correctly (i.e. call the `Destroy()` function). Since the native binder has not been written yet, we can visit `ReleaseHandle()` later.
2. Create `src/Interop/*Native.cs` file. Use the file in this example as a template to define every C functions. Start with the constructor (`Create()`) and the destructor (`Destroy(IntPtr)`), and continue to other functions. Do not forget to use the `SafeHandle` we wrote earlier.
```c
// (e.g. myclass_wrapper.h)

status_t The_Function_Name_In_C(mytype_t* handle, int arg1, char* arg2, int* result);
```
```csharp
// (e.g. Interop/MyClassNative.cs)

// the library name stored in NativeConstants.cs
[DllImport(
    NativeConstants.LibraryName,
    CallingConvention = CallingConvention.Cdecl,
    EntryPoint = "The_Function_Name_In_C")]
internal static extern MyStatus MyFunc(
    SafeMyClassHandle handle,
    int arg1,
    byte[] arg2,
    out int result
);
```
3. Go back to the `Safe*Handle` class in `src/Interop/Handles/`, and fix the `ReleaseHandle()` method since we have write the binding for the destructor.
4. Create a new file in `src/` which will be used by the library consumer. Write a new class which inherited from `IDisposable`. Here we start to reconstruct the object-oriented parts. Let's start with the handle and the constructor.
```csharp
// (e.g. MyClass.cs)

private readonly SafeMyClassHandle _handle;

public MyClass()
{
    _handle = MyClassNative.Create();
    if (_handle.IsInvalid)
        throw new OutOfMemoryException("Failed to create.");
}
```
5. Since the destructor implemented inside the `SafeHandle`, it does not need to re-implemented here. We only have to add the code to dispose the handle.
```csharp
// (e.g. MyClass.cs)

public void Dispose()
{
    _handle.Dispose();
}

private void ThrowIfDisposed()
{
    if (_handle.IsClosed)
        throw new ObjectDisposedException(nameof(MyClass));
}
```
6. Now it is time to reconstruct the object-oriented parts by adding the methods which calls the native functions.
```csharp
// (e.g. MyClass.cs)

public int MyMethod(int arg1, byte[] arg2)
{
    ThrowIfDisposed();
    var status = MyClassNative.Add(_handle, arg1, arg2, out int result);
    status.ThrowIfError();
    return result;
}
```
7. C++ public class members can be re-implemented as property. Call the getter and setter inside the property's getter and setter respectively.
```C
// In the C header file

status_t MyWrapper_Set_Age(mytype_t* handle, int age);
status_t MyWrapper_Get_Age(mytype_t* handle, int* age);

```
```csharp
// In the function binder

[DllImport(
    NativeConstants.LibraryName,
    CallingConvention = CallingConvention.Cdecl,
    EntryPoint = "MyWrapper_Set_Age")]
internal static extern MyStatus Set_Age(
    SafeMyClassHandle handle,
    int age
);

[DllImport(
    NativeConstants.LibraryName,
    CallingConvention = CallingConvention.Cdecl,
    EntryPoint = "MyWrapper_Get_Age")]
internal static extern MyStatus Set_Age(
    SafeMyClassHandle handle,
    out int age
);
```
```csharp
// Inside the class

public int Age
{
    get
    {
        ThrowIfDisposed();
        var status = MyClassNative.Get_Age(_handleAnimal, out int age);
        status.ThrowIfError();
        return age;
    }
    set
    {
        ThrowIfDisposed();
        var status = MyClassNative.Set_Age(_handleAnimal, value);
        status.ThrowIfError();
    }
}

```
8. For inheritance, remember there are 2 approaches [(they are mentioned when writing the C wrapper)](../c_wrapper/README.md#design-choice)? If you choose to use upcasting (which is more reflecting the nature of OO), you have to set the handles. Let me tell you by example.
```csharp
// In the base class (e.g. base.cs)

public class MyBaseClass : IDisposable
{
    private SafeBaseHandle _handleBase;

    public MyBaseClass()
    {
        _handleBase = BaseNative.Create();
        if (_handleBase.IsInvalid)
            throw new OutOfMemoryException("Failed to create base class.");
    }

    // _handleBase is needed when calling the inherited method
    private protected void InitializeBaseHandle(SafeBaseHandle handle)
    {
        _handleBase = handle;
    }

    // inherited class can use this method since _handleBase is defined
    public virtual void BaseMethod()
    {
        ThrowIfDisposed();
        var status = BaseNative.Sleep(_handleBase);
        status.ThrowIfError();
    }
}
```
```csharp
// In the base class (e.g. inherited.cs)

public class MyInheritedClass : MyBaseClass
{
    private SafeInheritedHandle _handleInherited;

    public MyInheritedClass()
    {
        _handleInherited = InheritedNative.Create();
        if (_handleInherited.IsInvalid)
            throw new OutOfMemoryException("Failed to create inherited class.");
        // using C# base keyword to call the base class' method
        base.InitializeBaseHandle(InheritedNative.As_Base(_handleBase));  // upcasting: initialise handle for parent class
    }

    // _handleInherited is needed when calling the inherited method
    private protected void InitializeInheritedHandle(SafeInheritedHandle handle)
    {
        _handleInherited = handle;
    }

    // no need to reimplement the BaseMethod()
}
```

Building and shipping the library
---
1. Put the DLL and its dependencies into `runtimes/<rid>/native`.
2. Run `dotnet build` or `dotnet build -c Release`.
3. Ship the `.dll` and `.xml` inside the `bin/<configuration>/<target_framework>`.
