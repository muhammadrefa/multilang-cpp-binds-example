package mylib.binding.handles.numberprocessor;

import java.util.function.LongToIntFunction;

public class NumberProcessorProxyHandle extends NumberProcessorHandle {

    public NumberProcessorProxyHandle(long value, LongToIntFunction releaser) {
        super(value, releaser);
    }

    public NumberProcessorProxyHandle(long value) {
        super(value);
    }
}
