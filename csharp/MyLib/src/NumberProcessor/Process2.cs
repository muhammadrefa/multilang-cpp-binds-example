using System;
using System.ComponentModel.Design;
using System.Text;
using MyLib.Interop;
using MyLib.Interop.Handles;

namespace MyLib
{
    /// <summary>
    /// Cat - bindings from C wrapper to C++ class
    /// </summary>
    public class Process2 : NumberProcessor
    {
        private SafeProcess2Handle handle;

        /// <summary>
        /// Create new Cat
        /// </summary>
        public Process2() : this(CreateHandle())
        {
        }

        /// <summary>
        /// Create Cat by passing the handle
        /// Used by its derivatives to set the handle for Cat
        /// </summary>
        /// <param name="handle">Cat handle which does not owns handle</param>
        private protected Process2(SafeProcess2Handle handle): base(Process2Native.As_NumberProcessor(handle))
        {
            this.handle = handle;
        }

        /// <summary>
        /// Calls the native code to create new Cat
        /// Used by the constructor
        /// </summary>
        /// <returns>Cat handle</returns>
        /// <exception cref="OutOfMemoryException"></exception>
        private static SafeProcess2Handle CreateHandle()
        {
            SafeProcess2Handle handle = Process2Native.Create();
            if (handle.IsInvalid)
                throw new OutOfMemoryException("Failed to create cat.");
            return handle;
        }

        public override void Process()
        {
            ThrowIfDisposed();
            var status = NumberProcessorNative.Process(Process2Native.As_NumberProcessor(handle));
            status.ThrowIfError();
        }

        public override void Dispose()
        {
            handle.Dispose();
        }

        private void ThrowIfDisposed()
        {
            if (handle.IsClosed)
                throw new ObjectDisposedException(nameof(Process2));
        }
    }
}
