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
        private bool _disposed;

        protected NumberProcessorProxy() : this(CreateHandleAndParkClosure())
        {
        }

        private protected NumberProcessorProxy(SafeNumberProcessorProxyHandle handle): base(NumberProcessorProxyNative.As_NumberProcessor(handle))
        {
            this.handle = handle;
            IntPtr baseHandle = base.GetHandle().DangerousGetHandle();
            ObjectRegistry.Register(baseHandle, this);          // using baseHandle to register the object

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

            _disposed = false;
        }

        protected internal NumberProcessorProxy(IntPtr rawHandle) : this(SafeNumberProcessorProxyHandle.AsReference(rawHandle))
        {
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
            // check for existing instance which holds the handle in the registry by using baseHandle
            if (ObjectRegistry.TryGet<T>(numberProcessor.GetHandle(), out T? existingInstance))
            {
                return existingInstance!;
            }

            // TODO
            // return (T)Activator.CreateInstance(
            //     typeof(T),
            //     BindingFlags.Instance | BindingFlags.Public | BindingFlags.NonPublic,
            //     null,
            //     new object[] { proxyHandle },
            //     null)!;
            return null;
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
            _disposed = true;
            IntPtr baseHandle = base.GetHandle().DangerousGetHandle();
            ObjectRegistry.Unregister(baseHandle);      // unregister the object/(base) handle from the registry
            handle.Dispose();
        }

        private void ThrowIfDisposed()
        {
            if (_disposed)
                throw new ObjectDisposedException(GetType().Name);
        }
    }
}
