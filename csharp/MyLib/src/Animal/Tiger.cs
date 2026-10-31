using System;
using System.ComponentModel.Design;
using System.Text;
using MyLib.Interop;
using MyLib.Interop.Handles;

namespace MyLib
{
    /// <summary>
    /// Tiger - bindings from C wrapper to C++ class
    /// </summary>
    public class Tiger : Cat
    {
        private SafeTigerHandle handle;

        /// <summary>
        /// Create new Tiger
        /// </summary>
        public Tiger() : this(CreateHandle())
        {
        }

        /// <summary>
        /// Create new Tiger
        /// </summary>
        /// <param name="name">Tiger name</param>
        public Tiger(string name) : this(CreateHandle(name))
        {
        }

        /// <summary>
        /// Create Tiger by passing the handle
        /// Used by its derivatives to set the handle for Tiger
        /// </summary>
        /// <param name="handle">Tiger handle which does not owns handle</param>
        private protected Tiger(SafeTigerHandle handle): base(TigerNative.As_Cat(handle))
        {
            this.handle = handle;
        }

        /// <summary>
        /// Calls the native code to create new Tiger
        /// Used by the constructor
        /// </summary>
        /// <returns>Tiger handle</returns>
        /// <exception cref="OutOfMemoryException"></exception>
        private static SafeTigerHandle CreateHandle()
        {
            SafeTigerHandle handle = TigerNative.Create();
            if (handle.IsInvalid)
                throw new OutOfMemoryException("Failed to create cat.");
            return handle;
        }

        /// <summary>
        /// Calls the native code to create new Tiger
        /// Used by the constructor
        /// </summary>
        /// <param name="name">Tiger name</param>
        /// <returns>Tiger handle</returns>
        /// <exception cref="OutOfMemoryException"></exception>
        private static SafeTigerHandle CreateHandle(string name)
        {
            SafeTigerHandle handle = TigerNative.Create_With_Name(Encoding.UTF8.GetBytes(name), name.Length);
            if (handle.IsInvalid)
                throw new OutOfMemoryException("Failed to create cat.");
            return handle;
        }

        /// <summary>
        /// Hunt!
        /// </summary>
        public void Hunt()
        {
            ThrowIfDisposed();
            var status = TigerNative.Hunt(handle);
            status.ThrowIfError();
        }

        /// <summary>
        /// Get hunger level
        /// </summary>
        /// <returns>Hunger level</returns>
        public int GetHunger()
        {
            ThrowIfDisposed();
            var status = TigerNative.GetHunger(handle, out int hunger);
            status.ThrowIfError();
            return hunger;
        }

        public override void Dispose()
        {
            handle.Dispose();
            base.Dispose();
        }

        private void ThrowIfDisposed()
        {
            if (handle.IsClosed)
                throw new ObjectDisposedException(nameof(Tiger));
        }
    }
}
