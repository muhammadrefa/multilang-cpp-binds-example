package mylib;

import mylib.binding.CalculatorNative;
import mylib.binding.handles.CalculatorHandle;
import mylib.binding.refs.IntRef;
import mylib.internal.StatusHelper;

public final class Calculator implements AutoCloseable {
    private final CalculatorHandle handle;

    public Calculator() {
        handle = CalculatorNative.create();
        if (handle.isNull())
            throw new RuntimeException("Cannot allocate new handle.");
    }

    public int add(int a, int b) {
        IntRef result = new IntRef();
        int status = CalculatorNative.add(handle, a, b, result);
        StatusHelper.check(status);

        return result.value;
    }

    public int sub(int a, int b) {
        IntRef result = new IntRef();
        int status = CalculatorNative.sub(handle, a, b, result);
        StatusHelper.check(status);

        return result.value;
    }

    public int cntOpsDone() {
        IntRef retval = new IntRef();
        int status = CalculatorNative.cntOpsDone(handle, retval);
        StatusHelper.check(status);

        return retval.value;
    }

    public int resetCounter() {
        IntRef retval = new IntRef();
        int status = CalculatorNative.resetCounter(handle, retval);
        StatusHelper.check(status);

        return retval.value;
    }

    @Override
    public void close() {
        handle.close();
    }
}
