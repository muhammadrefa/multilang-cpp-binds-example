using System;
using System.Runtime.InteropServices;
using MyLib.Interop.Handles;

namespace MyLib.Interop
{
    internal static class TigerNative
    {
        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Tiger_Create")]
        internal static extern SafeTigerHandle Create();

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Tiger_Create_With_Name")]
        internal static extern SafeTigerHandle Create_With_Name(
            byte[] name,
            int length
        );

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Tiger_Destroy")]
        internal static extern MyLibStatus Destroy(IntPtr handle);

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Tiger_As_Cat")]
        internal static extern SafeCatHandle As_Animal(
            SafeTigerHandle handle
        );

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Tiger_Hunt")]
        internal static extern MyLibStatus Hunt(
            SafeTigerHandle handle
        );

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Tiger_GetHunger")]
        internal static extern MyLibStatus GetHunger(
            SafeTigerHandle handle,
            out int hunger
        );

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Tiger_Speak")]
        internal static extern MyLibStatus Speak(
            SafeTigerHandle handle
        );

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Tiger_Sleep")]
        internal static extern MyLibStatus Sleep(
            SafeTigerHandle handle
        );
    }
}
