using System;
using System.ComponentModel.Design;
using System.Text;
using MyLib.Interop;
using MyLib.Interop.Handles;

namespace MyLib
{
    public class Process2 : NumberProcessor
    {
        private SafeProcess2Handle handle;

        public Process2() : this(CreateHandle())
        {
        }

        private protected Process2(SafeProcess2Handle handle): base(Process2Native.As_NumberProcessor(handle))
        {
            this.handle = handle;
        }

        private static SafeProcess2Handle CreateHandle()
        {
            SafeProcess2Handle handle = Process2Native.Create();
            if (handle.IsInvalid)
                throw new OutOfMemoryException("Failed to create cat.");
            return handle;
        }

        internal new SafeProcess2Handle GetHandle()
        {
            return handle;
        }

        public override void Process()
        {
            ThrowIfDisposed();
            // var status = NumberProcessorNative.Process(Process2Native.As_NumberProcessor(handle));
            var status = NumberProcessorNative.Process(((NumberProcessor)this).GetHandle());
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
