package mylib.binding.handles;

import java.util.function.LongToIntFunction;
import mylib.internal.StatusHelper;

public abstract class NativeHandle {

    private long value;
    private final LongToIntFunction releaser;

    protected NativeHandle(long value, LongToIntFunction releaser) {
        this.value = value;
        this.releaser = releaser;
    }

    protected NativeHandle(long value) {
        this(value, null);
    }

    public final void close() {
        if (value == 0)
            return;

        if (releaser != null)
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
