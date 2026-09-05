#ifndef JNI_NUMBERPROCESSORPROXYJNI_HPP
#define JNI_NUMBERPROCESSORPROXYJNI_HPP

#include <jni.h>

#include "number_processor_internal.h"
#include "number_processor/number_processor_proxy.h"
#include "status_code.h"
#include "../mylib_binding_numberprocessor_NumberProcessorProxyNative.h"


class NumberProcessorProxyJNI {
public:
    mylib_NumberProcessorProxy_t* handle;
    mylib_NumberProcessorProxy_cb_t* callbacks;      // has to live as long as the handle lives

    JavaVM* jvm;
    jobject java_instance;

    volatile bool is_java_ready = false;     // TRICK: Gates callbacks until the Java constructor completes!

    NumberProcessorProxyJNI(JNIEnv* env, jobject instance, mylib_NumberProcessorProxy_cb_t* cb);
    ~NumberProcessorProxyJNI();

    mylib_NumberProcessorProxy_t* get_handle() { return handle; }

    jmethodID func_process;
    void do_process();

    jmethodID func_print_number;
    void do_print_number();

private:
    template <typename Action>
    void executeWithJniEnv(Action action);
};


#endif //JNI_NUMBERPROCESSORPROXYJNI_HPP
