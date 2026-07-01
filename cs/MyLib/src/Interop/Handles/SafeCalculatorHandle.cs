using System;
using System.Runtime.InteropServices;

namespace MyLib.Interop.Handles
{
    internal sealed class SafeCalculatorHandle : SafeHandle
    {
        public override bool IsInvalid => handle == IntPtr.Zero;

        private SafeCalculatorHandle() : base(IntPtr.Zero, ownsHandle: true) { }

        protected override bool ReleaseHandle()
        {
            return CalculatorNative.Destroy(handle) == MyLibStatus.Ok;
        }
    }
}
