package binding;

import binding.refs.IntRef;

public final class CalculatorNative {

    static {
        Loader.load();
    }

    private CalculatorNative() {
    }

    // TODO: change long to handle
    public static native long create();
    public static native int destroy(long handle);
    public static native int add(long handle, int a, int b, IntRef result);
    public static native int sub(long handle, int a, int b, IntRef result);
    public static native int cntOpsDone(long handle, IntRef retval);
    public static native int resetCounter(long handle, IntRef retval);
}
