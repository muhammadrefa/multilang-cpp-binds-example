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

    private static native long nativeCreate();
    public static NumberProcessorProxyHandle create()
    {
        return new NumberProcessorProxyHandle(nativeCreate(), NumberProcessorProxyNative::nativeDestroy);
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
}
