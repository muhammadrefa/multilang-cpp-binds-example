package mylib.binding.handles.numberprocessor;

import java.util.function.LongToIntFunction;

public class ProcessAdd2Handle extends NumberProcessorHandle {

    public ProcessAdd2Handle(long value, LongToIntFunction releaser) {
        super(value, releaser);
    }

    public ProcessAdd2Handle(long value) {
        super(value);
    }
}
