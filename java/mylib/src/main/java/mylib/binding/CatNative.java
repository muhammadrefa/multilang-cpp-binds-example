package mylib.binding;

import mylib.binding.refs.CharRef;
import mylib.binding.refs.IntRef;
import mylib.binding.handles.AnimalHandle;
import mylib.binding.handles.CatHandle;

public final class CatNative {

    static {
        Loader.load();
    }

    private CatNative() {
    }

    private static native long nativeCreate();
    public static CatHandle create()
    {
        return new CatHandle(nativeCreate(), CatNative::nativeDestroy);
    }

    private static native long nativeCreateWithName(CharRef name, int length);
    public static CatHandle createWithName(CharRef name, int length)
    {
        return new CatHandle(nativeCreateWithName(name, length), CatNative::nativeDestroy);
    }
    
    private static native int nativeDestroy(long handle);
    public static int destroy(CatHandle handle)
    {
        return nativeDestroy(handle.value());
    }

    private static native long nativeAsAnimal(long handle);
    public static AnimalHandle asAnimal(CatHandle handle)
    {
        return new AnimalHandle(nativeAsAnimal(handle.value()));
    }
    
    private static native int nativeFight(long handle, int bigger_cat, IntRef success);
    public static int fight(CatHandle handle, int bigger_cat, IntRef success)
    {
        return nativeFight(handle.value(), bigger_cat, success);
    }
    
    private static native int nativeStillAlive(long handle, IntRef is_alive);
    public static int stillAlive(CatHandle handle, IntRef is_alive)
    {
        return nativeStillAlive(handle.value(), is_alive);
    }
}
