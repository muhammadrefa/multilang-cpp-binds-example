#include <jni.h>

#include "../helpers/ref_helper.h"
#include "number_processor_internal.h"
#include "number_processor/process_add2.h"
#include "status_code.h"
#include "../mylib_binding_numberprocessor_ProcessAdd2Native.h"

static mylib_ProcessAdd2_t* get_handle(jlong handle)
{
    return (mylib_ProcessAdd2_t*)handle;
}

JNIEXPORT jlong JNICALL Java_mylib_binding_numberprocessor_ProcessAdd2Native_nativeCreate
  (JNIEnv *env, jclass clazz)
{
    (void)env;      // unused
    (void)clazz;    // unused

    mylib_ProcessAdd2_t* add2 = MyLib_ProcessAdd2_Create();
    return (jlong)add2;
}

JNIEXPORT jint JNICALL Java_mylib_binding_numberprocessor_ProcessAdd2Native_nativeDestroy
  (JNIEnv *env, jclass clazz, jlong handle)
{
    (void)env;      // unused
    (void)clazz;    // unused
    
    int status = MyLib_ProcessAdd2_Destroy(get_handle(handle));
    return (jint)status;
}

JNIEXPORT jlong JNICALL Java_mylib_binding_numberprocessor_ProcessAdd2Native_nativeAsNumberProcessor
  (JNIEnv *env, jclass clazz, jlong handle)
{
    (void)env;      // unused
    (void)clazz;    // unused

    mylib_NumberProcessor_t* np = MyLib_ProcessAdd2_As_NumberProcessor(get_handle(handle));
    return (jlong)np;
}

JNIEXPORT jlong JNICALL Java_mylib_binding_numberprocessor_ProcessAdd2Native_nativeFromNumberProcessor
  (JNIEnv *env, jclass clazz, jlong handle)
{
    (void)env;      // unused
    (void)clazz;    // unused

    mylib_ProcessAdd2_t* np = MyLib_ProcessAdd2_From_NumberProcessor(NumberProcessor_Internal_NumberProcessor_get_handle(handle));
    return (jlong)np;
}
