using System;
using System.Runtime.InteropServices;

namespace MyLib.Interop.Handles
{
    internal sealed class SafeCircularBufferHandle : SafeHandle
    {
        public override bool IsInvalid => handle == IntPtr.Zero;

        private SafeCircularBufferHandle() : base(IntPtr.Zero, ownsHandle: true) { }

        protected override bool ReleaseHandle()
        {
            return CircularBufferNative.Destroy(handle) == MyLibStatus.Ok;
        }
    }
}
