using System;
using System.Text;
using MyLib.Interop;
using MyLib.Interop.Handles;

namespace MyLib
{
    /// <summary>
    /// Animal - bindings from C wrapper to C++ class
    /// </summary>
    public class Animal : IDisposable
    {
        private readonly SafeAnimalHandle handle;

        /// <summary>
        /// Create new Animal
        /// </summary>
        public Animal() : this(CreateHandle())
        {
        }

        /// <summary>
        /// Create new Animal
        /// </summary>
        /// <param name="name">Animal name</param>
        public Animal(string name) : this(CreateHandle(name))
        {
        }

        /// <summary>
        /// Create Animal by passing the handle
        /// Used by its derivatives to set the handle for Animal
        /// </summary>
        /// <param name="handle">Animal handle which does not owns handle</param>
        private protected Animal(SafeAnimalHandle handle)
        {
            this.handle = handle;
        }

        /// <summary>
        /// Calls the native code to create new Animal
        /// Used by the constructor
        /// </summary>
        /// <returns>Animal handle</returns>
        /// <exception cref="OutOfMemoryException"></exception>
        private static SafeAnimalHandle CreateHandle()
        {
            SafeAnimalHandle handle = AnimalNative.Create();
            if (handle.IsInvalid)
                throw new OutOfMemoryException("Failed to create animal.");
            return handle;
        }

        /// <summary>
        /// Calls the native code to create new Animal
        /// Used by the constructor
        /// </summary>
        /// <param name="name">Animal name</param>
        /// <returns>Animal handle</returns>
        /// <exception cref="OutOfMemoryException"></exception>
        private static SafeAnimalHandle CreateHandle(string name)
        {
            SafeAnimalHandle handle = AnimalNative.Create_With_Name(Encoding.UTF8.GetBytes(name), name.Length);
            if (handle.IsInvalid)
                throw new OutOfMemoryException("Failed to create animal.");
            return handle;
        }

        /// <summary>
        /// Animal name
        /// </summary>
        public string Name
        {
            get
            {
                ThrowIfDisposed();
                byte[] _name = new byte[100];
                var status = AnimalNative.Get_Name(handle, _name, 100, out int length);
                status.ThrowIfError();
                return Encoding.UTF8.GetString(_name);
            }
            set
            {
                ThrowIfDisposed();
                byte[] _name = Encoding.UTF8.GetBytes(value);
                var status = AnimalNative.Set_Name(handle, _name, _name.Length);
                status.ThrowIfError();
            }
        }

        public virtual void Speak()
        {
            ThrowIfDisposed();
            var status = AnimalNative.Speak(handle);
            status.ThrowIfError();
        }

        public void Speak(int times)
        {
            ThrowIfDisposed();
            var status = AnimalNative.Speak_Multiple_Times(handle, times);
            status.ThrowIfError();
        }

        public virtual void Sleep()
        {
            ThrowIfDisposed();
            var status = AnimalNative.Sleep(handle);
            status.ThrowIfError();
        }

        public virtual void Dispose()
        {
            handle.Dispose();
        }

        private void ThrowIfDisposed()
        {
            if (handle.IsClosed)
                throw new ObjectDisposedException(nameof(Animal));
        }
    }
}
