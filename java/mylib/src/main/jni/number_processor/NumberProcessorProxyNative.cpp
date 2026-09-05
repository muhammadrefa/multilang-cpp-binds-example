#include <jni.h>
#include <stdlib.h>
#include <unordered_map>
#include <shared_mutex>
#include <mutex>

#include "number_processor/number_processor_proxy.h"
#include "status_code.h"
#include "NumberProcessorProxyJNI.hpp"
#include "../mylib_binding_numberprocessor_NumberProcessorProxyNative.h"

static std::unordered_map<mylib_NumberProcessorProxy_t*, NumberProcessorProxyJNI*> g_registry;
static std::shared_mutex g_registry_mutex;

static NumberProcessorProxyJNI* get_object(mylib_NumberProcessorProxy_t* handle)
{
    NumberProcessorProxyJNI* npp = nullptr;
    {
        std::shared_lock<std::shared_mutex> lock(g_registry_mutex);
        auto it = g_registry.find(handle);
        if (it != g_registry.end()) {
            npp = it->second;
        }
    }
    return npp;
}

static void jni_process_thunk(mylib_NumberProcessorProxy_t* handle)
{
    auto npp = get_object(handle);
    if (npp != nullptr)
        npp->do_process();
}

static void jni_print_number_thunk(mylib_NumberProcessorProxy_t* handle)
{
    auto npp = get_object(handle);
    if (npp != nullptr)
        npp->do_print_number();
}

extern "C" {
static mylib_NumberProcessorProxy_cb_t callback = {
    .cb_process = jni_process_thunk,
    .cb_print_number = jni_print_number_thunk
};

JNIEXPORT jlong JNICALL Java_mylib_binding_numberprocessor_NumberProcessorProxyNative_nativeCreate
  (JNIEnv *env, jclass clazz, jobject instance)
{
    (void)env;      // unused
    (void)clazz;    // unused

    // create the object
    NumberProcessorProxyJNI* npp_jni = new NumberProcessorProxyJNI(env, instance, &callback);

    // add to dictionary
    if (npp_jni->get_handle()) {
        // Write Lock & Register
        std::unique_lock<std::shared_mutex> lock(g_registry_mutex);
        g_registry[npp_jni->get_handle()] = npp_jni;
    }

    return (jlong)&npp_jni;
}

JNIEXPORT jint JNICALL Java_mylib_binding_numberprocessor_NumberProcessorProxyNative_nativeDestroy
  (JNIEnv *env, jclass clazz, jlong handle) {
    (void)env;      // unused
    (void)clazz;    // unused
    
    // int status = MyLib_NumberProcessorProxy_Destroy(get_handle(wrapper_handle));
    // if (status == MYLIB_STATUS_OK)
    //     free((struct JniNumberProcessorProxyWrapper*)wrapper_handle);

    NumberProcessorProxyJNI* npp = get_object((mylib_NumberProcessorProxy_t*)handle);
    if (npp)
    {
        {
            std::unique_lock<std::shared_mutex> lock(g_registry_mutex);
            g_registry.erase(npp->get_handle());

            free(npp);
            return (jint)MYLIB_STATUS_OK;
        }
    }
    return (jint)MYLIB_STATUS_UNKNOWN_ERROR;
}

JNIEXPORT jlong JNICALL Java_mylib_binding_numberprocessor_NumberProcessorProxyNative_nativeAsNumberProcessor
  (JNIEnv *env, jclass clazz, jlong handle)
{
    (void)env;      // unused
    (void)clazz;    // unused

    mylib_NumberProcessor_t* np = MyLib_NumberProcessorProxy_As_NumberProcessor((mylib_NumberProcessorProxy_t*)handle);
    return (jlong)np;
}

// JNIEXPORT jlong JNICALL Java_mylib_binding_numberprocessor_NumberProcessorProxyNative_nativeFromNumberProcessor
//   (JNIEnv *env, jclass clazz, jlong handle)
// {
//     (void)env;      // unused
//     (void)clazz;    // unused
//
//     auto npp = get_object((mylib_NumberProcessorProxy_t*)handle);
//
//     mylib_NumberProcessorProxy_t* np = MyLib_NumberProcessorProxy_From_NumberProcessor(NumberProcessor_Internal_NumberProcessor_get_handle(handle));
//
//     return (jlong)np;
// }

JNIEXPORT jint JNICALL Java_mylib_binding_numberprocessor_NumberProcessorProxyNative_nativeBasePrintNumber
  (JNIEnv *env, jclass clazz, jlong handle)
{
    (void)env;      // unused
    (void)clazz;    // unused

    int status = MyLib_NumberProcessorProxy_CallBase_PrintNumber((mylib_NumberProcessorProxy_t*)handle);
    return (jint)status;
}
}
