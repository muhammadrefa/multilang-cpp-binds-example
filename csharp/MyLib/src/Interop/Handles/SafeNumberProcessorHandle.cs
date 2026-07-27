using System;
using System.Runtime.InteropServices;

namespace MyLib.Interop.Handles
{
    internal class SafeNumberProcessorHandle : SafeHandle
    {
        public override bool IsInvalid => handle == IntPtr.Zero;

        private protected SafeNumberProcessorHandle() : base(IntPtr.Zero, ownsHandle: true) { }
        private protected SafeNumberProcessorHandle(bool ownsHandle) : base(IntPtr.Zero, ownsHandle) { }

        internal static SafeNumberProcessorHandle AsReference(IntPtr ptr)
        {
            var handle = new SafeNumberProcessorHandle(false);
            handle.SetHandle(ptr);
            return handle;
        }

        protected override bool ReleaseHandle()
        {
            return NumberProcessorNative.Destroy(handle) == MyLibStatus.Ok;
        }
    }

    internal class SafeProcess2Handle : SafeNumberProcessorHandle
    {

        private protected SafeProcess2Handle() : base() { }
        private protected SafeProcess2Handle(bool ownsHandle) : base(ownsHandle) { }

        internal new static SafeProcess2Handle AsReference(IntPtr ptr)
        {
            var handle = new SafeProcess2Handle(false);
            handle.SetHandle(ptr);
            return handle;
        }

        protected override bool ReleaseHandle()
        {
            return Process2Native.Destroy(handle) == MyLibStatus.Ok;
        }
    }

    internal class SafeNumberProcessorProxyHandle : SafeNumberProcessorHandle
    {
        public override bool IsInvalid => handle == IntPtr.Zero;

        private protected SafeNumberProcessorProxyHandle() : base() { }
        private protected SafeNumberProcessorProxyHandle(bool ownsHandle) : base(ownsHandle) { }

        internal new static SafeNumberProcessorProxyHandle AsReference(IntPtr ptr)
        {
            var handle = new SafeNumberProcessorProxyHandle(false);
            handle.SetHandle(ptr);
            return handle;
        }

        protected override bool ReleaseHandle()
        {
            return NumberProcessorProxyNative.Destroy(handle) == MyLibStatus.Ok;
        }
    }
}
