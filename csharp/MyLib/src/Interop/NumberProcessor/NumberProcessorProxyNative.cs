using System;
using System.Runtime.InteropServices;
using MyLib.Interop.Handles;

namespace MyLib.Interop
{
    internal static class NumberProcessorProxyNative
    {
        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_NumberProcessorProxy_Create")]
        internal static extern SafeNumberProcessorProxyHandle Create(ref NumberProcessorProxyCallbacks callbacks);

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_NumberProcessorProxy_Destroy")]
        internal static extern MyLibStatus Destroy(IntPtr handle);

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_NumberProcessorProxy_As_NumberProcessor")]
        private static extern IntPtr As_NumberProcessor_Internal(SafeNumberProcessorProxyHandle handle);

        internal static SafeNumberProcessorHandle As_NumberProcessor(SafeNumberProcessorProxyHandle handle)
        {
            return SafeNumberProcessorHandle.AsReference(As_NumberProcessor_Internal(handle));
        }

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_NumberProcessorProxy_From_NumberProcessor")]
        private static extern IntPtr From_NumberProcessor_Internal(SafeNumberProcessorHandle handle, NumberProcessorProxyCallbacks callbacks);

        internal static SafeNumberProcessorProxyHandle From_NumberProcessor(SafeNumberProcessorHandle handle, NumberProcessorProxyCallbacks callbacks)
        {
            return SafeNumberProcessorProxyHandle.AsReference(From_NumberProcessor_Internal(handle, callbacks));
        }

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_NumberProcessorProxy_CallBase_PrintNumber")]
        internal static extern MyLibStatus Base_PrintNumber(
            SafeNumberProcessorProxyHandle handle
        );

        // ----- callbacks ----- //
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        internal delegate void ProcessCallback(IntPtr handle);
        
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        internal delegate void PrintNumberCallback(IntPtr handle);


        [StructLayout(LayoutKind.Sequential)]
        public struct NumberProcessorProxyCallbacks
        {
            public ProcessCallback Process;
            public PrintNumberCallback PrintNumber;
        }
    }
}
