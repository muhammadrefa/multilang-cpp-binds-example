package mylib.binding.numberprocessor;

import mylib.binding.Loader;
import mylib.binding.handles.numberprocessor.NumberProcessorHandle;
import mylib.binding.handles.numberprocessor.ProcessAdd2Handle;

public final class ProcessAdd2Native {

    static {
        Loader.load();
    }

    private ProcessAdd2Native() {
    }

    private static native long nativeCreate();
    public static ProcessAdd2Handle create()
    {
        return new ProcessAdd2Handle(nativeCreate(), ProcessAdd2Native::nativeDestroy);
    }
    
    private static native int nativeDestroy(long handle);
    public static int destroy(ProcessAdd2Handle handle)
    {
        return nativeDestroy(handle.value());
    }

    private static native long nativeAsNumberProcessor(long handle);
    public static NumberProcessorHandle asNumberProcessor(ProcessAdd2Handle handle)
    {
        return new NumberProcessorHandle(nativeAsNumberProcessor(handle.value()));
    }

    private static native long nativeFromNumberProcessor(long handle);
    public static ProcessAdd2Handle fromNumberProcessor(NumberProcessorHandle handle)
    {
        return new ProcessAdd2Handle(nativeFromNumberProcessor(handle.value()));
    }
}
