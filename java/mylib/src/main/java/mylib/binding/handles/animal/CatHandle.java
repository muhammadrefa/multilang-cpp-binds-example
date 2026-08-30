package mylib.binding.handles.animal;

import java.util.function.LongToIntFunction;

public class CatHandle extends AnimalHandle {

    public CatHandle(long value, LongToIntFunction releaser) {
        super(value, releaser);
    }

    public CatHandle(long value) {
        super(value);
    }
}
