#include <cstdlib>

#include "../helpers/ref_helper.h"
#include "number_processor_internal.h"
#include "number_processor/number_processor_proxy.h"
#include "status_code.h"
#include "NumberProcessorProxyJNI.hpp"

NumberProcessorProxyJNI::NumberProcessorProxyJNI(JNIEnv *env, jobject instance, mylib_NumberProcessorProxy_cb_t* cb)
{
    callbacks = cb;

    // populate jni context
    env->GetJavaVM(&jvm);
    java_instance = env->NewGlobalRef(instance);

    // look up method id on actual runtime class
    jclass actual_class = env->GetObjectClass(instance);

    // get functions
    func_process = env->GetMethodID(actual_class, "process", "()V");
    func_print_number = env->GetMethodID(actual_class, "printNumber", "()V");

    // (Optional but) Good practice: free local refs when done
    env->DeleteLocalRef(actual_class);

    handle = MyLib_NumberProcessorProxy_Create(cb);
}

NumberProcessorProxyJNI::~NumberProcessorProxyJNI()
{
    if (MyLib_NumberProcessorProxy_Destroy(handle) == MYLIB_STATUS_OK)
        handle = nullptr;

    // delete java instance
    executeWithJniEnv([this](JNIEnv* env) {
        env->DeleteGlobalRef(this->java_instance);
    });
}

void NumberProcessorProxyJNI::do_process()
{
    executeWithJniEnv([this](JNIEnv* env) {
        env->CallVoidMethod(this->java_instance, this->func_process);
    });
}

void NumberProcessorProxyJNI::do_print_number()
{
    executeWithJniEnv([this](JNIEnv* env) {
        env->CallVoidMethod(this->java_instance, this->func_print_number);
    });
}

template<typename Action>
void NumberProcessorProxyJNI::executeWithJniEnv(Action action)
{
    if (!jvm) return;

    JNIEnv* env = nullptr;
    bool attached = false;

    // 1. Try to get the environment for the current thread
    jint res = jvm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6);

    if (res == JNI_EDETACHED) {
        // 2. Thread is not attached to the JVM (Background C thread). Attach it!
        res = jvm->AttachCurrentThread(reinterpret_cast<void**>(&env), nullptr);
        if (res != JNI_OK) {
            // Failed to attach (fatal JVM state), safely abort
            return;
        }
        attached = true;
    } else if (res != JNI_OK) {
        // JNI_EVERSION or other critical error
        return;
    }

    // 3. Execute the provided C++ lambda, passing the valid JNIEnv*
    if (env) {
        action(env);
    }

    // 4. Detach ONLY if we were the ones who attached this thread.
    // If Java called us (and we didn't attach), detaching here would crash the JVM!
    if (attached) {
        jvm->DetachCurrentThread();
    }
}
