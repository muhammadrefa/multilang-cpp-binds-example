package mylib.numberprocessor;

import mylib.binding.handles.numberprocessor.NumberProcessorHandle;
import mylib.binding.handles.numberprocessor.NumberProcessorProxyHandle;
import mylib.binding.numberprocessor.NumberProcessorProxyNative;
import mylib.internal.StatusHelper;

public abstract class NumberProcessorProxy extends NumberProcessor {
    private final NumberProcessorProxyHandle handle;

    public NumberProcessorProxy() {
        super(new NumberProcessorHandle(0));
        this.handle = NumberProcessorProxyNative.create(this);
        if (handle.isNull())
            throw new RuntimeException("Cannot allocate new handle.");

        super.setHandle(NumberProcessorProxyNative.asNumberProcessor(handle));
    }

    protected NumberProcessorProxy(NumberProcessorProxyHandle handle) {
        super(NumberProcessorProxyNative.asNumberProcessor(handle));
        this.handle = handle;
    }

//    public static NumberProcessorProxy fromBase(NumberProcessor number_processor) {
//        return new NumberProcessorProxy(NumberProcessorProxyNative.fromNumberProcessor(number_processor.getHandle()));
//    }

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
    }
}
