package mylib.internal;

import java.nio.BufferOverflowException;
import mylib.binding.MyLibStatus;
import mylib.exceptions.MyLibException;

public final class StatusHelper {

    private StatusHelper() {
    }

    public static void check(int status) {
        switch(status) {
            case MyLibStatus.OK: return;
            case MyLibStatus.UNKNOWN_ERROR:
                throw new RuntimeException("Unknown error.");
            case MyLibStatus.INVALID_HANDLE:
                throw new NullPointerException();
            case MyLibStatus.INVALID_ARGUMENT:
                throw new IllegalArgumentException("Invalid argument.");
            case MyLibStatus.LOGIC_ERROR:
                throw new RuntimeException("Logic error.");
            case MyLibStatus.OVERFLOW_ERROR:
                throw new BufferOverflowException();
            case MyLibStatus.RANGE_ERROR:
                throw new IndexOutOfBoundsException("Range error.");
            case MyLibStatus.BUFFER_TOO_SMALL:
                throw new BufferOverflowException();
            default:
                throw new MyLibException("Native error: " + status);
        }
    }
}
