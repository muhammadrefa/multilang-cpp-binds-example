package mylib;

import java.lang.String;
import java.nio.BufferOverflowException;

import mylib.binding.AnimalNative;
import mylib.binding.handles.AnimalHandle;
import mylib.binding.refs.CharRef;
import mylib.binding.refs.IntRef;
import mylib.internal.StatusHelper;

public class Animal implements AutoCloseable {
    protected AnimalHandle handle;

    public Animal() {
        this(createHandle());
    }

    public Animal(String name) {
        this(createHandle(name));
    }

    protected Animal(AnimalHandle handle) {
        this.handle = handle;
    }

    private static AnimalHandle createHandle() {
        AnimalHandle handle = AnimalNative.create();
        if (handle.isNull())
            throw new RuntimeException("Cannot allocate new handle.");
        return handle;
    }

    private static AnimalHandle createHandle(String name) {
        CharRef _name = new CharRef(name.getBytes());
        AnimalHandle handle = AnimalNative.createWithName(_name, _name.value.length);
        if (handle.isNull())
            throw new RuntimeException("Cannot allocate new handle.");
        return handle;
    }

    public void speak() {
        int status = AnimalNative.speak(handle);
        StatusHelper.check(status);
    }

    public void speak(int times) {
        int status = AnimalNative.speakMultipleTimes(handle, times);
        StatusHelper.check(status);
    }

    public void sleep() {
        int status = AnimalNative.sleep(handle);
        StatusHelper.check(status);
    }

    public void setName(String name) {
        CharRef _name = new CharRef(name.getBytes());
        int status = AnimalNative.setName(handle, _name, _name.value.length);
        StatusHelper.check(status);
    }

    public String getName() {
        IntRef length = new IntRef();
        CharRef _name = new CharRef(100);
        try
        {
            int status = AnimalNative.getName(handle, _name, length);
            StatusHelper.check(status);

            return new String(_name.value);
        }
        catch (BufferOverflowException ex)
        {
            CharRef _name2 = new CharRef(length.value);
            int status = AnimalNative.getName(handle, _name, length);
            StatusHelper.check(status);

            return new String(_name2.value);
        }
    }

    @Override
    public void close() {
        handle.close();
    }
}
