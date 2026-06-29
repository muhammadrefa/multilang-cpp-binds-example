using System;
using MyLib.Interop;
using MyLib.Interop.Handles;

namespace MyLib
{
    public sealed class Calculator : IDisposable
    {
        private readonly SafeCalculatorHandle _handle;

        public Calculator()
        {
            _handle = CalculatorNative.Create();
            if (_handle.IsInvalid)
                throw new OutOfMemoryException("Failed to create calculator.");
        }

        public int Add(int a, int b)
        {
            ThrowIfDisposed();
            var status = CalculatorNative.Add(_handle, a, b, out int result);
            status.ThrowIfError();
            return result;
        }

        public int Sub(int a, int b)
        {
            ThrowIfDisposed();
            var status = CalculatorNative.Sub(_handle, a, b, out int result);
            status.ThrowIfError();
            return result;
        }

        public int CntOpsDone()
        {
            ThrowIfDisposed();
            var status = CalculatorNative.CntOpsDone(_handle, out int result);
            status.ThrowIfError();
            return result;
        }

        public int ResetCounter()
        {
            ThrowIfDisposed();
            var status = CalculatorNative.ResetCounter(_handle, out int result);
            status.ThrowIfError();
            return result;
        }

        public void Dispose()
        {
            _handle.Dispose();
        }

        private void ThrowIfDisposed()
        {
            if (_handle.IsClosed)
                throw new ObjectDisposedException(nameof(Calculator));
        }
    }
}
