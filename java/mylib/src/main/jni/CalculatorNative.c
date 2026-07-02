#include <jni.h>

#include "helpers/ref_helper.h"
#include "calculator.h"
#include "status_code.h"
#include "binding_CalculatorNative.h"

mylib_calculator_t* get_handle(jlong handle)
{
    return (mylib_calculator_t*)handle;
}

JNIEXPORT jlong JNICALL Java_binding_CalculatorNative_create(JNIEnv* env, jclass clazz)
{
    mylib_calculator_t* calc = MyLib_Calculator_Create();
    return (jlong)calc;
}

JNIEXPORT jint JNICALL Java_binding_CalculatorNative_destroy(JNIEnv* env, jclass clazz, jlong handle)
{
    return (jint)MyLib_Calculator_Destroy(get_handle(handle));
}

JNIEXPORT jint JNICALL Java_binding_CalculatorNative_add(JNIEnv* env, jclass clazz, jlong handle, jint a, jint b, jobject result)
{
    int c_result;
    mylib_status_t status = MyLib_Calculator_Add(get_handle(handle), a, b, &c_result);

    // // get the class
    // jclass ref_class = (*env)->GetObjectClass(env, result);
    // // find the field
    // jfieldID value_field = (*env)->GetFieldID(env, ref_class, "value", "I");
    // // store the result
    // (Env)->SetIntField(env, result, value_field, (jint)c_result);

    Helper_IntRef_Set(env, result, c_result);
    return (jint)status;
}

JNIEXPORT jint JNICALL Java_binding_CalculatorNative_sub(JNIEnv* env, jclass clazz, jlong handle, jint a, jint b, jobject result)
{
    int c_result;
    mylib_status_t status = MyLib_Calculator_Sub(get_handle(handle), a, b, &c_result);

    Helper_IntRef_Set(env, result, c_result);
    return (jint)status;
}

JNIEXPORT jint JNICALL Java_binding_CalculatorNative_cntOpsDone(JNIEnv* env, jclass clazz, jlong handle, jobject retval)
{
    int c_retval;
    mylib_status_t status = MyLib_Calculator_CntOpsDone(get_handle(handle), &c_retval);

    Helper_IntRef_Set(env, retval, c_retval);
    return (jint)status;
}

JNIEXPORT jint JNICALL Java_binding_CalculatorNative_resetCounter(JNIEnv* env, jclass clazz, jlong handle, jobject retval)
{
    int c_retval;
    mylib_status_t status = MyLib_Calculator_ResetCounter(get_handle(handle), &c_retval);

    Helper_IntRef_Set(env, retval, c_retval);
    return (jint)status;
}
