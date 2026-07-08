package mylib.binding;

import mylib.binding.refs.CharRef;
import mylib.binding.refs.IntRef;
import mylib.binding.handles.AnimalHandle;
import mylib.binding.handles.DogHandle;

public final class DogNative {

    static {
        Loader.load();
    }

    private DogNative() {
    }

    private static native long nativeCreate();
    public static DogHandle create()
    {
        return new DogHandle(nativeCreate(), DogNative::nativeDestroy);
    }

    private static native long nativeCreateWithName(CharRef name, int length);
    public static DogHandle createWithName(CharRef name, int length)
    {
        return new DogHandle(nativeCreateWithName(name, length), DogNative::nativeDestroy);
    }
    
    private static native int nativeDestroy(long handle);
    public static int destroy(DogHandle handle)
    {
        return nativeDestroy(handle.value());
    }

    // not needed because it still referencing the same object underneath
    private static native long nativeAsAnimal(long handle);
    public static AnimalHandle asAnimal(DogHandle handle)
    {
        return new AnimalHandle(nativeAsAnimal(handle.value()));
    }
    
    private static native int nativeSpeak(long handle);
    public static int speak(DogHandle handle)
    {
        return nativeSpeak(handle.value());
    }
    
    private static native int nativeSleep(long handle);
    public static int sleep(DogHandle handle)
    {
        return nativeSleep(handle.value());
    }
    
    private static native int nativeFetch(long handle, IntRef success);
    public static int fetch(DogHandle handle, IntRef success)
    {
        return nativeFetch(handle.value(), success);
    }
    
    private static native int nativeGetEnergy(long handle, IntRef energy);
    public static int getEnergy(DogHandle handle, IntRef energy)
    {
        return nativeGetEnergy(handle.value(), energy);
    }
}
