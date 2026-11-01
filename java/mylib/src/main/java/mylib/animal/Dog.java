package mylib.animal;

import java.lang.String;

import mylib.binding.animal.DogNative;
import mylib.binding.handles.animal.DogHandle;
import mylib.binding.refs.CharRef;
import mylib.binding.refs.IntRef;
import mylib.internal.StatusHelper;

public class Dog extends Animal {
    private final DogHandle handle;

    public Dog() {
        this(createHandle());
    }

    public Dog(String name) {
        this(createHandle(name));
    }

    protected Dog(DogHandle handle) {
        super(DogNative.asAnimal(handle));
        this.handle = handle;
    }

    private static DogHandle createHandle() {
        DogHandle handle = DogNative.create();
        if (handle.isNull())
            throw new RuntimeException("Cannot allocate new handle.");
        return handle;
    }

    private static DogHandle createHandle(String name) {
        CharRef _name = new CharRef(name.getBytes());
        DogHandle handle = DogNative.createWithName(_name, _name.value.length);
        if (handle.isNull())
            throw new RuntimeException("Cannot allocate new handle.");
        return handle;
    }

    public boolean fetch() {
        IntRef success = new IntRef();
        int status = DogNative.fetch(handle, success);
        StatusHelper.check(status);

        return (success.value != 0);
    }

    public int getEnergy() {
        IntRef energy = new IntRef();
        int status = DogNative.getEnergy(handle, energy);
        StatusHelper.check(status);
        return energy.value;
    }

    @Override
    public void close() {
        handle.close();
        super.close();
    }
}
