package binding.handles;

import java.util.function.LongToIntFunction;
import binding.StatusHelper;

public abstract class NativeHandle {

    private long value;
    private final LongToIntFunction releaser;

    protected NativeHandle(long value, LongToIntFunction releaser) {
        this.value = value;
        this.releaser = releaser;
    }

    public final void close() {
        if (value == 0)
            return;

        StatusHelper.check(releaser.applyAsInt(value));

        value = 0;
    }

    public final long value() {
        if (value == 0)
            throw new IllegalStateException("Handle is closed");
        return value;
    }

    public final boolean isNull() {
        return value == 0;
    }
}
