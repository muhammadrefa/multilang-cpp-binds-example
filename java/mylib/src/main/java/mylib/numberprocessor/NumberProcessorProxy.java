package mylib.numberprocessor;

import mylib.binding.handles.numberprocessor.NumberProcessorHandle;
import mylib.binding.handles.numberprocessor.NumberProcessorProxyHandle;
import mylib.binding.numberprocessor.NumberProcessorProxyNative;
import mylib.binding.numberprocessor.NumberProcessorProxyCallbacks;
import mylib.internal.StatusHelper;

public abstract class NumberProcessorProxy extends NumberProcessor implements NumberProcessorProxyCallbacks {
    private final NumberProcessorProxyHandle handle;

    public NumberProcessorProxy() {
        // because NPPNative constructor asks for 'this', we cannot use the regular 'static createHandle()' way
        // because of, you know, static does not know 'this'.

        // so construct NP with the handle value = 0 ...
        super(new NumberProcessorHandle(0));

        // ... create the NPP object ...
        this.handle = NumberProcessorProxyNative.create(this);
        if (handle.isNull())
            throw new RuntimeException("Cannot allocate new handle.");

        // ... and update the NP handle.
        super.setHandle(NumberProcessorProxyNative.asNumberProcessor(handle));
    }

    protected NumberProcessorProxy(NumberProcessorProxyHandle handle) {
        super(NumberProcessorProxyNative.asNumberProcessor(handle));
        this.handle = handle;
    }

    public static <T extends NumberProcessorProxy> T fromNumberProcessor(NumberProcessor number_processor, Class<T> clazz) {
        // the object registry is already in the JNI
        NumberProcessorProxyCallbacks obj = NumberProcessorProxyNative.fromNumberProcessor(number_processor.getHandle());
        if (clazz.isInstance(obj))
            return clazz.cast(obj);
        throw new ClassCastException("Object is not " + clazz.getName() + "!");
    }

    public abstract void process();

    @Override
    public void printNumber()
    {
        int status = NumberProcessorProxyNative.basePrintNumber(handle);
        StatusHelper.check(status);
    }

    @Override
    public void close() {
        handle.close();
        super.close();
    }
}
