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
    public class Cat : Animal
    {
        private SafeCatHandle handle;

        /// <summary>
        /// Create new Cat
        /// </summary>
        public Cat() : this(CreateHandle())
        {
        }

        /// <summary>
        /// Create new Cat
        /// </summary>
        /// <param name="name">Cat name</param>
        public Cat(string name) : this(CreateHandle(name))
        {
        }

        /// <summary>
        /// Create Cat by passing the handle
        /// Used by its derivatives to set the handle for Cat
        /// </summary>
        /// <param name="handle">Cat handle which does not owns handle</param>
        private protected Cat(SafeCatHandle handle): base(CatNative.As_Animal(handle))
        {
            this.handle = handle;
        }

        /// <summary>
        /// Calls the native code to create new Cat
        /// Used by the constructor
        /// </summary>
        /// <returns>Cat handle</returns>
        /// <exception cref="OutOfMemoryException"></exception>
        private static SafeCatHandle CreateHandle()
        {
            SafeCatHandle handle = CatNative.Create();
            if (handle.IsInvalid)
                throw new OutOfMemoryException("Failed to create cat.");
            return handle;
        }

        /// <summary>
        /// Calls the native code to create new Cat
        /// Used by the constructor
        /// </summary>
        /// <param name="name">Cat name</param>
        /// <returns>Cat handle</returns>
        /// <exception cref="OutOfMemoryException"></exception>
        private static SafeCatHandle CreateHandle(string name)
        {
            SafeCatHandle handle = CatNative.Create_With_Name(Encoding.UTF8.GetBytes(name), name.Length);
            if (handle.IsInvalid)
                throw new OutOfMemoryException("Failed to create cat.");
            return handle;
        }

        /// <summary>
        /// Fight!
        /// </summary>
        /// <param name="bigger_cat">Is the challenger cat bigger?</param>
        /// <returns></returns>
        public bool Fight(bool bigger_cat)
        {
            ThrowIfDisposed();
            int bigger_cat_int = bigger_cat ? 1 : 0;
            var status = CatNative.Fight(handle, bigger_cat_int, out int success_int);
            status.ThrowIfError();
            bool success = success_int != 0;
            return success;
        }

        /// <summary>
        /// Is the cat still alive?
        /// </summary>
        /// <returns>Is alive</returns>
        public bool StillAlive()
        {
            ThrowIfDisposed();
            var status = CatNative.StillAlive(handle, out int is_alive_int);
            status.ThrowIfError();
            bool is_alive = is_alive_int != 0;
            return is_alive;
        }

        public override void Speak()
        {
            ThrowIfDisposed();
            var status = CatNative.Speak(handle);
            status.ThrowIfError();
        }

        public override void Dispose()
        {
            handle.Dispose();
        }

        private void ThrowIfDisposed()
        {
            if (handle.IsClosed)
                throw new ObjectDisposedException(nameof(Cat));
        }
    }
}
