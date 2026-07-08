using System;
using System.Runtime.InteropServices;

namespace MyLib.Interop.Handles
{
    internal class SafeAnimalHandle : SafeHandle
    {
        public override bool IsInvalid => handle == IntPtr.Zero;

        private protected SafeAnimalHandle() : base(IntPtr.Zero, ownsHandle: true) { }
        private protected SafeAnimalHandle(bool ownsHandle) : base(IntPtr.Zero, ownsHandle) { }

        internal static SafeAnimalHandle AsReference(IntPtr ptr)
        {
            var handle = new SafeAnimalHandle(false);
            handle.SetHandle(ptr);
            return handle;
        }

        protected override bool ReleaseHandle()
        {
            return AnimalNative.Destroy(handle) == MyLibStatus.Ok;
        }
    }

    internal class SafeDogHandle : SafeAnimalHandle
    {

        private protected SafeDogHandle() : base() { }
        private protected SafeDogHandle(bool ownsHandle) : base(ownsHandle) { }

        internal new static SafeDogHandle AsReference(IntPtr ptr)
        {
            var handle = new SafeDogHandle(false);
            handle.SetHandle(ptr);
            return handle;
        }

        protected override bool ReleaseHandle()
        {
            return DogNative.Destroy(handle) == MyLibStatus.Ok;
        }
    }

    internal class SafeCatHandle : SafeAnimalHandle
    {
        public override bool IsInvalid => handle == IntPtr.Zero;

        private protected SafeCatHandle() : base() { }
        private protected SafeCatHandle(bool ownsHandle) : base(ownsHandle) { }

        internal new static SafeCatHandle AsReference(IntPtr ptr)
        {
            var handle = new SafeCatHandle(false);
            handle.SetHandle(ptr);
            return handle;
        }

        protected override bool ReleaseHandle()
        {
            return CatNative.Destroy(handle) == MyLibStatus.Ok;
        }
    }

    internal class SafeTigerHandle : SafeAnimalHandle
    {
        public override bool IsInvalid => handle == IntPtr.Zero;

        private protected SafeTigerHandle() : base() { }
        private protected SafeTigerHandle(bool ownsHandle) : base(ownsHandle) { }

        internal new static SafeTigerHandle AsReference(IntPtr ptr)
        {
            var handle = new SafeTigerHandle(false);
            handle.SetHandle(ptr);
            return handle;
        }

        protected override bool ReleaseHandle()
        {
            return TigerNative.Destroy(handle) == MyLibStatus.Ok;
        }
    }
}
