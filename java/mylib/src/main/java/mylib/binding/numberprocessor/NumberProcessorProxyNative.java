package mylib.binding.numberprocessor;

import mylib.binding.Loader;
import mylib.binding.handles.numberprocessor.NumberProcessorHandle;
import mylib.binding.handles.numberprocessor.NumberProcessorProxyHandle;
import mylib.numberprocessor.NumberProcessorProxy;

public final class NumberProcessorProxyNative {

    static {
        Loader.load();
    }

    private NumberProcessorProxyNative() {
    }

    private static native long nativeCreate(NumberProcessorProxy instance);
    public static NumberProcessorProxyHandle create(NumberProcessorProxy instance)
    {
        return new NumberProcessorProxyHandle(nativeCreate(instance), NumberProcessorProxyNative::nativeDestroy);
    }
    
    private static native int nativeDestroy(long handle);
    public static int destroy(NumberProcessorProxyHandle handle)
    {
        return nativeDestroy(handle.value());
    }

    private static native long nativeAsNumberProcessor(long handle);
    public static NumberProcessorHandle asNumberProcessor(NumberProcessorProxyHandle handle)
    {
        return new NumberProcessorHandle(nativeAsNumberProcessor(handle.value()));
    }
    
    private static native long nativeFromNumberProcessor(long handle);
    public static NumberProcessorProxyHandle fromNumberProcessor(NumberProcessorHandle handle)
    {
        return new NumberProcessorProxyHandle(nativeFromNumberProcessor(handle.value()));
    }

    private static native int nativeBasePrintNumber(long handle);
    public static int basePrintNumber(NumberProcessorProxyHandle handle)
    {
        return nativeBasePrintNumber(handle.value());
    }
}
