#include <jni.h>

#include "../helpers/ref_helper.h"
#include "number_processor_internal.h"
#include "number_processor/number_processor_proxy.h"
#include "status_code.h"
#include "../mylib_binding_numberprocessor_NumberProcessorProxyNative.h"

static mylib_NumberProcessorProxy_t* get_handle(jlong handle)
{
    return (mylib_NumberProcessorProxy_t*)handle;
}

// JNIEXPORT jlong JNICALL Java_mylib_binding_numberprocessor_NumberProcessorProxyNative_nativeCreate
//   (JNIEnv *env, jclass clazz)
// {
//     (void)env;      // unused
//     (void)clazz;    // unused
//
//     mylib_NumberProcessorProxy_t* add2 = MyLib_NumberProcessorProxy_Create();
//     return (jlong)add2;
// }

JNIEXPORT jint JNICALL Java_mylib_binding_numberprocessor_NumberProcessorProxyNative_nativeDestroy
  (JNIEnv *env, jclass clazz, jlong handle)
{
    (void)env;      // unused
    (void)clazz;    // unused
    
    int status = MyLib_NumberProcessorProxy_Destroy(get_handle(handle));
    return (jint)status;
}

JNIEXPORT jlong JNICALL Java_mylib_binding_numberprocessor_NumberProcessorProxyNative_nativeAsNumberProcessor
  (JNIEnv *env, jclass clazz, jlong handle)
{
    (void)env;      // unused
    (void)clazz;    // unused

    mylib_NumberProcessor_t* np = MyLib_NumberProcessorProxy_As_NumberProcessor(get_handle(handle));
    return (jlong)np;
}

// JNIEXPORT jlong JNICALL Java_mylib_binding_numberprocessor_NumberProcessorProxyNative_nativeFromNumberProcessor
//   (JNIEnv *env, jclass clazz, jlong handle)
// {
//     (void)env;      // unused
//     (void)clazz;    // unused
//
//     mylib_NumberProcessorProxy_t* np = MyLib_NumberProcessorProxy_From_NumberProcessor(NumberProcessor_Internal_NumberProcessor_get_handle(handle));
//     return (jlong)np;
// }
