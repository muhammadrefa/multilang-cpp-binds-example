#include <jni.h>

#include "helpers/ref_helper.h"
#include "circular_buffer.h"
#include "status_code.h"
#include "mylib_binding_CircularBufferNative.h"

static mylib_circular_buffer_t* get_handle(jlong handle)
{    
    return (mylib_circular_buffer_t*)handle;
}

JNIEXPORT jlong JNICALL Java_mylib_binding_CircularBufferNative_nativeCreate(JNIEnv* env, jclass clazz, jint bufsize)
{
    (void)env;      // unused
    (void)clazz;    // unused
    
    mylib_circular_buffer_t* calc = MyLib_CircularBuffer_Create(bufsize);
    return (jlong)calc;
}

JNIEXPORT jint JNICALL Java_mylib_binding_CircularBufferNative_nativeDestroy(JNIEnv* env, jclass clazz, jlong handle)
{
    (void)env;      // unused
    (void)clazz;    // unused
    
    return (jint)MyLib_CircularBuffer_Destroy(get_handle(handle));
}

JNIEXPORT jint JNICALL Java_mylib_binding_CircularBufferNative_nativeGetLength(JNIEnv* env, jclass clazz, jlong handle, jobject returned_length)
{
    (void)clazz;    // unused
    
    int c_returned_length;
    mylib_status_t status = MyLib_CircularBuffer_GetLength(get_handle(handle), &c_returned_length);
    
    Helper_IntRef_Set(env, returned_length, c_returned_length);
    return (jint)status;
}

JNIEXPORT jint JNICALL Java_mylib_binding_CircularBufferNative_nativePut(JNIEnv* env, jclass clazz, jlong handle, jobject data, jint length, jobject returned_length)
{
    (void)clazz;    // unused
    
    char* arr;
    int arr_len = Helper_CharRef_Get(env, data, &arr);
    (void)arr_len;  // unused
    
    int c_returned_length;
    mylib_status_t status = MyLib_CircularBuffer_Put(get_handle(handle), arr, length, &c_returned_length);

    Helper_IntRef_Set(env, returned_length, c_returned_length);
    Helper_CharRef_Release(env, data, arr);
    return (jint)status;
}

JNIEXPORT jint JNICALL Java_mylib_binding_CircularBufferNative_nativeGet(JNIEnv* env, jclass clazz, jlong handle, jobject dest, jint length, jobject returned_length)
{
    (void)clazz;    // unused
    
    char* arr;
    int arr_len = Helper_CharRef_Get(env, dest, &arr);
    (void)arr_len;  // unused
    
    int c_returned_length;
    mylib_status_t status = MyLib_CircularBuffer_Get(get_handle(handle), arr, length, &c_returned_length);

    Helper_IntRef_Set(env, returned_length, c_returned_length);
    Helper_CharRef_Release(env, dest, arr);
    return (jint)status;
}

JNIEXPORT jint JNICALL Java_mylib_binding_CircularBufferNative_nativeClean(JNIEnv* env, jclass clazz, jlong handle, jobject returned_length)
{
    (void)clazz;    // unused
    
    int c_returned_length;
    mylib_status_t status = MyLib_CircularBuffer_Clean(get_handle(handle), &c_returned_length);

    Helper_IntRef_Set(env, returned_length, c_returned_length);
    return (jint)status;
}
