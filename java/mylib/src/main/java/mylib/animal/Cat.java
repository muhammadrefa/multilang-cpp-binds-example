package mylib.animal;

import java.lang.String;

import mylib.binding.animal.CatNative;
import mylib.binding.handles.animal.CatHandle;
import mylib.binding.refs.CharRef;
import mylib.binding.refs.IntRef;
import mylib.internal.StatusHelper;

public class Cat extends Animal {
    private final CatHandle handle;

    public Cat() {
        this(createHandle());
    }

    public Cat(String name) {
        this(createHandle(name));
    }

    protected Cat(CatHandle handle) {
        super(CatNative.asAnimal(handle));
        this.handle = handle;
    }

    private static CatHandle createHandle() {
        CatHandle handle = CatNative.create();
        if (handle.isNull())
            throw new RuntimeException("Cannot allocate new handle.");
        return handle;
    }

    private static CatHandle createHandle(String name) {
        CharRef _name = new CharRef(name.getBytes());
        CatHandle handle = CatNative.createWithName(_name, _name.value.length);
        if (handle.isNull())
            throw new RuntimeException("Cannot allocate new handle.");
        return handle;
    }

    public boolean fight(boolean bigger_cat) {
        IntRef success = new IntRef();
        int status = CatNative.fight(handle, (bigger_cat ? 1 : 0), success);
        StatusHelper.check(status);

        return (success.value != 0);
    }

    public boolean stillAlive() {
        IntRef is_alive = new IntRef();
        int status = CatNative.stillAlive(handle, is_alive);
        StatusHelper.check(status);

        return (is_alive.value != 0);
    }
}
