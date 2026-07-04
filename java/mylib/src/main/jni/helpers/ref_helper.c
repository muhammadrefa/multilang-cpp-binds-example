#include <jni.h>

#include "ref_helper.h"

void Helper_IntRef_Set(JNIEnv* env, jobject intref_obj, int value)
{
    // get the class
    jclass ref_class = (*env)->GetObjectClass(env, intref_obj);
    // find the field
    jfieldID value_field = (*env)->GetFieldID(env, ref_class, "value", "I");
    // set the value
    (*env)->SetIntField(env, intref_obj, value_field, (jint)value);
}

int Helper_IntRef_Get(JNIEnv* env, jobject intref_obj)
{
    // get the class
    jclass ref_class = (*env)->GetObjectClass(env, intref_obj);
    // find the field
    jfieldID value_field = (*env)->GetFieldID(env, ref_class, "value", "I");
    // get the value
    jint value = (*env)->GetIntField(env, intref_obj, value_field);
    return (int)value;
}

// Is set needed?
/*
int Helper_CharRef_Set(JNIEnv* env, jobject charref_obj, char* data, int length)
{
    jclass ref_class = (*env)->GetObjectClass(env, charref_obj);
    jfieldID value_field = (*env)->GetFieldID(env, ref_class, "value", "[B");
    jbyteArray byte_arr = (jbyteArray)(*env)->GetObjectField(env, charref_obj, value_field);
    
    // get pointer to array and array length
    jbyte* arr = (*env)->GetByteArrayElements(env, byte_arr, NULL);
    jsize arr_len = GetArrayLength(env, byte_arr);

    // set the value using memcpy
    int _len = length < arr_len ? length : arr_len;    // only access what we can access
    memcpy(arr, data, _len);
    return _len;
}
*/

int Helper_CharRef_Get(JNIEnv* env, jobject charref_obj, char* dest)
{
    jclass ref_class = (*env)->GetObjectClass(env, charref_obj);
    jfieldID value_field = (*env)->GetFieldID(env, ref_class, "value", "[B");
    jbyteArray byte_arr = (jbyteArray)(*env)->GetObjectField(env, charref_obj, value_field);
    
    // get pointer to array and array length
    jbyte* arr = (*env)->GetByteArrayElements(env, byte_arr, NULL);
    jsize arr_len = GetArrayLength(env, byte_arr);

    // set the pointers
    dest = arr;
    return arr_len;
}
