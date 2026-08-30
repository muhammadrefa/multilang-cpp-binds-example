package mylib.binding.handles.animal;

import java.util.function.LongToIntFunction;

public class DogHandle extends AnimalHandle {

    public DogHandle(long value, LongToIntFunction releaser) {
        super(value, releaser);
    }

    public DogHandle(long value) {
        super(value);
    }
}
