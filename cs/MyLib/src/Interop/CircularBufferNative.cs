using System;
using System.Runtime.InteropServices;
using MyLib.Interop.Handles;

namespace MyLib.Interop
{
    internal static class CircularBufferNative
    {
        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_CircularBuffer_Create")]
        internal static extern SafeCircularBufferHandle Create(int bufsize);

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_CircularBuffer_Destroy")]
        internal static extern MyLibStatus Destroy(IntPtr handle);

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_CircularBuffer_GetLength")]
        internal static extern MyLibStatus GetLength(
            SafeCircularBufferHandle handle,
            out int returned_length
        );

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_CircularBuffer_Put")]
        internal static extern MyLibStatus Put(
            SafeCircularBufferHandle handle,
            byte[] data,
            int length,
            out int returned_length
        );

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_CircularBuffer_Get")]
        internal static extern MyLibStatus Get(
            SafeCircularBufferHandle handle,
            byte[] dest,
            int length,
            out int returned_length
        );

        [DllImport(
            NativeConstants.LibraryName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "MyLib_CircularBuffer_Clean")]
        internal static extern MyLibStatus Clean(
            SafeCircularBufferHandle handle,
            out int returned_length
        );
    }
}
