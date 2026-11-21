package mylib.binding.numberprocessor;

import mylib.binding.Loader;
import mylib.binding.handles.numberprocessor.NumberProcessorHandle;
import mylib.binding.refs.IntRef;

public final class NumberProcessorNative {

    static {
        Loader.load();
    }

    private NumberProcessorNative() {
    }

//    private static native long nativeCreate();
//    public static NumberProcessorHandle create()
//    {
//        return new NumberProcessorHandle(nativeCreate(), NumberProcessorNative::nativeDestroy);
//    }

    private static native int nativeDestroy(long handle);
    public static int destroy(NumberProcessorHandle handle)
    {
        return nativeDestroy(handle.value());
    }

    private static native int nativeProcess(long handle);
    public static int process(NumberProcessorHandle handle)
    {
        return nativeProcess(handle.value());
    }

    private static native int nativeGetNumber(long handle, IntRef number);
    public static int getNumber(NumberProcessorHandle handle, IntRef number)
    {
        return nativeGetNumber(handle.value(), number);
    }

    private static native int nativeSetNumber(long handle, int number);
    public static int setNumber(NumberProcessorHandle handle, int number)
    {
        return nativeSetNumber(handle.value(), number);
    }

    private static native int nativePrintNumber(long handle);
    public static int printNumber(NumberProcessorHandle handle)
    {
        return nativePrintNumber(handle.value());
    }
}
