#pragma once

#include "status_code.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct mylib_circular_buffer mylib_circular_buffer_t;

mylib_circular_buffer_t* MyLib_CircularBuffer_Create(int bufsize);
mylib_status_t MyLib_CircularBuffer_Destroy(mylib_circular_buffer_t* handle);
mylib_status_t MyLib_CircularBuffer_GetLength(mylib_circular_buffer_t* handle, int* returned_length);
mylib_status_t MyLib_CircularBuffer_Put(mylib_circular_buffer_t* handle, char* data, int length, int* returned_length);
mylib_status_t MyLib_CircularBuffer_Get(mylib_circular_buffer_t* handle, char* dest, int length, int* returned_length);
mylib_status_t MyLib_CircularBuffer_Clean(mylib_circular_buffer_t* handle, int* returned_length);

#ifdef __cplusplus
}
#endif
