using System;
using System.ComponentModel.Design;
using System.Text;
using MyLib.Interop;
using MyLib.Interop.Handles;

namespace MyLib
{
    public class Tiger : Cat
    {
        private SafeTigerHandle _handleTiger;

        public Tiger()
        {
            _handleTiger = TigerNative.Create();
            if (_handleTiger.IsInvalid)
                throw new OutOfMemoryException("Failed to create tiger.");
            base.InitializeCatHandle(TigerNative.As_Animal(_handleTiger));
        }

        public Tiger(string name)
        {
            _handleTiger = TigerNative.Create_With_Name(Encoding.UTF8.GetBytes(name), name.Length);
            if (_handleTiger.IsInvalid)
                throw new OutOfMemoryException("Failed to create tiger.");
            base.InitializeCatHandle(TigerNative.As_Animal(_handleTiger));
        }

        private protected void InitializeTigerHandle(SafeTigerHandle handle)
        {
            _handleTiger = handle;
            base.InitializeCatHandle(TigerNative.As_Animal(_handleTiger));
        }

        public void Hunt()
        {
            ThrowIfDisposed();
            var status = TigerNative.Hunt(_handleTiger);
            status.ThrowIfError();
        }

        public int GetHunger()
        {
            ThrowIfDisposed();
            var status = TigerNative.GetHunger(_handleTiger, out int hunger);
            status.ThrowIfError();
            return hunger;
        }

        public override void Speak()
        {
            ThrowIfDisposed();
            var status = TigerNative.Speak(_handleTiger);
            status.ThrowIfError();
        }

        public override void Sleep()
        {
            ThrowIfDisposed();
            var status = TigerNative.Sleep(_handleTiger);
            status.ThrowIfError();
        }

        public override void Dispose()
        {
            _handleTiger.Dispose();
        }

        private void ThrowIfDisposed()
        {
            if (_handleTiger.IsClosed)
                throw new ObjectDisposedException(nameof(Tiger));
        }
    }
}
