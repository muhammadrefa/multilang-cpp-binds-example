using System;
using System.ComponentModel.Design;
using System.Text;
using MyLib.Interop;
using MyLib.Interop.Handles;

namespace MyLib
{
    public class Dog : Animal
    {
        private SafeDogHandle _handleDog;

        public Dog()
        {
            _handleDog = DogNative.Create();
            if (_handleDog.IsInvalid)
                throw new OutOfMemoryException("Failed to create dog.");
            base.InitializeAnimalHandle(DogNative.As_Animal(_handleDog));
        }

        public Dog(string name)
        {
            _handleDog = DogNative.Create_With_Name(Encoding.UTF8.GetBytes(name), name.Length);
            if (_handleDog.IsInvalid)
                throw new OutOfMemoryException("Failed to create cat.");
            base.InitializeAnimalHandle(DogNative.As_Animal(_handleDog));
        }

        private protected void InitializeDogHandle(SafeDogHandle handle)
        {
            _handleDog = handle;
            base.InitializeAnimalHandle(DogNative.As_Animal(_handleDog));
        }

        public bool Fetch()
        {
            ThrowIfDisposed();
            var status = DogNative.Fetch(_handleDog, out int success_int);
            status.ThrowIfError();
            bool success = success_int != 0;
            return success;
        }

        public int GetEnergy()
        {
            ThrowIfDisposed();
            var status = DogNative.GetEnergy(_handleDog, out int energy);
            status.ThrowIfError();
            return energy;
        }

        public override void Speak()
        {
            ThrowIfDisposed();
            var status = DogNative.Speak(_handleDog);
            status.ThrowIfError();
        }

        public override void Sleep()
        {
            ThrowIfDisposed();
            var status = DogNative.Sleep(_handleDog);
            status.ThrowIfError();
        }

        public override void Dispose()
        {
            _handleDog.Dispose();
        }

        private void ThrowIfDisposed()
        {
            if (_handleDog.IsClosed)
                throw new ObjectDisposedException(nameof(Dog));
        }
    }
}
