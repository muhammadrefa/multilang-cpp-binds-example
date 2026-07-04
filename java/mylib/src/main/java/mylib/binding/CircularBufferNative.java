package mylib.binding;

import mylib.binding.refs.IntRef;
import mylib.binding.refs.CharRef;
import mylib.binding.handles.CircularBufferHandle;

public final class CircularBufferNative {

    static {
        Loader.load();
    }

    private CircularBufferNative() {
    }

    private static native long nativeCreate(int bufsize);
    public static CircularBufferHandle create(int bufsize)
    {
        return new CircularBufferHandle(nativeCreate(bufsize), CircularBufferNative::nativeDestroy);
    }
    
    private static native int nativeDestroy(long handle);
    public static int destroy(CircularBufferHandle handle)
    {
        return nativeDestroy(handle.value());
    }
    
    private static native int nativeGetLength(long handle, IntRef returned_length);
    public static int getLength(CircularBufferHandle handle, IntRef returned_length)
    {
        return nativeGetLength(handle.value(), returned_length);
    }
    
    private static native int nativePut(long handle, CharRef data, int length, IntRef returned_length);
    public static int put(CircularBufferHandle handle, CharRef data, int length, IntRef returned_length)
    {
        return nativePut(handle.value(), data, length, returned_length);
    }
    
    private static native int nativeGet(long handle, CharRef dest, int length, IntRef returned_length);
    public static int get(CircularBufferHandle handle, CharRef dest, int length, IntRef returned_length)
    {
        return nativeGet(handle.value(), dest, length, returned_length);
    }
    
    private static native int nativeClean(long handle, IntRef returned_length);
    public static int clean(CircularBufferHandle handle, IntRef returned_length)
    {
        return nativeClean(handle.value(), returned_length);
    }
}
