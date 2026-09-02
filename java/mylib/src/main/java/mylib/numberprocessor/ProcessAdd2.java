package mylib.numberprocessor;

import mylib.binding.numberprocessor.ProcessAdd2Native;
import mylib.binding.handles.numberprocessor.ProcessAdd2Handle;

public class ProcessAdd2 extends NumberProcessor {
    private volatile ProcessAdd2Handle handle;

    public ProcessAdd2() {
        this(createHandle());
    }

    protected ProcessAdd2(ProcessAdd2Handle handle) {
        super(ProcessAdd2Native.asNumberProcessor(handle));
        this.handle = handle;
    }

    private static ProcessAdd2Handle createHandle() {
        ProcessAdd2Handle handle = ProcessAdd2Native.create();
        if (handle.isNull())
            throw new RuntimeException("Cannot allocate new handle.");
        return handle;
    }

    public static ProcessAdd2 fromBase(NumberProcessor number_processor) {
        return new ProcessAdd2(ProcessAdd2Native.fromNumberProcessor(number_processor.getHandle()));
    }

    @Override
    public void close() {
        handle.close();
    }
}
