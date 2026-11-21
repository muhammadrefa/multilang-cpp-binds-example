package mylib.binding.handles.numberprocessor;

import mylib.binding.handles.NativeHandle;

import java.util.function.LongToIntFunction;

public class NumberProcessorHandle extends NativeHandle {

    public NumberProcessorHandle(long value, LongToIntFunction releaser) {
        super(value, releaser);
    }

    public NumberProcessorHandle(long value) {
        super(value);
    }
}
