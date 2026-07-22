package mylib.binding;

import mylib.binding.refs.CharRef;
import mylib.binding.refs.IntRef;
import mylib.binding.handles.CatHandle;
import mylib.binding.handles.TigerHandle;

public final class TigerNative {

    static {
        Loader.load();
    }

    private TigerNative() {
    }

    private static native long nativeCreate();
    public static TigerHandle create()
    {
        return new TigerHandle(nativeCreate(), TigerNative::nativeDestroy);
    }

    private static native long nativeCreateWithName(CharRef name, int length);
    public static TigerHandle createWithName(CharRef name, int length)
    {
        return new TigerHandle(nativeCreateWithName(name, length), TigerNative::nativeDestroy);
    }
    
    private static native int nativeDestroy(long handle);
    public static int destroy(TigerHandle handle)
    {
        return nativeDestroy(handle.value());
    }

    // not needed because it still referencing the same object underneath
    private static native long nativeAsCat(long handle);
    public static CatHandle asCat(TigerHandle handle)
    {
        return new CatHandle(nativeAsCat(handle.value()));
    }
    
    private static native int nativeHunt(long handle);
    public static int hunt(TigerHandle handle)
    {
        return nativeHunt(handle.value());
    }
    
    private static native int nativeGetHunger(long handle, IntRef hunger);
    public static int getHunger(TigerHandle handle, IntRef hunger)
    {
        return nativeGetHunger(handle.value(), hunger);
    }
}
