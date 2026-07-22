using System;
using System.ComponentModel;
using System.ComponentModel.Design;
using System.Text;
using MyLib.Interop;
using MyLib.Interop.Handles;

namespace MyLib
{
    /// <summary>
    /// Dog - bindings from C wrapper to C++ class
    /// </summary>
    public class Dog : Animal
    {
        private readonly SafeDogHandle handle;

        /// <summary>
        /// Create new Dog
        /// </summary>
        public Dog() : this(CreateHandle())
        {
        }

        /// <summary>
        /// Create new Dog
        /// </summary>
        /// <param name="name">Dog name</param>
        public Dog(string name) : this(CreateHandle(name))
        {
        }

        /// <summary>
        /// Create Dog by passing the handle
        /// Used by its derivatives to set the handle for Dog
        /// </summary>
        /// <param name="handle">Dog handle which does not owns handle</param>
        private protected Dog(SafeDogHandle handle): base(DogNative.As_Animal(handle))
        {
            this.handle = handle;
        }

        /// <summary>
        /// Calls the native code to create new Dog
        /// Used by the constructor
        /// </summary>
        /// <returns>Dog handle</returns>
        /// <exception cref="OutOfMemoryException"></exception>
        private static SafeDogHandle CreateHandle()
        {
            SafeDogHandle handle = DogNative.Create();
            if (handle.IsInvalid)
                throw new OutOfMemoryException("Failed to create dog.");
            return handle;
        }

        /// <summary>
        /// Calls the native code to create new Dog
        /// Used by the constructor
        /// </summary>
        /// <param name="name">Dog name</param>
        /// <returns>Dog handle</returns>
        /// <exception cref="OutOfMemoryException"></exception>
        private static SafeDogHandle CreateHandle(string name)
        {
            SafeDogHandle handle = DogNative.Create_With_Name(Encoding.UTF8.GetBytes(name), name.Length);
            if (handle.IsInvalid)
                throw new OutOfMemoryException("Failed to create dog.");
            return handle;
        }

        /// <summary>
        /// Fetch!
        /// </summary>
        /// <returns>Fetch result</returns>
        public bool Fetch()
        {
            ThrowIfDisposed();
            var status = DogNative.Fetch(handle, out int success_int);
            status.ThrowIfError();
            bool success = success_int != 0;
            return success;
        }

        /// <summary>
        /// Get energy
        /// </summary>
        /// <returns>Energy</returns>
        public int GetEnergy()
        {
            ThrowIfDisposed();
            var status = DogNative.GetEnergy(handle, out int energy);
            status.ThrowIfError();
            return energy;
        }

        public override void Dispose()
        {
            handle.Dispose();
        }

        private void ThrowIfDisposed()
        {
            if (handle.IsClosed)
                throw new ObjectDisposedException(nameof(Dog));
        }
    }
}
