package mylib.binding.numberprocessor;

import mylib.binding.Loader;
import mylib.binding.handles.numberprocessor.NumberProcessorHandle;
import mylib.binding.handles.numberprocessor.NumberProcessorProxyHandle;

public final class NumberProcessorProxyNative {

    static {
        Loader.load();
    }

    private NumberProcessorProxyNative() {
    }

    private static native long nativeCreate(NumberProcessorProxyCallbacks callbacks);
    public static NumberProcessorProxyHandle create(NumberProcessorProxyCallbacks callbacks)
    {
        return new NumberProcessorProxyHandle(nativeCreate(callbacks), NumberProcessorProxyNative::nativeDestroy);
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
    
    private static native NumberProcessorProxyCallbacks nativeFromNumberProcessor(long handle);
    public static NumberProcessorProxyCallbacks fromNumberProcessor(NumberProcessorHandle handle)
    {
        return nativeFromNumberProcessor(handle.value());
    }

    private static native int nativeBasePrintNumber(long handle);
    public static int basePrintNumber(NumberProcessorProxyHandle handle)
    {
        return nativeBasePrintNumber(handle.value());
    }
}
