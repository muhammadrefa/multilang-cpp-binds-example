using System;
using System.Runtime.InteropServices;
using MyLib.Interop.Handles;

namespace MyLib.Interop
{
    internal static class NumberProcessorNative
    {
        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_NumberProcessor_Destroy")]
        internal static extern MyLibStatus Destroy(IntPtr handle);

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_NumberProcessor_Process")]
        internal static extern MyLibStatus Process(
            SafeNumberProcessorHandle handle
        );

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_NumberProcessor_SetNumber")]
        internal static extern MyLibStatus SetNumber(
            SafeNumberProcessorHandle handle,
            int number
        );

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_NumberProcessor_GetNumber")]
        internal static extern MyLibStatus GetNumber(
            SafeNumberProcessorHandle handle,
            out int number
        );

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_NumberProcessor_PrintNumber")]
        internal static extern MyLibStatus PrintNumber(
            SafeNumberProcessorHandle handle
        );
    }
}
