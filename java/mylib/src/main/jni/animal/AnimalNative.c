#include <jni.h>

#include "../helpers/ref_helper.h"
#include "animal/animal.h"
#include "status_code.h"
#include "../mylib_binding_AnimalNative.h"

static mylib_animal_t* get_handle(jlong handle)
{
    return (mylib_animal_t*)handle;
}

JNIEXPORT jlong JNICALL Java_mylib_binding_AnimalNative_nativeCreate(JNIEnv* env, jclass clazz)
{
    mylib_animal_t* animal = MyLib_Animal_Create();
    return (jlong)animal;
}

JNIEXPORT jlong JNICALL Java_mylib_binding_AnimalNative_nativeCreateWithName(JNIEnv* env, jclass clazz, jobject name, jint length)
{
    char* _name;
    int name_length = Helper_CharRef_Get(env, name, &_name);
    mylib_animal_t* animal = MyLib_Animal_Create_With_Name(_name, length);
    Helper_CharRef_Release(env, name, _name);
    return (jlong)animal;
}

JNIEXPORT jint JNICALL Java_mylib_binding_AnimalNative_nativeDestroy(JNIEnv* env, jclass clazz, jlong handle)
{
    int status = MyLib_Animal_Destroy(get_handle(handle));
    return (jint)status;
}

JNIEXPORT jint JNICALL Java_mylib_binding_AnimalNative_nativeSpeak(JNIEnv* env, jclass clazz, jlong handle)
{
    int status = MyLib_Animal_Speak(get_handle(handle));
    return (jint)status;
}

JNIEXPORT jint JNICALL Java_mylib_binding_AnimalNative_nativeSpeakMultipleTimes(JNIEnv* env, jclass clazz, jlong handle, jint times)
{
    int status = MyLib_Animal_Speak_Multiple_Times(get_handle(handle), times);
    return (jint)status;
}

JNIEXPORT jint JNICALL Java_mylib_binding_AnimalNative_nativeSleep(JNIEnv* env, jclass clazz, jlong handle)
{
    int status = MyLib_Animal_Sleep(get_handle(handle));
    return (jint)status;
}

JNIEXPORT jint JNICALL Java_mylib_binding_AnimalNative_nativeSetName(JNIEnv* env, jclass clazz, jlong handle, jobject name, jint length)
{
    char* c_name;
    int name_length = Helper_CharRef_Get(env, name, &c_name);
    int status = MyLib_Animal_Set_Name(get_handle(handle), c_name, length);
    Helper_CharRef_Release(env, name, c_name);
    return (jint)status;
}

JNIEXPORT jint JNICALL Java_mylib_binding_AnimalNative_nativeGetName(JNIEnv* env, jclass clazz, jlong handle, jobject name, jobject length)
{
    char* dest;
    int bufsize = Helper_CharRef_Get(env, name, &dest);
    int c_length;
    int status = MyLib_Animal_Get_Name(get_handle(handle), dest, bufsize, &c_length);
    Helper_IntRef_Set(env, length, c_length);
    Helper_CharRef_Release(env, name, dest);
    return (jint)status;
}
