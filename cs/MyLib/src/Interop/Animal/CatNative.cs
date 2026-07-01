using System;
using System.Runtime.InteropServices;
using MyLib.Interop.Handles;

namespace MyLib.Interop
{
    internal static class CatNative
    {
        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Cat_Create")]
        internal static extern SafeCatHandle Create();

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Cat_Create_With_Name")]
        internal static extern SafeCatHandle Create_With_Name(
            byte[] name,
            int length
        );

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Cat_Destroy")]
        internal static extern MyLibStatus Destroy(IntPtr handle);

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Cat_As_Animal")]
        internal static extern SafeAnimalHandle As_Animal(
            SafeCatHandle handle
        );

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Cat_Fight")]
        internal static extern MyLibStatus Fight(
            SafeCatHandle handle,
            int bigger_cat,
            out int success
        );

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Cat_StillAlive")]
        internal static extern MyLibStatus StillAlive(
            SafeCatHandle handle,
            out int is_alive
        );

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Cat_Speak")]
        internal static extern MyLibStatus Speak(
            SafeCatHandle handle
        );
    }
}
