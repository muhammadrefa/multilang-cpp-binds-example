using System;
using System.Runtime.InteropServices;
using MyLib.Interop.Handles;

namespace MyLib.Interop
{
    internal static class ProcessAdd2Native
    {
        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_ProcessAdd2_Create")]
        internal static extern SafeProcessAdd2Handle Create();

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_ProcessAdd2_Destroy")]
        internal static extern MyLibStatus Destroy(IntPtr handle);

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_ProcessAdd2_As_NumberProcessor")]
        private static extern IntPtr As_NumberProcessor_Internal(
            SafeProcessAdd2Handle handle
        );

        internal static SafeNumberProcessorHandle As_NumberProcessor(SafeProcessAdd2Handle handle)
        {
            return SafeNumberProcessorHandle.AsReference(As_NumberProcessor_Internal(handle));
        }
    }
}
