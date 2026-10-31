using System;
using System.Reflection;
using MyLib.Interop;
using MyLib.Interop.Handles;

namespace MyLib
{
    public abstract class NumberProcessorProxy<T> : NumberProcessor
        where T : NumberProcessorProxy<T>
    {

        private class CallbackClosure
        {
            public T? Target;
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
            
            // get the handle as the key for the object registry
            ObjectRegistry.Register(handle.DangerousGetHandle(), this);

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

                _closure.Target = (T)this;
            }
        }

        private static SafeNumberProcessorProxyHandle CreateHandleAndParkClosure()
        {
            t_pendingClosure = null;

            var closure = new CallbackClosure();
            
            // set the callbacks
            closure.Callback = new NumberProcessorProxyNative.NumberProcessorProxyCallbacks
            {
                // we don't need the handle since the callbacks are already object-specific
                Process = (_) => closure.Target?.Process(),
                PrintNumber = (_) => closure.Target?.PrintNumber()
            };

            closure.Handle = NumberProcessorProxyNative.Create(ref closure.Callback);
            if (closure.Handle.IsInvalid)
                throw new OutOfMemoryException("Failed to create number processor proxy.");
            
            t_pendingClosure = closure;
            return closure.Handle;
        }

        public static T FromBase(NumberProcessor numberProcessor)
        {
            // check for existing instance which holds the handle in the registry
            using (var _handle = NumberProcessorProxyNative.From_NumberProcessor(numberProcessor.GetHandle()))
            {
                if (ObjectRegistry.TryGet<T>(_handle.DangerousGetHandle(), out T? existingInstance))
                {
                    return existingInstance!;
                }
            }
            
            // throw an exception if it is not T
            throw new InvalidCastException($"This object is not {typeof(T).Name}!");
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
            base.Dispose();
        }

        private void ThrowIfDisposed()
        {
            if (handle.IsClosed)
                throw new ObjectDisposedException(GetType().Name);
        }
    }
}
