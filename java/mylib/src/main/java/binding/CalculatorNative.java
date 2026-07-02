package binding;

import binding.refs.IntRef;
import binding.handles.CalculatorHandle;

public final class CalculatorNative {

    static {
        Loader.load();
    }

    private CalculatorNative() {
    }

    private static native long nativeCreate();
    public static CalculatorHandle create()
    {
        return new CalculatorHandle(nativeCreate());
    }
    
    private static native int nativeDestroy(long handle);
    public static int destroy(CalculatorHandle handle)
    {
        return nativeDestroy(handle.value());
    }
    
    private static native int nativeAdd(long handle, int a, int b, IntRef result);
    public static int add(CalculatorHandle handle, int a, int b, IntRef result)
    {
        return nativeAdd(handle.value(), a, b, result);
    }
    
    private static native int nativeSub(long handle, int a, int b, IntRef result);
    public static int sub(CalculatorHandle handle, int a, int b, IntRef result)
    {
        return nativeSub(handle.value(), a, b, result);
    }
    
    private static native int nativeCntOpsDone(long handle, IntRef retval);
    public static int cntOpsDone(CalculatorHandle handle, IntRef retval)
    {
        return nativeCntOpsDone(handle.value(), retval);
    }
    
    private static native int nativeResetCounter(long handle, IntRef retval);
    public static int resetCounter(CalculatorHandle handle, IntRef retval)
    {
        return nativeResetCounter(handle.value(), retval);
    }
}
