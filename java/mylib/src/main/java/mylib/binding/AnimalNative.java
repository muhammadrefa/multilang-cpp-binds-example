package mylib.binding;

import mylib.binding.refs.CharRef;
import mylib.binding.refs.IntRef;
import mylib.binding.handles.AnimalHandle;

public final class AnimalNative {

    static {
        Loader.load();
    }

    private AnimalNative() {
    }

    private static native long nativeCreate();
    public static AnimalHandle create()
    {
        return new AnimalHandle(nativeCreate(), AnimalNative::nativeDestroy);
    }

    private static native long nativeCreateWithName(CharRef name, int length);
    public static AnimalHandle createWithName(CharRef name, int length)
    {
        return new AnimalHandle(nativeCreateWithName(name, length), AnimalNative::nativeDestroy);
    }
    
    private static native int nativeDestroy(long handle);
    public static int destroy(AnimalHandle handle)
    {
        return nativeDestroy(handle.value());
    }
    
    private static native int nativeSpeak(long handle);
    public static int speak(AnimalHandle handle)
    {
        return nativeSpeak(handle.value());
    }
    
    private static native int nativeSpeakMultipleTimes(long handle, int times);
    public static int speakMultipleTimes(AnimalHandle handle, int times)
    {
        return nativeSpeakMultipleTimes(handle.value(), times);
    }
    
    private static native int nativeSleep(long handle);
    public static int sleep(AnimalHandle handle)
    {
        return nativeSleep(handle.value());
    }
    
    private static native int nativeSetName(long handle, CharRef name, int length);
    public static int setName(AnimalHandle handle, CharRef name, int length)
    {
        return nativeSetName(handle.value(), name, length);
    }
    
    private static native int nativeGetName(long handle, CharRef name, IntRef length);
    public static int getName(AnimalHandle handle, CharRef name, IntRef length)
    {
        return nativeGetName(handle.value(), name, length);
    }
}
