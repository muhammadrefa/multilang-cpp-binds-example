package mylib;

import java.lang.String;
import java.nio.BufferOverflowException;

import mylib.binding.TigerNative;
import mylib.binding.handles.TigerHandle;
import mylib.binding.refs.CharRef;
import mylib.binding.refs.IntRef;
import mylib.internal.StatusHelper;

public class Tiger extends Cat {
    private final TigerHandle handle;

    public Tiger() {
        this(createHandle());
    }

    public Tiger(String name) {
        this(createHandle(name));
    }

    protected Tiger(TigerHandle handle) {
        super(handle);
        this.handle = handle;
    }

    private static TigerHandle createHandle() {
        TigerHandle handle = TigerNative.create();
        if (handle.isNull())
            throw new RuntimeException("Cannot allocate new handle.");
        return handle;
    }

    private static TigerHandle createHandle(String name) {
        CharRef _name = new CharRef(name.getBytes());
        TigerHandle handle = TigerNative.createWithName(_name, _name.value.length);
        if (handle.isNull())
            throw new RuntimeException("Cannot allocate new handle.");
        return handle;
    }

    @Override
    public void speak() {
        int status = TigerNative.speak(handle);
        StatusHelper.check(status);
    }

    @Override
    public void sleep() {
        int status = TigerNative.sleep(handle);
        StatusHelper.check(status);
    }

    public void hunt() {
        int status = TigerNative.hunt(handle);
        StatusHelper.check(status);
    }

    public int getHunger() {
        IntRef hunger = new IntRef();
        int status = TigerNative.getHunger(handle, hunger);
        StatusHelper.check(status);

        return hunger.value;
    }
}
