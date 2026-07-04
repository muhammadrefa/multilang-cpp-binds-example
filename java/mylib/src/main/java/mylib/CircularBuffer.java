package mylib;

import mylib.binding.CircularBufferNative;
import mylib.binding.handles.CircularBufferHandle;
import mylib.binding.refs.IntRef;
import mylib.binding.refs.CharRef;
import mylib.internal.StatusHelper;

public final class CircularBuffer implements AutoCloseable {
    private final CircularfBufferHandle handle;

    public CircularBuffer(int bufsize)) {
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

    public int get(byte[] dest, int length) {
        IntRef returned_length = new IntRef();
        CharRef _dest = new CharRef(dest);
        int status = CircularBufferNative.get(handle, _dest, length, returned_length);
        StatusHelper.check(status);

        return returned_length.value;
    }

    public int clean() {
        IntRef returned_length = new IntRef();
        int status = CircularBufferNative.resetCounter(handle, returned_length);
        StatusHelper.check(status);

        return retval.value;
    }

    @Override
    public void close() {
        handle.close();
    }
}
