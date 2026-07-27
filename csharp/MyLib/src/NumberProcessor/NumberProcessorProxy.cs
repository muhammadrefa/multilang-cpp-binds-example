using System;
using System.ComponentModel.Design;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Text;
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
            public NumberProcessorProxyNative.ProcessCallback CbProcess = null!;
            public NumberProcessorProxyNative.PrintNumberCallback CbPrintNumber = null!;
        }

        [ThreadStatic]
        private static CallbackClosure? t_pendingClosure;
        
        private readonly CallbackClosure _closure;
        private SafeNumberProcessorProxyHandle handle;

        public NumberProcessorProxy() : this(CreateHandleAndParkClosure())
        {
        }

        private protected NumberProcessorProxy(SafeNumberProcessorProxyHandle handle): base(NumberProcessorProxyNative.As_NumberProcessor(handle))
        {
            this.handle = handle;
            
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

        private static SafeNumberProcessorProxyHandle CreateHandleAndParkClosure()
        {
            t_pendingClosure = null;

            var closure = new CallbackClosure();
            closure.CbProcess = (_) => closure.Target?.Process();
            closure.CbPrintNumber = (_) => closure.Target?.PrintNumber();

            var NativeCallbacks = new NumberProcessorProxyNative.NumberProcessorProxyCallbacks
            {
                Process = closure.CbProcess,
                PrintNumber = closure.CbPrintNumber
            };

            closure.Handle = NumberProcessorProxyNative.Create(ref NativeCallbacks);
            if (closure.Handle.IsInvalid)
                throw new OutOfMemoryException("Failed to create number processor proxy.");
            
            t_pendingClosure = closure;
            return closure.Handle;
        }

        protected internal static T CreateProxy<T>(Func <SafeNumberProcessorProxyHandle, T> factory)
            where T : NumberProcessorProxy
        {
            T instance = null!;

            // lambdas
            NumberProcessorProxyNative.ProcessCallback cbProcess = (h) => instance?.Process();
            NumberProcessorProxyNative.PrintNumberCallback cbPrintNumber = (h) => instance?.PrintNumber();

            var _callback = new NumberProcessorProxyNative.NumberProcessorProxyCallbacks
            {
                Process = cbProcess,
                PrintNumber = cbPrintNumber
            };

            SafeNumberProcessorProxyHandle handle = NumberProcessorProxyNative.Create(ref _callback);
            if (handle.IsInvalid)
                throw new OutOfMemoryException("Failed to create number processor proxy.");
            
            instance = factory(handle);

            instance._cbProcess = cbProcess;
            instance._cbPrintNumber = cbPrintNumber;

            return instance;
        }

        // private void OnProcessNative(IntPtr handle)
        // {
        //     Process();
        // }

        public abstract override void Process();

        // private void OnPrintNumberNative(IntPtr _handle)
        // {
        //     PrintNumber();
        // }

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
                throw new ObjectDisposedException(nameof(Process2));
        }
    }
}
