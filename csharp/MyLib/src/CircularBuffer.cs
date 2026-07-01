using System;
using MyLib.Interop;
using MyLib.Interop.Handles;

namespace MyLib
{
    /// <summary>
    /// Circular buffer - bindings from C wrapper to C++ class
    /// </summary>
    public sealed class CircularBuffer : IDisposable
    {
        private readonly SafeCircularBufferHandle _handle;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="bufsize">Buffer size</param>
        /// <exception cref="OutOfMemoryException"></exception>
        public CircularBuffer(int bufsize)
        {
            _handle = CircularBufferNative.Create(bufsize);
            if (_handle.IsInvalid)
                throw new OutOfMemoryException("Failed to create circular buffer.");
        }

        /// <summary>
        /// Get the number of elements inside the buffer
        /// </summary>
        /// <returns>The number of elements inside the buffer</returns>
        public int GetLength()
        {
            ThrowIfDisposed();
            var status = CircularBufferNative.GetLength(_handle, out int returned_length);
            status.ThrowIfError();
            return returned_length;
        }

        /// <summary>
        /// Put data into buffer
        /// </summary>
        /// <param name="data">Data to put</param>
        /// <returns>Number of inserted bytes</returns>
        public int Put(byte[] data)
        {
            ThrowIfDisposed();
            var status = CircularBufferNative.Put(_handle, data, data.Length, out int returned_length);
            status.ThrowIfError();
            return returned_length;
        }

        /// <summary>
        /// Put data into buffer
        /// </summary>
        /// <param name="data">Data to put</param>
        /// <param name="length">Length of data to put</param>
        /// <returns>Number of inserted bytes</returns>
        public int Put(byte[] data, int length)
        {
            ThrowIfDisposed();
            var status = CircularBufferNative.Put(_handle, data, length, out int returned_length);
            status.ThrowIfError();
            return returned_length;
        }

        /// <summary>
        /// Get data from buffer
        /// </summary>
        /// <param name="length">Data length to get</param>
        /// <returns>Data from buffer</returns>
        public byte[] Get(int length)
        {
            ThrowIfDisposed();
            byte[] dest = new byte[length];
            var status = CircularBufferNative.Get(_handle, dest, length, out int returned_length);
            status.ThrowIfError();
            return dest[..returned_length];
        }

        /// <summary>
        /// Clean up the buffer
        /// </summary>
        /// <returns>Number of items cleaned</returns>
        public int Clean()
        {
            ThrowIfDisposed();
            var status = CircularBufferNative.Clean(_handle, out int returned_length);
            status.ThrowIfError();
            return returned_length;
        }

        public void Dispose()
        {
            _handle.Dispose();
        }

        private void ThrowIfDisposed()
        {
            if (_handle.IsClosed)
                throw new ObjectDisposedException(nameof(CircularBuffer));
        }
    }
}
