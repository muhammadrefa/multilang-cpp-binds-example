using System;
using System.Runtime.InteropServices;
using MyLib.Interop.Handles;

namespace MyLib.Interop
{
    internal static class AnimalNative
    {
        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Animal_Create")]
        internal static extern SafeAnimalHandle Create();

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Animal_Create_With_Name")]
        internal static extern SafeAnimalHandle Create_With_Name(
            byte[] name,
            int length
        );

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Animal_Destroy")]
        internal static extern MyLibStatus Destroy(IntPtr handle);

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Animal_Speak")]
        internal static extern MyLibStatus Speak(
            SafeAnimalHandle handle
        );

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Animal_Speak_Multiple_Times")]
        internal static extern MyLibStatus Speak_Multiple_Times(
            SafeAnimalHandle handle,
            int times
        );

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Animal_Sleep")]
        internal static extern MyLibStatus Sleep(
            SafeAnimalHandle handle
        );

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Animal_Set_Name")]
        internal static extern MyLibStatus Set_Name(
            SafeAnimalHandle handle,
            byte[] name,
            int length
        );

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Animal_Get_Name")]
        internal static extern MyLibStatus Get_Name(
            SafeAnimalHandle handle,
            byte[] name,
            int bufsize,
            out int length
        );
    }
}
