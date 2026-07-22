#include <jni.h>

#include "../helpers/ref_helper.h"
#include "animal/cat.h"
#include "animal/tiger.h"
#include "status_code.h"
#include "../mylib_binding_TigerNative.h"

static mylib_tiger_t* get_handle(jlong handle)
{
    return (mylib_tiger_t*)handle;
}

JNIEXPORT jlong JNICALL Java_mylib_binding_TigerNative_nativeCreate(JNIEnv* env, jclass clazz)
{
    (void)env;      // unused
    (void)clazz;    // unused
    
    mylib_tiger_t* tiger = MyLib_Tiger_Create();
    return (jlong)tiger;
}

JNIEXPORT jlong JNICALL Java_mylib_binding_TigerNative_nativeCreateWithName(JNIEnv* env, jclass clazz, jobject name, jint length)
{
    (void)clazz;    // unused
    
    char* _name;
    int name_length = Helper_CharRef_Get(env, name, &_name);
    (void)name_length;  // unused

    mylib_tiger_t* tiger = MyLib_Tiger_Create_With_Name(_name, length);
    Helper_CharRef_Release(env, name, _name);
    return (jlong)tiger;
}

JNIEXPORT jint JNICALL Java_mylib_binding_TigerNative_nativeDestroy(JNIEnv* env, jclass clazz, jlong handle)
{
    (void)env;      // unused
    (void)clazz;    // unused
    
    int status = MyLib_Tiger_Destroy(get_handle(handle));
    return (jint)status;
}

JNIEXPORT jlong JNICALL Java_mylib_binding_TigerNative_nativeAsCat(JNIEnv* env, jclass clazz, jlong handle)
{
    (void)env;      // unused
    (void)clazz;    // unused
    
    mylib_cat_t* cat = MyLib_Tiger_As_Cat(get_handle(handle));
    return (jlong)cat;
}

JNIEXPORT jint JNICALL Java_mylib_binding_TigerNative_nativeHunt(JNIEnv* env, jclass clazz, jlong handle)
{
    (void)env;      // unused
    (void)clazz;    // unused
    
    int status = MyLib_Tiger_Hunt(get_handle(handle));
    return (jint)status;
}

JNIEXPORT jint JNICALL Java_mylib_binding_TigerNative_nativeGetHunger(JNIEnv* env, jclass clazz, jlong handle, jobject hunger)
{
    (void)clazz;    // unused
    
    int c_hunger;
    int status = MyLib_Tiger_GetHunger(get_handle(handle), &c_hunger);
    Helper_IntRef_Set(env, hunger, c_hunger);
    return (jint)status;
}
