using System;
using MyLib.Interop;
using MyLib.Interop.Handles;

namespace MyLib
{
    /// <summary>
    /// Calculator - bindings for C wrapper to C++ class
    /// </summary>
    public sealed class Calculator : IDisposable
    {
        private readonly SafeCalculatorHandle _handle;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <exception cref="OutOfMemoryException">Thrown when the object cannot be created because of memory full</exception>
        public Calculator()
        {
            _handle = CalculatorNative.Create();
            if (_handle.IsInvalid)
                throw new OutOfMemoryException("Failed to create calculator.");
        }

        /// <summary>
        /// Do addition
        /// </summary>
        /// <param name="a">First number</param>
        /// <param name="b">Second number</param>
        /// <returns>Result of <paramref name="a"/> + <paramref name="b"/></returns>
        public int Add(int a, int b)
        {
            ThrowIfDisposed();
            var status = CalculatorNative.Add(_handle, a, b, out int result);
            status.ThrowIfError();
            return result;
        }

        /// <summary>
        /// Do subtraction
        /// </summary>
        /// <param name="a">First number</param>
        /// <param name="b">Second number</param>
        /// <returns>Result of <paramref name="a"/> - <paramref name="b"/></returns>
        public int Sub(int a, int b)
        {
            ThrowIfDisposed();
            var status = CalculatorNative.Sub(_handle, a, b, out int result);
            status.ThrowIfError();
            return result;
        }

        /// <summary>
        /// Counter for the number of operations done
        /// </summary>
        /// <returns>How many operations done</returns>
        public int CntOpsDone()
        {
            ThrowIfDisposed();
            var status = CalculatorNative.CntOpsDone(_handle, out int result);
            status.ThrowIfError();
            return result;
        }

        /// <summary>
        /// Reset the counter
        /// </summary>
        /// <returns>Last counter value</returns>
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
