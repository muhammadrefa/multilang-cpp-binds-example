package mylib.numberprocessor;

import mylib.binding.numberprocessor.NumberProcessorNative;
import mylib.binding.handles.numberprocessor.NumberProcessorHandle;
import mylib.binding.refs.IntRef;
import mylib.internal.StatusHelper;

public abstract class NumberProcessor implements AutoCloseable {
    protected NumberProcessorHandle handle;

    protected NumberProcessor(NumberProcessorHandle handle) {
        this.handle = handle;
    }

    public void process() {
        int status = NumberProcessorNative.process(handle);
        StatusHelper.check(status);
    }

    public void setNumber(int number) {
        int status = NumberProcessorNative.setNumber(handle, number);
        StatusHelper.check(status);
    }

    public int getNumber() {
        IntRef number = new IntRef();
        int status = NumberProcessorNative.getNumber(handle, number);
        StatusHelper.check(status);
        return number.value;
    }

    public void printNumber() {
        int status = NumberProcessorNative.printNumber(handle);
        StatusHelper.check(status);
    }

    @Override
    public void close() {
        handle.close();
    }
}
