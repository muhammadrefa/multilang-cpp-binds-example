package mylib.binding.handles;

import java.util.function.LongToIntFunction;

public final class CircularBufferHandle extends NativeHandle {

    public CircularBufferHandle(long value, LongToIntFunction releaser) {
        super(value, releaser);
    }
}
