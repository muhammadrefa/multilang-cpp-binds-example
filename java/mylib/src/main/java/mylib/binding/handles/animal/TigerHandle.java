package mylib.binding.handles.animal;

import java.util.function.LongToIntFunction;

public class TigerHandle extends CatHandle {

    public TigerHandle(long value, LongToIntFunction releaser) {
        super(value, releaser);
    }

    public TigerHandle(long value) {
        super(value);
    }
}
