package binding.handles;

public abstract class NativeHandle {
    private final long value;

    protected NativeHandle(long value) {
        this.value = value;
    }

    public final long value() {
        return value;
    }

    public final boolean isNull() {
        return value == 0;
    }
}
