package api;

import binding.CalculatorNative;
import binding.handles.CalculatorHandle;
import binding.refs.IntRef;
import binding.StatusHelper;

public final class Calculator implements AutoCloseable {

    private final CalculatorHandle handle;
    private boolean is_closed = false;

    public Calculator() {
        handle = CalculatorNative.create();
        if (handle.isNull())
            throw new OutOfMemoryError("Cannot allocate new handle.");
    }

    public int add(int a, int b) {
        ensureOpen();

        IntRef result = new IntRef();
        int status = CalculatorNative.add(handle, a, b, result);
        StatusHelper.check(status);

        return result.value;
    }

    public int sub(int a, int b) {
        ensureOpen();
        
        IntRef result = new IntRef();
        int status = CalculatorNative.sub(handle, a, b, result);
        StatusHelper.check(status);

        return result.value;
    }

    public int cntOpsDone() {
        ensureOpen();
        
        IntRef retval = new IntRef();
        int status = CalculatorNative.cntOpsDone(handle, retval);
        StatusHelper.check(status);

        return retval.value;
    }

    public int resetCounter() {
        ensureOpen();
        
        IntRef retval = new IntRef();
        int status = CalculatorNative.resetCounter(handle, retval);
        StatusHelper.check(status);

        return retval.value;
    }

    @Override
    public void close() {
        ensureOpen();
        
        int status = CalculatorNative.destroy(handle);
        StatusHelper.check(status);
        is_closed = true;
    }

    private void ensureOpen() {
        if (is_closed)
            throw new IllegalStateException("Calculator is closed.");
    }
}
