using System;
using MyLib.Interop;
using MyLib.Interop.Handles;

namespace MyLib
{
    public abstract class NumberProcessorProxy : NumberProcessor
    {

        private class CallbackClosure
        {
            public NumberProcessorProxy? Target;
            public SafeNumberProcessorProxyHandle Handle = null!;
            public NumberProcessorProxyNative.NumberProcessorProxyCallbacks Callback;
        }

        [ThreadStatic]
        private static CallbackClosure? t_pendingClosure;
        
        private readonly CallbackClosure _closure;
        private SafeNumberProcessorProxyHandle handle;

        protected NumberProcessorProxy() : this(CreateHandleAndParkClosure())
        {
        }

        private protected NumberProcessorProxy(SafeNumberProcessorProxyHandle handle): base(NumberProcessorProxyNative.As_NumberProcessor(handle))
        {
            this.handle = handle;

            if (t_pendingClosure != null)
            {
                try
                {
                    _closure = t_pendingClosure!;
                }
                finally
                {
                    t_pendingClosure = null;
                }

                _closure.Target = this;
            }
        }

        private static SafeNumberProcessorProxyHandle CreateHandleAndParkClosure()
        {
            t_pendingClosure = null;

            var closure = new CallbackClosure();
            
            // set the callbacks
            closure.Callback = new NumberProcessorProxyNative.NumberProcessorProxyCallbacks
            {
                Process = (_) => closure.Target?.Process(),
                PrintNumber = (_) => closure.Target?.PrintNumber()
            };

            closure.Handle = NumberProcessorProxyNative.Create(ref closure.Callback);
            if (closure.Handle.IsInvalid)
                throw new OutOfMemoryException("Failed to create number processor proxy.");
            
            t_pendingClosure = closure;
            return closure.Handle;
        }

        internal new SafeNumberProcessorProxyHandle GetHandle()
        {
            return handle;
        }

        public abstract override void Process();

        public override void PrintNumber()
        {
            ThrowIfDisposed();
            var status = NumberProcessorProxyNative.Base_PrintNumber(handle);
            status.ThrowIfError();
        }

        public override void Dispose()
        {
            handle.Dispose();
        }

        private void ThrowIfDisposed()
        {
            if (handle.IsClosed)
                throw new ObjectDisposedException(nameof(NumberProcessorProxy));
        }
    }
}
