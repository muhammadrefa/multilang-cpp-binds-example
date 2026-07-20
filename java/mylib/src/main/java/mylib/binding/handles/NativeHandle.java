package mylib.binding.handles;

import java.util.function.LongToIntFunction;
import mylib.internal.StatusHelper;

public abstract class NativeHandle {

    private final AtomicLong native_pointer;
    private final LongToIntFunction releaser;

    protected NativeHandle(long value, LongToIntFunction releaser) {
        this.native_pointer = new AtomicLong(value);
        this.releaser = releaser;
    }

    protected NativeHandle(long value) {
        this(value, null);
    }

    public final void close() {
        if (releaser == null)       // non-owning handle
            return;

        long pointer_to_free = native_pointer.getAndSet(0);

        if (pointer_to_free != 0)
            StatusHelper.check(releaser.applyAsInt(pointer_to_free));
    }

    public final long value() {
        long ptr_value = native_pointer.get();
        if (ptr_value == 0)
            throw new IllegalStateException("Handle is closed");
        return ptr_value;
    }

    public final boolean isNull() {
        return native_pointer.get() == 0;
    }

    @Override
    protected void finalize() throws Throwable {
        try {
            close();
        } finally {
            super().finalize();
        }
    }
}
