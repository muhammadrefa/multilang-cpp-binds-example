package mylib;

import java.util.Arrays;

import mylib.binding.CircularBufferNative;
import mylib.binding.handles.CircularBufferHandle;
import mylib.binding.refs.IntRef;
import mylib.binding.refs.CharRef;
import mylib.internal.StatusHelper;

public final class CircularBuffer implements AutoCloseable {
    private final CircularBufferHandle handle;

    public CircularBuffer(int bufsize) {
        handle = CircularBufferNative.create(bufsize);
        if (handle.isNull())
            throw new RuntimeException("Cannot create circular buffer.");
    }

    public int getLength() {
        IntRef returned_length = new IntRef();
        int status = CircularBufferNative.getLength(handle, returned_length);
        StatusHelper.check(status);

        return returned_length.value;
    }

    public int put(byte[] data) {
        IntRef returned_length = new IntRef();
        CharRef _data = new CharRef(data);
        int status = CircularBufferNative.put(handle, _data, data.length, returned_length);
        StatusHelper.check(status);

        return returned_length.value;
    }

    public int put(byte[] data, int length) {
        IntRef returned_length = new IntRef();
        CharRef _data = new CharRef(data);
        int status = CircularBufferNative.put(handle, _data, length, returned_length);
        StatusHelper.check(status);

        return returned_length.value;
    }

    public byte[] get(int length) {
        CharRef dest = new CharRef(length);
        IntRef returned_length = new IntRef();
        int status = CircularBufferNative.get(handle, dest, length, returned_length);
        StatusHelper.check(status);

        return Arrays.copyOfRange(dest.value, 0, returned_length.value);
    }

    public int clean() {
        IntRef returned_length = new IntRef();
        int status = CircularBufferNative.clean(handle, returned_length);
        StatusHelper.check(status);

        return returned_length.value;
    }

    @Override
    public void close() {
        handle.close();
    }
}
