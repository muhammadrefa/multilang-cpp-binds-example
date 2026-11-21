using System;
using System.Text;
using MyLib.Interop;
using MyLib.Interop.Handles;

namespace MyLib
{
    public abstract class NumberProcessor : IDisposable
    {
        private readonly SafeNumberProcessorHandle handle;

        private protected NumberProcessor(SafeNumberProcessorHandle handle)
        {
            this.handle = handle;
        }

        internal SafeNumberProcessorHandle GetHandle()
        {
            return handle;
        }

        public abstract void Process();

        public void SetNumber(int number)
        {
            ThrowIfDisposed();
            var status = NumberProcessorNative.SetNumber(handle, number);
            status.ThrowIfError();
        }

        public virtual int GetNumber()
        {
            ThrowIfDisposed();
            var status = NumberProcessorNative.GetNumber(handle, out int number);
            status.ThrowIfError();
            return number;
        }

        public virtual void PrintNumber()
        {
            ThrowIfDisposed();
            var status = NumberProcessorNative.PrintNumber(handle);
            status.ThrowIfError();
        }

        public virtual void Dispose()
        {
            handle.Dispose();
        }

        private void ThrowIfDisposed()
        {
            if (handle.IsClosed)
                throw new ObjectDisposedException(nameof(NumberProcessor));
        }
    }
}
