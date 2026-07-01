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
        private SafeCatHandle _handleCat;

        /// <summary>
        /// Create new Cat
        /// </summary>
        /// <exception cref="OutOfMemoryException"></exception>
        public Cat()
        {
            _handleCat = CatNative.Create();
            if (_handleCat.IsInvalid)
                throw new OutOfMemoryException("Failed to create cat.");
            base.InitializeAnimalHandle(CatNative.As_Animal(_handleCat));
        }

        /// <summary>
        /// Create new Cat
        /// </summary>
        /// <param name="name">Cat name</param>
        /// <exception cref="OutOfMemoryException"></exception>
        public Cat(string name)
        {
            _handleCat = CatNative.Create_With_Name(Encoding.UTF8.GetBytes(name), name.Length);
            if (_handleCat.IsInvalid)
                throw new OutOfMemoryException("Failed to create cat.");
            base.InitializeAnimalHandle(CatNative.As_Animal(_handleCat));
        }

        /// <summary>
        /// Initialise handle from its derivative
        /// </summary>
        /// <param name="handle">Cat handle</param>
        private protected void InitializeCatHandle(SafeCatHandle handle)
        {
            _handleCat = handle;
            base.InitializeAnimalHandle(CatNative.As_Animal(_handleCat));
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
            var status = CatNative.Fight(_handleCat, bigger_cat_int, out int success_int);
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
            var status = CatNative.StillAlive(_handleCat, out int is_alive_int);
            status.ThrowIfError();
            bool is_alive = is_alive_int != 0;
            return is_alive;
        }

        public override void Speak()
        {
            ThrowIfDisposed();
            var status = CatNative.Speak(_handleCat);
            status.ThrowIfError();
        }

        public override void Dispose()
        {
            _handleCat.Dispose();
        }

        private void ThrowIfDisposed()
        {
            if (_handleCat.IsClosed)
                throw new ObjectDisposedException(nameof(Cat));
        }
    }
}
