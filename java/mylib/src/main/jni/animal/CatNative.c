#include <jni.h>

#include "../helpers/ref_helper.h"
#include "animal/animal.h"
#include "animal/cat.h"
#include "status_code.h"
#include "../mylib_binding_CatNative.h"

static mylib_cat_t* get_handle(jlong handle)
{
    return (mylib_cat_t*)handle;
}

JNIEXPORT jlong JNICALL Java_mylib_binding_CatNative_nativeCreate(JNIEnv* env, jclass clazz)
{
    (void)env;      // unused
    (void)clazz;    // unused
    
    mylib_cat_t* cat = MyLib_Cat_Create();
    return (jlong)cat;
}

JNIEXPORT jlong JNICALL Java_mylib_binding_CatNative_nativeCreateWithName(JNIEnv* env, jclass clazz, jobject name, jint length)
{
    (void)clazz;    // unused
    
    char* _name;
    int name_length = Helper_CharRef_Get(env, name, &_name);
    (void)name_length;  // unused

    mylib_cat_t* cat = MyLib_Cat_Create_With_Name(_name, length);
    Helper_CharRef_Release(env, name, _name);
    return (jlong)cat;
}

JNIEXPORT jint JNICALL Java_mylib_binding_CatNative_nativeDestroy(JNIEnv* env, jclass clazz, jlong handle)
{
    (void)env;      // unused
    (void)clazz;    // unused
    
    int status = MyLib_Cat_Destroy(get_handle(handle));
    return (jint)status;
}

JNIEXPORT jlong JNICALL Java_mylib_binding_CatNative_nativeAsAnimal(JNIEnv* env, jclass clazz, jlong handle)
{
    (void)env;      // unused
    (void)clazz;    // unused
    
    mylib_animal_t* animal = MyLib_Cat_As_Animal(get_handle(handle));
    return (jlong)animal;
}

JNIEXPORT jint JNICALL Java_mylib_binding_CatNative_nativeSpeak(JNIEnv* env, jclass clazz, jlong handle)
{
    (void)env;      // unused
    (void)clazz;    // unused
    
    int status = MyLib_Cat_Speak(get_handle(handle));
    return (jint)status;
}

JNIEXPORT jint JNICALL Java_mylib_binding_CatNative_nativeFight(JNIEnv* env, jclass clazz, jlong handle, jint bigger_cat, jobject success)
{
    (void)clazz;    // unused
    
    int c_success;
    int status = MyLib_Cat_Fight(get_handle(handle), bigger_cat, &c_success);
    Helper_IntRef_Set(env, success, c_success);
    return (jint)status;
}

JNIEXPORT jint JNICALL Java_mylib_binding_CatNative_nativeStillAlive(JNIEnv* env, jclass clazz, jlong handle, jobject is_alive)
{
    (void)clazz;    // unused
    
    int c_is_alive;
    int status = MyLib_Cat_StillAlive(get_handle(handle), &c_is_alive);
    Helper_IntRef_Set(env, is_alive, c_is_alive);
    return (jint)status;
}
