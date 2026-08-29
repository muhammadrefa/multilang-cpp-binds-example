using System;
using System.ComponentModel.Design;
using System.Text;
using MyLib.Interop;
using MyLib.Interop.Handles;

namespace MyLib
{
    public class ProcessAdd2 : NumberProcessor
    {
        private SafeProcessAdd2Handle handle;

        public ProcessAdd2() : this(CreateHandle())
        {
        }

        private protected ProcessAdd2(SafeProcessAdd2Handle handle): base(ProcessAdd2Native.As_NumberProcessor(handle))
        {
            this.handle = handle;
        }

        private static SafeProcessAdd2Handle CreateHandle()
        {
            SafeProcessAdd2Handle handle = ProcessAdd2Native.Create();
            if (handle.IsInvalid)
                throw new OutOfMemoryException("Failed to create cat.");
            return handle;
        }

        public static ProcessAdd2 FromBase(NumberProcessor numberProcessor)
        {
            return new ProcessAdd2(ProcessAdd2Native.From_NumberProcessor(numberProcessor.GetHandle()));
        }

        internal new SafeProcessAdd2Handle GetHandle()
        {
            return handle;
        }

        public override void Process()
        {
            ThrowIfDisposed();
            // var status = NumberProcessorNative.Process(ProcessAdd2Native.As_NumberProcessor(handle));
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
                throw new ObjectDisposedException(nameof(ProcessAdd2));
        }
    }

    public static class ProcessAdd2Extensions
    {
        public static ProcessAdd2 ToProcessAdd2(this NumberProcessor numberProcessor)
        {
            return ProcessAdd2.FromBase(numberProcessor);
        }
    }
}
