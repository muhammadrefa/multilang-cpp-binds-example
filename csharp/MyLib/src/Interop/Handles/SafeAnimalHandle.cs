using System;
using System.Runtime.InteropServices;

namespace MyLib.Interop.Handles
{
    internal sealed class SafeAnimalHandle : SafeHandle
    {
        public override bool IsInvalid => handle == IntPtr.Zero;

        private SafeAnimalHandle() : base(IntPtr.Zero, ownsHandle: true) { }

        protected override bool ReleaseHandle()
        {
            return AnimalNative.Destroy(handle) == MyLibStatus.Ok;
        }
    }

    internal sealed class SafeDogHandle : SafeHandle
    {
        public override bool IsInvalid => handle == IntPtr.Zero;

        private SafeDogHandle() : base(IntPtr.Zero, ownsHandle: true) { }

        protected override bool ReleaseHandle()
        {
            return DogNative.Destroy(handle) == MyLibStatus.Ok;
        }
    }

    internal sealed class SafeCatHandle : SafeHandle
    {
        public override bool IsInvalid => handle == IntPtr.Zero;

        private SafeCatHandle() : base(IntPtr.Zero, ownsHandle: true) { }

        protected override bool ReleaseHandle()
        {
            return CatNative.Destroy(handle) == MyLibStatus.Ok;
        }
    }

    internal sealed class SafeTigerHandle : SafeHandle
    {
        public override bool IsInvalid => handle == IntPtr.Zero;

        private SafeTigerHandle() : base(IntPtr.Zero, ownsHandle: true) { }

        protected override bool ReleaseHandle()
        {
            return TigerNative.Destroy(handle) == MyLibStatus.Ok;
        }
    }
}
