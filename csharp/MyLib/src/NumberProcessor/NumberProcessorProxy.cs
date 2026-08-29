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
            ObjectRegistry.Register(this.handle.DangerousGetHandle(), this);

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
            SafeNumberProcessorProxyHandle proxyHandle = NumberProcessorProxyNative.From_NumberProcessor(numberProcessor.GetHandle());
            
            // check for existing instance which holds the handle in the registry
            if (ObjectRegistry.TryGet<T>(proxyHandle, out T? existingInstance))
            {
                return existingInstance!;
            }
            
            return (T)Activator.CreateInstance(
                typeof(T),
                BindingFlags.Instance | BindingFlags.Public | BindingFlags.NonPublic,
                null,
                new object[] { proxyHandle },
                null)!;
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
                throw new ObjectDisposedException(GetType().Name);
        }
    }
}
