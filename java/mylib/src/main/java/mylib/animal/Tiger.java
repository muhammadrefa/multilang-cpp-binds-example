package mylib.animal;

import java.lang.String;

import mylib.binding.animal.TigerNative;
import mylib.binding.handles.animal.TigerHandle;
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
        super(TigerNative.asCat(handle));
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

    @Override
    public void close() {
        handle.close();
        super.close();
    }
}
