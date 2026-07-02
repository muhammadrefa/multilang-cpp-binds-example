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
