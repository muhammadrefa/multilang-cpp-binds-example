package mylib.binding.handles.animal;

import mylib.binding.handles.NativeHandle;

import java.util.function.LongToIntFunction;

public class AnimalHandle extends NativeHandle {

    public AnimalHandle(long value, LongToIntFunction releaser) {
        super(value, releaser);
    }

    public AnimalHandle(long value) {
        super(value);
    }
}
