using System;
using MyLib.Interop;
using MyLib.Interop.Handles;

namespace MyLib
{
    public sealed class CircularBuffer : IDisposable
    {
        private readonly SafeCircularBufferHandle _handle;

        public CircularBuffer(int bufsize)
        {
            _handle = CircularBufferNative.Create(bufsize);
            if (_handle.IsInvalid)
                throw new OutOfMemoryException("Failed to create circular buffer.");
        }

        public int GetLength()
        {
            ThrowIfDisposed();
            var status = CircularBufferNative.GetLength(_handle, out int returned_length);
            status.ThrowIfError();
            return returned_length;
        }

        public int Put(byte[] data)
        {
            ThrowIfDisposed();
            var status = CircularBufferNative.Put(_handle, data, data.Length, out int returned_length);
            status.ThrowIfError();
            return returned_length;
        }

        public int Put(byte[] data, int length)
        {
            ThrowIfDisposed();
            var status = CircularBufferNative.Put(_handle, data, length, out int returned_length);
            status.ThrowIfError();
            return returned_length;
        }

        public byte[] Get(int length)
        {
            ThrowIfDisposed();
            byte[] dest = new byte[length];
            var status = CircularBufferNative.Get(_handle, dest, length, out int returned_length);
            status.ThrowIfError();
            return dest[..returned_length];
        }

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
