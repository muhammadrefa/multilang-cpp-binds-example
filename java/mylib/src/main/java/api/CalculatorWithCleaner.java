/*
 * Reference implementation
 * 
 * Cleaner requires Java 9+
 */

package api;

import binding.NativeCleaner;
import binding.CalculatorNative;
import binding.handles.CalculatorHandle;
import binding.refs.IntRef;
import binding.StatusHelper;

public final class CalculatorWithCleaner implements AutoCloseable {

    private static final class State implements Runnable {
        private CalculatorHandle handle;

        State(CalculatorHandle handle) {
            this.handle = handle;
        }

        CalculatorHandle handle() {
            if (handle == null)
                throw new IllegalStateException("Calculator is closed");
            return handle;
        }

        @Override
        public void run() {
            if (handle == null)
                return;

            int status = CalculatorNative.destroy(handle);
            StatusHelper.check(status);
            handle = null;
        }
    }

    private final State state;
    private final Cleaner.Cleanable cleanable;

    public Calculator() {
        CalculatorHandle handle = CalculatorNative.create();
        if (handle.isNull())
            throw new RuntimeException("Cannot allocate new handle.");
        this.state = new State(handle);
        
        this.cleanable = NativeCleaner.INSTANCE.register(this, state);
    }

    public int add(int a, int b) {
        IntRef result = new IntRef();
        int status = CalculatorNative.add(state.handle(), a, b, result);
        StatusHelper.check(status);

        return result.value;
    }

    public int sub(int a, int b) {
        IntRef result = new IntRef();
        int status = CalculatorNative.sub(state.handle(), a, b, result);
        StatusHelper.check(status);

        return result.value;
    }

    public int cntOpsDone() {
        IntRef retval = new IntRef();
        int status = CalculatorNative.cntOpsDone(state.handle(), retval);
        StatusHelper.check(status);

        return retval.value;
    }

    public int resetCounter() {
        IntRef retval = new IntRef();
        int status = CalculatorNative.resetCounter(state.handle(), retval);
        StatusHelper.check(status);

        return retval.value;
    }

    @Override
    public void close() {
        cleanable.clean();
    }
}

