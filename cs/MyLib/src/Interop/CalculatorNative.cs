using System;
using System.Runtime.InteropServices;
using MyLib.Interop.Handles;

namespace MyLib.Interop
{
    internal static class CalculatorNative
    {
        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Calculator_Create")]
        internal static extern SafeCalculatorHandle Create();

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Calculator_Destroy")]
        internal static extern MyLibStatus Destroy(IntPtr handle);

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Calculator_Add")]
        internal static extern MyLibStatus Add(
            SafeCalculatorHandle handle,
            int a,
            int b,
            out int result
        );

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Calculator_Sub")]
        internal static extern MyLibStatus Sub(
            SafeCalculatorHandle handle,
            int a,
            int b,
            out int result
        );

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Calculator_CntOpsDone")]
        internal static extern MyLibStatus CntOpsDone(
            SafeCalculatorHandle handle,
            out int result
        );

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Calculator_ResetCounter")]
        internal static extern MyLibStatus ResetCounter(
            SafeCalculatorHandle handle,
            out int result
        );
    }
}
