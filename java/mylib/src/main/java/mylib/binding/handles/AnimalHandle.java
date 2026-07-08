package mylib.binding.handles;

import java.util.function.LongToIntFunction;

public final class AnimalHandle extends NativeHandle {

    public AnimalHandle(long value, LongToIntFunction releaser) {
        super(value, releaser);
    }
}
