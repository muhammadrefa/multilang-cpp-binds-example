using System;
using System.Runtime.InteropServices;
using MyLib.Interop.Handles;

namespace MyLib.Interop
{
    internal static class DogNative
    {
        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Dog_Create")]
        internal static extern SafeDogHandle Create();

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Dog_Create_With_Name")]
        internal static extern SafeDogHandle Create_With_Name(
            byte[] name,
            int length
        );

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Dog_Destroy")]
        internal static extern MyLibStatus Destroy(IntPtr handle);

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Dog_As_Animal")]
        private static extern IntPtr As_Animal_Internal(
            SafeDogHandle handle
        );

        internal static SafeAnimalHandle As_Animal(SafeDogHandle handle)
        {
            return SafeAnimalHandle.AsReference(As_Animal_Internal(handle));
        }

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Dog_Fetch")]
        internal static extern MyLibStatus Fetch(
            SafeDogHandle handle,
            out int success
        );

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Dog_GetEnergy")]
        internal static extern MyLibStatus GetEnergy(
            SafeDogHandle handle,
            out int energy
        );

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Dog_Speak")]
        internal static extern MyLibStatus Speak(
            SafeDogHandle handle
        );

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Dog_Sleep")]
        internal static extern MyLibStatus Sleep(
            SafeDogHandle handle
        );
    }
}
