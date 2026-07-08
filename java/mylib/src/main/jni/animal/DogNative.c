#include <jni.h>

#include "../helpers/ref_helper.h"
#include "animal/animal.h"
#include "animal/dog.h"
#include "status_code.h"
#include "../mylib_binding_DogNative.h"

static mylib_dog_t* get_handle(jlong handle)
{
    return (mylib_dog_t*)handle;
}

JNIEXPORT jlong JNICALL Java_mylib_binding_DogNative_nativeCreate(JNIEnv* env, jclass clazz)
{
    (void)env;      // unused
    (void)clazz;    // unused
    
    mylib_dog_t* dog = MyLib_Dog_Create();
    return (jlong)dog;
}

JNIEXPORT jlong JNICALL Java_mylib_binding_DogNative_nativeCreateWithName(JNIEnv* env, jclass clazz, jobject name, jint length)
{
    (void)clazz;    // unused
    
    char* _name;
    int name_length = Helper_CharRef_Get(env, name, &_name);
    (void)name_length;  // unused

    mylib_dog_t* dog = MyLib_Dog_Create_With_Name(_name, length);
    Helper_CharRef_Release(env, name, _name);
    return (jlong)dog;
}

JNIEXPORT jint JNICALL Java_mylib_binding_DogNative_nativeDestroy(JNIEnv* env, jclass clazz, jlong handle)
{
    (void)env;      // unused
    (void)clazz;    // unused
    
    int status = MyLib_Dog_Destroy(get_handle(handle));
    return (jint)status;
}

JNIEXPORT jlong JNICALL Java_mylib_binding_DogNative_nativeAsAnimal(JNIEnv* env, jclass clazz, jlong handle)
{
    (void)env;      // unused
    (void)clazz;    // unused
    
    mylib_animal_t* animal = MyLib_Dog_As_Animal(get_handle(handle));
    return (jlong)animal;
}

JNIEXPORT jint JNICALL Java_mylib_binding_DogNative_nativeSpeak(JNIEnv* env, jclass clazz, jlong handle)
{
    (void)env;      // unused
    (void)clazz;    // unused
    
    int status = MyLib_Dog_Speak(get_handle(handle));
    return (jint)status;
}

JNIEXPORT jint JNICALL Java_mylib_binding_DogNative_nativeSleep(JNIEnv* env, jclass clazz, jlong handle)
{
    (void)env;      // unused
    (void)clazz;    // unused
    
    int status = MyLib_Dog_Sleep(get_handle(handle));
    return (jint)status;
}

JNIEXPORT jint JNICALL Java_mylib_binding_DogNative_nativeFetch(JNIEnv* env, jclass clazz, jlong handle, jobject success)
{
    (void)clazz;    // unused
    
    int c_success;
    int status = MyLib_Dog_Fetch(get_handle(handle), &c_success);
    Helper_IntRef_Set(env, success, c_success);
    return (jint)status;
}

JNIEXPORT jint JNICALL Java_mylib_binding_DogNative_nativeGetEnergy(JNIEnv* env, jclass clazz, jlong handle, jobject energy)
{
    (void)clazz;    // unused
    
    int c_energy;
    int status = MyLib_Dog_GetEnergy(get_handle(handle), &c_energy);
    Helper_IntRef_Set(env, energy, c_energy);
    return (jint)status;
}
