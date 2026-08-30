#include <jni.h>

#include "../helpers/ref_helper.h"
#include "number_processor/number_processor.h"
#include "number_processor_internal.h"
#include "status_code.h"
#include "../mylib_binding_numberprocessor_NumberProcessorNative.h"

mylib_NumberProcessor_t* NumberProcessor_Internal_NumberProcessor_get_handle(jlong handle)
{
    return (mylib_NumberProcessor_t*)handle;
}

static mylib_NumberProcessor_t* get_handle(jlong handle)
{
    return NumberProcessor_Internal_NumberProcessor_get_handle(handle);
}

JNIEXPORT jint JNICALL Java_mylib_binding_numberprocessor_NumberProcessorNative_nativeDestroy
  (JNIEnv *env, jclass clazz, jlong handle)
{
    (void)env;      // unused
    (void)clazz;    // unused
    
    int status = MyLib_NumberProcessor_Destroy(get_handle(handle));
    return (jint)status;
}

JNIEXPORT jint JNICALL Java_mylib_binding_numberprocessor_NumberProcessorNative_nativeProcess
  (JNIEnv *env, jclass clazz, jlong handle)
{
    (void)env;      // unused
    (void)clazz;    // unused
    
    int status = MyLib_NumberProcessor_Process(get_handle(handle));
    return (jint)status;
}

JNIEXPORT jint JNICALL Java_mylib_binding_numberprocessor_NumberProcessorNative_nativeGetNumber
  (JNIEnv *env, jclass clazz, jlong handle, jobject number)
{
    (void)clazz;    // unused

    int c_number;
    int status = MyLib_NumberProcessor_GetNumber(get_handle(handle), &c_number);
    Helper_IntRef_Set(env, number, c_number);
    return (jint)status;
}

JNIEXPORT jint JNICALL Java_mylib_binding_numberprocessor_NumberProcessorNative_nativeSetNumber
  (JNIEnv *env, jclass clazz, jlong handle, jint number)
{
    (void)env;      // unused
    (void)clazz;    // unused
    
    int status = MyLib_NumberProcessor_SetNumber(get_handle(handle), number);
    return (jint)status;
}

JNIEXPORT jint JNICALL Java_mylib_binding_numberprocessor_NumberProcessorNative_nativePrintNumber
  (JNIEnv *env, jclass clazz, jlong handle)
{
    (void)env;      // unused
    (void)clazz;    // unused

    int status = MyLib_NumberProcessor_PrintNumber(get_handle(handle));
    return (jint)status;
}
