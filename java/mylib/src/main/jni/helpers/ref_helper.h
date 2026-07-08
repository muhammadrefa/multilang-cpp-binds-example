#include <jni.h>


void Helper_IntRef_Set(JNIEnv* env, jobject intref_obj, int value);
int Helper_IntRef_Get(JNIEnv* env, jobject intref_obj);

// int Helper_CharRef_Set(JNIEnv* env, jobject charref_obj, char* data, int length);
int Helper_CharRef_Get(JNIEnv* env, jobject charref_obj, char** dest);
void Helper_CharRef_Free(JNIEnv* env, jobject charref_obj, char* p_char);
