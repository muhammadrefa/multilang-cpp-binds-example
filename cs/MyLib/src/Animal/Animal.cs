using System;
using System.Text;
using MyLib.Interop;
using MyLib.Interop.Handles;

namespace MyLib
{
    public class Animal : IDisposable
    {
        private SafeAnimalHandle _handleAnimal;

        public Animal()
        {
            _handleAnimal = AnimalNative.Create();
            if (_handleAnimal.IsInvalid)
                throw new OutOfMemoryException("Failed to create animal.");
        }

        public Animal(string name)
        {
            _handleAnimal = AnimalNative.Create_With_Name(Encoding.UTF8.GetBytes(name), name.Length);
            if (_handleAnimal.IsInvalid)
                throw new OutOfMemoryException("Failed to create animal.");
        }

        private protected void InitializeAnimalHandle(SafeAnimalHandle handle)
        {
            _handleAnimal = handle;
        }

        public string Name
        {
            get
            {
                ThrowIfDisposed();
                byte[] _name = new byte[100];
                var status = AnimalNative.Get_Name(_handleAnimal, _name, 100, out int length);
                status.ThrowIfError();
                return Encoding.UTF8.GetString(_name);
            }
            set
            {
                ThrowIfDisposed();
                byte[] _name = Encoding.UTF8.GetBytes(value);
                var status = AnimalNative.Set_Name(_handleAnimal, _name, _name.Length);
                status.ThrowIfError();
            }
        }

        public virtual void Speak()
        {
            ThrowIfDisposed();
            var status = AnimalNative.Speak(_handleAnimal);
            status.ThrowIfError();
        }

        public void Speak(int times)
        {
            ThrowIfDisposed();
            var status = AnimalNative.Speak_Multiple_Times(_handleAnimal, times);
            status.ThrowIfError();
        }

        public virtual void Sleep()
        {
            ThrowIfDisposed();
            var status = AnimalNative.Sleep(_handleAnimal);
            status.ThrowIfError();
        }

        public virtual void Dispose()
        {
            _handleAnimal.Dispose();
        }

        private void ThrowIfDisposed()
        {
            if (_handleAnimal.IsClosed)
                throw new ObjectDisposedException(nameof(Animal));
        }
    }
}
