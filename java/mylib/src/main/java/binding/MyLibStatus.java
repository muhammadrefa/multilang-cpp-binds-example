package binding;

public final class MyLibStatus {
    private MyLibStatus() {}

    public static final int OK = 0;

    public static final int UNKNOWN_ERROR = -1;
    public static final int INVALID_HANDLE = -2;
    public static final int INVALID_ARGUMENT = -3;

    public static final int LOGIC_ERROR = -11;
    public static final int OVERFLOW_ERROR = -12;
    public static final int RANGE_ERROR = -13;

    public static final int BUFFER_TOO_SMALL = -51;
}
