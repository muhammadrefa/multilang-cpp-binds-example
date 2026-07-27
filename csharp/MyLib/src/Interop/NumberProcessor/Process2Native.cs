using System;
using System.Runtime.InteropServices;
using MyLib.Interop.Handles;

namespace MyLib.Interop
{
    internal static class Process2Native
    {
        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Process2_Create")]
        internal static extern SafeProcess2Handle Create();

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Process2_Destroy")]
        internal static extern MyLibStatus Destroy(IntPtr handle);

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_Process2_As_NumberProcessor")]
        private static extern IntPtr As_NumberProcessor_Internal(
            SafeProcess2Handle handle
        );

        internal static SafeNumberProcessorHandle As_NumberProcessor(SafeProcess2Handle handle)
        {
            return SafeNumberProcessorHandle.AsReference(As_NumberProcessor_Internal(handle));
        }
    }
}
