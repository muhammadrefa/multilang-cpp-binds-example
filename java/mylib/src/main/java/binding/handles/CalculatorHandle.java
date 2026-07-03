package binding.handles;

import java.util.function.LongToIntFunction;

public final class CalculatorHandle extends NativeHandle {

    public CalculatorHandle(long value, LongToIntFunction releaser) {
        super(value, releaser);
    }
}
